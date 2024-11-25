// Fügen Sie dies zu Configuration.h hinzu, nach den bestehenden Definitionen:

// Arbeitsbereich-Konfiguration
#define WORK_AREA_OFFSET_FEATURE    // Ermöglicht Offset-Einstellung
#define SAVE_WORK_AREA_SETTINGS     // Speichert Einstellungen im EEPROM

// Z-Probe Offset Einstellungen
#define Z_PROBE_OFFSET_FROM_EXTRUDER -2  // Z-Offset von der Düse
#define PROBING_MARGIN 20                // Randabstand für Probing
#define Z_PROBE_CENTER_OFFSET_X 20       // X-Offset von der Düsenmitte
#define Z_PROBE_CENTER_OFFSET_Y 20       // Y-Offset von der Düsenmitte

// Neue Strukturen für die Arbeitsflächen-Einstellungen
struct WorkAreaSettings {
    float x_size;
    float y_size;
    float x_offset;
    float y_offset;
    float z_probe_x_offset;
    float z_probe_y_offset;
};

// EEPROM Adressen für die Einstellungen
#define EEPROM_WORK_AREA_SETTINGS    (EEPROM_OFFSET + 100)
#define EEPROM_WORK_AREA_MODE        (EEPROM_WORK_AREA_SETTINGS + sizeof(WorkAreaSettings))