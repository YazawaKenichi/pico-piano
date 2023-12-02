#ifndef __CODE_H__
#define __CODE_H__

#include "usb_descriptors.h"

#define SIZE 128

//! 曲の設定
#define BPM 78

typedef enum
{
    C0 = HID_KEY_Z,
    D0 = HID_KEY_X,
    E0 = HID_KEY_C,
    F0 = HID_KEY_V,
    G0 = HID_KEY_B,
    A0 = HID_KEY_N,
    B0 = HID_KEY_M,
    C1 = HID_KEY_A,
    D1 = HID_KEY_S,
    E1 = HID_KEY_D,
    F1 = HID_KEY_F,
    G1 = HID_KEY_G,
    A1 = HID_KEY_H,
    B1 = HID_KEY_J,
    C2 = HID_KEY_Q,
    D2 = HID_KEY_W,
    E2 = HID_KEY_E,
    F2 = HID_KEY_R,
    G2 = HID_KEY_T,
    A2 = HID_KEY_Y,
    B2 = HID_KEY_U
} Pitch;

typedef struct
{
    Pitch pitch;
    uint8_t length;
} Note;

#endif

