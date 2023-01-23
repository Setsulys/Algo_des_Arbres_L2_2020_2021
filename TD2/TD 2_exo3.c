int verifierSub(Arbre a, int * min, int * max)
{
  int fgMax, fdMax, fgMin, fdMin;
  
  if (NULL == a) {
    return 1;
  }
  
  if (NULL != a->fg) {
    if (0 == verifierSub(a->fg, &fgMin, &fgMax))
      return 0;
    
    if (a->valeur <= fgMax)
      return 0;
  }
  
  if (NULL != a->fd) {
    if (0 == verifierSub(a->fd, &fdMin, &fdMax))
      return 0;
    
    if (a->valeur >= fdMin)
      return 0;
  }
  
  *min = (NULL != a->fg) ? fgMin : a->valeur;
  *max = (NULL != a->fd) ? fdMax : a->valeur;
  return 1;
}

int verifier(Arbre a)
{
  int min, max;
  
  return verifierSub(a, &min, &max);
}