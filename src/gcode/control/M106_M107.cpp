// Marlin/src/gcode/control/M106_M107.cpp
// Dies ist die Implementierung der M106/M107 Befehle:

#include "../gcode.h"
#include "../../module/temperature.h"

void GcodeSuite::M106() {
    const uint8_t fan = 0; // Wir verwenden nur einen Fan/Laser
    uint8_t speed;

    if (parser.seen('S')) {
        speed = parser.value_byte();
    }
    else {
        speed = 255;
    }

    set_fan_speed(fan, speed);
}

void GcodeSuite::M107() {
    const uint8_t fan = 0;
    set_fan_speed(fan, 0);
}
