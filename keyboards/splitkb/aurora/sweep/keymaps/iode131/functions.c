
// COMBOS
const uint16_t PROGMEM combo0[] = { MT(MOD_RSFT, KC_N), MT(MOD_RGUI, KC_E), MT(MOD_RCTL, KC_I), MT(MOD_RALT, KC_O), COMBO_END};
const uint16_t PROGMEM combo1[] = { MT(MOD_LSFT, KC_T), MT(MOD_RSFT, KC_N), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ESCAPE),
    COMBO(combo1, KC_CAPSLOCK),
};
