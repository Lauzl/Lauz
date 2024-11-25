// Debug Menü Integration
// src/lcd/menu/menu_debug.cpp

void menu_debug() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    
    MENU_ITEM(function, "Show Position", []{ StatusHandler::show_position(); });
    MENU_ITEM(function, "Show Work Area", []{ StatusHandler::show_work_area(); });
    
    MENU_ITEM_EDIT(uint8, "Debug Level", &debug_level, 0, 2);
    
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
        MENU_ITEM(function, "Work Area Bounds", []{ 
            float x1 = work_area_handler.get_offset_x();
            float y1 = work_area_handler.get_offset_y();
            float x2 = x1 + work_area_handler.get_size_x();
            float y2 = y1 + work_area_handler.get_size_y();
            
            // Move around work area bounds
            motion.move_to(x1, y1, current_position[Z_AXIS], 3000);
            motion.move_to(x2, y1, current_position[Z_AXIS], 3000);
            motion.move_to(x2, y2, current_position[Z_AXIS], 3000);
            motion.move_to(x1, y2, current_position[Z_AXIS], 3000);
            motion.move_to(x1, y1, current_position[Z_AXIS], 3000);
        });
    }
    
    END_MENU();
}