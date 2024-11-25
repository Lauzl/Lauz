// motion.cpp
// In der Funktion prepare_move_to_destination():

void prepare_move_to_destination() {
  #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
      // Arbeitsbereich-Prüfung für Laser-Modus
      if (!work_area_handler.validate_move(destination)) {
        SERIAL_ERROR_MSG("Move outside work area!");
        return;
      }
      
      // Laser-spezifische Bewegungsparameter
      const feedRate_t fr_mm_s = MMS_SCALED(feedrate_mm_s);
      if (laser_device.is_enabled() && fr_mm_s > 0.0f) {
        laser_device.set_power_for_speed(fr_mm_s);
      }
    }
  #endif

  // Bestehender Bewegungscode...
}