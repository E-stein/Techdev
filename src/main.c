#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

/** @file main.c
@author STEIN Eloise
@brief Fonction pour créer le "Jeu de la vie"
@date 28/04/2016
**/

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g,0);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
