#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VD KC__VOLDOWN
#define KC_VU KC__VOLUP

// layer
#define KC_L_SPC LT(_LOWER, KC_SPC)
#define KC_R_ENT LT(_RAISE, KC_ENT)

// shift_t
#define KC_S_TAB LSFT_T(KC_TAB)
#define KC_S_ESC LSFT_T(KC_ESC)
#define KC_S_JA LSFT_T(KC_LANG1)
#define KC_S_EN LSFT_T(KC_LANG2)

// cmd_t
#define KC_M_F LCMD_T(KC_F)
#define KC_M_D LCMD_T(KC_D)
#define KC_M_J LCMD_T(KC_J)
#define KC_M_K LCMD_T(KC_K)

// ctl_t
#define KC_C_S LCTL_T(KC_S)
#define KC_C_L LCTL_T(KC_L)
#define KC_C_BS LCTL_T(KC_BSPC)

// alt_t
#define KC_A_D ALT_T(KC_D)
#define KC_A_K ALT_T(KC_K)
#define KC_A_Z ALT_T(KC_Z)
#define KC_A_SL ALT_T(KC_SLSH)
#define KC_A_DEL ALT_T(KC_DEL)

// cmd+shift_t
#define KC_MS_Q SCMD_T(KC_Q)
#define KC_MS_A SCMD_T(KC_A)
#define KC_MS_S SCMD_T(KC_S)
#define KC_MS_SC SCMD_T(KC_SCLN)
#define KC_MS_ESC SCMD_T(KC_ESC)

//
#define KC_MR RCMD(KC_R)
#define KC_MF RCMD(KC_F)
#define KC_MW RCMD(KC_W)
#define KC_MX RCMD(KC_X)
#define KC_MC RCMD(KC_C)
#define KC_MV RCMD(KC_V)
#define KC_MTAB RCMD(KC_TAB)
#define KC_MSF RCMD(RSFT(KC_F))
#define KC_MSR RCMD(RSFT(KC_R))
#define KC_MST RCMD(RSFT(KC_T))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // M_ = LCMD_T(
  // A_ = ALT_T(
  // C_ = LCTL_T(
  // MS_ = SMD_T(
  // R_ = LT(_RAISE
  // L_ = LT(_LOWER

  [_QWERTY] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,       Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
    S_TAB, A  ,C_S , D  ,M_F , G  ,       H  ,M_J , K  ,C_L ,SCLN,S_ESC,
  //|----+----+----+----+----+----+     |----+----+----+----+----+----|
         , Z  , X  , C  , V  , B  ,       N  , M  ,COMM,DOT ,SLSH,    ,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
             A_DEL,S_EN,L_SPC,C_BS,      C_BS,R_ENT,S_JA,A_DEL
  //          `----+----+----+----'     `----+----+----+----'
  ),

  //   \ ^ ! & |  @ = + * % -
  // ( # $ " ' ~  ← ↓ ↑ → ` )
  //         { [  ] }

  [_RAISE] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         ,BSLS,CIRC,EXLM,AMPR,PIPE,      AT  ,EQL ,PLUS,ASTR,PERC,MINS,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
     LPRN,HASH,DLR ,DQT ,QUOT,TILD,      LEFT,DOWN, UP ,RGHT,GRV ,RPRN,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
        ,     ,    ,    ,LCBR,LBRC,      RBRC,RCBR,    ,    ,    ,    ,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
                   ,    ,BSPC,    ,          ,    ,    ,RST
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         ,    ,    ,MSF ,MSR ,MST ,          ,EQL ,PLUS,ASTR,PERC,MINS,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         , 1  , 2  , 3  , 4  , 5  ,       6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,          ,    ,COMM,DOT ,SLSH,    ,
  //`----+----+----+--+-+----+----/     \----+----+----+----+----+----'
               RST ,    ,    ,    ,          ,DEL ,    ,
  //          `----+----+----+----'     `----+----+----+----'
  ),
};

#ifdef OLED_DRIVER_ENABLE
#include "../../lib/layer_state_reader.c"
#include "../../lib/logo_reader.c"
#include "../../lib/keylogger.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_180;
  } else {
    return OLED_ROTATION_0;
  }
}

void oled_task_user(void) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif//OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}

