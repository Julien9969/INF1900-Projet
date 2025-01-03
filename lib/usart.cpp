/*
 * Classe permettant l'acces aux fonction pour transmission eeprom et UART
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


#include "usart.h"


Usart::Usart() {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0;

    // Transmission et reception RS232
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C |= (0 << USBS0 ) | (1 << UCSZ01) | (1 << UCSZ00); //pg 188
}

// Du USART vers le PC
void Usart::transmissionUART (uint8_t donnee) {
    // On attend que le canal soit libre
    while ( !( UCSR0A & (1<<UDRE0)) );
        UDR0 = donnee;
}

uint8_t Usart::receptionUART () {
    // On attend que le canal soit libre
    while ( !( UCSR0A & (1<<RXC0)) );
        return UDR0;
}