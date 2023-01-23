void descente(Tas * T, int indice)
{
  int enfant, parent, tmp;
  
  if (NULL == T || indice < 0 || indice >= T->taille)
    return;
  
  enfant = Fils(*T, indice), parent = indice;
  
  while (enfant > -1 && T->arbre[enfant] < T->arbre[parent]){
    tmp = T->arbre[enfant];
    T->arbre[enfant] = T->arbre[parent];
    T->arbre[parent] = tmp;
    parent = enfant;
    enfant = Fils(*T, parent);
  }
}

void remontee(Tas * T, int indice)
{
  int enfant, parent, tmp;
  
  if (NULL == T || indice < 0 || indice >= T->taille)
    return;
  
  enfant = indice, parent = (indice - 1) / 2;
  
  while (enfant > 0 && T->arbre[enfant] < T->arbre[parent]){
    tmp = T->arbre[enfant];
    T->arbre[enfant] = T->arbre[parent];
    T->arbre[parent] = tmp;
    enfant = parent;
    parent = (enfant - 1) / 2;
  }
}


int Ajout(Tas *T, int valeur) {
    if (NULL == T || taille >= MAX)
        return 0;
    
    T->arbre[T->taille] = valeur;
    T->taille++;
    return remonte(T, T->taille - 1);
}