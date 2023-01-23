#include <stdio.h>
#include <stdlib.h>

typedef struct noeud{
int valeur;			/*etiquette du noeud*/
struct noeud *fg; 	/*adresse du fils gauche*/
struct noeud *fd;	/*adresse du fils droit*/
}Noeud,*Arbre;

/*Exercice 1*/

Arbre alloueNoeud(int val){
	Arbre tmp= (Noeud*)malloc(sizeof(Noeud));
	if(tmp==NULL){
		return tmp;
	}
	tmp->valeur=val;
	tmp->fg=NULL;
	tmp->fd=NULL;
	return tmp;
}

/*Exercice 2*/
/*-----a----*/
int max(int a, int b){
	if (a<b){
		return b;
	}
	else{
		return a;
	}
}

int hauteur(Arbre a) {
	if (NULL == a){
    	return -1;
	}
	return 1 + max(hauteur(a->fg), hauteur(a->fd));
}

/*-----b----*/
int nb_noeuds(Arbre a){
	if(NULL == a){
    	return 0;
	}
	return 1 + nb_noeuds(a->fg) + nb_noeuds(a->fd);
}

/*-----c----*/
int nb_noeuds_internes(Arbre a){
	int interne;

	if(NULL==a){
		return 0;
	}
  	if (a->fg == NULL && a->fd == NULL) {
    	interne = 0;
  	} 
  	else {
    	interne = 1;
  	}
  	return interne + nb_noeuds_internes(a->fg) + nb_noeuds_internes(a->fd);
}

/*-----d----*/
int nb_feuilles(Arbre a){
	if(NULL==a){
		return 0;
	}
	if(a->fg == NULL && a->fd == NULL){
		return 1;
	}
	return nb_feuilles(a->fg) + nb_feuilles(a->fd); 
}

/*-----e----*/
int nb_noeuds_internes_deux_fils(Arbre a){
	int interne = 0;

	if(NULL==a){
		return 0;
	}
	if(NULL != a->fg && NULL != a->fd){
		interne = 1;
	}
	return interne + nb_noeuds_internes_deux_fils(a->fg) + nb_noeuds_internes_deux_fils(a->fd);
}

/*Exercice 3*/

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

int reconstruire_arbre_fichier(Arbre *a, char fichier[]){
    FILE *fichier;
	fichier = fopen(fichier, "r");

    if (fichier != NULL){
        *a = construitArbre(fichier);
        return 1;
    }
    return 0;
}

int verifierSub(Arbre a, int * min, int * max)
{
  int fgMax, fdMax, fgMin, fdMin;
  
  if (NULL == a) {
    return 1;
  }
  
  if (NULL != a->fg) {
    if (0 == verifierSub(a->fg, &fgMin, &fgMax))
      return 0;
    
    if (a->valeur <= fgMax)
      return 0;
  }
  
  if (NULL != a->fd) {
    if (0 == verifierSub(a->fd, &fdMin, &fdMax))
      return 0;
    
    if (a->valeur >= fdMin)
      return 0;
  }
  
  *min = (NULL != a->fg) ? fgMin : a->valeur;
  *max = (NULL != a->fd) ? fdMax : a->valeur;
  return 1;
}

int verifier(Arbre a)
{
  int min, max;
  
  return verifierSub(a, &min, &max);
}

/*Exercice 4*/

Arbre alloueNoeudd(int val){
	Arbre tmp= (Noeud*)malloc(sizeof(Noeud));
	if(tmp==NULL){
		return tmp;
	}
	tmp->valeur=val;
	tmp->fd=NULL;
	return tmp;
}

Arbre alloueNoeudg(int val){
	Arbre tmp= (Noeud*)malloc(sizeof(Noeud));
	if(tmp==NULL){
		return tmp;
	}
	tmp->valeur=val;
	tmp->fg=NULL;
	return tmp;
}


Arbre construitArbreQuelconque(FILE*in){
	int *i;
	int token;
	int *tokendiection;
	
	while(token != EOF){
		token= fgetc(in);
		if((*i)%2!=0){
			(*tokendiection)=&token;
			(*i)++;
			construitArbreQuelconque(in);
		}
		else{
			if(tokendiection==1){
				alloueNoeudd(token);
				(*i)++;
				construitArbreQuelconque(in);

			}
			else if( tokendiection==2){
				alloueNoeudg(token);
				(*i)++;
				construitArbreQuelconque(in);

			}
			else{
				alloueNoeud(token);
				(*i)++;
				construitArbreQuelconque(in);
			}
		}
	}
}




int main(){
	
	Arbre a = alloueNoeud(1);
	Arbre b = alloueNoeud(5);
	/*Exemple 1*/
	a->fg = alloueNoeud(2);
	a->fg->fd = alloueNoeud(42);

	/*Exemple 2*/
	b->fg = alloueNoeud(1);
	b->fg->fg = alloueNoeud(11);
	b->fg->fd = alloueNoeud(11);
	b->fd = alloueNoeud(21);
	b->fd->fd = alloueNoeud(42);
	b->fd->fd->fd = alloueNoeud(15);


	hauteur(a);
	nb_noeuds(a);
	nb_noeuds_internes(a);
	nb_feuilles(a);
	nb_noeuds_internes_deux_fils(a);

	hauteur(b);
	nb_noeuds(b);
	nb_noeuds_internes(b);
	nb_feuilles(b);
	nb_noeuds_internes_deux_fils(b);

	/*free*/
	free(a);
	free(a->fg);
	free(a->fg->fd);

	free(b);
	free(b->fg);
	free(b->fg->fg);
	free(b->fg->fd);
	free(b->fd);
	free(b->fd->fd);
	free(b->fd->fd->fd);
	return 0;
}
