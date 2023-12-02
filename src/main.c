#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"
#include <unistd.h>
#include "pico/stdlib.h"
#include "code.h"

#define SLEEP_MS 1

Note notes[SIZE];
uint64_t note_index = 0;
uint8_t keycode[6] = {0};

void hid_task();
void init_note();
void set_note(Pitch, uint8_t);

void main_init()
{
    init_note();
    stdio_init_all();
    board_init();
    tusb_init();
}

int main()
{
    main_init();
    while(1)
    {
        tud_task();
        hid_task();
        sleep_ms(SLEEP_MS);
    }
    return 0;
}

void init_note()
{
    note_index = 0;

    set_note(C1, 4);
    set_note(C1, 4);
    set_note(C1, 4);

    set_note(B0, 4);
    set_note(D1, 4);
    set_note(E1, 4);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(E1, 8 + 8*2);
    set_note(E1, 16);
    set_note(D1, 8);
    set_note(B0, 8);
    set_note(A0, 8 + 8*2);
    set_note(G0, 16);
    set_note(A0, 8);
    set_note(B0, 8);
    set_note(G0, 4);
    set_note(E0, 8);
    set_note(G0, 8);
    set_note(A0, 4);
    set_note(A0, 8);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(B0, 8);
    set_note(A0, 8);
    set_note(G0, 8);

    set_note(A0, 4);
    set_note(A0, 8);
    set_note(G0, 8);
    set_note(B0, 4);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(E1, 4);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(E1, 4);
    set_note(E1, 8);
    set_note(B1, 8);
    set_note(A1, 8);
    set_note(B1, 8);
    set_note(A1, 8);
    set_note(G1, 8);
    set_note(E1, 4);
    set_note(G1, 8);
    set_note(A1, 8);
    set_note(A1, 16);
    set_note(G1, 16);
    set_note(A1, 8);
    set_note(A1, 16);
    set_note(G1, 16);
    set_note(A1, 8);
    set_note(A1, 16);
    set_note(G1, 16);
    set_note(A1, 8);
    set_note(A1, 16);
    set_note(G1, 16);
    set_note(E1, 8);
    set_note(G1, 8);
    set_note(E1, 8);
    set_note(D1, 8);
    set_note(E1, 4);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(E1, 4);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(E1, 8 + 8 * 2);
    set_note(E1, 16);
    set_note(D1, 8);
    set_note(B0, 8);
    set_note(A0, 8 + 8 * 2);
    set_note(G0, 16);
    set_note(A0, 8);
    set_note(B0, 8);
    set_note(G0, 4);
    set_note(E0, 8);
    set_note(G0, 8);
    set_note(A0, 4);
    set_note(A0, 8);
    set_note(B0, 8);
    set_note(D1, 8);
    set_note(B0, 8);
    set_note(A0, 8);
    set_note(G0, 8);

    note_index = 0;
}

void set_note(Pitch p, uint8_t l)
{
    notes[note_index].pitch = p;
    notes[note_index].length = l;
    note_index++;
}

Note get_note()
{
    Note _note;
    _note.pitch = notes[note_index].pitch;
    _note.length = notes[note_index].length;
    return _note;
}

uint64_t report_count = 0;

static void send_report(uint8_t report_id)
{
    if(!tud_hid_ready()) return;
    switch(report_id)
    {
        case REPORT_ID_KEYBOARD:
        {
            Note _note = {0, 4};
            if(report_count == 0)
            {
                _note = get_note();
                note_index++;
            }
            else
            {
                Pitch pitch = 0;
                _note = get_note();
                _note.pitch = pitch;
            }
            keycode[0] = _note.pitch;
            board_led_write(keycode[0]);
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            if(report_count++ >= 240 / (float) BPM / (float) _note.length * (float) 250)
            {
                report_count = 0;
            }
        }
        break;
        default:
        break;
    }
}

void hid_task()
{
    if(tud_suspended())
    {
        tud_remote_wakeup();
    }
    else
    {
        send_report(REPORT_ID_KEYBOARD);
    }
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    return 0;
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
    uint8_t next_report_id = report[0] + 1;

    if(next_report_id < REPORT_ID_COUNT)
    {
        send_report(next_report_id);
    }
}

