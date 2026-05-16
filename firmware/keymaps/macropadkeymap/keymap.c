#include QMK_KEYBOARD_H

enum layers
{
    _BASE,
};
enum custom_keycodes
{
    OPEN_GMAIL = SAFE_RANGE,
    OPEN_KICAD,
    OPEN_WORD,
    OPEN_YT,
    RGB_SWITCH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x3(
        OPEN_GMAIL, OPEN_YT, OPEN_WORD,
        KC_VOLD, KC_MPLY, KC_VOLU,
        LCTL(KC_C), LCTL(KC_V), RGB_SWITCH),
};

layer_state_t layer_state_set_user(layer_state_t state)
{

    switch (get_highest_layer(state))
    {
    case 0:
        rgblight_sethsv(HSV_BLUE);
        break;

    case 1:
        rgblight_sethsv(HSV_RED);
        break;

    case 2:
        rgblight_sethsv(HSV_GREEN);
        break;
    }
    return state;
}

char keylog_str[24] = "";

const char *keycode_to_string(uint16_t keycode)
{
    switch (keycode)
    {
    case OPEN_GMAIL:
        return "GMAIL";
    case OPEN_YT:
        return "YouTube";
    case OPEN_WORD:
        return "Word";
    case KC_VOLD:
        return "Vol -";
    case KC_VOLU:
        return "Vol +";
    case KC_MPLY:
        return "Play/Pause";
    case LCTL(KC_C):
        return "Copy";
    case LCTL(KC_V):
        return "Paste";
    case RGB_SWITCH:
        return "RGB";
    default:
        return "unknown";
    }
}

void set_keylog(uint16_t keycode, keyrecord_t *record)
{
    snprintf(keylog_str, sizeof(keylog_str),
             "KC:%s", keycode_to_string(keycode));
}

bool oled_task_user(void)
{
    oled_write_ln(keylog_str, false);
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        set_keylog(keycode, record);
    }

    switch (keycode)
    {

    case OPEN_GMAIL:
        if (record->event.pressed)
        {
            tap_code16(G(KC_R));
            wait_ms(200);
            SEND_STRING("chrome mail.google.com");
            tap_code(KC_ENTER);
        }
        return false;

    case OPEN_WORD:
        if (record->event.pressed)
        {
            // SEND_STRING(SS_LGUI("r"));
            tap_code16(G(KC_R));
            wait_ms(200);
            SEND_STRING("winword\n");
            tap_code(KC_ENTER);
        }
        return false;
    case RGB_SWITCH:
        rgblight_step();
        return false;
    case OPEN_YT:
        if (record->event.pressed)
        {
            tap_code16(G(KC_R));
            wait_ms(200);
            SEND_STRING("www.zoutube.com"); // z for german layout
            tap_code(KC_ENTER);
        }

        return false;
    }

    return true;
}
