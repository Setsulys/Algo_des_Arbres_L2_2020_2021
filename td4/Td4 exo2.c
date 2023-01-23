int estTas(int tab[], int taille){
  int i;
  for(i = taille - 1; i > 0; i--){
    if(tab[i] <= tab[(i - 1) / 2])
      return 0;
   }
   return 1;
}