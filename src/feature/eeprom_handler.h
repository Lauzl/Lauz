// src/feature/eeprom_handler.h
#ifndef EEPROM_HANDLER_H
#define EEPROM_HANDLER_H

#include "../Configuration.h"

struct ModeSettings {
    uint8_t current_mode;            // 0 = 3D Drucker, 1 = Laser
    WorkAreaSettings work_area;
    uint32_t validation_key;         // Zur Prüfung der EEPROM-Daten
};

class EEPROMHandler {
public:
    static bool save_mode_settings();
    static bool load_mode_settings();
    static void reset_mode_settings();
    static bool is_data_valid();
    
private:
    static const uint32_t VALIDATION_KEY = 0xA55A3D3D;  // Validierungsschlüssel
};