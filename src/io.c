#include "io.h"

/** @file io.c
@brief Ensemble de fonction pour afficher la grille
@date 28/04/2016
**/

/** @brief Fonction qui affiche un trait horizontal
@param c Nombre de colonne
**/

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/** @brief Fonction qui affiche une ligne de la grille avec le vieillissement desactivé
@param c Nombre de colonne de la grille
@param ligne Pointeur sur la ligne à afficher de la grille
**/

void affiche_ligne (int c, int* ligne ){
        int i;
        for (i=0; i<c; ++i)
                if (ligne[i] == 0 ) printf ("|   "); else if(ligne[i] == -1){printf("| X ");} else{printf ("| O ");}
        printf("|\n");
        return;
}


/** @brief Fonction qui affiche une ligne de la grille avec le vieillissement activé 
@param c Nombre de colonnes de la grille
@param ligne Pointeur sur la ligne à afficher de la grille
**/ 

void affiche_ligne_v (int c, int* ligne ){
        int i;
        for (i=0; i<c; ++i)
                if (ligne[i] == 0 ) printf ("|   ");else if(ligne[i] == -1){printf("| X ");} else printf ("| %d ", ligne[i]);
        printf("|\n");
        return;
}

void (*Ptr_affiche_ligne)(int, int*)=affiche_ligne; // Pointeur sur la fonction affiche_ligne

/** @brief Fonction qui affiche une ligne de la grille lors de la désactivation ou de l'activation du vieillissement **/

void affichage(){
	if (Ptr_affiche_ligne==affiche_ligne)
	{
		Ptr_affiche_ligne=affiche_ligne_v;
	}
	else
	{
		Ptr_affiche_ligne=affiche_ligne;
	}
}


/** @brief Fonction qui affiche la grille et son temps d'évolution
@param g Nom de la grille
@param t Temps d'évolution
**/

void affiche_grille (grille g, int t){
	int i, l=g.nbl, c=g.nbc;
	printf("Temps d'évolution: %d\n", t);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		Ptr_affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/** @brief Fonction qui efface la grille
@param g Nom de la grille
**/

void efface_grille (grille g){
	
	system("clear");
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/** @brief Fonction qui debute le jeu 
@param g Pointeur sur la grille
@param gc Pointeur sur la copie de la grille
**/

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	static int t=0;
	while (c != 'q') // touche 'q' pour quitter
        {
                switch (c) {
                        case '\n' :
                        { // touche "entree" pour évoluer
				t++;
                        	evolue(g,gc);
                        	efface_grille(*g);
                        	affiche_grille(*g, t);
                        	break;
                        }
			case 'c' :
			{ //  touche "c" pour activer/desactiver le voisinage cyclique
				active_cyclique();
				break;
			}
			case 'v':
			{// touche "v" pour activer le vieillissement
				calcul_vieillissement();
				affichage();
			}
			case 'o':
			{// touche "o" pour tester si une colonie est oscillante
			
			}
                        default :
                        { // touche non traitée
                        	printf("\n\e[1A");
                              	break;
                        }
                }	
                c = getchar();
        }    
	return;	
}


