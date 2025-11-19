#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
  BASE,  // default layer
  QWRT,  // qwerty layout
  SYMB,  // symbols
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  CTRL_Q,
  CMD_Q,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_moonlander(
    LT(SYMB,KC_EQL),   KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_VOLD,                    KC_VOLU,      KC_6,    KC_7,      KC_8,    KC_9,     KC_0,              KC_BSLS,
    KC_TAB,            KC_QUOT,     KC_COMM,       KC_DOT,  KC_P,    KC_Y,    TG(QWRT),                   TG(SYMB),     KC_F,    KC_G,      KC_C,    KC_R,     KC_L,              KC_SLSH,
    CTRL_Q,            KC_A,        KC_O,          KC_E,    KC_U,    KC_I,    KC_CAPS_LOCK,               CW_TOGG,      KC_D,    KC_H,      KC_T,    KC_N,     KC_S,              KC_MINS,
    KC_LSFT,           KC_SCLN,     KC_Q,          KC_J,    KC_K,    KC_X,                                              KC_B,    KC_M,      KC_W,    KC_V,     ALT_T(KC_Z),       KC_RSFT,
                                                                     /* red key (L) */                                  /* red key (R) */
    KC_GRV,            CMD_Q,       KC_LALT,       MO(SYMB),KC_ENT,  KC_DEL,                                            KC_ESC,  KC_SPC,    MO(SYMB),KC_LBRC,  KC_RBRC,           KC_NO,
    // thumb cluster keys
    KC_SPC, KC_NO, CMD_Q,         KC_NO, MO(SYMB), KC_BSPC
  ),

  [QWRT] = LAYOUT_moonlander(
    _______,           _______,     _______,       _______, _______, _______, _______,                    _______,      _______,  _______,  _______, _______,  _______,           _______,
    _______,           KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    _______,                    _______,      KC_Y,     KC_U,     KC_I,    KC_O,     KC_P,              KC_BSLS,
    _______,           KC_A,        KC_S,          KC_D,    KC_F,    KC_G,    _______,                    _______,      KC_H,     KC_J,     KC_K,    KC_L,     KC_SCLN,           KC_QUOT,
    _______,           KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,                                              KC_N,     KC_M,     KC_COMM, KC_DOT,   KC_SLSH,           _______,
    _______,           _______,     _______,       _______, _______, _______,                                           _______,  _______,  _______, _______,  _______,           _______,
    // thumb cluster keys
    _______, _______, _______,         _______, _______, _______
  ),

  [SYMB] = LAYOUT_moonlander(
    _______,           KC_F1,       KC_F2,         KC_F3,   KC_F4,   KC_F5,   _______,                    _______,      KC_F6,    KC_F7,    KC_F8,   KC_F9,    KC_F10,            KC_F11,
    _______,           KC_EXLM,     KC_AT,         KC_LCBR, KC_RCBR, KC_PIPE, _______,                    _______,      _______,  KC_PGDN,  KC_PGUP, KC_HOME,  KC_END,            KC_F12,
    _______,           KC_HASH,     KC_DLR,        KC_LPRN, KC_RPRN, KC_GRV,  _______,                    _______,      KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, _______,           _______,
    _______,           KC_PERC,     KC_CIRC,       KC_LBRC, KC_RBRC, KC_TILD,                                           _______,  _______,  _______, _______,  _______,           _______,
                                                                     /* red key (L) */                                  /* red key (R) */
    _______,           _______,     _______,       _______, _______, QK_RBT,                                            _______,  _______,  _______, _______,  _______,           VRSN,
    // thumb cluster keys
    _______, _______, _______,         _______, _______, _______
  ),
};

static bool g_last_qwerty_state = false;

static bool handle_mod_q(uint16_t target_keycode, bool pressed) {
    if (pressed) {
        register_code(target_keycode);
        // Remember state of QWRT layer before key pressed
        g_last_qwerty_state = layer_state & (1<<QWRT);
        layer_on(QWRT);
    }
    else {
        if (!g_last_qwerty_state) {
            layer_off(QWRT);
        }
        unregister_code(target_keycode);
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
    }
  }

  switch (keycode) {
    case CTRL_Q:
      return handle_mod_q(KC_LCTL, record->event.pressed);
    case CMD_Q:
      return handle_mod_q(KC_LGUI, record->event.pressed);
  }

  return true;
}

// Runs whenever LED states change
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        STATUS_LED_1(true);
    } else {
        STATUS_LED_1(false);
    }

    return false;
}

// Runs whenever caps word is toggled
void caps_word_set_user(bool active) {
  if (active) {
    STATUS_LED_2(true);
  } else {
    STATUS_LED_2(false);
  }
}

// Configure RGB effects
void keyboard_post_init_user() {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv_noeeprom(0, 0, 0);  // HSV: 0 value = off
}

bool rgb_matrix_indicators_user() {
  if (IS_LAYER_ON(QWRT)) {
    // Top mid button on left side
    rgb_matrix_set_color(30, RGB_BLUE);
  }
  if (IS_LAYER_ON(SYMB)) {
    rgb_matrix_set_color(66, RGB_GREEN);
  }
  return true;
}

// Note: moonlander.c doesn't call layer_state_set_user when
// MOONLANDER_USER_LEDS is set (this is probably a bug)
// Thus we do this logic in housekeeping_task_user instead
//layer_state_t layer_state_set_user(layer_state_t layer_state) {
void housekeeping_task_user(void) {
  if (IS_LAYER_ON(QWRT)) {
    STATUS_LED_4(true);
  } else {
    STATUS_LED_4(false);
  }

  if (IS_LAYER_ON(SYMB)) {
    STATUS_LED_5(true);
  } else {
    STATUS_LED_5(false);
  }
};
