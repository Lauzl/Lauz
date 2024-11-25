// Marlin/Marlin.h
#ifndef MARLIN_H
#define MARLIN_H

#include "Version.h"
#include "Configuration.h"
#include "Configuration_adv.h"

#include "src/core/boards.h"
#include "src/core/language.h"
#include "src/core/utility.h"
#include "src/core/serial.h"

#include "src/inc/Conditionals_LCD.h"
#include "src/inc/Conditionals_post.h"

#include "src/HAL/HAL.h"
#include "src/pins/pins.h"

// Grundlegende Typen und Konstanten
typedef float xyz_pos_t[XYZ];
typedef float xyze_pos_t[XYZE];
typedef int16_t xy_int_t[2];
typedef int16_t xyz_int_t[3];
typedef int16_t xyze_int_t[4];

// Globale Variablen
extern float current_position[XYZE];
extern float destination[XYZE];
extern bool axis_relative_modes[];
extern float feedrate_mm_s;
extern int16_t feedrate_percentage;

// DUAL MODE spezifische Definitionen
#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
  #include "src/feature/laser_offset.h"
  #include "src/lcd/menu/menu_laser.h"
  
  extern bool laser_mode_active;
  extern LaserOffset laser_offset;
  extern MenuLaser menu_laser;
#endif

// Funktionsdeklarationen
void setup();
void loop();

// Hardware-Steuerung
void safe_delay(millis_t ms);
void idle(bool no_stepper_sleep=false);
void kill(PGM_P const lcd_error=nullptr, PGM_P const lcd_component=nullptr, const bool steppers_off=false);
void quickstop_stepper();

// Bewegungssteuerung
void prepare_arc_move(bool clockwise);
void get_cartesian_from_steppers();
void set_current_from_steppers_for_axis(const AxisEnum axis);

// Temperatursteuerung
void disable_all_heaters();
void disable_e_steppers();
void zero_fan_speeds();

// LCD und UI
void lcd_init();
void lcd_update();
void lcd_setstatus(const char* message, const bool persist=false);
void lcd_reset_alert_level();
void lcd_reset_status();

// SD-Karte
void card_init();
void card_release();
void manage_media();
void print_job_timer_start();
void print_job_timer_stop();
void print_job_timer_increase();

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
  // Laser-Modus Funktionen
  void enable_laser_mode();
  void disable_laser_mode();
  bool is_laser_mode();
  void apply_laser_offsets();
  void handle_laser_mode();
#endif

#endif // MARLIN_H