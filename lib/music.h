#ifndef F_CPU
   #define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>

enum Notes {
    c0 = 65,
    d0 = 73,
    e0 = 82,
    f0 = 87,
    g0 = 98,
    a0 = 110,
    b0 = 124,
    C0 = 69,
    D0 = 78,
    F0 = 93,
    G0 = 104,
    A0 = 117,
    c3 = 198,
    d3 = 229,
    e3 = 255,
    f3 = 276,
    g3 = 327,
    a3 = 375,
    b3 = 430,
    C3 = 226,
    D3 = 280,
    F3 = 305,
    G3 = 350,
    A3 = 400,
    tiret = 0, 

};

class Music
{
public:

   Music();

   void noteLettre(Notes note, uint8_t octave, uint16_t duree);
   void jouerMusic();

private:

    void delay(uint16_t duree);

    uint16_t periodeCPU_ = 31250;

};
