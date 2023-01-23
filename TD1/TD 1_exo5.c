


/*NAIF*/
int estHG(Arbre a) {
    if (NULL == a)
        return 1;
    if (nb_feuilles(a->fg) < nb_feuilles(a->fd))
        return 0;
    else
        return estHG(a->fg) && estHG(a->fd); 
}



int est_HG_lineaire_aux(Arbre a, int *nb_feuille){
    int nb_f_gauche, nb_f_droite;
    if (NULL == a){ /* un arbre vide est HG */
        *nb_feuille = 0;
        return 1;
    }
    /* Désormais, on a un vrai noeud */
    if (NULL == a->fg && NULL == a->fd){ /* un arbre réduit à sa racine est HG */
        *nb_feuille = 1;
        return 1;
    }
    /* Désormais, l'arbre n'est pas réduit à sa racine */
    if (NULL == a->fg) /* un fils droit uniquement */
        return 0; /* pas besoin de parcourir le ss-arbre droit pour avoir le nb de feuille */
    if (NULL == a->fd) /* un fils gauche uniquement */
        return est_HG_lineaire_aux(a->fg, nb_feuille);
    /* Désormais, l'arbre possède deux fils */
    if (est_HG_lineaire_aux(a->fg, &nb_f_gauche) == 1 &&
        est_HG_lineaire_aux(a->fd, &nb_f_droite) == 1){
        if (nb_f_gauche >=nb_f_droite){
            *nb_feuille = nb_f_gauche + nb_f_droite;
            return 1;
        }
        return 0;
    }
    return 0;
}


int est_HG_lineaire(Arbre a) {
  int nb_feuille = 0;
  return est_HG_lineaire_aux(a, &nb_feuille);
}