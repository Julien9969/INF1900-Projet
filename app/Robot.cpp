#include "Robot.h"


Robot::Robot()
{
    
}


void Robot::depart() {
    moteurDroit.ajusterPWM(70, AVANT);
    moteurGauche.ajusterPWM(70, AVANT);
    _delay_ms(100);
}

void Robot::ecriture(uint8_t donnee)
{
    memoire.ecriture(adresse, donnee);
    _delay_ms(3);
    adresse++;
}

uint8_t Robot::lecture()
{
    memoire.lecture(adresse, &tempDonneeLecture);
    _delay_ms(2);
    adresse++;
    return tempDonneeLecture;
}

bool Robot::bouttonInterruptPresse(){
     if ((PIND & (1 << PORTD2)) != 0)
    {
        _delay_ms(5);
        return bouttons.bouttonInterrupt =  (PIND & (1 << PORTD2)) != 0;
    }
    return bouttons.bouttonInterrupt = false;
}



bool Robot::bouttonBlancPresse(){

    if ((PIND & (1 << PORTD3)) == 0)
    {
        _delay_ms(5);    
        return bouttons.bouttonBlanc = (PIND & (1 << PORTD3)) == 0;
    }
    return bouttons.bouttonBlanc = false;
}

bool Robot::blancDernierPresse() {
    return bouttons.bouttonBlanc;
}

bool Robot::interruptDernierPresse(){
    return bouttons.bouttonInterrupt;
}

void Robot::bouttonsSurFaux(){
    bouttons.bouttonBlanc = false, bouttons.bouttonInterrupt = false;
}

#define ROUE_EXTERIEUR 58
#define ROUE_INTERIEUR 40

void Robot::demieTour()
{
    
    del.allumerDelAmbre();
    moteurGauche.ajusterPWM(ROUE_EXTERIEUR, AVANT);
    moteurDroit.ajusterPWM(ROUE_EXTERIEUR, AVANT);
    _delay_ms(200);

    
    moteurDroit.ajusterPWM(ROUE_INTERIEUR, AVANT);
    _delay_ms(3500);

    while (uint8_t(convertAnalogique.lecture(PORTD7) >> 2) < 40){
        moteurDroit.ajusterPWM(ROUE_INTERIEUR, AVANT);
        _delay_ms(200);
        //DEBUG_PRINT("mur detecte %d\n", mur);
    }
    _delay_ms(500);
    
    moteurGauche.ajusterPWM(ROUE_EXTERIEUR, AVANT);
    _delay_ms(2000);

    moteurGauche.arreterMoteur();
    moteurDroit.arreterMoteur();

    del.eteindreDel();
}

void Robot::delClignoteRouge(){
    for (int i = 0 ; i < 15; i++){
        del.allumerDelRouge();
        _delay_ms(100);
        del.eteindreDel();
        _delay_ms(100);
    }
    del.allumerDelRouge();
}

void Robot::delClignoteVert() {
    for (int i = 0 ; i < 15; i++){
        del.allumerDelVert();
        _delay_ms(100);
        del.eteindreDel();
        _delay_ms(100);
    }
    del.allumerDelVert();
}