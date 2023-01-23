#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 20


typedef	struct celmot{
	char *mot;
	int nombre;
	struct celmot *suivant;
}CelluleM, *ListeM;

ListeM Allouecellule(char Mot[]){
	ListeM tmp=NULL;
	tmp=(celmot *)malloc(sizeof(celmot));
	if(NULL!=tmp){
		tmp->mot=Mot;
		tmp->nombre=1;
		tmp->suivant=NULL;
	}
	return tmp;
}

int AjouteListe(ListeM *L,char Mot[]){
	ListeM tmp= *L;
	while(tmp!=NULL){
		if(tmp->mot==Mot){
			tmp->nombre+=1;
			return 1;
		}
		tmp=tmp->suivant;
	}
	tmp=(Allouecellule(Mot));/*creation de la cellule suivante */
	if (tmp != NULL){ 
		tmp->suivant = tmp;
		return 1;
	}
	return 0;
}

unsigned int Hachage(char Mot[]){
	int n = strlen(Mot);
	int i, somme = 0;

	for(i=0; i < n; i++){
		somme += (i+ 1)*Mot[i];
	}

	return somme % N;
}

int RechercheDico(ListeM T[], char Mot[]){
	int i = Hachage(Mot);
	ListeM tmp = T[i];
	while(tmp != NULL){
		if(strcmp(tmp->mot, Mot) == 0){
			return tmp->nombre;
		}
		else if(strcmp(tmp->mot, Mot) > 0){
			return 0;
		}
		tmp = tmp->suivant;
	}
	return 0;
}

int AjouteDico(ListeM T[], char Mot[]){
	int i = Hachage(Mot);
	if(AjouteListe(&(T[i]), Mot) == 1)
		return 1;
	return 0; 
}

int NombreMot(ListeM T[]){
	ListeM tmp = NULL;
	int i, total = 0;
	for(i=0; i< N; i++){
		if(T[i] == NULL){
			continue;
		}
		tmp = T[i];
		while(tmp != NULL){
			total += tmp->nombre;
			tmp = tmp->suivant;
		}
	}
	return total;
}

int main(){
	ListeM *L;
	ListeM T[N];
	char Mot [N];

	scanf("%50s",Mot);
	AjouteListe(L,Mot);
	Hachage(Mot);
	RechercheDico(T,Mot);
	AjouteDico(T,Mot);
	NombreMot(T);
	return 0;
}