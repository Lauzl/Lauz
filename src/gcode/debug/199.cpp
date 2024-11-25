// Debug-Befehl für Work Area Test
// src/gcode/debug/M199.cpp

void GcodeSuite::M199() {
    if (mode_switch.get_current_mode() != ModeSwitch::MODE_LASER) {
        SERIAL_ECHOLNPGM("Only available in laser mode");
        return;
    }
    
    // Test Work Area Bounds
    float x1 = work_area_handler.get_offset_x();
    float y1 = work_area_handler.get_offset_y();
    float x2 = x1 + work_area_handler.get_size_x();
    float y2 = y1 + work_area_handler.get_size_y();
    float z = current_position[Z_AXIS];
    
    // Move around work area bounds
    planner.synchronize();
    
    motion.move_to(x1, y1, z, 3000);
    planner.synchronize();
    SERIAL_ECHOLNPGM("Corner 1");
    
    motion.move_to(x2, y1, z, 3000);
    planner.synchronize();
    SERIAL_ECHOLNPGM("Corner 2");
    
    motion.move_to(x2, y2, z, 3000);
    planner.synchronize();
    SERIAL_ECHOLNPGM("Corner 3");
    
    motion.move_to(x1, y2, z, 3000);
    planner.synchronize();
    SERIAL_ECHOLNPGM("Corner 4");
    
    motion.move_to(x1, y1, z, 3000);
    planner.synchronize();
    SERIAL_ECHOLNPGM("Back to start");
}