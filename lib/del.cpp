/*
 * Classe permettant l'acces aux fonction ajustant les couleurs sur les DEL
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

#include "del.h"



// La fonction allumerDelAmbre fonctionne uniquement pour une del branché sur PORTD4 et PORTD5 (5 et 7 sur la carte physique) 
void Del::allumerDelAmbre() {

    cli();

    TCNT0 = 0;
    
    // Timer 2 en mode phase correct PWM, sur compare OCR2A, en compte (mode non-inversé) 
    TCCR2A |= (1 << COM2A1) | (1 << WGM20); // Atmel P102 tableau 15-4 (WGM21 pour simulide)
    // Timer 2 en mode phase correct PWM, sur compare OCR2B, en decompte (mode inversé)
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
    
    // division d'horloge par 8
    TCCR2B |= (1 << CS21); //Doc Atmel p104

    // On met la même valeur aux deux registres car on à configuré le Timer pour que leur diagrammes temporel soit inverse l'un de l'autre.
    // Ainsi quand le port lié a OCR2A est à 0 alors OCR2B est à 1 et inversement.
    OCR2A = VALEUR_AMBRE;
    OCR2B = VALEUR_AMBRE;

    TCCR1C = 0;

    couleur_ = AMBRE;

    sei();
}

void Del::arretAmbre(){ 
    // On arrete le pwm
    TCCR2A &= ~(1 << COM2A1) & ~(1 << WGM20); // & ~(WGM21) pour simulide
    TCCR2A &= ~(1 << COM2B1) & ~(1 << COM2B0);
    
    TCCR2B &= ~(1 << CS21); //Doc Atmel p104
}


void Del::allumerDelRouge()
{
    if ((pin1_ == PORTD7) | (pin1_ == PORTD6) ){
        arretAmbre();
    }
    *PORTx_ &= ~(1 << pin1_);
    *PORTx_ |= (1 << pin2_);
    couleur_ = ROUGE;
}

void Del::allumerDelVert()
{
    if ((pin1_ == PORTD7) | (pin1_ == PORTD6) ){
        arretAmbre();
    }
    *PORTx_ |= (1 << pin1_);
    *PORTx_ &= ~(1 << pin2_);
    couleur_ = VERT;
}

void Del::eteindreDel()
{
    if ((pin1_ == PORTD7) | (pin1_ == PORTD6) ){
        arretAmbre();
    }
    *PORTx_ &= ~(1 << pin1_);
    *PORTx_ &= ~(1 << pin2_);
    couleur_ = ETEINT;
}

int Del::lireCouleur(){
    return couleur_;
}

// Ce utile pour allumer une del ambre par scrutation, dans le cas ou tous les timer sont utile
// Il doit etre appele dans une boucle (ref tp6 pb2), et le temps envoye est adaptable tout dependant 
// le temps d execution de la boucle dans lequel ce code est appele, ou pour attenuer/augmenter le rouge
void Del::allumerDelAmbreScrutation()
{
    allumerDelVert();
    delaisMs(TEMPS_VERT);
    allumerDelRouge();
    delaisMs(TEMPS_ROUGE);

}

void Del::delaisMs(int temps)
{
    for(int i=0;i<temps;i++)
    {
        _delay_ms(1);
    }
}
