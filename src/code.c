#include "code.h"

Note notes[SIZE];
uint64_t _note_index;

void note_set(Pitch p, uint8_t l)
{
    Note n = {p, l};
    notes[_note_index] = n;
    if(_note_index < SIZE)
    {
        _note_index++;
    }
    else
    {
    }
}

void note_init()
{
    _note_index = 0;
    note_set(C0, 1);
    note_set(D0, 1);
    note_set(E0, 1);
    note_set(F0, 1);
    note_set(G0, 1);
    note_set(A0, 1);
}

