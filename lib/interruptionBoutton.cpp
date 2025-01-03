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


#include "interruptionBoutton.h"

void interruptionBoutton::initialization1Button() 
{
    cli (); 

    EIMSK |= (1 << INT0);

    //Le front montant génère une demande d'interruption de facon asynchrone p.68
    EICRA |= (1 << ISC00) ;

    sei();
}

void interruptionBoutton::initialization2Buttons()
{
    cli ();

    EIMSK |= (1 << INT0) | (1 << INT1);

    //Le front montant génère une demande d'interruption de facon asynchrone p.68
    EICRA |= ( 1 << ISC00) ;

    sei ();
}