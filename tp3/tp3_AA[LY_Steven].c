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

/*-------Exercice 1 Arbres binaires de recherche-------*/
	/*-----1a-----*/
		Arbre recherche(Arbre a, int n){
			if(a==NULL){
				return NULL;
			}
			else if(a->valeur == n){
				return a;
			}
			if(a->valeur > n){
				return recherche(a->fg,n);
			}
			return recherche(a->fd,n);
		}

	/*-----1b-----*/
		void ajout(Arbre *a, int n){
			if(*a ==NULL){
				*a=alloueNoeud(n);
			}
			else if((*a)->valeur < n){
				ajout(&((*a)->fd),n);
			}
			else if((*a)->valeur > n){
				ajout(&((*a)->fg),n);
			}
			else{
				return;
			}
		}
	/*-----1c-----*/
		Arbre extraitMin(Arbre *a){
			Arbre tmp;
			if(*a==NULL){
				return NULL;
			}
			if(((*a)->fg) == NULL){
				tmp=(*a);
				(*a)=(*a)->fd;
				return	tmp;
			}
			return extraitMin(&((*a)->fg));
		}
	/*-----1d-----*/
		Arbre extraitMax(Arbre *a){
			Arbre tmp;
			if(*a==NULL){
				return NULL;
			}
			if(((*a)->fd) == NULL){
				tmp=(*a);
				(*a)=(*a)->fg;
				return	tmp;
			}
			return extraitMax(&((*a)->fd));
		}
	/*-----1e-----*/
		Arbre extrait(Arbre *a,int n){
			Arbre tmp;
			if(*a==NULL){
				return NULL;
			}
			if(((*a)->valeur) > n){
				return extrait(&((*a)->fg));
			}
			if(((*a)->valeur) < n ){
				return extrait(&((*a)->fd));
			}
			if(((*a)->valeur) == n){
				if(((*a)->fg) == NULL && ((*a)->fd) == NULL){
					tmp=(*a);
					(*a)=NULL;
				}
				else if(((*a)->fg) ==NULL){
					tmp=(*a);
					(*a)=extraitMin(&((*a)->fd));
				}
				else{
					tmp=(*a);
					(*a)=extraitMax(&((*a)->fg));
				}
				return tmp;
			}
			return NULL;
		}

/*-------Exercice 2 Verification-------*/

	int Verification(Arbre a){
		if(a==NULL){
			return 1;
		}
		if(a->fg < a){
			return Verification(a->fg);
		}
		if(a->fd > a){
			return Verification(a->fd);
		}
		if(a->fd < a || a->fg > a){
			return 0;
		}
	}






int main(int argc, char const *argv[]){
	Arbre a=NULL;
	int n=5;

	while(n>=0){
		printf("inserer une valeur :\n");
		scanf("%d",&n);
		if(n>=0)
			ajout(&a,n);
	}
	n=0;
	scanf(" %2d",&n);
	if(recherche(a,n)==NULL)
		printf("NULL\n");
	else
		printf("present\n");


	extrait(&a,n);
	return 0;
}