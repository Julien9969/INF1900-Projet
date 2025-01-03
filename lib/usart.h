/*
 * En-tête Classe permettant l'acces aux fonction pour transmission eeprom et UART
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

#include <avr/io.h>
#include <util/delay.h>


class Usart{
public:

    Usart();

    void transmissionUART (uint8_t donnee);

    uint8_t receptionUART();

private:



};