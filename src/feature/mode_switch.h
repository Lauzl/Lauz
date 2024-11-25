//src/feature/mode_switch.h

#ifndef MODE_SWITCH_H
#define MODE_SWITCH_H

class ModeSwitch {
public:
    enum PrinterMode {
        MODE_3D_PRINTER = 0,
        MODE_LASER = 1
    };

    static void init();
    static void switch_mode(PrinterMode new_mode);
    static PrinterMode get_current_mode() { return current_mode; }
    static bool is_switching() { return mode_switching; }
    static void process();
    static void save_mode_settings();
    static void load_mode_settings();

private:
    static PrinterMode current_mode;
    static bool mode_switching;
    static uint32_t mode_switch_start;
    static const uint32_t MODE_SWITCH_DELAY = 1000; // 1 Sekunde Verzögerung

    static void handle_mode_switch();
    static void safe_mode_switch();
};

extern ModeSwitch mode_switch;

#endif