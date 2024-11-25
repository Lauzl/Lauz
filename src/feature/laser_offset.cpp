// Marlin/src/feature/laser_offset.cpp
#include "laser_offset.h"
#include "../core/serial.h"
#include "../module/settings.h"
#include "../lcd/ultralcd.h"

// Statische Variablen initialisieren
float LaserOffset::x_offset = 0;
float LaserOffset::y_offset = 0;
bool LaserOffset::is_modified_ = false;

LaserOffset laser_offset;

void LaserOffset::init() {
    reset();
    load_offsets();
}

void LaserOffset::reset() {
    x_offset = 0;
    y_offset = 0;
    is_modified_ = true;
    save_offsets();
}

void LaserOffset::set_x_offset(const float x) {
    if (x_offset != x) {
        x_offset = x;
        is_modified_ = true;
        
        // Status Anzeige aktualisieren
        char buf[32];
        sprintf_P(buf, PSTR("X Offset: %4.2f"), x_offset);
        ui.set_status(buf);
    }
}

void LaserOffset::set_y_offset(const float y) {
    if (y_offset != y) {
        y_offset = y;
        is_modified_ = true;
        
        // Status Anzeige aktualisieren
        char buf[32];
        sprintf_P(buf, PSTR("Y Offset: %4.2f"), y_offset);
        ui.set_status(buf);
    }
}

void LaserOffset::save_offsets() {
    // Validierungsschlüssel speichern
    uint32_t valid = EEPROM_VALID;
    persistentStore.write_data(
        EEPROM_START,
        &valid,
        sizeof(valid)
    );
    
    // X-Offset speichern
    persistentStore.write_data(
        EEPROM_START + sizeof(uint32_t),
        &x_offset,
        sizeof(x_offset)
    );
    
    // Y-Offset speichern
    persistentStore.write_data(
        EEPROM_START + sizeof(uint32_t) + sizeof(float),
        &y_offset,
        sizeof(y_offset)
    );
    
    persistentStore.commit();
    is_modified_ = false;
    
    SERIAL_ECHOLNPAIR("Laser offsets saved - X:", x_offset, " Y:", y_offset);
}

void LaserOffset::load_offsets() {
    // Validierungsschlüssel prüfen
    uint32_t valid;
    persistentStore.read_data(EEPROM_START, &valid, sizeof(valid));
    
    if (valid != EEPROM_VALID) {
        SERIAL_ECHOLNPGM("No valid laser offsets found - using defaults");
        reset();
        return;
    }
    
    // X-Offset laden
    persistentStore.read_data(
        EEPROM_START + sizeof(uint32_t),
        &x_offset,
        sizeof(x_offset)
    );
    
    // Y-Offset laden
    persistentStore.read_data(
        EEPROM_START + sizeof(uint32_t) + sizeof(float),
        &y_offset,
        sizeof(y_offset)
    );
    
    SERIAL_ECHOLNPAIR("Laser offsets loaded - X:", x_offset, " Y:", y_offset);
    is_modified_ = false;
}

// Einfache Offset-Anwendung für Positionen
void apply_laser_offset(float &x, float &y) {
    x += laser_offset.get_x_offset();
    y += laser_offset.get_y_offset();
}

// Einfache Offset-Entfernung für Anzeigen
void remove_laser_offset(float &x, float &y) {
    x -= laser_offset.get_x_offset();
    y -= laser_offset.get_y_offset();
}