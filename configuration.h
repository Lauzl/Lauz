// Configuration.h
// 
#define CONFIGURATION_H_VERSION 02010300

// Drucker Name
#define CUSTOM_MACHINE_NAME "LAUZ WORKSTATION"

// Drucker Informationen
#define STRING_CONFIG_H_AUTHOR "LAUZ" 
#define MACHINE_UUID "00000000-0000-0000-0000-000000000000"

//===========================================================================
//============================= Mechanische Einstellungen ====================
//===========================================================================

// Druckvolumen
#define X_BED_SIZE 400
#define Y_BED_SIZE 400
#define Z_MAX_POS 400

// Schritte pro mm
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 93 }

// Maximale Geschwindigkeit (mm/s)
#define DEFAULT_MAX_FEEDRATE          { 500, 500, 5, 25 }

// Maximale Beschleunigung (mm/s2)
#define DEFAULT_MAX_ACCELERATION      { 500, 500, 100, 1000 }

// Standard Beschleunigung
#define DEFAULT_ACCELERATION          500    // X, Y, Z and E acceleration
#define DEFAULT_RETRACT_ACCELERATION  1000   // E acceleration für Retracts
#define DEFAULT_TRAVEL_ACCELERATION   500    // X, Y, Z acceleration für Travel

//===========================================================================
//============================= Zusätzliche Funktionen =======================
//===========================================================================

// Dual Mode Konfiguration
#define DUAL_MODE_PRINTER_AND_LASER
#define LASER_PIN                  PA7  // Gleicher Pin wie FAN_PIN für Dual-Use

// Temperatur Limits
#define HEATER_0_MAXTEMP 275
#define BED_MAXTEMP 120

// Filament Sensor
#define FILAMENT_RUNOUT_SENSOR
#define FIL_RUNOUT_PIN PC0
#define FIL_RUNOUT_STATE LOW

// Display Konfiguration
#define LCD_INTERFACE_TYPE         RAMPS_INTERFACE
#define LCD_DISPLAY_TYPE           CUSTOM_LCD
#define LCD_WIDTH                  480
#define LCD_HEIGHT                 320

// Custom Boot Screen
#define SHOW_CUSTOM_BOOTSCREEN
#define CUSTOM_BOOTSCREEN_TIMEOUT  2000
#define CUSTOM_BOOTSCREEN_TEXT    "LAUZ WORKSTATION"

// Endstops
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG

#define X_MIN_ENDSTOP_INVERTING false
#define Y_MIN_ENDSTOP_INVERTING false
#define Z_MIN_ENDSTOP_INVERTING false

// Auto Bed Leveling
#define AUTO_BED_LEVELING_BILINEAR
#define GRID_MAX_POINTS_X 5
#define GRID_MAX_POINTS_Y 5
#define Z_PROBE_SPEED_FAST 10  // mm/s
#define Z_PROBE_SPEED_SLOW 2   // mm/s
#define PROBE_OFFSET_FEATURE

// Thermistor Einstellungen
#define TEMP_SENSOR_0 1  // 100k Thermistor
#define TEMP_SENSOR_BED 1  // 100k Thermistor

// PID Settings (Standard für Hotend)
#define DEFAULT_Kp 22.2
#define DEFAULT_Ki 1.08
#define DEFAULT_Kd 114

// PID Settings (Standard für Bett)
#define DEFAULT_bedKp 10.00
#define DEFAULT_bedKi .023
#define DEFAULT_bedKd 305.4

// Homing Speeds
#define HOMING_FEEDRATE_XY (50*60)
#define HOMING_FEEDRATE_Z  (4*60)

// SD Card Support
#define SDSUPPORT
#define SD_CHECK_AND_RETRY

//===========================================================================
//============================= Laser Mode Settings ==========================
//===========================================================================

#ifdef DUAL_MODE_PRINTER_AND_LASER
  #define LASER_FEATURE
  #define SPINDLE_LASER_ACTIVE_HIGH    // TRUE wenn Laser bei HIGH aktiv
  #define SPINDLE_LASER_PWM            // PWM Steuerung für Laser
  #define SPEED_POWER_STARTUP   50     // Defaultwert beim Start (0-255)
  #define SPEED_POWER_MIN       0      // Minimale Power (0-255)
  #define SPEED_POWER_MAX      255     // Maximale Power (0-255)
  #define LASER_SAFETY_TIMEOUT_MS 5000 // Timeout für Laser
#endif

//===========================================================================
//============================= UI Anpassungen ==============================
//===========================================================================

// Custom Menü Einträge
#define CUSTOM_MENU_MAIN
#define CUSTOM_MENU_ITEMS_MAIN \
  MENU_ITEM(submenu, "3D PRINTER", printer_menu); \
  MENU_ITEM(submenu, "LASER", laser_menu);

// Printer Mode Menü
#define CUSTOM_MENU_PRINTER \
  MENU_ITEM(submenu, "PRINT", print_menu); \
  MENU_ITEM(submenu, "CONTROL", control_menu); \
  MENU_ITEM(submenu, "SETTINGS", settings_menu); \
  MENU_ITEM(submenu, "INFO", info_menu);

// Laser Mode Menü
#define CUSTOM_MENU_LASER \
  MENU_ITEM(submenu, "LASER CONTROL", laser_control_menu); \
  MENU_ITEM(submenu, "LASER SETTINGS", laser_settings_menu);

//===========================================================================
//============================= Emergency Parser Settings ====================
//===========================================================================

#define EMERGENCY_PARSER
#define HOST_KEEPALIVE_FEATURE
#define DEFAULT_KEEPALIVE_INTERVAL 2