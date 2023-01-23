typedef struct noeud{
int valeur; /* étiquette */
struct noeud *fg; /* fils gauche */
struct noeud *fd; /* fils droit */
} Noeud, *Arbre;


/*4 Description d'un arbre étiqueté par des entiers strictement positifs*/

void afficheArbPositif(Arbre a){
  if(NULL == a)
    printf("0");
  else{
    printf("%d ", a->valeur);
    afficheArbPositif(a->fg);
    afficheArbPositif(a->fd);
  }
}

int construitArbPositif(Arbre *a) {
    int n;
    scanf("%d", &n);
    
    if (n > 0) {
        if ((*a = alloueNoeud(n)) == NULL) 
            return 0;
        if (construitArbPositif(&((*a)->fg)) != 1)
            return 0;
        if (construitArbPositif(&((*a)->fd)) != 1)
            return 0;
    }
    return 1;
}


int estHG(Arbre a) {
    if (NULL == a)
        return 1;
    if (nb_feuilles(a->fg) < nb_feuilles(a->fd))
        return 0;
    else
        return estHG(a->fg) && estHG(a->fd); 
}
