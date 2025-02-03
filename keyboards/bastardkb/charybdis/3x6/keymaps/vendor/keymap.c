/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_GAME,
    LAYER_FN,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 2000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
// #define QEM ACTION_TAP_DANCE_DOUBLE(KC_SLSH, S(KC_1))
// tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_QEM] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, S(KC_1)),
// };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_LGUI,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  // ├──────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TAB,     KC_A,    KC_S, MT(MOD_LSFT,KC_D), MT(MOD_LCTL,KC_F), KC_G,    KC_H, MT(MOD_LCTL|MOD_RCTL,KC_J), MT(MOD_LSFT|MOD_RSFT,KC_K), LT(LAYER_POINTER,KC_L), KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TG(LAYER_FN), LT(LAYER_POINTER,KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  // ╰──────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                          LT(LAYER_LOWER,KC_ESC), KC_BSPC,  KC_SPC,             MO(LAYER_RAISE),  KC_ENT
  //                            ╰───────────────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       RGB_MOD, RGB_TOG, KC_MNXT, KC_MPLY, KC_MPRV, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, KC_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_MINS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,       KC_0,    KC_1,    KC_2,    KC_3, KC_PSLS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, XXXXXXX, XXXXXXX,    XXXXXXX, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    _______, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_TRNS, XXXXXXX, XXXXXXX, EE_CLR, QK_BOOT,    QK_BOOT, EE_CLR, XXXXXXX, XXXXXXX, KC_TRNS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1,    KC_MS_BTN3, KC_MS_BTN1
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_GAME] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TRNS,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TRNS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TG(LAYER_FN),      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_ESC,   KC_SPC,   KC_TAB,    KC_TRNS, KC_TRNS
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_FN] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_F7,     KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TG(LAYER_BASE),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_TRNS, KC_TRNS, KC_TRNS,    XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  )
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
          //   rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
          //   rgb_matrix_sethsv_noeeprom(HSV_GREEN);
          // rgb_matrix_set_color(19, 255, 0, 0);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
     //    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color_all(0, 0, 0);
    
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case LAYER_BASE:
        if (is_keyboard_left()) {
            rgb_matrix_set_color(4, RGB_PURPLE);
            rgb_matrix_set_color(7, RGB_PURPLE);
            rgb_matrix_set_color(10, RGB_PURPLE);
            rgb_matrix_set_color(13, RGB_PURPLE);
        }
            rgb_matrix_set_color(22, RGB_PURPLE);
            rgb_matrix_set_color(25, RGB_PURPLE);
            rgb_matrix_set_color(28, RGB_PURPLE);
            rgb_matrix_set_color(31, RGB_PURPLE);
            break;

        case LAYER_RAISE:
            break;
        case LAYER_LOWER:
            rgb_matrix_set_color(27, RGB_TEAL);
            rgb_matrix_set_color(28, RGB_TEAL);
            rgb_matrix_set_color(29, RGB_TEAL);
            rgb_matrix_set_color(30, RGB_TEAL);
            rgb_matrix_set_color(31, RGB_TEAL);
            rgb_matrix_set_color(32, RGB_TEAL);
            rgb_matrix_set_color(33, RGB_TEAL);
            rgb_matrix_set_color(34, RGB_TEAL);
            rgb_matrix_set_color(35, RGB_TEAL);
            rgb_matrix_set_color(38, RGB_TEAL);

            rgb_matrix_set_color(37, RGB_RED);
            rgb_matrix_set_color(25, RGB_RED);
            break;
        case LAYER_POINTER:
            rgb_matrix_set_color(25, RGB_GREEN);
            rgb_matrix_set_color(28, RGB_GREEN);
            rgb_matrix_set_color(31, RGB_GREEN);
            rgb_matrix_set_color(34, RGB_GREEN);
            break;
        case LAYER_FN:
        if (is_keyboard_left()) {
            rgb_matrix_set_color(0, RGB_YELLOW);
            rgb_matrix_set_color(1, RGB_YELLOW);
            rgb_matrix_set_color(3, RGB_YELLOW);
            rgb_matrix_set_color(4, RGB_YELLOW);
            rgb_matrix_set_color(6, RGB_YELLOW);
            rgb_matrix_set_color(7, RGB_YELLOW);
            rgb_matrix_set_color(9, RGB_YELLOW);
            rgb_matrix_set_color(10, RGB_YELLOW);
            rgb_matrix_set_color(12, RGB_YELLOW);
            rgb_matrix_set_color(13, RGB_YELLOW);
            rgb_matrix_set_color(15, RGB_YELLOW);
            rgb_matrix_set_color(16, RGB_YELLOW);
            rgb_matrix_set_color(18, RGB_YELLOW);
            rgb_matrix_set_color(19, RGB_YELLOW);

            rgb_matrix_set_color(2, RGB_TEAL);
        }
            break;
        case LAYER_GAME:
        if (is_keyboard_left()) {
            rgb_matrix_set_color(4, RGB_RED);
            rgb_matrix_set_color(6, RGB_RED);
            rgb_matrix_set_color(7, RGB_RED);
            rgb_matrix_set_color(10, RGB_RED);

            rgb_matrix_set_color(2, RGB_TEAL);
        }
            break;
    }
    return false;
}


