#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct noeud{
    int valeur; /* étiquette du nœud */
    struct noeud *fg; /* adresse du fils gauche */
    struct noeud *fd; /* adresse du fils droit */
} Noeud, *Arbre;


Arbre alloueNoeud(int val) {
    Arbre tmp;
    tmp = (Noeud*)malloc(sizeof(Noeud));
    if (tmp != NULL) {
        tmp->valeur = val;
        tmp->fg = NULL;
        tmp->fd = NULL;
    }
    return tmp;
}

void AfficheArbre(Arbre a) {
    if (a == NULL) {
        printf("0 ");
    }
    else {
        printf("%d ", a->valeur);
        AfficheArbre(a->fg);
        AfficheArbre(a->fd);
    }
}

void construitArbreQuelconque(Arbre *a) {
    int val;
    printf("Selectionnez la relation:");
    scanf("%d", &val);
    if(val == 0) {
        printf("0, Selectionnez l'etiquette:");
        scanf("%d", &val);
        *a = alloueNoeud(val);
    }
    else if(val == 1) {
        printf("1, Selectionnez l'etiquette:");
        scanf("%d", &val);
        *a = alloueNoeud(val);
        if(*a != NULL)
            construitArbreQuelconque(&(*a)->fd);
    }
    else if(val == 2) {
        printf("2, Selectionnez l'etiquette:");
        scanf("%d", &val);
        *a = alloueNoeud(val);
        if(*a != NULL)
            construitArbreQuelconque(&(*a)->fg);
    }
    else if(val == 3) {
        printf("3, Selectionnez l'etiquette:");
        scanf("%d", &val);
        *a = alloueNoeud(val);
        if(*a != NULL) {
            construitArbreQuelconque(&(*a)->fg);
            construitArbreQuelconque(&(*a)->fd);
        }
    }
}

void ecrireDebut(FILE *f) {
	fprintf(f, "digraph arbre { \n");
	fprintf(f, "	node [shape = record , height = .1]; \n");
	fprintf(f, "	edge [tailclip = false, arrowtail = dot, dir = both ]; \n");
}


void ecrireArbre(FILE *f, Arbre a) {
	if (a != NULL) {
		fprintf(f, "	n%p [label=\"<gauche> | <valeur> %d | <droit>\"];\n", a, a->valeur);
		if ((a->fg) != NULL) {
			fprintf(f, "	n%p: gauche:c -> n1: valeur; \n", a);
			ecrireArbre(f, a->fg);
		}
		if ((a->fd) != NULL) {
			fprintf(f, "	n%p: droit:c ->n1: valeur; \n", a);
			ecrireArbre(f, a->fd);
		}
	}
}

void ecrireFin(FILE *f) {
	fprintf(f, "}");
}

void dessine(FILE *f, Arbre a) {
	ecrireDebut(f);
	ecrireArbre(f, a);
	ecrireFin(f);
}

void creePDF (char * dot, char * pdf, Arbre a ) {
	FILE * out = fopen (dot, "w") ;
	dessine (out, a) ;
	fclose (out) ;
	int len = strlen (dot) + strlen (pdf) + 15;
	char cmd [len];
	strcpy (cmd, "dot  -Tpdf  ") ;
	strcat (cmd, dot) ;
	strcat (cmd, " -o ") ;
	strcat (cmd, pdf) ;
	system (cmd) ;
}

int main(int argc, char* argv[]){
    Arbre a;
    construitArbreQuelconque(&a);
    FILE * file = fopen(argv[1], "w");
    AfficheArbre(a);
	dessine(file, a);
	return 0;
}
		
			

		
