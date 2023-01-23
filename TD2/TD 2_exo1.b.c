

/*c. Érire une fonction Arbre Recherche(Arbre a, int n) qui recherche un élément n dans l’arbre a.
Cette fonction renverra l’adresse du nœud contenant l’élément n s’il est présent, et renverra NULL
sinon.
*/

Arbre recherche(Arbre a, int n) {
    if (NULL == a)
        return NULL;
    if (a->valeur == n)
        return a;
    if (a->valeur <= n)
        return recherche(a->fd, n);
    return recherche(a->fg, n);
}