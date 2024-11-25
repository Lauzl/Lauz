// src/feature/mode_switch.h
#ifndef MODE_SWITCH_H
#define MODE_SWITCH_H

class ModeSwitch {
public:
    enum PrinterMode {
        MODE_3D_PRINTER = 0,
        MODE_LASER = 1
    };

    static void init();
    static void handle_mode_switch();
    static PrinterMode get_current_mode() { return current_mode; }
    static void set_mode(PrinterMode mode);

private:
    static PrinterMode current_mode;
};
