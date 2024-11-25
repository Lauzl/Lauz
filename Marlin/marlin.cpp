// Marlin/Marlin.cpp
#include "Marlin.h"

#include "src/module/motion.h"
#include "src/module/planner.h"
#include "src/module/endstops.h"
#include "src/module/temperature.h"
#include "src/module/settings.h"
#include "src/module/printcounter.h"

#include "src/gcode/gcode.h"
#include "src/gcode/parser.h"
#include "src/gcode/queue.h"

#include "src/lcd/ultralcd.h"
#include "src/lcd/menu/menu.h"

#include "src/sd/cardreader.h"

// Globale Instanzen
MarlinSettings settings;
PrintCounter print_job_timer;
CardReader card;

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
  bool laser_mode_active = false;
  LaserOffset laser_offset;
  MenuLaser menu_laser;
#endif

// Setup Funktion
void setup() {
    // Serielle Kommunikation initialisieren
    MYSERIAL0.begin(BAUDRATE);
    SERIAL_ECHOPGM("Start\n");
    
    // Hardware initialisieren
    HAL_init();
    
    #if ENABLED(USE_WATCHDOG)
        watchdog_init();
    #endif
    
    // Speicher initialisieren
    settings.load();
    
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        // Laser-Offset laden
        laser_offset.init();
    #endif
    
    // Stepper initialisieren
    stepper.init();
    
    // Temperatursteuerung initialisieren
    thermalManager.init();
    
    // Endstops initialisieren
    endstops.init();
    
    // LCD initialisieren
    lcd_init();
    ui.init();
    ui.reset_status();
    
    // SD-Karte initialisieren
    card.init();
    
    SERIAL_ECHOLNPGM("Initialization complete.");
}

// Hauptschleife
void loop() {
    // Watchdog zurücksetzen
    #if ENABLED(USE_WATCHDOG)
        watchdog_reset();
    #endif
    
    // UI aktualisieren
    ui.update();
    
    // Befehle verarbeiten
    if (queue.length < BUFSIZE) get_available_commands();
    if (queue.length) process_next_command();
    
    // Endstops prüfen
    endstops.update();
    
    // Temperaturen verwalten
    thermalManager.manage_heater();
    
    // SD-Karte verarbeiten
    card.manage_media();
    
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        // Laser-Modus Verarbeitung
        if (laser_mode_active) {
            handle_laser_mode();
        }
    #endif
    
    // Inaktivität prüfen
    manage_inactivity(false);
}

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    void enable_laser_mode() {
        laser_mode_active = true;
        // Spezielle Konfiguration für Laser-Modus
        planner.settings.reset_acceleration();
        planner.settings.reset_max_feed_rate();
        ui.push_status_P(PSTR("Laser Mode Enabled"), 1000);
    }
    
    void disable_laser_mode() {
        laser_mode_active = false;
        // Zurück zu 3D-Drucker Konfiguration
        planner.settings.reset_acceleration();
        planner.settings.reset_max_feed_rate();
        ui.push_status_P(PSTR("3D Printer Mode Enabled"), 1000);
    }
    
    bool is_laser_mode() {
        return laser_mode_active;
    }
    
    void handle_laser_mode() {
        // Spezielle Laser-Modus Verarbeitung
        if (laser_mode_active && planner.movesplanned()) {
            float x = current_position[X_AXIS];
            float y = current_position[Y_AXIS];
            laser_offset.apply_offsets(x, y);
            
            // Status aktualisieren
            char buffer[32];
            sprintf_P(buffer, PSTR("X:%4.1f Y:%4.1f"), x, y);
            ui.set_status(buffer);
        }
    }
#endif

// Zusätzliche Hilfsfunktionen
void get_available_commands() {
    if (MYSERIAL0.available() > 0) {
        char c = MYSERIAL0.read();
        if (queue.length < BUFSIZE) queue.push(c);
    }
}

void process_next_command() {
    if (!queue.length) return;
    
    char* current = queue.pop();
    parser.parse(current);
    
    gcode.process_parsed_command();
}

void manage_inactivity(bool ignore_stepper_queue) {
    if (queue.length) return;
    
    // Stepper ausschalten nach Inaktivität
    if (stepper_inactive_time && !ignore_stepper_queue) {
        if (planner.has_blocks_queued())
            gcode.reset_stepper_timeout();
        else if (ELAPSED(millis(), gcode.previous_move_ms + stepper_inactive_time)) {
            disable_e_steppers();
            if (!axis_homed[X_AXIS] || !axis_homed[Y_AXIS] || !axis_homed[Z_AXIS])
                disable_all_steppers();
        }
    }
}