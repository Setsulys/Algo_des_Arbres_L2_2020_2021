#include <stdio.h>

#define NBLETTRES 256
#define NBNOEUDS (NBLETTRES*2+1)

typedef struct{
	unsigned char lettre;
	int occur;
	int fg;
	int fd;
}Noeud;

typedef struct {
	int taille;
	char *code;
}Code;

/*-------------1-------------*/
	int compare_noeud(const void * ptr1, const void * ptr2){
	    Noeud p = * ((Noeud *) ptr1);
	    Noeud q = * ((Noeud *) ptr2);
	    return p.occur - q.occur;
	}

	int compteLettre(FILE*in,Noeud tab[]){
		int i,nb;
		char c;
		nb=0;

		for(i=0;i<NBLETTRES;i++){
			tab[i].lettre=(char)i;
			tab[i].occur=0;
			tab[i].fg=-1;
			tab[i].fd=-1;
		}
		while((c=fgetc(in))!=EOF){
			i=(int)c;
			tab[i].occur++;
			if(tab[i].occur == 1){
				nb++;
			}
		}
		qsort(tab,256,sizeof(Noeud),compare_noeud);
		return Nb;
	}


	void afficheTab(Noeud tab[]){
		int i;
		for (int i = 0; i < NBLETTRES; i++){
			printf("lettre : %d| occurence : %d",tab[i].lettre,tab[i].occurence);
		}
	}

/*-------------2-------------*/
	int plusPetit(Noeud tab[], int *prem_feuille, int *prem_noeud, int noeud_libre){
		int pluspetit = 0;
		if (*prem_feuille == NBLETTRES){ /*cas ou toutes les feuilles ont un parent*/
			pluspetit = *prem_noeud;
			*prem_noeud = pluspetit++;
			return pluspetit;
		}
		else if (*prem_feuille == noeud_libre){ /*cas ou tout les noeuds ont un parent*/
			pluspetit = *prem_feuille;
			*prem_feuille = pluspetit +1;
			return pluspetit;
		}
		else if (tab[*prem_feuille].occur < tab[*prem_noeud].occur){
			pluspetit = *prem_feuille;
			*prem_feuille = pluspetit +1;
			return pluspetit;
		}
		else{
			pluspetit = *prem_noeud;
			*prem_noeud = pluspetit++;
			return pluspetit;
		}
	}

	int construitArbre(Noeud tab[],int taille){
		int i,fg,fd;
		int prem_feuille = 251;
		int prem_noeud = NBLETTRES;
		int noeud_libre = NBLETTRES;

		for(i = 0; i < taille; i++ ){
			fg=plusPetit(tab,&prem_feuille,&prem_noeud,noeud_libre);
			fd=plusPetit(tab,&prem_feuille,&prem_noeud,noeud_libre);
			tab[noeud_libre].fd=fd;
			tab[noeud_libre].fg=fg;
			tab[noeud_libre].occur =tab[fd].occur +tab[fg].occur;
			noeud_libre++;
		}
		return noeud_libre-1;
	}

/*-------------3-------------*/
	void construitCodeAux(Noeud arbre[], Code traduction[], char code[], int racine, int indice, int *result){
		
		if(arbre[racine].fd == -1 && arbre[racine].fg == -1 ){
	        code[indice] = '\0';
	        traduction[arbre[racine].lettre].code = (char*) malloc (indice *sizeof(char));
			strcpy ( traduction[arbre[racine].lettre].code,code ) ;
	        traduction[arbre[racine].lettre].taille = indice;
	        *result = *result + (arbre[racine].occur) * indice;
	    }
	    else{
	        code[indice] = '0';
	        construitCodeAux(arbre, traduction, code, arbre[racine].fg, indice + 1, result);
	        code[indice] = '1';
	        construitCodeAux(arbre, traduction, code, arbre[racine].fd, indice + 1, result);
	    }
	}

	int construitCode(Noeud arbreH[], int racine, Code traduc[]){
		char code[NBLETTRES +1];
		int result = 0;

		construitCodeAux(arbreH, traduc, code, racine, &result);
		return result;
	}

/*-----------------4--------------*/
	void affiche_code(Code traduction[]){
    	int i;
    	for(i = 0; i < NBLETTRES; i++){
        	if(traduction[i].taille > 0){
            	printf("%s : %c , place %d\n", traduction[i].code, i, i);
        	}
    	}
	}