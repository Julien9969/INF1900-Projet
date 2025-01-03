/*
 * En-tête de la classe permettant l'acces aux fonction ajustant le timer 1 pour delay
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1900
 *
 * William Martin, Jeremi Bellemare, Victor Gilbert, Julien Roux
 * 2022
 *
 * Code qui n'est sous aucune license.
 * 
 * dernière modification: 07/03/2022
 * 
 */


#include "minuteurInterruption.h"


void minuteurInterruption::startMinuteurA(uint16_t temps)
{
    TCNT1 = 0;

    TCCR1A = 0;

    // Durée de la minuterie
    OCR1A = temps;

    // Configuration minuterie clk/1024 et mode CTC p103 atmel
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    // Timer compteur compare OCR1A et interruption TIMER1_COMPA_vect

    TIMSK1 &= ~(1 << OCIE1B);
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void minuteurInterruption::startMinuteurB(uint16_t temps)
{
    TCNT1 = 0;

    TCCR1A = 0;

    // Durée de la minuterie
    OCR1A = temps;

    // Configuration minuterie clk/1024 et mode CTC p103 atmel
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    // Timer compteur compare  OCR1A et interuption TIMER1_COMPB_vect
    TIMSK1 &= ~(1 << OCIE1A);
    TIMSK1 |= (1 << OCIE1B);

    sei();
}


void minuteurInterruption::arreterMinuteur(){

    TCCR1B &= ~(1 << WGM12) & ~(1 << CS12) & ~(1 << CS10);
    TIMSK1 &= ~(1 << OCIE1A) & ~(OCIE1B);

}