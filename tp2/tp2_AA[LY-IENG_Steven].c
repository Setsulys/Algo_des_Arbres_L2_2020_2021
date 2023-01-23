#include <stdio.h>
#include <stdlib.h>

typedef struct noeud{
int valeur;			//etiquette du noeud
struct noeud *fg; 	//adresse du fils gauche
struct noeud *fd;	//adresse du fils droit
}Noeud,*Arbre;


//1 creation d'arbres à la main

Arbre alloueNoeud(int val){
	Arbre tmp;
	if((tmp=(Noeud*)malloc(sizeof(Noeud)))!=NULL){
		tmp->valeur=val;
		tmp->fg=NULL;
		tmp->fd=NULL;
	}
	return tmp;
}

int max(int a, int b){
	if (a<b)
		return b;
	else
		return a;
}

//Fonctions de mesures d'arbre
//a hauteur
int hauteur(Arbre a){
	if(a==NULL)
		return -1;
	else
		return 1+max(hauteur(a->fg),hauteur(a->fd));
}
//b nombre de noeud
int compte_noeud(Arbre a){
	if(a==NULL)
		return 0;
	else
		return 1+compte_noeud(a->fg)+compte_noeud(a->fd);
}
//c nombre de noeud interne non fini
int compte_noeud_interne(Arbre a){
	int x=1;
	if(a==NULL)
		return 0;
	else{
		if(a->fg==NULL && a->fd==NULL)
			x=0;
	}
	return x+compte_noeud_interne(a->fg)+compte_noeud_interne(a->fd);
}
//d nombre de feuilles
int compte_feuille(Arbre a){
	if(a==NULL)
		return 0;
	if(a->fg==NULL && a->fg==NULL)
			return 1;
	return compte_feuille(a->fg)+compte_feuille(a->fd);
}
//e nombre de noeud interne a exactement deux fils
int deux_fils(Arbre a){//binaire
	int nb_noeud=0;
	if(a==NULL)
		return 0;
	else if (a->fg==NULL||a->fd==NULL)
		return 0;
	else
		return 1;
}

int main(){
	int valeur;
	//creation de l'arbre
    Arbre a=alloueNoeud(1);
    a->fg = alloueNoeud (1) ;
	a->fg->fg = alloueNoeud (11) ;
	a->fg->fd = alloueNoeud (11) ;
	a->fd = alloueNoeud (21) ;
	a->fd->fd = alloueNoeud (42) ;
	a->fd->fd->fd = alloueNoeud (15) ;

	valeur=hauteur(a);
	printf("La hauteur de l'arbre est de : %d\n ",valeur);
	valeur=compte_noeud(a);
	printf("Le nombre de noeud est de %d\n",valeur);
    valeur=compte_noeud_interne(a);
    printf("Le nombre de noeud interne est de : %d\n",valeur);
    valeur=compte_feuille(a);
    printf("Le nombre de feuile est de : %d\n",valeur);
    valeur=deux_fils(a);
    printf("Le nombre de noeud internes a deux fils est de : %d\n",valeur);
	


	return 0;
}


