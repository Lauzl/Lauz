// Marlin/src/feature/laser_offset.h
#ifndef LASER_OFFSET_H
#define LASER_OFFSET_H

class LaserOffset {
public:
    // Konstruktor
    LaserOffset() : x_offset(0), y_offset(0), is_modified_(false) {}

    // Basisfunktionen
    static void init();
    static void reset();
    
    // Offset Funktionen
    static float get_x_offset() { return x_offset; }
    static float get_y_offset() { return y_offset; }
    static void set_x_offset(const float x);
    static void set_y_offset(const float y);
    
    // EEPROM Funktionen
    static void save_offsets();
    static void load_offsets();
    
    // Status Funktionen
    static bool is_modified() { return is_modified_; }
    static void clear_modified() { is_modified_ = false; }

private:
    static float x_offset;
    static float y_offset;
    static bool is_modified_;
    
    // EEPROM Adressen
    static const int EEPROM_START = 200;  // Startadresse im EEPROM
    static const uint32_t EEPROM_VALID = 0x4C4F4646;  // "LOFF" in ASCII
};

extern LaserOffset laser_offset;

#endif // LASER_OFFSET_H