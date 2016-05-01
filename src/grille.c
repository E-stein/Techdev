#include "grille.h"

/** @file grille.c
@brief Ensembles de fonction pour créer ou modifier une grille
@date 28/04/2016
**/

/** @brief Fonction qui alloue et initialise une grille à partir d'un fichier
@param filename Nom du fichier
@param g Pointeur sur la grille
**/
 
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, non_viables=0,m,p,k;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
 	fscanf(pfile, "%d", &non_viables);
        for(m=0; m<non_viables;m++)
        {
                fscanf(pfile,"%d", &k);
                fscanf(pfile, "%d", &p);
                set_non_viable(k,p,*g);
        }	
	fclose (pfile);
	return;
}

/** @brief Fonction qui recopie une grille dans une autre grille sans allocation de mémoire
@param gs Grille à recopier
@param gd Grille où l'on effectue le copiage
**/

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/** @brief Fonction qui alloue une grille de taille l*c et initialise toutes les cellules à mortes
@param l Nombre de lignes
@param c Nombre de colonnes
@param g Pointeur sur la grille
**/

void alloue_grille (int l, int c, grille* g)
{
	int i, j;
	g->nbl=l;
	g->nbc=c;
	g->cellules=malloc(l*sizeof(int*));
	for(i=0;i<l;i++)
	{
		g->cellules[i]=malloc(c*sizeof(int));
	}
	for(i=0;i<l;i++)
	{
		for(j=0;j<c;j++)
		{
			g->cellules[i][j]=0;
		}
	}
}

/** @brief Fonction qui libère une grille
@param g Pointeur sur la grille
**/

void libere_grille (grille* g)
{
	int i;
	for(i=0;i<g->nbl;i++)
	{
		free(g->cellules[i]);
	}
	free(g->cellules);
}

