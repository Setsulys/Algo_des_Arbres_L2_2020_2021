

/*2) Programmation*/

typedef struct noeud{
int valeur; /* étiquette */
struct noeud *fg; /* fils gauche */
struct noeud *fd; /* fils droit */
} Noeud, *Arbre;

int hauteur(Arbre arbre) {
  if (NULL == arbre)
    return -1;
  return 1 + max(hauteur(arbre->fg), hauteur(arbre->fd));
}

int nb_noeuds(Arbre a){
  if(NULL == a)
    return 0;
  return 1 + nb_noeuds(a->fg) + nb_noeuds(a->fd);
}

int nb_noeuds_internes (Arbre a) {
    if (NULL == a)
        return 0;
    if (a->fg == NULL && a->fd == NULL)
        return 0;
    return 1 + nb_noeuds_internes(a->fg) + nb_noeuds_internes(a->fd);
}

int nb_interne(Arbre tree){
    if (NULL == tree)
        return (0);
    if (NULL != tree->fg && NULL != tree->fd)
        return 1 + nb_interne(tree->fg) + nb_interne(tree->fd);
    if (NULL == tree->fg && NULL != tree->fd)
        return 1 + nb_interne(tree->fd);
    if (NULL != tree->fg && NULL == tree->fd)
        return 1 + nb_interne(tree->fg);
}

int nb_feuilles (Arbre a) {
    if (NULL == a)
        return 0;
    if (a->fg == NULL && a->fd == NULL)
        return 1;
    return nb_feuilles(a->fg) + nb_feuilles(a->fd);
}

int nb_deux_fils (Arbre a) {
    if (NULL == a)
        return 0;
    if (NULL != a->fg && NULL == a->fd)
        return 1 + nb_deux_fils(a->fg) + nb_deux_fils(a->fd);
    return nb_deux_fils(a->fg) + nb_deux_fils(a->fd);
}


