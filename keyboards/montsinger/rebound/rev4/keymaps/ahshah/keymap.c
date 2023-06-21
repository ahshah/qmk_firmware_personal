#include QMK_KEYBOARD_H
#include "i2c_userspace.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_all(
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                               KC_Y,           KC_U,           KC_I,           KC_O,       KC_P,               KC_NO,
    LT(2,KC_ESC),   KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_PGUP,            KC_H,           KC_J,           KC_K,           KC_L,       KC_SCLN,            KC_QUOT,
    KC_LCTL,        LSFT_T(KC_Z),   KC_X,           KC_C,           KC_V,           KC_B,           KC_LGUI,            KC_N,           KC_M,           KC_COMM,        KC_DOT,     RSFT_T(KC_SLSH),    KC_RCTL,
    KC_LGUI,        KC_LALT,        KC_NO,          KC_SPC,         MO(1),          KC_NO,          KC_LGUI,            KC_ENT,         MO(1),          KC_BSPC,        KC_ENT,     KC_NO,              KC_SPC),

        [1] = LAYOUT_all(
    KC_NO,          KC_EXLM,     KC_AT,     KC_LCBR,    KC_RCBR,    KC_PIPE,                                  KC_ASTR,     KC_P7,   KC_P8,     KC_P9,     KC_BSLS,      KC_NO,
    KC_NO,          KC_HASH,     KC_DLR,    KC_LPRN,    KC_RPRN,    KC_GRV,               KC_NO,              KC_PLUS,     KC_P4,   KC_P5,     KC_P6,     KC_PMNS,      KC_UNDS,
    KC_NO,          KC_PERC,     KC_CIRC,   KC_LBRC,    KC_RBRC,    KC_TILD,              KC_NO,              KC_AMPR,     KC_P1,   KC_P2,     KC_P3,     KC_PEQL,      KC_NO,
    KC_NO,          KC_NO,       KC_NO,     KC_NO,      KC_TRNS,    KC_NO,                KC_NO,              KC_NO,       KC_DOT,  KC_P0,     KC_NO,     KC_NO,        KC_NO),

        [2] = LAYOUT_all(
    KC_F1,      KC_F2,   KC_F3,      KC_F4,      KC_F5,      KC_F6,                                  KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    KC_NO,      KC_MS_L, KC_MS_D,    KC_MS_U,    KC_MS_R,    KC_BTN1,            KC_NO,              KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      KC_NO,
    KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_NO,              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_NO,              KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO)
};

// This is live
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPC:
            return 300;
        default:
            return TAPPING_TERM;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_SPC):
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_SPC):
            return false;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SLSH):
            return false;
        default:
            return true;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SLSH):
            return false;
        default:
            return true;
    }
}

bool transmit = false;
bool i2c_userspace_task_user(void) {
    if (transmit) {
        uint8_t byte = 0x1;
        i2c_userspace_write(&byte, 1);
        transmit = false;
    }
    return true;
}

#define COMM_COPY LT(0, KC_COMM)
static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
    if (record->tap.count == 0) {  // Key is being held.
        if (record->event.pressed) {
            transmit = true;
        }
        return false;  // Skip default handling.
    }
    return true;  // Continue default handling.
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMM:  // Comma on tap, Ctrl+C on long press.
            return process_tap_or_long_press_key(record, C(KC_C));
        default:
            break;
    }
    return true;
}



