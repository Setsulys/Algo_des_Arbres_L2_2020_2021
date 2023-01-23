int recherche(Arbre a,char mot[],int i){/*arbre de recherche de mot fini*/
        if(a->lettre=='\n' && mot[i]=='\0'){    /*quand on arrive en fin de mot et en fin d'arbre c'est a dire que le mot est dans l'arbre sinon il n'y est pas*/
            return 1;
        }
        else if(a->lettre < mot[i]){    /*si la lettre est superieur a la lettre dans l'arbre on passe au frere droit*/
            if(a->fd!=NULL){            /*seulement si il existe un frere droit*/
                return recherche(a->fd,mot,i);
            }
            else{
                return 0;
            }
        }
        else if(a->lettre > mot[i]){    /*si la lettre est superieur a la lettre dans l'arbre on passe au frere gauche*/
            if(a->fg!=NULL){            /*seulement si il existe un frere gauche*/
                return recherche(a->fg,mot,i);
            }
            else{
                return 0;
            }
        }
        else if(a->lettre == mot[i]){   /*si la lettre est similaire on prend la branche du fils*/
            i++;
            return recherche(a->fils,mot,i);
        }
        else{
            return 0;
        }
    }