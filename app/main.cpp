#ifndef F_CPU
    #define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "Robot.h"
#include "debug.h"


//niveaux
#define LUMIERE_AMBIANTE_OU_MOINS 0
#define NIVEAU_1 1
#define NIVEAU_2 2
#define NIVEAU_3 3
#define NIVEAU_4 4

#define FIN_AMBIANTE 4
#define FIN_NIVEAU_1 7
#define FIN_NIVEAU_2 11
#define FIN_NIVEAU_3 15

//vitesse des Moteurs suvis lumière
#define LENT 35
#define MOYEN 45
#define RAPIDE 55
#define VERSTAPPEN 65

#define TOURNE_UN_PEU 5
#define TOURNE_BEAUCOUP 10
#define TOURNE_PASSIONEMMENT 20
#define TOURNE_FOLLEMENT 0

//Delai
#define DELAI_ENREGISTREMENT 976
#define DELAI_MUR 94
#define DELAI_LUMIERE 79
#define DELAI_RELECTURE 100
#define ANTI_DOUBLE_APPUI 500

//distance | valeur usb | valeur pile
// 20           75             65
// 10           130
// 30           55
// inf          <25

#define VINGT_CM 65
#define DISTANCE_MIN_MUR 30
#define REPRISE_DE_MUR 40
#define ANTI_ZIGZAG_PROCHE 3
#define ANTI_ZIGZAG_lOIN 3
#define Vitesse 47
#define variationD 2

//Port
#define PHOTORESISTANCE_DROITE 0
#define PHOTORESISTANCE_GAUCHE 1
#define CAPTEUR_DISTANCE 7
#define BOUTTON_D2 2
#define BOUTTON_D3 3


void init() {
    //Port lecture convertisseur analogique numerique
    DDRA &= ~(1 << PHOTORESISTANCE_DROITE) & ~(1 << PHOTORESISTANCE_GAUCHE);
    DDRA &= ~(1 << CAPTEUR_DISTANCE);

    //Port DEL
    DDRD |= (1 << PORTD7) | (1 << PORTD6);

    //Port Moteurs
    DDRB |= (1 << PORTB3) | (1 << PORTB2);
    DDRB |= (1 << PORTB4) | (1 << PORTB5);

    //Port Bouttons
    DDRD &= ~(1 << BOUTTON_D2) & ~(1 << BOUTTON_D3);

}


enum Instructions {toutDroit = 0, tourneDroite = 1, tourneGauche = 2, arreter = 3};


Robot robot;

volatile Instructions gInstructions;
volatile uint8_t gOperande = 0;


uint8_t loin(const uint8_t& a)
{
    if (a < 40){
        return 11;
    }
    else if ( a < 45) {
       return 8;
    }
    else {
        return 6;
    }
}


uint8_t proche(const uint8_t& a)
{ 
    if ( a > 130){
        return 11;
    }
    else {
        return 6;
    }
}


ISR (TIMER1_COMPA_vect){

    robot.ecriture(gInstructions);
    robot.ecriture(gOperande);

    DEBUG_PRINT("Timer A\n");
    //DEBUG_PRINT("inst %d, operande %d: \n", gInstructions, gOperande);
    robot.minuteur.startMinuteurA(DELAI_ENREGISTREMENT); 

}


ISR (TIMER1_COMPB_vect){

    gInstructions = Instructions(robot.lecture());
    gOperande = robot.lecture();

    // DEBUG_PRINT("inst %d, operande %d: \n", gInstructions, gOperande);
    DEBUG_PRINT("Timer B\n");
    robot.minuteur.startMinuteurB(DELAI_ENREGISTREMENT); //1172
}


void suivisDeMur(bool onEnregistre)
{
    uint8_t distanceLue;
    bool mur = true;

    if (onEnregistre){
        robot.minuteur.startMinuteurA(DELAI_ENREGISTREMENT);
    }

    robot.depart();

    while (mur)
    {
        distanceLue = uint8_t(robot.convertAnalogique.lecture(PORTA7) >> 2);
        //DEBUG_PRINT("donnée lu : %d\n", distanceLue);

        if (distanceLue > (VINGT_CM + ANTI_ZIGZAG_PROCHE) )
        {
            gInstructions = tourneGauche;
            gOperande = proche(distanceLue);

            robot.moteurDroit.ajusterPWM(Vitesse + gOperande, AVANT);    
            robot.moteurGauche.ajusterPWM(Vitesse - gOperande , AVANT);

            //DEBUG_PRINT("On est proche vitesse : %d\n", robot.moteurGauche.lirePourcent()); 
            robot.del.allumerDelRouge();
        }
        else if (distanceLue < (VINGT_CM - ANTI_ZIGZAG_lOIN) )
        {
            gInstructions = tourneDroite;
            gOperande = loin(distanceLue);

            robot.moteurGauche.ajusterPWM(Vitesse + gOperande , AVANT);    
            robot.moteurDroit.ajusterPWM(Vitesse - gOperande, AVANT);  

            //DEBUG_PRINT("On est loin, vitesse : %d\n", robot.moteurDroit.lirePourcent());
            robot.del.allumerDelVert(); 
        }
        else 
        {
            gInstructions = toutDroit;
            gOperande = Vitesse;

            robot.moteurGauche.ajusterPWM(Vitesse , AVANT);
            robot.moteurDroit.ajusterPWM(Vitesse, AVANT);

            //DEBUG_PRINT("On est Bon\n");
            robot.del.allumerDelAmbre();
        }

        if (distanceLue < DISTANCE_MIN_MUR){
            mur = false;
            //DEBUG_PRINT("PLUS DE MUR");
            gOperande = 0;
        }
        _delay_ms(DELAI_MUR);
        DEBUG_PRINT("Boucle suivis: ");

    }
    robot.minuteur.arreterMinuteur();

    robot.moteurGauche.arreterMoteur();
    robot.moteurDroit.arreterMoteur();
}



int etatLumineux(uint8_t lumiereAmbiante, uint8_t port){
    
    uint8_t resistanceDroite = uint8_t(robot.convertAnalogique.lecture(port) >> 2);

    // 0 = lum ambiante ou en-dessous, 1 = 1er niveau de luminosite, 2 = 2eme niveau de lum, 3 = 3eme niveau de lum
    
    int deltaResistanceDroite = resistanceDroite - lumiereAmbiante;

    if (deltaResistanceDroite < FIN_AMBIANTE ){
        return LUMIERE_AMBIANTE_OU_MOINS;
    } 
    else if (deltaResistanceDroite < FIN_NIVEAU_1){
        return NIVEAU_1;
    }
    else if (deltaResistanceDroite < FIN_NIVEAU_2){
        return NIVEAU_2;
    }
    else if (deltaResistanceDroite < FIN_NIVEAU_3){
        return NIVEAU_3;
    }
    else {
        return NIVEAU_4;
    }
}



void suiviLumiere(bool onEnregistre){

    uint8_t lumiereAmbianteDroite = uint8_t(robot.convertAnalogique.lecture(PHOTORESISTANCE_DROITE) >> 2);
    uint8_t lumiereAmbianteGauche = uint8_t(robot.convertAnalogique.lecture(PHOTORESISTANCE_GAUCHE) >> 2);

    uint8_t distance = uint8_t(robot.convertAnalogique.lecture(CAPTEUR_DISTANCE) >> 2);

    //DEBUG_PRINT("distance %d,\n",distance);

    uint8_t etatDroit;
    uint8_t etatGauche;
    int delta;
    

    while (!robot.bouttonBlancPresse() && !robot.bouttonInterruptPresse() && (distance < REPRISE_DE_MUR)){

        etatDroit = etatLumineux(lumiereAmbianteDroite, PHOTORESISTANCE_DROITE);
        etatGauche = etatLumineux(lumiereAmbianteGauche, PHOTORESISTANCE_GAUCHE);

        distance = uint8_t(robot.convertAnalogique.lecture(CAPTEUR_DISTANCE) >> 2);

        delta = etatGauche - etatDroit;
        // DEBUG_PRINT("enr %d, gauche droite : %d", onEnregistre);

        if (onEnregistre && (etatDroit != 0 || etatGauche !=0)){
            onEnregistre = false;
            robot.minuteur.startMinuteurA(DELAI_ENREGISTREMENT);
            DEBUG_PRINT("debut minu\n");
        }
        // DEBUG_PRINT("lec 1 = %d, lec 2 = %d detat = %d\n", etatDroit, etatGauche, delta);
        if (delta == 0){
            
            gInstructions = toutDroit;

            switch (etatGauche)
            {

            case 0:
                gOperande = 1;
                break;
            case 1:
                gOperande = LENT;
                break;
            
            case 2:
                gOperande = MOYEN;
                break;
            case 3:
                gOperande = RAPIDE;
                break;

            default:
                gOperande = VERSTAPPEN;
                break;
            }
            
            robot.moteurDroit.ajusterPWM(gOperande, AVANT);
            robot.moteurGauche.ajusterPWM(gOperande, AVANT);
            
            //DEBUG_PRINT("tout droit %d", gOperande);
        }

        else if(delta < 0){
            
            gInstructions = tourneDroite;

            switch (delta)
            {
            case -1:
                gOperande = TOURNE_UN_PEU;
                break;
            case -2:
                gOperande = TOURNE_BEAUCOUP;
                break;
            case -3:
                gOperande = TOURNE_PASSIONEMMENT;
                break;
            default:
                gOperande = TOURNE_FOLLEMENT;
                break;
            }


            robot.moteurGauche.ajusterPWM(Vitesse + gOperande, AVANT);
            
            if (gOperande != 0){
                robot.moteurDroit.ajusterPWM(Vitesse - gOperande, AVANT);
            }
            else
            {
                robot.moteurDroit.ajusterPWM(Vitesse - gOperande, ARRIERE);
                // DEBUG_PRINT("toupie ");
            }

            //DEBUG_PRINT("tourne droite %d\n", gOperande);
        }
        
        else {

            gInstructions = tourneGauche;

            switch (delta)
            {
            case 1:
                gOperande = TOURNE_UN_PEU;
                break;
            case 2:
                gOperande = TOURNE_BEAUCOUP;
                break;
            case 3:
                gOperande = TOURNE_PASSIONEMMENT;
                break;
            default:
                gOperande = TOURNE_FOLLEMENT;
                break;
            }

            robot.moteurDroit.ajusterPWM(Vitesse + gOperande, AVANT);
            if (gOperande != 0){
                robot.moteurGauche.ajusterPWM(Vitesse - gOperande, AVANT);
            }
            else
            {
                robot.moteurGauche.ajusterPWM(Vitesse - gOperande, ARRIERE);
                // DEBUG_PRINT("toupie ");
            }

            //DEBUG_PRINT("tourne gauche %d\n", gOperande);
        }

        _delay_ms(DELAI_LUMIERE); // 105
        DEBUG_PRINT(" : Boucle lumiere\n");
    
    }
    robot.minuteur.arreterMinuteur();

    robot.moteurGauche.arreterMoteur();
    robot.moteurDroit.arreterMoteur();

    robot.del.allumerDelAmbre();     
}

void finEnregistrement() {
    gInstructions = arreter;

    robot.ecriture(gInstructions);
};

void reLecture(){
    robot.adresse = 0x00;
    bool pasFini = true;

    robot.minuteur.startMinuteurB(DELAI_ENREGISTREMENT);
    robot.depart();

    while (pasFini)
    {
        switch (gInstructions)
        {
        case toutDroit:
            robot.moteurDroit.ajusterPWM(gOperande, AVANT);
            robot.moteurGauche.ajusterPWM(gOperande, AVANT);
            // DEBUG_PRINT("bien\n");
            break;
        case tourneGauche:
            robot.moteurDroit.ajusterPWM(Vitesse + gOperande, AVANT);    

            if (gOperande != 0){
                robot.moteurGauche.ajusterPWM(Vitesse - gOperande , AVANT);
            }
            else {
                robot.moteurGauche.ajusterPWM(Vitesse - gOperande , ARRIERE);
            }
            // DEBUG_PRINT("proche\n");
            break;
        case tourneDroite:
            robot.moteurGauche.ajusterPWM(Vitesse + gOperande , AVANT);    
            // DEBUG_PRINT("loin\n");
            
            if (gOperande != 0){
                robot.moteurDroit.ajusterPWM(Vitesse - gOperande , AVANT);
            }
            else {
                // DEBUG_PRINT("inst %d, operande %d: \n", gInstructions, gOperande);
                robot.moteurDroit.ajusterPWM(Vitesse - gOperande, ARRIERE);
            }

            break;
        case arreter:
            // DEBUG_PRINT("Pas de mur\n");
            pasFini = false;
            break;
        }

        _delay_ms (DELAI_RELECTURE);
        DEBUG_PRINT("Boucle relecture");
    }

    robot.minuteur.arreterMinuteur();

    robot.moteurGauche.arreterMoteur();
    robot.moteurDroit.arreterMoteur();
}

void modeParcourt(){

    bool onEnregistre = true;
    bool finDeParcours = false;
    robot.bouttonsSurFaux();

    while (!finDeParcours) {
        
        if (robot.blancDernierPresse())
        {
            //DEBUG_PRINT("demie Tour\n");
            robot.bouttonsSurFaux();
            finEnregistrement();
            onEnregistre = false;
            robot.demieTour();
            _delay_ms(ANTI_DOUBLE_APPUI);
        }
        else if (robot.interruptDernierPresse()) 
        {
            robot.bouttonsSurFaux();
            //DEBUG_PRINT("Fin parcours\n");
            finDeParcours = true;
            robot.del.allumerDelRouge();
            _delay_ms(ANTI_DOUBLE_APPUI);
            robot.del.allumerDelVert();
        }
        else 
        {
            //DEBUG_PRINT("Mur et lumiere\n");
            suivisDeMur(onEnregistre);
            _delay_ms(ANTI_DOUBLE_APPUI);
            suiviLumiere(onEnregistre);
        }

    }
}

void choixDuMode() {
    bool epreuve = true;

    while (epreuve)
    {
        robot.del.eteindreDel();

        if (robot.bouttonInterruptPresse())
        {
            robot.delClignoteVert();
            modeParcourt();
        }
        else if (robot.bouttonBlancPresse())
        {
            robot.delClignoteRouge();
            reLecture();
            robot.del.allumerDelVert();
            epreuve = false;
        }
    }
}


int main()
{
    init();

    choixDuMode();

    return 0; 
}
