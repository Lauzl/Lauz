// src/feature/status_handler.cpp
#include "status_handler.h"
#include "../lcd/ultralcd.h"
#include "../module/motion.h"
#include "../feature/mode_switch.h"
#include "../feature/work_area_handler.h"

bool StatusHandler::is_busy = false;
bool StatusHandler::has_error = false;
char StatusHandler::error_message[64] = "";
uint8_t StatusHandler::debug_level = 1;

void StatusHandler::init() {
    is_busy = false;
    has_error = false;
    error_message[0] = '\0';
}

void StatusHandler::update_status() {
    update_lcd_status();
    if (debug_level > 0) {
        update_serial_status();
    }
}

void StatusHandler::update_lcd_status() {
    // Aktuelle Position
    float x, y, z;
    PositionMonitor::get_real_position(x, y);
    z = current_position[Z_AXIS];
    
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
        // Laser-Modus Status
        char buffer[32];
        
        // Erste Zeile: Modus und Position
        lcd_moveto(0, 0);
        sprintf(buffer, "Laser X%3d Y%3d Z%3d", (int)x, (int)y, (int)z);
        lcd_put_u8str(buffer);
        
        // Zweite Zeile: Arbeitsbereich
        lcd_moveto(0, 1);
        sprintf(buffer, "Area %3dx%3d", 
            (int)work_area_handler.get_size_x(),
            (int)work_area_handler.get_size_y());
        lcd_put_u8str(buffer);
        
        // Dritte Zeile: Offset
        lcd_moveto(0, 2);
        sprintf(buffer, "Offs X%3d Y%3d", 
            (int)work_area_handler.get_offset_x(),
            (int)work_area_handler.get_offset_y());
        lcd_put_u8str(buffer);
        
        // Vierte Zeile: Status/Fehler
        lcd_moveto(0, 3);
        if (has_error) {
            lcd_put_u8str(error_message);
        } else if (is_busy) {
            lcd_put_u8str("BUSY");
        } else {
            lcd_put_u8str("READY");
        }
    }
}

void StatusHandler::update_serial_status() {
    if (debug_level >= 2) {
        show_position();
        show_work_area();
    }
}

void StatusHandler::show_position() {
    float x, y, z;
    PositionMonitor::get_real_position(x, y);
    z = current_position[Z_AXIS];
    
    SERIAL_ECHOPGM("Position - ");
    SERIAL_ECHOPAIR(" X:", x);
    SERIAL_ECHOPAIR(" Y:", y);
    SERIAL_ECHOLNPAIR(" Z:", z);
}

void StatusHandler::show_work_area() {
    SERIAL_ECHOPGM("Work Area - ");
    SERIAL_ECHOPAIR(" Size X:", work_area_handler.get_size_x());
    SERIAL_ECHOPAIR(" Y:", work_area_handler.get_size_y());
    SERIAL_ECHOPAIR(" Offset X:", work_area_handler.get_offset_x());
    SERIAL_ECHOLNPAIR(" Y:", work_area_handler.get_offset_y());
}

void StatusHandler::log_debug(const char* message) {
    if (debug_level > 0) {
        SERIAL_ECHO_START();
        SERIAL_ECHOPGM("DEBUG: ");
        SERIAL_ECHOLN(message);
    }
}

void StatusHandler::set_debug_level(uint8_t level) {
    debug_level = min(level, (uint8_t)2);
}
