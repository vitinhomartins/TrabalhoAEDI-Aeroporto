struct no {
    string companhia;
    string nomeVoo;
    int info;
    int prior;
    no *link;
};

no *inicializaFP(no *L)
{
    L = NULL;
    return L;
}

no *insereFP(no *L, int prior, string companhia, int number)
{
    no *N, *P, *ANT;

    N = new no;
    N->prior = prior;
    N->companhia = companhia;
    N->nomeVoo = companhia + to_string(number);

    if (L == NULL) {
        L = N;
        N->link = NULL;
    }
    else {
        P = L;

        while ((P != NULL) && (prior >= P->prior)) {
            ANT = P;
            P = P->link;
        }
        if (P == L) {
            N->link = L;
            L = N;
        }
        else {
            ANT->link = N;
            N->link = P;
        }
    }
    return L;
}

no *removeFP(no *L, int * prior, string *nomeV, string *companhia) {
	no *AUX;

	if (L != NULL) {
		*prior = L->prior; 
        *nomeV = L->nomeVoo;
        *companhia = L->companhia;
		AUX = L;
		L = L->link;
		delete AUX;
	}
	return L;
}

int verificaSeVazia(no *L) {
	if (L == NULL)
		return 1;
	else
		return 0;
}

void exibe(no *L)
{
    no *P = L;
    cout << " ";
    while (P != NULL) {
		cout << "Nome:" << P->companhia<< " Numero:" << P->nomeVoo << "|" ;
        P = P->link;
    }
}

no* insereFilaChegada(no *L, int data, int prior) {
	no *P, *N;

	N = (no *) malloc (sizeof(no)); 
	N->info = data; 
	N->prior = prior; 
	N->link = NULL; 
	 
	if (L == NULL){ 
		L = N;
	}
	else { 
		P = L;	
	
		while(P->link != NULL) {
			P = P->link;
		}
		P->link = N;
	} 
	return L;
}