Arbre extraitMin(Arbre *a){
	Arbre tmp;
	if(*a==NULL){
		return NULL;
	}
	if(((*a)->fg) == NULL){
		tmp=(*a);
		(*a)=(*a)->fd;
		return	tmp;
	}
	return extraitMin(&((*a)->fg));
}


Arbre extraitMax(Arbre *a){
	Arbre tmp;
	if(*a==NULL){
		return NULL;
	}
	if(((*a)->fd) == NULL){
		tmp=(*a);
		(*a)=(*a)->fg;
		return	tmp;
	}
	return extraitMax(&((*a)->fd));
}

Arbre extrait(Arbre *a,int n){
	Arbre tmp;
	if(*a==NULL){
		return NULL;
	}
	if(((*a)->valeur) > n){
		return extrait(&((*a)->fg));
	}
	if(((*a)->valeur) < n ){
		return extrait(&((*a)->fd));
	}
	if(((*a)->valeur) == n){
		if(((*a)->fg) == NULL && ((*a)->fd) == NULL){
			tmp=(*a);
			(*a)=NULL;
		}
		else if(((*a)->fg) ==NULL){
			tmp=(*a);
			(*a)=extraitMin(&((*a)->fd));
		}
		else{
			tmp=(*a);
			(*a)=extraitMax(&((*a)->fg));
		}
		return tmp;
	}
	return NULL;
}