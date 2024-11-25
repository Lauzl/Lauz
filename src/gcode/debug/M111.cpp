// M-Code für Debug-Funktionen
// src/gcode/debug/M111.cpp

void GcodeSuite::M111() {
    if (parser.seen('S')) {
        StatusHandler::set_debug_level(parser.value_byte());
    
        SERIAL_ECHO_START();
        SERIAL_ECHOPAIR("Debug Level: ", parser.value_byte());
        SERIAL_EOL();
    }
}