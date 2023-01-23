#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud{
int valeur;			/*etiquette du noeud*/
struct noeud *fg; 	/*adresse du fils gauche*/
struct noeud *fd;	/*adresse du fils droit*/
}Noeud,*Arbre;


Arbre alloueNoeud(int val){
	Arbre tmp;
	if((tmp=(Noeud*)malloc(sizeof(Noeud)))!=NULL){
		tmp->valeur=val;
		tmp->fg=NULL;
		tmp->fd=NULL;
	}
	return tmp;
}

Arbre construitArbre(FILE* fichier){
    int val;
    Arbre a;
    
    fscanf(fichier, "%d", &val);
    if (val != 1){
        return NULL;
    }
    if (val == 0)
        return NULL;
    a = alloueNoeud(val);
    if (a == NULL)
        return NULL;

    a->fg = construitArbre(fichier);
    a->fd = construitArbre(fichier);

    return a;
}

int reconstruire_arbre_fichier(Arbre *a, char nomfichier[]){
    FILE *fichier;
	fichier = fopen(nomfichier, "r");

    if (fichier != NULL){
        *a = construitArbre(fichier);
        return 1;
    }
    return 0;
}

void ecrireDebut(FILE*out){
	fprintf(out,"digraph arbre {\n");
	fprintf(out,"\tnode [ shape = record , height = .1 ] \n");
	fprintf(out,"\tedge [ tailclip = false , arrowtail = dot , dir = both ];\n\n");
}


void ecrireArbre(FILE *out, Arbre a) {
	if (a != NULL) {
		fprintf(out, "	n%p [label=\"<gauche> | <valeur> %d | <droit>\"];\n", a, a->valeur);
		if ((a->fg) != NULL) {
			fprintf(out, "	n%p: gauche:c -> n%p: valeur; \n", a,a->fg);
			ecrireArbre(out, a->fg);
		}
		if ((a->fd) != NULL) {
			fprintf(out, "	n%p: droit:c ->n%p: valeur; \n", a,a->fd);
			ecrireArbre(out, a->fd);
		}
	}
}

void ecrireFin(FILE*out){

	fprintf(out,"}");
}


void dessine(FILE*out,Arbre a){
	ecrireDebut(out);
	ecrireArbre(out,a);
	ecrireFin(out);
}

void creePDF(char*dot,char*pdf,Arbre a){
	FILE*out=fopen(dot,"w");
	dessine(out,a);
	fclose(out);
	int len =strlen(dot)+strlen(pdf)+15;
	char cmd[len];

	strcpy (cmd,"dot -Tpdf ");
	strcat (cmd,dot);
	strcat (cmd," -o ");
	strcat (cmd,pdf);
	system(cmd);
}

int main(){
	Arbre a=NULL;

	creePDF("affiche.dot","affichage.pdf",a);
	return 0;
}