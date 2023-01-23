

typedef struct noeud{
int valeur; /* étiquette */
struct noeud *fg; /* fils gauche */
struct noeud *fd; /* fils droit */
} Noeud, *Arbre;

/*3) Parcours */

void affichePrefixe(Arbre a) {
    if (NULL == a)
        return;
    printf("%d ", a->valeur);
    affichePrefixe(a->fg);
    affichePrefixe(a->fd);
}

void parcours_infixe(Arbre a){
  if(NULL != a){
    parcours_infixe(a->fg);
    printf("%d ", a->valeur);
    parcours_infixe(a->fd);
  }
}

void afficheSuffixe(Arbre a) {
    if (NULL == a)
        return;
    afficheSuffixe(a->fg);
    afficheSuffixe(a->fd);
    printf("%d\n", a->valeur);
}