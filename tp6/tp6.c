 #include <stdio.h>

typedef struct unionfind {
	int taille ; // Taille des tableaux
	int * pere ; // Tableau des peres
	int * rang ; // Tableau des rangs
	unsigned nb_appels ;
} unionfind_t ;



/*2*/
unionfind_t* initialisation(int N){
    unionfind_t* tmp = (unionfind_t*) malloc(sizeof(unionfind_t));
    if (tmp == NULL) {
      return NULL;
    }
    tmp->taille = N;
    tmp->pere = malloc(sizeof(int) * N);
    tmp->rang = malloc(sizeof(int) * N);
    if (tmp->pere == NULL || tmp->rang == NULL) {
      return NULL;
    }
    for (int i = 0; i < N; i++) {
      tmp->pere[i] = i;
      tmp->rang[i] = 0;
    }
    tmp->nb_appels = 0;
    return tmp;
}

/*3*/
int trouve_naif(unionfind_t*partition,int x){

	partition->nb_appels++;
	if(x==partition->pere[x]){
		return x;
	}
	return trouve_naif(partition,partition->pere[x]);
}

/*4*/
void fusion_naive(unionfind_t *partition,int x,int y){
	int valx,valy;

	valx=trouve_naif(partition,x);
	valy=trouve_naif(partition,y);
	if(valx==valy){
		return;
	}
	else{
		partition->nb_appels++;
		partition->pere[valx]=valy;
	}
}

/*5*/
int trouve_compresse(unionfind_t *partition, int x){
	
	partition->nb_appels++;
	if(partition->pere[x]!=x){
		partition->pere[x]=trouve_compresse(partition,partition->pere[x]);
	}
	return partition->pere[x];
}

/*6*/
int compare_val(int x,int valx){
	if(x==valx)
		return 1;
	return 2;
}


void fusion_rang(unionfind_t* partition, int x, int y){
    int valx, valy;
    
    valx = trouve_compresse(partition, x);
    valy = trouve_compresse(partition, y);

    if (valx != valy){
        if (partition->rang[valx] >= partition->rang[valy]){
            partition->nb_appels++;
            partition->pere[valy] = x;
            if (partition->rang[valx] < partition->rang[valy] + compare_val(x,valx)){
                partition->rang[valx] = partition->rang[valy] + compare_val(x,valx);
                partition->rang[valy] = '?';
            }
        }
        else{
            partition->nb_appels++;
            partition->pere[valx] = y;
            if (partition->rang[valy] < partition->rang[valx] + compare_val(y,valy)){
                partition->rang[valy] = partition->rang[valx] + compare_val(y,valy);
                partition->rang[valy] = '?';
            }
        }
    }
}