// src/feature/work_area_handler.cpp


#include "work_area_handler.h"
#include "../module/motion.h"
#include "../module/probe.h"
#include "../lcd/ultralcd.h"
#include "../module/configuration_store.h"

WorkAreaSettings work_area = {
    .x_size = X_BED_SIZE,
    .y_size = Y_BED_SIZE,
    .x_offset = 0,
    .y_offset = 0,
    .z_probe_x_offset = Z_PROBE_CENTER_OFFSET_X,
    .z_probe_y_offset = Z_PROBE_CENTER_OFFSET_Y
};

void WorkAreaHandler::init() {
    load_settings();
}

void WorkAreaHandler::save_settings() {
    persistentStore.write_data(EEPROM_WORK_AREA_SETTINGS, &work_area, sizeof(work_area));
    persistentStore.write_data(EEPROM_WORK_AREA_MODE, &current_mode, sizeof(current_mode));
}

void WorkAreaHandler::load_settings() {
    if (persistentStore.read_data(EEPROM_WORK_AREA_SETTINGS, &work_area, sizeof(work_area)) != sizeof(work_area)) {
        // Standardwerte laden wenn keine gültigen Daten
        reset_settings();
    }
    persistentStore.read_data(EEPROM_WORK_AREA_MODE, &current_mode, sizeof(current_mode));
}

void WorkAreaHandler::reset_settings() {
    work_area.x_size = X_BED_SIZE;
    work_area.y_size = Y_BED_SIZE;
    work_area.x_offset = 0;
    work_area.y_offset = 0;
    work_area.z_probe_x_offset = Z_PROBE_CENTER_OFFSET_X;
    work_area.z_probe_y_offset = Z_PROBE_CENTER_OFFSET_Y;
}

void WorkAreaHandler::set_work_area_size(float x, float y) {
    work_area.x_size = constrain(x, 50, X_BED_SIZE);
    work_area.y_size = constrain(y, 50, Y_BED_SIZE);
    update_software_endstops();
}

void WorkAreaHandler::set_work_area_offset(float x, float y) {
    // Begrenzen der Offsets auf sinnvolle Werte
    work_area.x_offset = constrain(x, 0, X_BED_SIZE - work_area.x_size);
    work_area.y_offset = constrain(y, 0, Y_BED_SIZE - work_area.y_size);
    
    // Aktuelle Position an neue Offsets anpassen
    current_position[X_AXIS] += work_area.x_offset;
    current_position[Y_AXIS] += work_area.y_offset;
    sync_plan_position();
    
    update_software_endstops();
}

void WorkAreaHandler::set_probe_offset(float x, float y) {
    work_area.z_probe_x_offset = x;
    work_area.z_probe_y_offset = y;
    
    // Z-Probe Offsets aktualisieren
    probe.offset.x = x;
    probe.offset.y = y;
}

void WorkAreaHandler::update_software_endstops() {
    soft_endstop.min.x = work_area.x_offset;
    soft_endstop.min.y = work_area.y_offset;
    soft_endstop.max.x = work_area.x_offset + work_area.x_size;
    soft_endstop.max.y = work_area.y_offset + work_area.y_size;
}

// Menü-Handler für LCD
void WorkAreaHandler::menu_work_area_settings() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    
    MENU_ITEM_EDIT(float52, MSG_WORK_AREA_SIZE_X, &work_area.x_size, 50, X_BED_SIZE);
    MENU_ITEM_EDIT(float52, MSG_WORK_AREA_SIZE_Y, &work_area.y_size, 50, Y_BED_SIZE);
    MENU_ITEM_EDIT(float52, MSG_WORK_AREA_OFFSET_X, &work_area.x_offset, 0, X_BED_SIZE - work_area.x_size);
    MENU_ITEM_EDIT(float52, MSG_WORK_AREA_OFFSET_Y, &work_area.y_offset, 0, Y_BED_SIZE - work_area.y_size);
    
    MENU_ITEM_EDIT(float52, MSG_PROBE_OFFSET_X, &work_area.z_probe_x_offset, -50, 50);
    MENU_ITEM_EDIT(float52, MSG_PROBE_OFFSET_Y, &work_area.z_probe_y_offset, -50, 50);
    
    MENU_ITEM(function, MSG_STORE_SETTINGS, work_area_handler.save_settings);
    MENU_ITEM(function, MSG_RESET_SETTINGS, work_area_handler.reset_settings);
    
    END_MENU();
}

// G-Code Handler
void WorkAreaHandler::process_M860() {  // Custom G-Code für Arbeitsbereich
    if (parser.seen('S')) {  // Größe setzen
        if (parser.seen('X')) work_area.x_size = parser.value_float();
        if (parser.seen('Y')) work_area.y_size = parser.value_float();
        update_software_endstops();
    }
    else if (parser.seen('O')) {  // Offset setzen
        if (parser.seen('X')) work_area.x_offset = parser.value_float();
        if (parser.seen('Y')) work_area.y_offset = parser.value_float();
        update_software_endstops();
    }
    else if (parser.seen('P')) {  // Probe Offset setzen
        if (parser.seen('X')) work_area.z_probe_x_offset = parser.value_float();
        if (parser.seen('Y')) work_area.z_probe_y_offset = parser.value_float();
        set_probe_offset(work_area.z_probe_x_offset, work_area.z_probe_y_offset);
    }
    else {  // Status ausgeben
        SERIAL_ECHOPAIR("Work Area Size X: ", work_area.x_size);
        SERIAL_ECHOPAIR(" Y: ", work_area.y_size);
        SERIAL_EOL();
        SERIAL_ECHOPAIR("Work Area Offset X: ", work_area.x_offset);
        SERIAL_ECHOPAIR(" Y: ", work_area.y_offset);
        SERIAL_EOL();
        SERIAL_ECHOPAIR("Probe Offset X: ", work_area.z_probe_x_offset);
        SERIAL_ECHOPAIR(" Y: ", work_area.z_probe_y_offset);
        SERIAL_EOL();
    }
}