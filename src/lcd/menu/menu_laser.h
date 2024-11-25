// Marlin/src/lcd/menu/menu_laser.h
#ifndef MENU_LASER_H
#define MENU_LASER_H

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)

class MenuLaser {
public:
    static void menu_laser_main();
    static void menu_laser_offset();
    
    // Hilfsfunktionen für das Menü
    static void draw_offset_screen();
    static void update_offset_value(const float value, const bool is_x_axis);
    static void save_current_offsets();
    static void reset_offsets();
};

extern MenuLaser menu_laser;

#endif // DUAL_MODE_PRINTER_AND_LASER
#endif // MENU_LASER_H