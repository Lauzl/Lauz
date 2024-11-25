// src/lcd/menu/menu_modes.cpp

//=============================================================================
// Laser Modus Menüs - Vereinfachte Version
//=============================================================================

void menu_laser_control() {
  START_MENU();
  MENU_BACK(MSG_MAIN);

  // Grundlegende Bewegungssteuerung
  MENU_ITEM(submenu, "Move Laser", menu_move);
  MENU_ITEM(gcode, "Auto Home", PSTR("G28"));
  
  // Arbeitsflächen-Steuerung
  MENU_ITEM(submenu, "Set Work Area", menu_work_area);
  MENU_ITEM(function, "Set Work Origin", []{ 
    queue.inject_P(PSTR("G92 X0 Y0 Z0"));
    ui.return_to_status();
  });
  
  MENU_ITEM(gcode, "Disable Steppers", PSTR("M84"));
  
  END_MENU();
}

void menu_work_area() {
  START_MENU();
  MENU_BACK(MSG_LASER_CONTROL);

  float x_size = work_area_handler.get_current_size_x();
  float y_size = work_area_handler.get_current_size_y();
  float x_offset = work_area_handler.get_current_offset_x();
  float y_offset = work_area_handler.get_current_offset_y();

  MENU_ITEM_EDIT(float52, "Area Width", &x_size, 50, X_BED_SIZE);
  MENU_ITEM_EDIT(float52, "Area Height", &y_size, 50, Y_BED_SIZE);
  MENU_ITEM_EDIT(float52, "X Offset", &x_offset, 0, X_BED_SIZE - x_size);
  MENU_ITEM_EDIT(float52, "Y Offset", &y_offset, 0, Y_BED_SIZE - y_size);
  
  MENU_ITEM(function, "Apply Settings", []{ 
    work_area_handler.set_work_area_size(x_size, y_size);
    work_area_handler.set_work_area_offset(x_offset, y_offset);
    work_area_handler.save_settings();
    ui.return_to_status();
  });
  
  MENU_ITEM(function, "Reset Area", []{ 
    work_area_handler.reset_settings();
    ui.return_to_status();
  });
  
  END_MENU();
}

// Gemeinsames Bewegungsmenü
void menu_move() {
  START_MENU();
  MENU_BACK(MSG_CONTROL);

  if (mode_switch.get_current_mode() == ModeSwitch::MODE_3D_PRINTER) {
    MENU_ITEM(submenu, MSG_MOVE_E, menu_move_e);
  }
  
  MENU_ITEM(submenu, MSG_MOVE_X, menu_move_x);
  MENU_ITEM(submenu, MSG_MOVE_Y, menu_move_y);
  MENU_ITEM(submenu, MSG_MOVE_Z, menu_move_z);
  
  MENU_ITEM(function, MSG_AUTO_HOME, []{ queue.inject_P(PSTR("G28")); });
  
  END_MENU();
}