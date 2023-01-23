#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud_avl {
	unsigned int valeur ;
	int hauteur ;
	struct noeud_avl * fg , * fd ;
} NoeudAVL , * AVL;


int max(int a, int b){
	if(a>b){
		return b;
	}
	return a;
}


/*-------------Allocation de noeuds-------------*/
	NoeudAVL *alloue_noeud(int valeur) {
	    NoeudAVL *result = (NoeudAVL *) malloc(sizeof(NoeudAVL));
	    if(result == NULL) {
	        printf("Allocation Erroné\n");
	        return NULL;
	    }
	    result->fg = NULL;
	    result->fd = NULL;
	    result->hauteur = 0;
	    result->valeur = valeur;
	    return result;
	}

/*-------------hauteur-------------*//*Exo 1*/
	int hauteur(AVL avl){
		if(NULL == avl){
			return -1;
		}
		return avl->hauteur;
	}

/*-------------balance-------------*//*Exo 2*/
	int balance(AVL avl){
		if(NULL == avl){
			return 0;
		}
		return hauteur(avl->fd) - hauteur(avl->fg);
	}

/*-------------dot-------------*//*Exo 3*/
	void affiche_prefix(AVL avl){
	    if (avl != NULL){
	        printf("%d\n", avl->valeur);
	        affiche_prefix(avl->fg);
	        affiche_prefix(avl->fd);
	    }
	}

	void ecrireDebut(FILE *f){
		fprintf(f, "digraph arbre {\n");
		fprintf(f, "\tnode [shape = record, height = .1]\n");
		fprintf(f, "\tedge [tailclip = false, arrowtail = dot, dir = both];\n\n");
	}

	void ecrireArbre(FILE *f, AVL avl){
		if (avl != NULL){
			if(balance(avl)!=1 &&balance(avl)!=0&& balance(avl)!=1){
				fprintf(f, "\tn%p [style=filled , fillcolor=yellow , label =\"<gauche > | H:%d| <valeur > %d | B:%d| <droit >\"];\n", (void *) avl, hauteur(avl), avl->valeur, balance(avl));
			}
			fprintf(f, "\tn%p [label =\"<gauche > | H:%d| <valeur > %d | B:%d|<droit >\"];\n", (void *) avl, hauteur(avl), avl->valeur, balance(avl));
			
			if (avl->fg != NULL){
				fprintf(f, "\tn%p: gauche : c -> n%p: valeur ;\n", (void *) avl, (void *) avl->fg);
				ecrireArbre(f, avl->fg);
			}
			if (avl->fd != NULL){
				fprintf(f, "\tn%p: droit : c -> n%p: valeur ;\n", (void *) avl, (void *) avl->fd);
				ecrireArbre(f, avl->fd);
			}
		}
	}

	void ecrireFin(FILE *f){
		fprintf(f, "}");
	}

	void dessine(FILE *f, AVL avl){
		ecrireDebut(f);
		ecrireArbre(f, avl);
		ecrireFin(f);
	}

	void creePDF(char *dot, char *pdf, AVL avl){
		FILE *out = fopen(dot, "w");
		int len = strlen(dot) + strlen(pdf) + 15;
		char cmd[len];

		dessine(out, avl);
		fclose(out);

		strcpy(cmd, "dot -Tpdf ");
		strcat(cmd, dot);
		strcat(cmd, " -o ");
		strcat(cmd, pdf);

		system(cmd);
	}

	void afficheAVL(AVL avl){
		FILE * out;
		affiche_prefix(avl);
		printf("\n");

		out = fopen("pdf/fichier_annexe/monfichier.dot", "w");
		dessine(out, avl);

		/* exercice 3 */
		creePDF("pdf/fichier_annexe/visualise_tp9.dot", "pdf/visualise_tp9.pdf", avl);
	}

/*-------------Rotations-------------*//*Exo 4*/
	void maj_hauteur(AVL *avl){
		int hg = hauteur((*avl)->fg);
		int hd = hauteur((*avl)->fd);
		(*avl)->hauteur = 1 + max(hg,hd);
	}

	void RotationGauche(AVL * avl){
		AVL a =(*avl);
		AVL b = a->fd;
		AVL c = b->fg;
		b->fg = a;
		a->fd = c;
		(*avl) = b;
		maj_hauteur(&a);
		maj_hauteur(&b);
	}

		void RotationDroite(AVL * avl){
		AVL a =(*avl);
		AVL b = a->fg;
		AVL c = b->fd;
		b->fd = a;
		a->fg = c;
		(*avl) = b;
		maj_hauteur(&a);
		maj_hauteur(&b);
	}

	void RotationDoubleDroiteGauche(AVL* avl) {
	    RotationDroite(&(*avl)->fd);
	    RotationGauche(avl);
	}
	void RotationDoubleGaucheDroite(AVL* avl) {
	    RotationGauche(&(*avl)->fg);
	    RotationDroite(avl);
	}

/*-------------insertion-------------*//*Exo5*/
	void equilibrer(AVL *avl){
		if(NULL != avl){
			if(balance(*avl) == 2){
				if(balance((*avl)->fg) == -1){
					RotationDoubleGaucheDroite(avl);
				}
				else{
					RotationDroite(avl);
				}
			}
			else if(balance(*avl)== -2){
				if(balance((*avl)->fd) == 1){
					RotationDoubleDroiteGauche(avl);
				}
				else{
					RotationGauche(avl);
				}
			}
			else{
				return;
			}
		}
		return;
	}


	int inserer(AVL* avl, unsigned int x){

		if((*avl)==NULL){
			(*avl)=alloue_noeud(x);
			return 1;
		}
		else if((*avl)->valeur == x){
			return 0;
		}
		else if(x < (*avl)->valeur){
			inserer(&((*avl)->fg),x);
			equilibrer(avl);
		}
		else if(x > (*avl)->valeur){
			inserer(&((*avl)->fd),x);
			equilibrer(avl);
		}

	}

/*-------------test insertion------------*//*Exo6*/
	void test_inserer_2(AVL avl,AVL avl2,AVL avl3, AVL avl4){
		/*rotation gauche*/
		inserer(&avl,1);
		inserer(&avl,2);
		inserer(&avl,5);
		afficheAVL(avl);
		/*rotation droite*/
		inserer(&avl2,6);
		inserer(&avl2,4);
		inserer(&avl2,3);
		afficheAVL(avl2);
		/*rotation droite gauche*/
		inserer(&avl3,1);
		inserer(&avl3,5);
		inserer(&avl3,2);
		afficheAVL(avl2);
		/*rotation gauche droite*/
		inserer(&avl4,10);
		inserer(&avl4,5);
		inserer(&avl4,8);
		afficheAVL(avl2);
	}


/*-------------Suppression------------*//*Exo7*/



int main(int argc, char const *argv[]){

	AVL avl = NULL;
	AVL avl1, avl2, avl3, alv4;
	avl = alloue_noeud(13);
	avl->hauteur = 4;
	avl->fd = alloue_noeud(15);
	avl->fg = alloue_noeud(8);
	avl->fg->hauteur = 3;
	avl->fg->fd = alloue_noeud(10);
	avl->fg->fd->hauteur = 2;
	avl->fg->fd->fg = alloue_noeud(9);
	avl->fg->fd->fd = alloue_noeud(11);
	avl->fg->fd->fd->hauteur =1;
	avl->fg->fd->fd->fd = alloue_noeud(12);

	printf("hauteur : %d\n",hauteur(avl));
	printf(" balance : %d\n",balance(avl));
	afficheAVL(avl);
	printf("------------------\n");
	printf("------------------\n");
	inserer(&avl, 5);
	test_inserer_2(avl1,avl2,avl3,avl4);
	
	return 0;
}





/*	void RotationGauche(AVL *avl) {
	    AVL b; 
	    int i,j;
	    b = (*avl)->fd; 
	    (*avl)->fd = b->fg; 
	    b->fg = *avl;
	    i = balance((*avl)); 
	    j = balance((*avl));
	    if(j >= 0) {
	        (*avl)->hauteur = i - j - 1;
	    } else {
	        (*avl)->hauteur = i - 1;
	    }
	    if((*avl)->hauteur <= 0) {
	        b->hauteur = j + (*avl)->hauteur - 1;
	    } else {
	        b->hauteur = j - 1;
	    }
	    *avl = b;
	    maj_hauteur(avl);
	}

	void RotationDroite(AVL *avl) {
	    AVL b; 
	    int i,j;
	    b = (*avl)->fg; (*avl)->fg = b->fd; b->fd = *avl;
	    i = balance((*avl)); j = balance((*avl));
	    if(j >= 0) {
	        (*avl)->hauteur = i - j - 1;
	    } else {
	        (*avl)->hauteur = i - 1;
	    }
	    if((*avl)->hauteur <= 0) {
	        b->hauteur = j + (*avl)->hauteur - 1;
	    } else {
	        b->hauteur = j - 1;
	    }
	    *a = b;
	    maj_hauteur(a);
	}*/