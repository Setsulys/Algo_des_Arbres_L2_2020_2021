#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct celmot{
	char *mot;
	int nombre;
	struct celmot *suivant;
}CelluleM,*ListeM;

typedef struct hashtable{
	int N;
	int nbMots;
	ListeM *tableau;
}HashTable,*Dico;

Dico creeDico(int n){
	int i;
	Dico tmp=NULL;

	tmp=(HashTable *)malloc(sizeof(HashTable));/*tmp=(Dico)malloc(sizeof(HashTable))*/
	if(NULL==tmp)
		return tmp;
	tmp->N=n;
	tmp->nbMots=0;
	tmp->tableau=(ListeM *)malloc(n*sizeof(ListeM));/*alloue la place necessaire pour avoir n listes chainnées dans le tableau*/
	for(i=0;i<n;i++)
		tmp->tableau[i]=NULL;/*inintialisation des listes a null*/	
	return tmp;
}

ListeM alloueCellule(char mot[],int nb){
	ListeM tmp=NULL;
	int i, len=strlen(mot);

	tmp=(CelluleM *)malloc(sizeof(CelluleM));
	if(NULL==tmp)
		return tmp;
	tmp->nombre=nb;
	tmp->suivant=NULL;
	tmp->mot=(char*)malloc((len+1)*sizeof(char));
	if(NULL==tmp->mot)
		return NULL;
	for(i=0;i<len;i++)
		tmp->mot[i]=mot[i];
	tmp->mot[len]='\0';
	return tmp;
}

int ajouteListe(ListeM *L,char mot[],int nb){
	ListeM cell, tmp= *L;
	int cpt=0;
	
	if(tmp==NULL){
		*L=alloueCellule(mot,nb);
		return 1;
	}
	else{
		cpt=strcmp(tmp->mot,mot);
		if(cpt==0){
			tmp->nombre+=nb;
			return 0;
		}
		else if(cpt<0){
			return ajouteListe(&(tmp->suivant),mot,nb);
		}
		else{
			cell=alloueCellule(mot,nb);
			cell->suivant=tmp;
			*L=cell;
			return 1;
		}
	}
}

int hachage(int N,char word[]){
	int n = strlen(word);
	int i, somme = 0;

	for(i=0; i < n; i++){
		somme += (i+ 1)*word[i];
	}

	return somme % N;
}

int rechercheDico(Dico dico, char mot[]){
	int i = Hachage(mot);
	Dico tmp = dico;
	while(tmp != NULL){
		if(strcmp(tmp->mot, mot) == 0)
			return tmp->nombre;
		tmp = tmp->suivant;
	}
	return 0;
}

void ajouteDico(Dico dico,char mot[],int nb){
	int i=hachage(mot);
	if(ajouteListe(&dico->tableau[i],mot,nb)==1)
		return 1;
	return 0;
}

int nombreMots(Dico dico){
	Dico tmp=NULL;
	int i,total=0;
	for(i=0;i<tmp->nbMots;i++){
		if(tmp->tableau[i]==NULL)
			continue;
		tmp=tmp->tableau[i];
		while(tmp!=NULL){
			total +=tmp->nbMots;
			tmp->tableau->suivant;
		}
	}
}

int main(int argc, char const *argv[]){
	/*int n=5;
	HashTable a;

	creeDico(n);
	alloueCellule("bonjour",5);

	printf("%d\n",(a).N);*/
	return 0;
}