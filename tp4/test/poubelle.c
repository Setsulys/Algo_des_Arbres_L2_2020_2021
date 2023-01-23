void ecrireArbre(FILE*out,Arbre a){
	reconstruire_arbre_fichier(&a,"arbre1");
	if (a==NULL){
		fprintf(out,"\tn%d [ label=\"<gauche> | <valeur> %s | <droit>\"];\n", 0,"NULL");
	}

	else if(a->fg != NULL && a->fd == NULL){
		fprintf(out, "\tn%p : gauche c-> n%p: valeur;",a,a->fg);
		fprintf(out,"\tn%p [ label=\"<gauche> | <valeur> %d | <droit>\"];\n", a,a->valeur);
		ecrireArbre(out,a->fg);
	}
	else if(a->fg == NULL && a->fd != NULL){
		fprintf(out, "\tn%p : droit c-> n%p: valeur;",a,a->fd);
		fprintf(out,"\tn%p [ label=\"<gauche> | <valeur> %d | <droit>\"];\n", a,a->valeur);
		ecrireArbre(out,a->fd);
	}

	else{
		fprintf(out,"\tn%p [ label=\"<gauche> | <valeur> %d | <droit>\"];\n", a,a->valeur);
	}
}