#include "jeu.h"

/** @file jeu.c
@brief Ensemble de fonctions pour lancer le jeu
@date 28/04/2016
**/

/** @brief Fonction qui compte le nombre de voisins vivants de la cellule (les bords sont cycliques)
@param i Numéro de la ligne de la cellule
@param j Numéro de la colonne de la cellule
@param g Nom de la grille
@return v Nombre de voisins vivants
**/

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/** @brief Fonction qui compte le nombre de voisins vivants de la cellule (les bords ne sont pas cycliques)
@param i Numéro de la ligne de la cellule
@param j Numéro de la colonne de la cellule
@param g Nom de la grille
@return v Nombre de voisins vivants
**/

int compte_voisins_vivants2 (int i, int j, grille g){
	int v=0, l=g.nbl, c=g.nbc;
	if (((i-1)>=0)&&((j-1)>=0))
	{
		v+= est_vivante(i-1,j-1,g);
	}
	if ((i-1)>=0)
	{
		v+= est_vivante(i-1,j,g);
	}
	if (((i-1)>=0)&&((j+1)<c))
	{
		v+= est_vivante(i-1, j+1, g);
	}
	if ((j-1)>=0)
	{
		v+= est_vivante (i, j-1,g);
	}
	if ((j+1)<c)
	{
		v+= est_vivante (i, j+1, g);
	}
	if (((i+1)<l)&&((j-1)>=0))
	{
		v+= est_vivante (i+1, j-1, g);
	}
	if ((i+1)<l)
	{
		v+= est_vivante (i+1, j, g);
	}
	if (((i+1)<l)&&((j+1)<c))
	{
		v+= est_vivante (i+1, j+1, g);
	}
	return v;
}	

int (*Ptr_compte_voisins_vivants)(int, int, grille)=compte_voisins_vivants; // Pointeur sur la fonction compte_voisins_vivants

/** @brief Fonction qui permet de désactiver ou d'activer le mode cyclique
**/

void active_cyclique()
{
	if (Ptr_compte_voisins_vivants==compte_voisins_vivants)
	{
		Ptr_compte_voisins_vivants=compte_voisins_vivants2;
	}
	else{
		Ptr_compte_voisins_vivants=compte_voisins_vivants;
	}
}

/** @brief Fonction qui active le vieillissement des cellules
@param i Numéro de la ligne de la grille
@param j Numéro de la colonne de la grille
@param g Pointeur sur la grille
**/

void active_v(int i, int j, grille* g)
{
        g->cellules[i][j]++;
	if (g->cellules[i][j]==8)
	{
		g->cellules[i][j]=0;
	}
}

/** @brief Fonction qui desactive le vieillissement des cellules
@param i Numéro de la ligne de la grille
@param j Numéro de la colonne de la grille
@param g Pointeur sur la grille
**/

void no_active_v(int i, int j, grille* g)
{
        g->cellules[i][j]=1;
}

void (*vieillissement)(int, int, grille*)=no_active_v; //Pointeur sur la fonction no_active_v

/** @brief Fonction qui permet d'activer ou de désactiver le vieillissement des cellules **/

void calcul_vieillissement(){
        if(vieillissement==no_active_v)
        {
                vieillissement=active_v;
        }
        else
        {
                vieillissement=no_active_v;
        }
}


/** @brief Fonction qui fait évoluer la grille g d'un pas de temps
@param g Pointeur sur la grille
@param gc Pointeur sur la copie de la grille
**/

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = Ptr_compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 )
				{
					set_morte(i,j,*g);
				}
				else if((v==2)||(v==3))
				{
					vieillissement(i, j, g);
				}
				
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 )
				{
					if(est_non_viable(i,j,*g))
					{
						set_non_viable(i,j,*g);
					}
					else
					{
						set_vivante(i,j,*g);
					}
				}
				
			}
		}
		
	}
	return;
}

void test(grille* g, grille* gc)
{
	char touche;
	touche=getchar();
	grille* gb;
	grille* gi;
	int i,j,l=g->nbl, c = g->nbc,test=0, t=0;
	alloue_grille(l,c, gb);
	copie_grille(*g,*gb);
	alloue_grille(l,c, gi);
	copie_grille(*g,*gi);
	while((touche!="q")||(test!=1))
	{
		for (i=0; i<g->nbl; i++)
		{
			for(j=0; j<g->nbc;j++)
			{
				if(t>=1)
				{
					test=comparer_grilles(g, gc);
				}
				if(t>=1)
				{
					test=comparer_grilles(g, gb);
				}
			}	
		}
		evolue(g, gi);
		copie_grille (*g,*gc);
		t++;
		touche=getchar();
	}
	libere_grille(gc);
	libere_grille(gb);
	libere_grille(gi);
	if (test)
	{
		printf("La colonie est osccillante et sa période est %d\n", t);
	}
	else
	{
		printf("La colonie n'est pas oscillante\n");
	}
}
				
	

