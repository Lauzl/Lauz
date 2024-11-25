// src/feature/status_handler.h
#ifndef STATUS_HANDLER_H
#define STATUS_HANDLER_H

class StatusHandler {
public:
    static void init();
    static void update_status();
    static void show_position();
    static void show_work_area();
    static void log_debug(const char* message);
    static void set_debug_level(uint8_t level);
    
    // Status-Flags
    static bool is_busy;
    static bool has_error;
    static char error_message[64];
    
private:
    static uint8_t debug_level;  // 0=Off, 1=Basic, 2=Verbose
    static void update_lcd_status();
    static void update_serial_status();
};