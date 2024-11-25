// Gcode.cpp
// In der process_parsed_command Funktion:

void GcodeSuite::process_parsed_command() {
  switch(parser.command_letter) {
    // Bestehende Cases...
    
    case 'M': switch (parser.codenum) {
      // Bestehende M-Codes...
      
      #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        case 860:  // Arbeitsbereich Konfiguration
          work_area_handler.process_M860();
          break;
          
        case 861:  // Moduswechsel
          if (parser.seen('S')) {
            const uint8_t new_mode = parser.value_byte();
            mode_switch.switch_mode(static_cast<ModeSwitch::PrinterMode>(new_mode));
          } else {
            SERIAL_ECHO_START();
            SERIAL_ECHOPAIR("Current Mode: ", mode_switch.get_current_mode());
            SERIAL_EOL();
          }
          break;
      #endif
      
      default: parser.unknown_command_error();
    }
    break;
    
    default: parser.unknown_command_error();
  }
}