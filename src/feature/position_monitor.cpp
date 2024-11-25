// src/feature/position_monitor.cpp
#include "position_monitor.h"
#include "../module/motion.h"
#include "../feature/mode_switch.h"
#include "../feature/work_area_handler.h"

float PositionMonitor::last_valid_x = 0;
float PositionMonitor::last_valid_y = 0;
float PositionMonitor::last_valid_z = 0;

void PositionMonitor::init() {
    last_valid_x = current_position[X_AXIS];
    last_valid_y = current_position[Y_AXIS];
    last_valid_z = current_position[Z_AXIS];
}

bool PositionMonitor::validate_move(float x, float y, float z) {
    if (mode_switch.get_current_mode() != ModeSwitch::MODE_LASER)
        return true;  // Im 3D-Drucker-Modus keine Einschränkung
        
    // Arbeitsbereich-Prüfung
    float adjusted_x = x - work_area_handler.get_offset_x();
    float adjusted_y = y - work_area_handler.get_offset_y();
    
    if (adjusted_x < 0 || adjusted_x > work_area_handler.get_size_x() ||
        adjusted_y < 0 || adjusted_y > work_area_handler.get_size_y())
        return false;
        
    return true;
}

bool PositionMonitor::is_within_work_area(float x, float y) {
    if (mode_switch.get_current_mode() != ModeSwitch::MODE_LASER)
        return true;
        
    float adjusted_x = x - work_area_handler.get_offset_x();
    float adjusted_y = y - work_area_handler.get_offset_y();
    
    return (adjusted_x >= 0 && adjusted_x <= work_area_handler.get_size_x() &&
            adjusted_y >= 0 && adjusted_y <= work_area_handler.get_size_y());
}

void PositionMonitor::apply_work_area_offset(float &x, float &y) {
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
        x += work_area_handler.get_offset_x();
        y += work_area_handler.get_offset_y();
    }
}

void PositionMonitor::get_real_position(float &x, float &y) {
    x = current_position[X_AXIS];
    y = current_position[Y_AXIS];
    
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
        x -= work_area_handler.get_offset_x();
        y -= work_area_handler.get_offset_y();
    }
}

void PositionMonitor::update_current_position() {
    if (validate_move(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS])) {
        last_valid_x = current_position[X_AXIS];
        last_valid_y = current_position[Y_AXIS];
        last_valid_z = current_position[Z_AXIS];
    } else {
        // Zurück zur letzten gültigen Position
        current_position[X_AXIS] = last_valid_x;
        current_position[Y_AXIS] = last_valid_y;
        current_position[Z_AXIS] = last_valid_z;
        sync_plan_position();
    }
}