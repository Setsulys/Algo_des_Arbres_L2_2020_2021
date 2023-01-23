void descente(Tas * T, int indice){
    int enfant = fils(*T, indice), parent = indice, tmp;
    while (enfant > -1 && T->arbre[enfant] < T->arbre[parent]){
        tmp = T->arbre[enfant];
        T->arbre[enfant] = T->arbre[parent];
        T->arbre[parent] = tmp;
        parent = enfant;
        enfant = fils(*T, parent);
    }
}


void remontee(Tas * T, int indice){
    int enfant = indice, parent = (indice - 1) / 2, tmp;
    while (enfant > 0 && T->arbre[enfant] < T->arbre[parent]){
        tmp = T->arbre[enfant];
        T->arbre[enfant] = T->arbre[parent];
        T->arbre[parent] = tmp;
        enfant = parent;
        parent = (enfant - 1) / 2;
    }
}

void change(Tas * T, int indice, int valeur){
    int enfant = fils(*T, indice), parent = (indice - 1) / 2;
    if(indice > T->taille)
        return;
    T->arbre[indice] = valeur;
    if (T->arbre[indice] < T->arbre[parent]) /* remontée de valeur à faire */
        remontee(T, indice);
    else if (T->arbre[indice] > T->arbre[enfant]) /* descente de valeur à faire */
            descente(T, indice);
}