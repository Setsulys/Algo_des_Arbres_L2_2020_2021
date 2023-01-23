#define NBLETTRES 256
#define NBNOEUDS (NBLETTRES*2-1)

typedef struct{
	unsigned char lettre;
	int occur;
	int fg
	int fd
}NoeudHuffman;

typedef struct{
	int code[NBLETTRES];
	int nombre bit;
}codage;


int compare_noeud(const void * ptr1, const void * ptr2){
    Noeud p = * ((Noeud *) ptr1);
    Noeud q = * ((Noeud *) ptr2);
    return p.occur - q.occur;
}

int compteLettre(FILE*in,Noeud tab[]){
	int i,nb;
	char c;
	nb=0;

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


int plusPetit(Noeud tab[], int *prem_feuille, int *prem_noeud, int noeud_libre) {
    if (*prem_noeud >= noeud_libre) {
        /* Pas de noeud dispo */
        if (*prem_feuille >= NBLETTRES)
            /* Pas de noeud ni feuille */
            return -1;
        else {
            (*prem_feuille)++;
            return *prem_feuille - 1;
        }
    }
    if (*prem_feuille >= NBLETTRES) {
        /* Pas de feuille dispo */
        (*prem_noeud)++;
        return *prem_noeud - 1;
    }
    if (tab[*prem_feuille].occur < tab[*prem_noeud].occur) {
        (*prem_feuille)++;
        return *prem_feuille - 1;
    }

    return (*prem_noeud)++;;
}

int construitArbre(Noeud tab[], int taille) {
    int prem_feuille, prem_noeud, noeud_libre, fg, fd;

    prem_feuille = NBLETTRES - taille;
    prem_noeud = noeud_libre = NBLETTRES;

    fg = plusPetit(tab, &prem_feuille, &prem_noeud, noeud_libre);
    fd = plusPetit(tab, &prem_feuille, &prem_noeud, noeud_libre);

    /* Quand fd vaut -1, c'est qu'il ne reste plus que la racine : on s'arrête */
    while (fd != -1) {
        /* On construit le noeud interne suivant */
        tab[noeud_libre].fg = fg;
        tab[noeud_libre].fd = fd;
        tab[noeud_libre].occur = tab[fg].occur + tab[fd].occur;
        noeud_libre++;

        fg = plusPetit(tab, &prem_feuille, &prem_noeud, noeud_libre);
        fd = plusPetit(tab, &prem_feuille, &prem_noeud, noeud_libre);
    }
    return prem_noeud - 1;
}

int creerCodeAux(Codage C[], NoeudHuffman arbre[], int racine, char *tampon, int niveau) {
    int lettre, total, fg, fd;
    if (arbre[racine].fg < 0) {
        /* Feuille */
        lettre = arbre[racine].lettre;
        memcpy(C[lettre].code, tampon, niveau);
        C[lettre].nombrebit = niveau;
        return arbre[racine].occur * niveau;
    }
    /* Noeud interne */
    fg = arbre[racine].fg;
    fd = arbre[racine].fd;
    total = 0;
    tampon[niveau] = '0';
    total += creerCodeAux(C, arbre, fg, tampon, niveau + 1);
    tampon[niveau] = '1';
    total += creerCodeAux(C, arbre, fd, tampon, niveau + 1);
    return total;
}

int creerCode(Codage C[], NoeudHuffman arbre[], int racine) {
    char tampon[NBLETTRES];
    return creerCodeAux(C, arbre, racine, tampon, 0);
}

void codeArbre(FILE *sortie, NoeudHuffman arbre[], int racine) {
    char tampon[9];
    if (arbre[racine].fd == -1) {
        /* Feuille */
        char_vers_binaire(arbre[racine].lettre, tampon);
        fprintf(sortie, "1%s", tampon);
    }
    else {
        /* Noeud interne */
        fprintf(sortie, "0");
        codeArbre(sortie, arbre, arbre[racine].fg);
        codeArbre(sortie, arbre, arbre[racine].fd);
    }
}

void char_vers_binaire(unsigned char n, char *dest) {
    int i;
    memset(dest, '0', 8);
    dest[8] = '\0';
    for (i = 0 ; n > 0 ; i++) {
        dest[7 - i] = '0' + n % 2;
        n /= 2;
    }
}

void CodeArbre(FILE *sortie, NoeudHuffman arbre[], int racine){
  if(racine < 256){
    fputc('1', sortie);
    fprintf(sortie, "[%c]", arbre[racine].lettre);
  }
  else{
    fputc('0', sortie);
    CodeArbre(sortie, arbre, arbre[racine].fg);
    CodeArbre(sortie, arbre, arbre[racine].fd);
  }
} 