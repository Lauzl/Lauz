// Marlin/src/lcd/menu/menu_laser.cpp
#include "menu_laser.h"
#include "menu_item.h"
#include "menu.h"
#include "../../feature/laser_offset.h"
#include "../../module/motion.h"
#include "../../gcode/queue.h"

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)

MenuLaser menu_laser;

void MenuLaser::menu_laser_offset() {
    START_MENU();
    MENU_BACK(MSG_BACK);

    // X Offset Einstellung
    MENU_ITEM_EDIT_CALLBACK(float42_52, "X Offset", &laser_offset.get_x_offset(),
                           -100, 100, []{ laser_offset.set_x_offset(menuData.value); });

    // Y Offset Einstellung
    MENU_ITEM_EDIT_CALLBACK(float42_52, "Y Offset", &laser_offset.get_y_offset(),
                           -100, 100, []{ laser_offset.set_y_offset(menuData.value); });

    // Speichern
    MENU_ITEM(function, "Save Settings", []{ menu_laser.save_current_offsets(); });

    // Reset
    MENU_ITEM(function, "Reset Offsets", []{ menu_laser.reset_offsets(); });

    END_MENU();
}

void MenuLaser::menu_laser_main() {
    START_MENU();
    MENU_BACK(MSG_MAIN);

    // Hauptmenü für Lasermodus
    MENU_ITEM(submenu, "Move", menu_move);
    MENU_ITEM(gcode, "Set Zero", PSTR("G92 X0 Y0"));
    MENU_ITEM(submenu, "Offset Settings", menu_laser_offset);

    if (card.isMounted())
        MENU_ITEM(submenu, "Print from SD", menu_media);

    END_MENU();
}

void MenuLaser::draw_offset_screen() {
    ui.clear_lcd();
    ui.draw_edit_screen(LCD_STR_OFFSETS, ftostr52(laser_offset.get_x_offset()));
    lcd_moveto(0, 2);
    lcd_put_u8str("Y:");
    lcd_put_u8str(ftostr52(laser_offset.get_y_offset()));
}

void MenuLaser::update_offset_value(const float value, const bool is_x_axis) {
    if (is_x_axis)
        laser_offset.set_x_offset(value);
    else
        laser_offset.set_y_offset(value);
        
    draw_offset_screen();
}

void MenuLaser::save_current_offsets() {
    laser_offset.save_offsets();
    ui.push_status_P(PSTR("Offsets saved"), 1000);
}

void MenuLaser::reset_offsets() {
    laser_offset.reset();
    ui.push_status_P(PSTR("Offsets reset"), 1000);
    draw_offset_screen();
}

// Modifizierung des Hauptmenüs für den Moduswechsel
void menu_main() {
    START_MENU();

    // Modusauswahl
    MENU_ITEM_TOGGLE(
        ui.get_laser_mode(),
        "Mode",
        MSG_3D_PRINTER,
        MSG_LASER,
        []{ 
            ui.set_laser_mode(!ui.get_laser_mode());
            ui.push_status_P(ui.get_laser_mode() ? PSTR("Laser Mode") : PSTR("3D Printer Mode"), 1000);
        }
    );

    // Verzweigung basierend auf Modus
    if (ui.get_laser_mode()) {
        MENU_ITEM(submenu, MSG_LASER_MENU, menu_laser.menu_laser_main);
    }
    else {
        MENU_ITEM(submenu, MSG_PREPARE, menu_prepare);
        MENU_ITEM(submenu, MSG_CONTROL, menu_control);
    }

    END_MENU();
}

#endif // DUAL_MODE_PRINTER_AND_LASER