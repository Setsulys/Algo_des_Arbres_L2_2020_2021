int ExtraireMin(Tas *T)
{
  int min;
  
  if (NULL == T && T->taille > 0)
    return -1;
  
  min = T->arbre[0];
  change(T, 0, T->arbre[--(T->taille)]);
  return min;
}