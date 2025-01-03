### Projet intégrateur INF1900
Équipe 0213 : Julien Roux, William Martin, Jeremi Bellemare et Victor Gilbert
Robot : Verstappen le croque-mitaine

Instruction pour compiler le programme et le mettre sur le micro processeur ATmega 324PA du robot.

1. Compiler la librairie
    - Ouvrir un terminal à l'emplacement projet/lib
    - Executer la commande `make`

2. Compiler le programme
    - Ouvrir un terminal à l'emplacement projet/app
    - Executer la commande `make`

3. Mettre le programme dans le robot
    - Ouvrir un terminal à l'emplacement projet/app
    - Executer la commande `make install`


Note :
Des warning peuvent apparaitre à la compilation mais ils sont due à des fonctions lié à : - Des fichiers fournis comme librairie du robot.
                                                                                          - Des lignes copié depuis la documentation Atmel.
