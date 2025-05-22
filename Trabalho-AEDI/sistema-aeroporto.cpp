#include <iostream>
#include <unistd.h>
#include <ctime>
#include <iomanip>

#define ALTA 1
#define MEDIA 2

using namespace std;

#include "fila-prioridade.h"

string cias[8] = {"Latam", "Lufthansa", "Delta", "American Airlines", "Gol", "Azul", "Awalines", "IsaAirlines"};


string getCurrentTIme(int totalSeconds) {
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600)/60;
    int seconds = totalSeconds % 60;
    
    string h = (hours < 10 ? "0" : "") + to_string(hours);
    string m = (minutes < 10 ? "0" : "") + to_string(minutes);
    string s = (seconds < 10 ? "0" : "") + to_string(seconds);
    return h + ":" + m + ":" + s;
}


int main() { // P1 = pousos P2 = decolagens
    no *P1, *P2;
    bool pousando = false, decolando = false;
    int ut = 0, avioes = 0, tempo = 54000;
    string nome_voo_pouso;
    srand(time(nullptr));
    P1 = inicializaFP(P1);
    P2 = inicializaFP(P2);
    while(P1 != NULL || P2 != NULL || ut == 0) { // condição inicial
        for(int i = 0; i < 5; i++){
            if(avioes >= 60) break;
            int prioridade = rand() % 2 + 1, escolha = rand() % 2 + 1;
            if(escolha == 1) {
                P1 = insereFP(P1, prioridade, cias[rand() % 8], rand() % 9999 + 1);
            } else {
                P2 = insereFP(P2, prioridade, cias[rand() % 8], rand() % 9999 + 1);           
            }
            avioes++;
            cout << avioes << endl;
        }
        if(P1 != NULL && ut % 2 == 0) {
            cout << "--------PISTA DE POUSOS (AIRPORT-78A)-------- (" << getCurrentTIme(tempo) << ")" << endl;
            if(pousando) {
                cout << "Pouso " << nome_voo_pouso << " concluido com sucesso! (passageiros liberados)." << endl;
            } 
            P1 = removeFP()
        }
        if(P2 != NULL && ut % 3 == 0) {
            cout << "--------PISTA DE DECOLAGENS (AIRPORT-78B)-------- (" << getCurrentTIme(tempo) << ")" << endl;   
        }
        tempo+=60;
        ut++;
        sleep(2);
    }
}