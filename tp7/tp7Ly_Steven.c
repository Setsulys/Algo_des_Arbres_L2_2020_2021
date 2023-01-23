// LY-IENG Steven

#include <stdio.h>


int est_Tas(int tab[],int taille){
	int i;
	for (i=1;i<taille;i++){
		if (tab[i]<tab[(i-1)/2])
			return 0;
	}
	return 1;
}

void affichage(int tab[],int n){
	int i,j;
	for(i=0;i<n;i++){
		if(tab[i]==0){
			return;
		}
	}
	for(j=0;j<n;j++){
		printf("%d",tab[j] );
	}
	printf("\n");
}

int enum_permutation(int tab[],int premier,int n){
	int i;
	int resultat=0;

	if(premier>n){
		return 1;
	}
	for(i=0;i<n;i++){
		if(tab[i]==0){
			tab[i]=premier;
			resultat+=enum_permutation(tab,premier+1,n);
			affichage(tab,n);
			tab[i]=0;
		}
	}
	return resultat;
}

int enumTasNaif(int tab[],int premier,int n){
	int i;
	int resultat=0;

	if(premier>n){
		return est_Tas(tab,n);
	}
	for(i=0;i<n;i++){
		if(tab[i]==0){
			tab[i]=premier;
			resultat+=enumTasNaif(tab,premier+1,n);
			tab[i]=0;
		}
	}
	return resultat;
}

int estTasPartiel(int tab[], int n){
	int i;
	for(i=1;i<n;i++){
		if(tab[i]!=0 && tab[(i-1)/2]==0 || tab[i]<tab[(i-1)/2]){
			return 0;
		}
	}
	return 1;
}


int enumTas(int tab[], int premier, int n){
	int i;
	int resultat=0;
	if(premier>n){
		return 1;
	}
	resultat+=estTasPartiel(tab,n);
	return resultat;
}


/*d*/
/*si on met un n+1 a la place de 0 en faisant un est tas on aurait instantanément un est tas^partiel*/
/*estTas jouera aussi le role de estTasPartiel*/


int main(){
	int taille=12;
	int tab[12]={1,5,7,6,5,8,9,12,7,5,8,9};
	int tab2[4]={0,0,0,0};
	int tab3[6]={1,0,3,2,0,0};

	if(est_Tas(tab,taille)){
		printf("le tableau est un tas\n");
	}
	else{
		printf("le tableau n'est pas un tas\n ");
	}
	printf("Il y a :\t%d permutation·s\n\n",enum_permutation(tab2,1,4));
	printf("Il y a :\t%d permutation·s\n\n",enum_permutation(tab3,4,6));

	printf("Il y a :\t%d permutation·s qui sont des tas\n\n",enumTasNaif(tab2,1,4) );
	return 0;
}
