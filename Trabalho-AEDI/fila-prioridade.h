#include <string>

struct no {
    string companhia;
    string nomeVoo;
    int info;
    int prior;
    string tempoEspera;
    no *link;
};

string getCurrentTImeFP(int totalSeconds) {
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600)/60;
    int seconds = totalSeconds % 60;
    
    string h = (hours < 10 ? "0" : "") + to_string(hours);
    string m = (minutes < 10 ? "0" : "") + to_string(minutes);
    string s = (seconds < 10 ? "0" : "") + to_string(seconds);
    return h + ":" + m + ":" + s;
}

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

void exibe(no *L, int tempo, int tipo)
{
    int i = 0;
    no *P = L;
    cout << " ";
    while (P != NULL && i < 5) {
        if(tipo == 1) {
            cout << "[ FILA POUSOS ] Nome: " << P->companhia << " Voo: " << P->nomeVoo << " | " << " previsao: " << getCurrentTImeFP(tempo + i * 120) << endl;
            P = P->link;
            i++;
        } else if(tipo == 2) {
            cout << "[ FILA DECOLAGENS] Nome: " << P->companhia << " Voo: " << P->nomeVoo << " | " << "previsao: " << getCurrentTImeFP(tempo + i * 180) << endl;
            P = P->link;
            i++;            
        }

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