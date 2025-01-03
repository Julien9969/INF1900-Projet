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

#ifndef F_CPU
   #define F_CPU 8000000
#endif

#ifndef DEL_H
#define DEL_H

#define TEMPS_ROUGE 2
#define TEMPS_VERT 5

#define VALEUR_AMBRE 185

#define ETEINT 0
#define VERT 1
#define ROUGE 2
#define AMBRE 3

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>


// Classe del: La clase s'occupe de l'assignement de des pin permettant ainsi les changements de couleurs
 
class Del
{
public:
   // Construction d'une del avec choix des ports, incompatible del ambre
   Del(volatile uint8_t* PORTx, int pin1, int pin2) : pin1_(pin1), pin2_(pin2), PORTx_(PORTx){};

   // Construction de la del par default (PORT 6 et 7) compatible del ambre
   Del() : pin1_(PORTD7), pin2_(PORTD6), PORTx_(&PORTD) {}; 


   // On change couleur de la led via ses attributs
   void allumerDelRouge();
   void allumerDelVert();
   void allumerDelAmbre ();
   void eteindreDel();

   // Methode pour lire la couleur de la del
   int lireCouleur();
   void allumerDelAmbreScrutation();
   void delaisMs(int temps);

private:
   void arretAmbre();

   int couleur_;
   int pin1_, pin2_;
   volatile uint8_t* PORTx_;
};

#endif 
