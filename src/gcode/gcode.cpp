/ Integration in den G-Code-Parser
// src/gcode/gcode.cpp

void GcodeSuite::process_parsed_command() {
    switch(parser.command_letter) {
        // ... bestehende Cases ...
        
        case 'M':
            switch (parser.codenum) {
                // ... bestehende M-Codes ...
                
                #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
                    case 600:
                        CustomGCodeHandler::process_M600();
                        break;
                    case 601:
                        CustomGCodeHandler::process_M601();
                        break;
                    case 602:
                        CustomGCodeHandler::process_M602();
                        break;
                #endif
            }
            break;
    }
}