
#include QMK_KEYBOARD_H

enum custom_keycodes {
    ST_MACRO_0 = SAFE_RANGE,
    ST_MACRO_1,
    ST_MACRO_2,
};

enum tap_dance_codes {
    DANCE_0,
    DANCE_1,
    DANCE_2,
    DANCE_3,
    DANCE_4,
    DANCE_5,
    DANCE_6,
    DANCE_7,
    DANCE_8,
    DANCE_9,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, MT(MOD_LALT, KC_A), MT(MOD_LCTL, KC_R), MT(MOD_LGUI, KC_S), MT(MOD_LSFT, KC_T), KC_G, KC_M, MT(MOD_RSFT, KC_N), MT(MOD_RGUI, KC_E), MT(MOD_RCTL, KC_I), MT(MOD_RALT, KC_O), KC_Z, LT(3, KC_X), LT(2, KC_C), KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, MO(1), MT(MOD_HYPR, KC_SPC), KC_ESCAPE, MO(2)),
    [1] = LAYOUT(KC_TRNS, KC_RCBR, KC_RPRN, KC_RBRC, KC_TILD, TO(4), KC_COLN, KC_EQUAL, KC_PLUS, KC_ASTR, TD(DANCE_0), TD(DANCE_1), TD(DANCE_2), MT(MOD_LSFT, KC_LBRC), KC_PIPE, KC_ASTR, MT(MOD_RSFT, KC_MINS), TD(DANCE_3), TD(DANCE_4), TD(DANCE_5), KC_PERC, KC_DQUO, KC_QUOT, KC_TRNS, KC_GRV, KC_AMPR, KC_EXLM, KC_CIRC, KC_DLR, KC_BSLS, KC_TRNS, KC_ENT, KC_ENT, KC_BSPC),
    [2] = LAYOUT(KC_TRNS, KC_TRNS, ST_MACRO_1, ST_MACRO_2, KC_TRNS, KC_TRNS, KC_HOME, KC_UP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_STOP, LSFT(KC_5), KC_AUDIO_MUTE, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_TRNS, KC_PGDN, KC_CIRC, KC_DEL, KC_DLR, KC_TRNS, KC_DEL, KC_TAB, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, MT(MOD_LALT, KC_F6), MT(MOD_LCTL, KC_F7), MT(MOD_LGUI, KC_F8), MT(MOD_LSFT, KC_F9), KC_F10, KC_KP_DOT, MT(MOD_RSFT, KC_4), MT(MOD_RGUI, KC_5), MT(MOD_RCTL, KC_6), MT(MOD_RALT, KC_TRNS), KC_F11, KC_F12, KC_F13, KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_TRNS, RGB_RMOD, KC_TRNS, KC_TRNS, KC_TRNS),
    [4] = LAYOUT(LGUI(KC_1), TD(DANCE_6), LGUI(KC_7), LGUI(KC_0), KC_I, KC_S, KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT, KC_RIGHT, TD(DANCE_7), TD(DANCE_8), KC_U, KC_TRANSPARENT, KC_TRANSPARENT, KC_R, KC_C, KC_NO, LSFT(KC_LEFT), LSFT(KC_RIGHT), KC_O, KC_P, KC_D, KC_MINUS, KC_PLUS, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_E, TD(DANCE_9), KC_TRANSPARENT, TO(0)),
};
const uint16_t PROGMEM combo0[] = {MT(MOD_RSFT, KC_N), MT(MOD_RGUI, KC_E), MT(MOD_RCTL, KC_I), MT(MOD_RALT, KC_O), COMBO_END};
const uint16_t PROGMEM combo1[] = {MT(MOD_LSFT, KC_T), MT(MOD_RSFT, KC_N), COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_Q, KC_SCLN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ESCAPE),
    COMBO(combo1, KC_CAPS_LOCK),
    COMBO(combo2, ST_MACRO_0),
};

typedef struct {
    bool    is_press_action;
    uint8_t step;
} tap;

enum { SINGLE_TAP = 1, SINGLE_HOLD, DOUBLE_TAP, DOUBLE_HOLD, DOUBLE_SINGLE_TAP, MORE_TAPS };

static tap dance_state[10];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_AT);
        tap_code16(KC_AT);
        tap_code16(KC_AT);
    }
    if (state->count > 3) {
        tap_code16(KC_AT);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP:
            register_code16(KC_AT);
            break;
        case SINGLE_HOLD:
            register_code16(KC_LALT);
            break;
        case DOUBLE_TAP:
            register_code16(KC_AT);
            register_code16(KC_AT);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_AT);
            register_code16(KC_AT);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP:
            unregister_code16(KC_AT);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_LALT);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_AT);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_AT);
            break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_LCBR);
        tap_code16(KC_LCBR);
        tap_code16(KC_LCBR);
    }
    if (state->count > 3) {
        tap_code16(KC_LCBR);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP:
            register_code16(KC_LCBR);
            break;
        case SINGLE_HOLD:
            register_code16(KC_LGUI);
            break;
        case DOUBLE_TAP:
            register_code16(KC_LCBR);
            register_code16(KC_LCBR);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_LCBR);
            register_code16(KC_LCBR);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_LGUI);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LCBR);
            break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_LPRN);
        tap_code16(KC_LPRN);
        tap_code16(KC_LPRN);
    }
    if (state->count > 3) {
        tap_code16(KC_LPRN);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case SINGLE_HOLD:
            register_code16(KC_LSFT);
            break;
        case DOUBLE_TAP:
            register_code16(KC_LPRN);
            register_code16(KC_LPRN);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_LPRN);
            register_code16(KC_LPRN);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_LSFT);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_UNDS);
        tap_code16(KC_UNDS);
        tap_code16(KC_UNDS);
    }
    if (state->count > 3) {
        tap_code16(KC_UNDS);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP:
            register_code16(KC_UNDS);
            break;
        case SINGLE_HOLD:
            register_code16(KC_RGUI);
            break;
        case DOUBLE_TAP:
            register_code16(KC_UNDS);
            register_code16(KC_UNDS);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_UNDS);
            register_code16(KC_UNDS);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP:
            unregister_code16(KC_UNDS);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_RGUI);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_UNDS);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_UNDS);
            break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_QUES);
        tap_code16(KC_QUES);
        tap_code16(KC_QUES);
    }
    if (state->count > 3) {
        tap_code16(KC_QUES);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP:
            register_code16(KC_QUES);
            break;
        case SINGLE_HOLD:
            register_code16(KC_RCTL);
            break;
        case DOUBLE_TAP:
            register_code16(KC_QUES);
            register_code16(KC_QUES);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_QUES);
            register_code16(KC_QUES);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP:
            unregister_code16(KC_QUES);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_RCTL);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_QUES);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_QUES);
            break;
    }
    dance_state[4].step = 0;
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_HASH);
        tap_code16(KC_HASH);
        tap_code16(KC_HASH);
    }
    if (state->count > 3) {
        tap_code16(KC_HASH);
    }
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP:
            register_code16(KC_HASH);
            break;
        case SINGLE_HOLD:
            register_code16(KC_RALT);
            break;
        case DOUBLE_TAP:
            register_code16(KC_HASH);
            register_code16(KC_HASH);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_HASH);
            register_code16(KC_HASH);
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP:
            unregister_code16(KC_HASH);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_RALT);
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_HASH);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_HASH);
            break;
    }
    dance_state[5].step = 0;
}
void on_dance_6(tap_dance_state_t *state, void *user_data);
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void on_dance_6(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(LGUI(KC_2));
        tap_code16(LGUI(KC_2));
        tap_code16(LGUI(KC_2));
    }
    if (state->count > 3) {
        tap_code16(LGUI(KC_2));
    }
}

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP:
            register_code16(LGUI(KC_2));
            break;
        case DOUBLE_TAP:
            register_code16(LGUI(KC_4));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(LGUI(KC_2));
            register_code16(LGUI(KC_2));
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP:
            unregister_code16(LGUI(KC_2));
            break;
        case DOUBLE_TAP:
            unregister_code16(LGUI(KC_4));
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LGUI(KC_2));
            break;
    }
    dance_state[6].step = 0;
}
void on_dance_7(tap_dance_state_t *state, void *user_data);
void dance_7_finished(tap_dance_state_t *state, void *user_data);
void dance_7_reset(tap_dance_state_t *state, void *user_data);

void on_dance_7(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(LGUI(KC_LEFT));
        tap_code16(LGUI(KC_LEFT));
        tap_code16(LGUI(KC_LEFT));
    }
    if (state->count > 3) {
        tap_code16(LGUI(KC_LEFT));
    }
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP:
            register_code16(LGUI(KC_LEFT));
            break;
        case SINGLE_HOLD:
            register_code16(LGUI(KC_G));
            break;
        case DOUBLE_TAP:
            register_code16(LGUI(KC_LEFT));
            register_code16(LGUI(KC_LEFT));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(LGUI(KC_LEFT));
            register_code16(LGUI(KC_LEFT));
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP:
            unregister_code16(LGUI(KC_LEFT));
            break;
        case SINGLE_HOLD:
            unregister_code16(LGUI(KC_G));
            break;
        case DOUBLE_TAP:
            unregister_code16(LGUI(KC_LEFT));
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LGUI(KC_LEFT));
            break;
    }
    dance_state[7].step = 0;
}
void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

void on_dance_8(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(LGUI(KC_RIGHT));
        tap_code16(LGUI(KC_RIGHT));
        tap_code16(LGUI(KC_RIGHT));
    }
    if (state->count > 3) {
        tap_code16(LGUI(KC_RIGHT));
    }
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[8].step = dance_step(state);
    switch (dance_state[8].step) {
        case SINGLE_TAP:
            register_code16(LGUI(KC_RIGHT));
            break;
        case SINGLE_HOLD:
            register_code16(LGUI(KC_F));
            break;
        case DOUBLE_TAP:
            register_code16(LGUI(KC_RIGHT));
            register_code16(LGUI(KC_RIGHT));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(LGUI(KC_RIGHT));
            register_code16(LGUI(KC_RIGHT));
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[8].step) {
        case SINGLE_TAP:
            unregister_code16(LGUI(KC_RIGHT));
            break;
        case SINGLE_HOLD:
            unregister_code16(LGUI(KC_F));
            break;
        case DOUBLE_TAP:
            unregister_code16(LGUI(KC_RIGHT));
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LGUI(KC_RIGHT));
            break;
    }
    dance_state[8].step = 0;
}
void on_dance_9(tap_dance_state_t *state, void *user_data);
void dance_9_finished(tap_dance_state_t *state, void *user_data);
void dance_9_reset(tap_dance_state_t *state, void *user_data);

void on_dance_9(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
    }
    if (state->count > 3) {
        tap_code16(KC_SPACE);
    }
}

void dance_9_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[9].step = dance_step(state);
    switch (dance_state[9].step) {
        case SINGLE_TAP:
            register_code16(KC_SPACE);
            break;
        case DOUBLE_TAP:
            register_code16(LSFT(KC_SPACE));
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code16(KC_SPACE);
            register_code16(KC_SPACE);
    }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[9].step) {
        case SINGLE_TAP:
            unregister_code16(KC_SPACE);
            break;
        case DOUBLE_TAP:
            unregister_code16(LSFT(KC_SPACE));
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SPACE);
            break;
    }
    dance_state[9].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset), [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset), [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset), [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset), [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset), [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset), [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset), [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset), [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset), [DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_9, dance_9_finished, dance_9_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ST_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_1) SS_DELAY(100) SS_TAP(X_5) SS_DELAY(100) SS_TAP(X_2) SS_DELAY(100) SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_ENTER));
            }
            break;
        case ST_MACRO_1:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LBRC) SS_DELAY(100) SS_TAP(X_M));
            }
            break;
        case ST_MACRO_2:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RBRC) SS_DELAY(100) SS_TAP(X_M));
            }
            break;
    }
    return true;
}
