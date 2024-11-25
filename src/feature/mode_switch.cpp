// src/feature/mode_switch.cpp
#include "mode_switch.h"
#include "../module/motion.h"
#include "../module/temperature.h"
#include "../lcd/ultralcd.h"
#include "../module/planner.h"

ModeSwitch::PrinterMode ModeSwitch::current_mode = MODE_3D_PRINTER;
bool ModeSwitch::mode_switching = false;
uint32_t ModeSwitch::mode_switch_start = 0;

void ModeSwitch::init() {
    // Lade gespeicherten Modus aus EEPROM
    load_mode_settings();
}

void ModeSwitch::switch_mode(PrinterMode new_mode) {
    if (new_mode == current_mode || mode_switching) return;

    // Prüfe ob Drucker bereit für Moduswechsel
    if (planner.has_blocks_queued() || thermalManager.still_heating()) {
        LCD_MESSAGEPGM("Cannot switch mode while printing/heating");
        return;
    }

    mode_switching = true;
    mode_switch_start = millis();
    
    LCD_MESSAGEPGM("Switching mode...");
    safe_mode_switch();
}

void ModeSwitch::process() {
    if (!mode_switching) return;

    if (millis() - mode_switch_start >= MODE_SWITCH_DELAY) {
        handle_mode_switch();
        mode_switching = false;
        
        // Speichere neuen Modus
        save_mode_settings();
    }
}

void ModeSwitch::safe_mode_switch() {
    // Sichere Abschaltung aller Systeme
    thermalManager.disable_all_heaters();
    stepper.disable_all_steppers();
    
    #if ENABLED(LASER_FEATURE)
        if (current_mode == MODE_LASER) {
            // Laser ausschalten
            laser_device.disable();
        }
    #endif
}

void ModeSwitch::handle_mode_switch() {
    if (current_mode == MODE_3D_PRINTER) {
        // Wechsel zu Laser-Modus
        current_mode = MODE_LASER;
        
        // Laser-spezifische Einstellungen
        #if ENABLED(LASER_FEATURE)
            laser_device.init();
            planner.settings.max_feedrate_mm_s[X_AXIS] = LASER_MAX_FEEDRATE_X;
            planner.settings.max_feedrate_mm_s[Y_AXIS] = LASER_MAX_FEEDRATE_Y;
            planner.settings.acceleration = LASER_ACCELERATION;
        #endif
        
        LCD_MESSAGEPGM("Laser Mode Active");
    }
    else {
        // Wechsel zu 3D-Drucker-Modus
        current_mode = MODE_3D_PRINTER;
        
        // 3D-Drucker-spezifische Einstellungen
        planner.settings.max_feedrate_mm_s[X_AXIS] = DEFAULT_MAX_FEEDRATE[X_AXIS];
        planner.settings.max_feedrate_mm_s[Y_AXIS] = DEFAULT_MAX_FEEDRATE[Y_AXIS];
        planner.settings.acceleration = DEFAULT_ACCELERATION;
        
        LCD_MESSAGEPGM("3D Printer Mode Active");
    }
    
    // Gemeinsame Aktionen nach Moduswechsel
    planner.reset_acceleration_rates();
    planner.refresh_positioning();
}

void ModeSwitch::save_mode_settings() {
    uint8_t mode = (uint8_t)current_mode;
    persistentStore.write_data(EEPROM_MODE_SETTINGS, &mode, sizeof(mode));
}

void ModeSwitch::load_mode_settings() {
    uint8_t mode;
    if (persistentStore.read_data(EEPROM_MODE_SETTINGS, &mode, sizeof(mode)) == sizeof(mode)) {
        current_mode = (PrinterMode)mode;
    } else {
        current_mode = MODE_3D_PRINTER; // Standard-Modus
    }
}