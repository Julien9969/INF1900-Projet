#ifndef F_CPU
    #define F_CPU 8000000
#endif

#include <avr/io.h>
#include "del.h"
#include "can.h"
#include "Pwm.h"
#include "memoire_24.h"
#include "music.h"
#include "minuteurInterruption.h"


struct Bouttons {
    bool bouttonInterrupt;
    bool bouttonBlanc;
};

class Robot
{    
public:
    Robot();

    void depart();
    void demieTour();

    void ecriture(uint8_t donnee);
    uint8_t lecture();

    bool bouttonInterruptPresse();
    bool bouttonBlancPresse();

    bool blancDernierPresse();
    bool interruptDernierPresse();
    void bouttonsSurFaux();

    void delClignoteRouge();
    void delClignoteVert();


    PWM moteurGauche = PWM(Pin::B3, PORTB2);
    PWM moteurDroit = PWM(Pin::B4, PORTB5);

    Memoire24CXXX memoire;
    uint16_t adresse = 0x00;

    Del del;

    can convertAnalogique;

    minuteurInterruption minuteur;


private:
    Bouttons bouttons;
    uint8_t tempDonneeLecture;

};

