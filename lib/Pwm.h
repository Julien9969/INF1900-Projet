/*
 * En-tête de la classe PWM pour controle des moteurs du robot par PWM matériel.
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

#ifndef PWM_H
#define PWM_H

#define AVANT -1
#define ARRIERE 1

#include <avr/interrupt.h>
#include <avr/io.h>

enum class Pin {B3, B4};

class PWM{
public:
    PWM(){};
    PWM(Pin pin, int portDirection);
    void ajusterPWM(int pourcent, int direction);
    void changerDeDirection();
    void arreterMoteur();
    void redemarerMoteur();
    void accelerer(int pourcent);
    void ralentir(int pourcent);

    ~PWM();

    int lirePourcent() {return pourcent_;}
    int lireDirection() {return direction_;}


private:
    // Variables pour ajuster le PWM.
    int direction_;
    int pourcent_;

    // Variables pour la configuration.
    Pin pin_;
    int portDirection_;
    volatile uint8_t* OCR0x;
    int COM0x1;
};

#endif
