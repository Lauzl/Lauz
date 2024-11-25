// src/feature/eeprom_handler.cpp
#include "eeprom_handler.h"
#include "../module/configuration_store.h"

bool EEPROMHandler::save_mode_settings() {
    ModeSettings settings;
    
    // Aktuelle Einstellungen sammeln
    settings.current_mode = mode_switch.get_current_mode();
    settings.work_area = work_area_handler.get_settings();
    settings.validation_key = VALIDATION_KEY;
    
    // In EEPROM speichern
    persistentStore.write_data(
        EEPROM_MODE_SETTINGS,
        &settings,
        sizeof(ModeSettings)
    );
    
    return persistentStore.commit();
}

bool EEPROMHandler::load_mode_settings() {
    ModeSettings settings;
    
    // Aus EEPROM lesen
    if (persistentStore.read_data(
        EEPROM_MODE_SETTINGS,
        &settings,
        sizeof(ModeSettings)
    ) != sizeof(ModeSettings)) {
        reset_mode_settings();
        return false;
    }
    
    // Validierung prüfen
    if (settings.validation_key != VALIDATION_KEY) {
        reset_mode_settings();
        return false;
    }
    
    // Einstellungen anwenden
    mode_switch.set_mode((ModeSwitch::PrinterMode)settings.current_mode);
    work_area_handler.apply_settings(settings.work_area);
    
    return true;
}

void EEPROMHandler::reset_mode_settings() {
    // Standardeinstellungen
    ModeSettings settings;
    settings.current_mode = ModeSwitch::MODE_3D_PRINTER;
    settings.work_area = WorkAreaSettings{
        .x_size = X_BED_SIZE,
        .y_size = Y_BED_SIZE,
        .x_offset = 0,
        .y_offset = 0
    };
    settings.validation_key = VALIDATION_KEY;
    
    // In EEPROM speichern
    persistentStore.write_data(
        EEPROM_MODE_SETTINGS,
        &settings,
        sizeof(ModeSettings)
    );
    persistentStore.commit();
}

bool EEPROMHandler::is_data_valid() {
    uint32_t key;
    if (persistentStore.read_data(
        EEPROM_MODE_SETTINGS + offsetof(ModeSettings, validation_key),
        &key,
        sizeof(uint32_t)
    ) != sizeof(uint32_t)) {
        return false;
    }
    return key == VALIDATION_KEY;
}