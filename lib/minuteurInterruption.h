/*
 * Classe permettant l'acces aux fonction ajustant le timer 1 pour delay
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

#include <avr/io.h> 
#include <avr/interrupt.h>


class minuteurInterruption
{
public:

   void startMinuteurA(uint16_t temps);
   void startMinuteurB(uint16_t temps);
   void arreterMinuteur();
};