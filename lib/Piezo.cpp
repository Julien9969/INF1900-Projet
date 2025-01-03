/*
 * Classe permettant l'acces aux fonction pour le controle du piezo
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

 
#include "Piezo.h"

// constructeur: initialisation du convertisseur
Piezo::Piezo()
{
    DDRD |= _BV(PORTD6) | _BV(PORTD7);
    PORTD &= ~_BV(PORTD6);    

    //CTC, Toggle compare match
    TCCR2A = (1 << COM0A0) | (1 << WGM01);

    //clk/256
    TCCR2B |= (1 << CS02);
        
}


void Piezo::jouerUneNote(uint16_t numNote){ //,double temps_s){
    Piezo();
    if ((numNote > 44) & (numNote < 82)){
        uint8_t index = numNote - 45;
    
        // Octave permet de regler si le son voulu et aigu ou grave, ++octave == ++aigu
        // periode cpu = 8 000 000 / 256 = 31250 correspond au nb de compte pour 1s
        // OCR2A prend la periode de la note
        OCR2A = (periodeCPU_ / (notes[index] )) - 1;

    }
};

void Piezo::noteLettre(Notes note, uint8_t octave, uint16_t duree){


    OCR2A = (periodeCPU_ / (int(note) * octave )) - 1;

    delay(duree);

    OCR2A = 0;
    
}


void Piezo::pauseNote(uint16_t duree){
    OCR2A = 0;
    delay(duree);
}

void Piezo::arreteNote(){ //,double temps_s){
    
    // On met a 0 tout les registrer modifier pour jouer la note
    OCR2A = 0;
    TCCR2A &= ~(1 << COM0A0) & ~(1 << WGM01);
    TCCR2B &= ~(1 << CS02);
};

void Piezo::delay(uint16_t duree) {
    for (uint16_t i = 0; i < duree; i++)
        _delay_ms(1);
}


