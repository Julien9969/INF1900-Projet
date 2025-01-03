#include "music.h"


Notes Song[] = {g0, tiret, tiret ,g0, tiret, tiret, g0, tiret, tiret, g0, a0, g0, A0, g0, a0, g0, g0, tiret, tiret, g0, tiret, tiret, g0, g0, A0, tiret, \
tiret, tiret, tiret, tiret, tiret, tiret, g3, tiret, tiret, tiret, g3,tiret, tiret, tiret, D3, tiret, tiret, tiret, D3, tiret, A3, tiret, A3, tiret, tiret, tiret,  \
A0, tiret,f0, tiret,c0, tiret,tiret,tiret,c0, tiret,g0, tiret,g0, tiret,tiret,tiret,g0, tiret,tiret,tiret,D0, tiret,tiret,tiret,D0, tiret, \
A0, tiret,d3, tiret,tiret,tiret,A3, tiret,f0, tiret,f0, tiret,tiret,tiret,f0, tiret,c0, tiret,g3, tiret,g3, A3, a3, tiret,a3, tiret, \
A3,tiret,g3,tiret,tiret,tiret,tiret,tiret,a3,tiret,a3,tiret,A3,tiret,A3,tiret,tiret,A3,A3,tiret,tiret,tiret,A3,a3,A3,tiret, \
A3,tiret,tiret,tiret,tiret,tiret,d0,tiret,A3,tiret,f0,tiret,tiret,tiret,F0,tiret,tiret,tiret,tiret,tiret,tiret,tiret,g3, a3, tiret,A3,  \
c3,tiret,F3,tiret,g3,tiret,tiret,g3,tiret,tiret,g3,tiret,tiret,g3,a3,g3,A3,g3,a3,g3,g3,tiret,tiret,g3,tiret,tiret, \
g0,tiret,tiret,tiret,tiret,tiret,tiret,tiret,tiret,tiret,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0, \
g3,g0,g0,g3,g0,g0,g3,g0,g0,g3,A3,g3,g0,g3,A3,a3,g3,g0,g0,g3,g0,g0,g3,g0,g0,g3, \
a3,g3,A3,g3,a3,g3,g3,g0,g0,g3,g0,g0,g3,g0,g0,g3,a3,g3,a3,A3,g0,g0,g3,g0,g0,g3, \
g0,g0,g3,g0,g0,g3,a3,g3,A3,g3,a3,g3,g3,g0,g0,g3,g0,g0,g3,g0,g0,g3,A3,g3,g0,g3, \
A3,a3,g3,g0,g0,g3,g0,g0,g3,g0,g0,g3,a3,g3,A3,g3,a3,g3,g3,g0,g0,g3,g0,g0,g3,g0, \
g0,g0,g0,g0,g0,g0,g0,g0,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,c0,tiret, \
c3,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,g0,tiret,g0,tiret,g0,tiret,g0,tiret,g0,tiret,g0,tiret, \
g0,tiret,g0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,D0,tiret,A0,tiret,tiret,tiret, \
A3,tiret,g3,tiret,D3,tiret,A0,tiret,g0,tiret,c3,tiret,D3,tiret,g3,tiret,A3,tiret,tiret,tiret,A3,tiret,g3,tiret,d3,tiret, \
g0,tiret,d3,tiret,g3,tiret,A3,tiret,g3,tiret,d3,tiret,A0,tiret,g0,tiret,f0,tiret,c3,tiret,f3,tiret,a3,tiret,tiret,tiret, \
a3,tiret,f3,tiret,c3,tiret,D0,tiret,A0,tiret,D3,tiret,g3,tiret,D0,tiret,A0,tiret,D3,tiret,g3,tiret,g0,tiret,g0,tiret, \
g0,tiret,g0,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,g0,\
a3,g3,g3,tiret,tiret,g3,tiret,tiret,g3,tiret,tiret,g3,A3,g3,tiret,g3,a3,a3,g3,tiret,tiret,g3,tiret,tiret,g3,tiret,\
g0,g3,a3,g3,a3,g3,a3,g3,g3,g0,g0,g3,g0,g0,g3,g0,g0,g3,a3,g3,a3,a3,g0,g0,g3,g0,\
D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,D0,tiret,c0,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,c3,tiret,\
c3,tiret,c3,tiret,g0,tiret,g0,tiret,g0,tiret,A3,tiret,g0,tiret,g0,tiret,g0,tiret,g0,tiret,A0,tiret,A0,tiret,A0,tiret, \
A0,tiret,A0,tiret,A0,tiret,A0,tiret,A0,tiret,D0, tiret,A0,tiret,D3,tiret,A3,tiret,g3,tiret,D3,tiret,A0,tiret,g0,tiret,\
c3,tiret,D3,tiret,g3,tiret,A3,tiret,D3,tiret,A3,tiret,g3,tiret,D3,tiret,A3,tiret,D3,tiret,g3,tiret,A3,tiret,g3,tiret,\
d3,tiret,A0,tiret,g0,tiret,f0,tiret,c3,tiret,f3,tiret,a3,tiret,tiret,tiret,a3,tiret,f3,tiret,c3,tiret,D0,tiret,A0,tiret} ;


Music::Music()
{
    DDRD |= _BV(PORTD6) | _BV(PORTD7);
    PORTD &= ~_BV(PORTD6);    

    //CTC, Toggle compare match
    TCCR2A = (1 << COM0A0) | (1 << WGM01);

    //clk/256
    TCCR2B |= (1 << CS02);
        
}

void Music::noteLettre(Notes note,  uint8_t octave ,uint16_t duree){

    OCR2A = (periodeCPU_ / (int(note) * octave * 2 )) - 1;

    delay(duree);

    OCR2A = 0;
    
}


void Music::delay(uint16_t duree) {

    uint16_t nb = duree / 10;
    for (uint16_t i = 0; i < nb; i++)
        _delay_ms(10);
}

void Music::jouerMusic() {


    for (uint8_t i = 0; i < sizeof(Song); i++)
    {
        switch (Song[i])
        {
        case c0:
            noteLettre(c0,1, 160);
            break;

        case d0:
            noteLettre(d0, 1, 160);
            break;

        case e0:
            noteLettre(e0, 1, 160);
            break;

        case f0:
            noteLettre(f0, 1, 160);
            break;

        case g0:
            noteLettre(g0, 1, 160);
            break;

        case a0:
            noteLettre(a0, 1, 160);
            break;

        case b0:
            noteLettre(b0, 1, 160);
            break;
        
        case C0:
            noteLettre(C0, 1, 160);
            break;
            
        case D0:
            noteLettre(D0, 1, 160);
            break;

        case F0:
            noteLettre(F0, 1, 160);
            break;

        case G0:
            noteLettre(G0, 1, 160);
            break;

        case A0:
            noteLettre(A0, 1, 160);
            break;

        case c3:
            noteLettre(c3, 1, 160);
            break;

        case d3:
            noteLettre(d3, 1, 160);
            break;

        case e3:
            noteLettre(e3, 1, 160);
            break;

        case f3:
            noteLettre(f3, 1, 160);
            break;

        case g3:
            noteLettre(g3, 1, 160);
            break;

        case a3:
            noteLettre(a3, 1, 160);
            break;

        case b3:
            noteLettre(b3, 1, 160);
            break;
        
        case C3:
            noteLettre(b3, 1, 160);
            break;
            
        case D3:
            noteLettre(D3, 1, 160);
            break;

        case F3:
            noteLettre(F3, 1, 160);
            break;

        case G3:
            noteLettre(G3, 1, 160);
            break;

        case A3:
            noteLettre(A3, 1, 160);
            break;

        case tiret:
            delay(150);
            break; 
        
        }

    }

}
