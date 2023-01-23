void afficheCheminAux(Arbre a ,int *buffer,int indice){
    int i = 0;
    if(a != NULL){
        buffer[indice] = a->valeur;
        (if a->fg == NULL && a->fd == NULL)
            printf("%s",buffer);
    }

    afficheCheminAux(a->fg,buffer,indice+1);
    afficheCheminAux(a->fd,buffer,indice+1);

}

void afficheChemin(Arbre T){
    int buffer[MAX];
    int indice = 0;
    afficheCheminAux(T,buffer,indice);
}


/*autre verssion*/
void afficheCheminAux(Arbre T, int buffer[], int niveau) {
    int i;
    if (NULL == T)
        return;
    buffer[niveau] = T->valeur;
    if (NULL == T->fg && NULL = T->fd) {
        for (i = 0 ; i < valeur + 1 ; i++) {
            printf("%d ", buffer[i]);
        	printf("\n");
    	}
    }
    afficheCheminAux(T->fg, buffer, niveau + 1);
    afficheCheminAux(T->fd, buffer, niveau + 1);
}

void afficheChemin(Arbre T) {
    int buffer[MAX];
    int niveau = 0;
    afficheCheminAux(Arbre T, buffer, niveau);
}