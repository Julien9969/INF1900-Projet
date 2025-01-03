/*
 * Corps de la classe PWM pour controle des moteurs du robot par PWM matériel.
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
 */



#include "Pwm.h"

PWM::PWM(Pin pin, int portDirection) : pin_(pin), portDirection_(portDirection){
    
    switch (pin)
    {
    case Pin::B3:
        OCR0x = &OCR0A;
        COM0x1 = COM0A1;
        break;
    
    case Pin::B4:
        OCR0x = &OCR0B;
        COM0x1 = COM0B1;
        break;
    }

    direction_ = 1;
    pourcent_ = 0;

    //On bloque les intéruptions
    cli();

    // On commence le compte à 0.
    TCNT0 = 0;
    
    // pwm phase correct + compare match OCR0x downcounting
    // Commenter WGM01 pour le robot physique (mettre phase correct pwm).
    TCCR0A |= (1 << COM0x1) |(1 << WGM00) | (1 << WGM01); //Doc Atmel p101-103
    
    // division d'horloge par 8
    TCCR0B |= (1 << CS01); //Doc Atmel p104
    
    TCCR1C = 0;

    // On reprend les intéruptions
    sei();
}

void PWM::ajusterPWM(int pourcent, int direction = 0){
    // On enregistre le pourcentage de PWM
    pourcent_ = pourcent;

    //On déreférence la variable correspondant au registe de comparaison pour la modifier.
    *OCR0x = (254 * pourcent_) / 100;

    // Si direction est pris par defaut (pas de valeur donné). on lui met la direction actuelle.
    if (direction == 0) 
        direction = direction_; 
        
    // On change la valeur du port de direction
    switch (direction)
    {
    case 1:
        PORTB |= (1 << portDirection_);
        break;
    
    case -1:
        PORTB &= ~(1 << portDirection_);
        break;
    }
    direction_ = direction;    
}

void PWM::changerDeDirection(){
    // On change la valeur du port de direction
    // Si Avant(1) devient Arriere(-1)
    // Si Arriere(-1) devient Avant(1)
    switch (direction_)
    {
    case 1:
        direction_ = -1;
        PORTB &= ~(1 << portDirection_);
        break;
    
    case -1:
        direction_ = 1;
        PORTB |= (1 << portDirection_);
        break;
    }
}

void PWM::arreterMoteur(){
    *OCR0x = 0;
}

void PWM::redemarerMoteur(){
    *OCR0x = (254 * pourcent_) / 100;
}

void PWM::accelerer(int pourcent){
    // On enregistre le nouveau pourcentage de PWM et on vérifie qu'il ne soit pas >100.
    pourcent_ = pourcent + pourcent_;
    if (pourcent_ > 100){
        pourcent_ = 100;
    }

    //On déreférence la variable correspondant au registe de comparaison pour la modifier
    *OCR0x = (254 * pourcent_) / 100;
}

void PWM::ralentir(int pourcent){
    // On enregistre le nouveau pourcentage de PWM et on vérifie qu'il ne soit pas <0.
    pourcent_ = pourcent_ - pourcent;
    if (pourcent_ < 0){
        pourcent_ = 0;
    }

    //On déreférence la variable correspondant au registe de comparaison pour la modifier
    *OCR0x = (254 * pourcent_) / 100;
}

PWM::~PWM(){
    // On remet tous les registes à 0.
    TCCR0A &= ~(1 << COM0x1) & ~(1 << WGM00) & ~(1 << WGM01);  // Commenter WGM01 pour le robot physique.
    TCCR0B &= ~(1 << CS01);
    *OCR0x = 0;
}



