#pragma once

#include QMK_KEYBOARD_H

enum combos {
    JK_OPEN_PAREN,
    KL_CLOSE_PAREN,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

#define COMB_V2(name, val, ...) const uint16_t PROGMEM name ## _combo[] = {__VA_ARGS__, COMBO_END}; combo_t name = {.val = val, .keys = name ## _combo};

#include "combos.def" 