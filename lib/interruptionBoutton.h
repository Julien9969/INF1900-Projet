/*
 * Classe permettant l'acces aux fonction pour les interruptions de boutton
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

class interruptionBoutton
{
public:

   void initialization1Button();
   void initialization2Buttons();

};