#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants (int i, int j, grille g);
// les bords sont non cycliques.
int compte_voisins_vivants2 (int i, int j, grille g);

// active/désactive le mode cyclique
void active_cyclique();

// active le vieillissement
void active_v(int i, int j, grille* g);

// désactive le vieillissement
void no_active_v(int i, int j, grille* g);

// active/désactive le vieillissement
void calcul_vieillissement();

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
