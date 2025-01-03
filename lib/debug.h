/*
 * Definition de la macro DEBUG_PRINT
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
 * dernière modification: 10/03/2022
 * 
 */

#include <string.h>
#include <stdio.h>
#include "usart.h"


// Macro DEBUG_PRINT qui permet d'afficher des chaines de caractère dans le terminal du pc (SerieViaUSB)
// La macro de permet d'afficher des strings formaté (intégration de variable dans le message)
// Exemple d'utilisation : DEBUG_PRINT("Exemple : une string %s et un int %d\n", "Hello", 2022);
#ifdef DEBUG
char str[128]; // Définition d'une string assez grande pour contenir le message.
// sprintf crée la string formaté et la met dans str.
Usart usb;
#define DEBUG_PRINT(...) sprintf (str, __VA_ARGS__); \
    for (uint8_t i = 0; i < strlen(str); ++i)\
        usb.transmissionUART(str[i])
// L'appel d'une fonction pour la boucle for qui affiche la string rend son affichage parfois corrompu 

#else
// code mort
#define DEBUG_PRINT(...) do {} while (0)
#endif