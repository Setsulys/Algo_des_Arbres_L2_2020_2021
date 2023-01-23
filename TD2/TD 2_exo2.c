Arbre ajout(Arbre*a, int n){
	if (*a == NULL){
		*a = alloueNoeud(n);
		printf("ajout reussis \n");
		return 1;/*(*a)*/
	}
	if (n == (*a)-> valeur)
		return 1;/*(*a)*/
	if (n < (*a)-> valeur)
		return ajout(&((*a)->fg),n);
	if (n > (*a)-> valeur)
		return ajout(&((*a)->fd),n);
	return 0;
}

/*aprrouvé par le prof*/
int ajout(Arbre *a, int n) {
    if (*a == NULL) {
        *a = alloueNoeud(n);
        return (*a != NULL);
    }
    if ((*a)->valeur == n)
        return 1;
    if ((*a)->valeur < n)
        return ajout(&((*a)->fd), n);
    return ajout(&((*a)->fg), n);
}