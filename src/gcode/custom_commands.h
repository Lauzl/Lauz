// src/gcode/custom_commands.h
#ifndef CUSTOM_GCODE_COMMANDS_H
#define CUSTOM_GCODE_COMMANDS_H

class CustomGCodeHandler {
public:
    static void process_M600();  // Moduswechsel
    static void process_M601();  // Arbeitsbereich einstellen
    static void process_M602();  // Arbeitsbereich-Offset einstellen
};