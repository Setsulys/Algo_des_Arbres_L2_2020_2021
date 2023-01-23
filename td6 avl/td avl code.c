
/*fonction EstAVL*/
int EstAVL(AVL a){
    int g, d;
    if(a == NULL)
        return 0;
   	g=EstAVL(a->fd);
   	d=EstAVL(a->fg);
    if((g-d) > 1 || (g - d < -1))
        return -1;
    else
        return 1 + max(g, d);
}


#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int estAVLaux(AVL a, int *min, int *max, int *hauteur) {
    int hg, hd, mind, ming, maxd, maxg;
    
    /* Arbre vide */
    if (NULL == a) {
        *hauteur = -1;
        return 1;
    }
    /* Si enfants ne sont pas des AVL, ou ne vérifient pas l'inégalité avec la racine */
    if (estAVLaux(a->fg, &ming, &maxg, &hg) == 0 || maxg > a->valeur)
        return 0;
    if (estAVLaux(a->fd, &mind, &maxd, &hd) == 0 || mind < a->valeur)
        return 0;
    /* MaJ min, max, hauteur */
    *hauteur = 1 + MAX(hg, hd);
    *min = (NULL != a->fg) ? ming : a->valeur;
    *max = (NULL != a->fd) ? maxd : a->valeur;
    return (hg - hd <= 1) && (hg - hd >= -1);
}

int estAVL(AVL a) {
    int h, min, max;
    return estAVLaux(a, &min, &max, &h);
}


void rotationD(AVL *a) {
    AVL fg;
    int bal_a, bal_fg;
    
    if (NULL == a) return;
    
    fg = (*a)->fg;
    bal_a = (*a)->bal;
    bal_fg = fg->bal;

    /* Premiere partie de la rotation */
    (*a)->fg = fg->fd;
    fg->fd = *a;

    /* MaJ balance */
    (*a)->bal = (bal_fg <= 0) ?  bal_a + 1 - bal_fg : bal_a - 1;
    fg->bal = ((*a)->bal >= 0) ? 1 + (*a)->bal + bal_fg : bal_fg + 1;
    
    /* Fin rotation */
    *a = fg;  
}

