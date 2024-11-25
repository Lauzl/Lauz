// src/feature/position_monitor.h
#ifndef POSITION_MONITOR_H
#define POSITION_MONITOR_H

class PositionMonitor {
public:
    static void init();
    static bool validate_move(float x, float y, float z);
    static bool is_within_work_area(float x, float y);
    static void apply_work_area_offset(float &x, float &y);
    static void get_real_position(float &x, float &y);
    static void update_current_position();

private:
    static float last_valid_x;
    static float last_valid_y;
    static float last_valid_z;
};
