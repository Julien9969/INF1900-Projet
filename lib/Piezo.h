#ifndef F_CPU
   #define F_CPU 8000000
#endif

#ifndef PIEZO_H
#define PIEZO_H

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
// conversion[25] = 466.16;
const uint16_t notes[] = {110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 207, 220, 233, 246, 261, 277, 293, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880};

// Le nom des notes allemand, indice 1 pour note prime (')
enum class Notes {
   A = 110,
   AB = 117,
   H = 123,
   c = 131,
   cd = 139,
   d = 147,
   de = 156,
   e = 165,
   f = 175,
   fg = 185,
   g = 196,
   ga = 208,
   a = 220,
   ab = 233,
   h = 247,
   c1 = 262,
   c1d1 = 277,
   d1 = 294,
   d1e1 = 311,
   e1= 330,
   f1 = 349,
   f1g1 = 370,
   g1 = 392,
   g1a1 = 415,
   a1Kamer = 440,
   ai1b1 = 466,
   h1 = 494,
   c11 = 523,
   c11d11 = 554,
   d11 = 587,
   di11e11 = 622,
   e11 = 659,
   f11 = 698,
   f11g11 = 740,
   g11 = 783,
   g11a11 = 831,
   a11 = 880
};

class Piezo
{
public:

   Piezo();

   void jouerUneNote(uint16_t numNote);
   void noteLettre(Notes note, uint8_t octave, uint16_t duree);

   void arreteNote();
   void pauseNote(uint16_t duree);

private:

    void delay(uint16_t duree);

    uint16_t periodeCPU_ = 31250;

};

#endif /* PIEZO_H */
