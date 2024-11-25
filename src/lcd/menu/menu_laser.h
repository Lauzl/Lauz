// Marlin/src/lcd/menu/menu_laser.h
#pragma once

#include "../../inc/MarlinConfig.h"

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)

class MenuLaser {
public:
    static void init();
    
    // Hauptmenüs
    static void menu_laser_main();        // Hauptmenü für Laser-Modus
    static void menu_laser_offset();      // Offset-Einstellungsmenü
    
    // Status-Funktionen
    static bool is_laser_mode();
    static void set_laser_mode(bool mode);
    
    // Hilfsfunktionen
    static void draw_status_line();
    static void update_status();
    
private:
    static bool laser_mode;               // Aktueller Modus-Status
    static uint16_t last_update;          // Zeitpunkt des letzten Updates
    
    // Private Hilfsfunktionen
    static void save_current_offsets();
    static void reset_offsets();
    static void update_offset_value(const float value, const bool is_x_axis);
};

extern MenuLaser menu_laser;

// Menüpunktdeklarationen
void menu_main();                         // Hauptmenü
void menu_move();                         // Bewegungsmenü
void menu_prepare();                      // Vorbereitungsmenü
void menu_control();                      // Kontrollmenü
void menu_media();                        // SD-Karten Menü

// Spezielle Laser-Menüs
void laser_control_menu();
void laser_settings_menu();

#endif // DUAL_MODE_PRINTER_AND_LASER