#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define QWRT 1 // qwerty
#define SYMB 2 // symbols

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
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  =/SYM |   1  |   2  |   3  |   4  |   5  |VolDn |           | VolUp|   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   P  |   Y  |  Qw  |           | Sym  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|------|           |      |------+------+------+------+------+--------|
 * | Ctl(Q) |   A  |   O  |   E  |   U  |   I  | Hyper|           |------|   D  |   H  |   T  |   N  |   S  |- or Cmd|
 * |--------+------+------+------+------+------|------'           | Caps |------+------+------+------+------+--------|
 * | LShift |  :/; |   Q  |   J  |   K  |   X  |                  |      |   B  |   M  |   W  |   V  |Z/Alt | RShift |
 * `--------+------+------+------+------+------'                  `-------------+------+------+------+------+--------'
 *   |Grv/Qw|Cmd(Q)| Alt  | Sym  | Enter|                                       |Space |  Sym |   [  |   ]  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |     Del     |       |     Esc     |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | PgUp |        |      |
 *                                 | Space|Enter | CmdQ |       |------|   Sym  | Bksp |
 *                                 |      |      |      |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT(
  // left hand
  LT(SYMB,KC_EQL),   KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_VOLD,
  KC_TAB,            KC_QUOT,     KC_COMM,       KC_DOT,  KC_P,    KC_Y,    TG(QWRT),
  CTRL_Q,            KC_A,        KC_O,          KC_E,    KC_U,    KC_I,
  KC_LSFT,           KC_SCLN,     KC_Q,          KC_J,    KC_K,    KC_X,    ALL_T(KC_NO),
  LT(QWRT,KC_GRV),   CMD_Q,       KC_LALT,       MO(SYMB),KC_ENT,
                                                                 KC_DEL,  KC_HOME,
                                                                          KC_END,
                                                         KC_SPC, KC_ENT,  CMD_Q,
  // right hand
  KC_VOLU,      KC_6,    KC_7,    KC_8,    KC_9,     KC_0,              KC_BSLS,
  TG(SYMB),     KC_F,    KC_G,    KC_C,    KC_R,     KC_L,              KC_SLSH,
                KC_D,    KC_H,    KC_T,    KC_N,     KC_S,              GUI_T(KC_MINS),
  KC_CAPS_LOCK, KC_B,    KC_M,    KC_W,    KC_V,     ALT_T(KC_Z),       KC_RSFT,
                         KC_SPC,  MO(SYMB), KC_LBRC,  KC_RBRC,           KC_TRNS,
  KC_ESC, KC_APP,
  KC_PGUP,
  KC_PGDN, MO(SYMB), KC_BSPC
),

/* Keymap 1: QWERTY keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
#define _MODIFIER
[QWRT] = LAYOUT(
        // left hand
        KC_TRNS,      KC_TRNS,       KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,
        KC_TRNS,      _MODIFIER(KC_Q),    _MODIFIER(KC_W),  _MODIFIER(KC_E), _MODIFIER(KC_R), _MODIFIER(KC_T),   KC_TRNS,
        KC_TRNS,      _MODIFIER(KC_A),    _MODIFIER(KC_S),  _MODIFIER(KC_D), _MODIFIER(KC_F), _MODIFIER(KC_G),
        KC_TRNS,      _MODIFIER(KC_Z),    _MODIFIER(KC_X),  _MODIFIER(KC_C), _MODIFIER(KC_V), _MODIFIER(KC_B),   KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,
                                                               KC_TRNS, KC_TRNS,
                                                                        KC_TRNS,
                                                      KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,       KC_TRNS,      KC_TRNS,       KC_TRNS,
             KC_TRNS, _MODIFIER(KC_Y), _MODIFIER(KC_U), _MODIFIER(KC_I),    _MODIFIER(KC_O),   _MODIFIER(KC_P),    _MODIFIER(KC_BSLS),
                      _MODIFIER(KC_H), _MODIFIER(KC_J), _MODIFIER(KC_K),    _MODIFIER(KC_L),   _MODIFIER(KC_SCLN), _MODIFIER(KC_QUOT),
             KC_TRNS, _MODIFIER(KC_N), _MODIFIER(KC_M), _MODIFIER(KC_COMM), _MODIFIER(KC_DOT), _MODIFIER(KC_SLSH), KC_TRNS,
                                  KC_TRNS,    KC_TRNS,       KC_TRNS,      KC_TRNS,       KC_TRNS,
             KC_TRNS, KC_TRNS,
             KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS
),
#undef _MODIFIER

/* Keymap 2: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Left | Down |  Up  |Right |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  | VRSN |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |  RST |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT(
  // left hand
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, QK_RBT,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
           KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_PLUS, KC_TRNS,
  KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                    KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  VRSN,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
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
      return handle_mod_q(KC_LCTL);
    case CMD_Q:
      return handle_mod_q(KC_LGUI);
  }

  return true;
}

// Runs whenever LED states change
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        ML_LED_1(true);
    } else {
        ML_LED_1(false);
    }

    return false;
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t layer_state) {
  if (layer_state & (1<<QWRT)) {
    ML_LED_4(true);
  } else {
    ML_LED_4(false);
  }

  if (layer_state & (1<<SYMB)) {
    ML_LED_5(true);
  } else {
    ML_LED_5(false);
  }

  return layer_state;
};
