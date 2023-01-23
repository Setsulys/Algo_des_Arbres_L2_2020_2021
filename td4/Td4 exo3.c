int Fils(Tas T, int indice)
{
  if (indice * 2 + 1 > T.taille) /* Fils hors Tas */
    return -1;
  
  if (indice * 2 + 2 > T.taille) /* Uniquement fils gauche */
    return indice * 2 + 1;
    
  return (T.arbre[indice * 2 + 1] < T.arbre[indice * 2 + 2]) ? indice * 2 + 1 : indice * 2 + 2;
}