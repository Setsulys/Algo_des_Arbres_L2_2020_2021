void TriTas(int t[], int taille){
    int i;
    Tas tas;
    tas.taille = 0;
    tas.arbre = t;
    tas.max = taille;
    for(i = 0; i < taille; i++)
        Ajout(&tas, t[i]);
    for(i = taille - 1; i >=0 ; i--)
        t[i] = ExtraireMin(&tas);
}


int reallocation(Tas * T)
{
  if (NULL == T)
    return 0;
  T->Max *= 2;
  return (NULL != (T->arbre = (int*) realloc(T->arbre, sizeof(int) * T->Max)));
}

int allocation(Tas * T)
{
  if (NULL == T)
    return 0;
  if (T->Max == 0) {
    T->Max = TAILLE_DEFAUT;
    return (NULL != (T->arbre = (int*) malloc(sizeof(int) * T->Max)));
  }
  return reallocation(T);
}


/*
void TriTas(int T[], int taille) {
    Tas tas;
    tas.taille = 0;
    tas.arbre = T;
    tas.max = taille;
    for (i = 0 ; i < taille ; i++)
        ajout(&T, T[i]);
    
    for (i = 0 ; i < taille ; i++)
        extraireMin(&T);
}

void TriTas(int T[], int taille) {
    Tas tas;
    tas.taille = 0;
    tas.arbre = calloc(taille, sizeof(int));
    if (NULL == tas.arbre)
        return;
    tas.max = taille;
    
    for (i = 0 ; i < taille ; i++)
        ajout(&T, T[i]);
    
    for (i = 0 ; i < taille ; i++)
        extraireMin(&T);
}*/