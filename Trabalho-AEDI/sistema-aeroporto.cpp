#include <iostream>
#include <string> 
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define ALTA 1
#define MEDIA 2

using namespace std;

#include "fila-prioridade.h"

string cias[8] = {"Latam", "Lufthansa", "Delta", "American Airlines", "Gol", "Azul", "Awalines", "IsaAirlines"};

struct voo_ocorrendo {
    string nome_voo, companhia;
    int prioridade;
};

string getCurrentTIme(int totalSeconds) {
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600)/60;
    int seconds = totalSeconds % 60;
    
    string h = (hours < 10 ? "0" : "") + to_string(hours);
    string m = (minutes < 10 ? "0" : "") + to_string(minutes);
    string s = (seconds < 10 ? "0" : "") + to_string(seconds);
    return h + ":" + m + ":" + s;
}

void dormir(int milissegundos) {
#ifdef _WIN32
    Sleep(milissegundos);
#else
    usleep(milissegundos * 1000);
#endif
}

void limparLinha() {
    cout << "\33[2K\r" << flush;
}

void limparChat() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void animarAviao(const string& voo, const string& numero) {
    cout << "VOO - " << voo << " - " << numero;
    string frames[] = {
        "->________________________",
        "_______->_________________",
        "______________->__________",
        "____________________->____",
        "________________________->",
        "___________(OK)___________"
    };
    for(const auto& frame : frames) {
        limparLinha();
        cout << frame << flush;
        dormir(1); // 1000 - padrão normal * teste professora = 1
    }
}

int main() { // P1 = pousos P2 = decolagens
    no *P1, *P2;
    bool pousando = false, decolando = false, solicitacoes = true;
    voo_ocorrendo voos[2];
    int ut = 0, avioes = 0, tempo = 54000;
    srand(time(nullptr));
    P1 = inicializaFP(P1);
    P2 = inicializaFP(P2);
    while(P1 != NULL || P2 != NULL || ut == 0 || pousando == true || decolando == true) { // condição inicial
        if(solicitacoes) {
            cout << endl;
            cout << "->NOVAS SOLICITACOES -- AEROPORTO (" << getCurrentTIme(tempo) << ") <-" << endl;
            cout << endl;
        }
        for(int i = 0; i < 5; i++){
            if(avioes >= 60){
                solicitacoes = false;
                break;
            } 
            int prioridade = rand() % 5 + 1, escolha = rand() % 2 + 1;
            if(escolha == 1) {
                string cia = cias[rand() % 8];
                int number = rand() % 9999 + 1;
                switch(prioridade) {
                    case 1 ... 4:
                        cout << "Aviao - " << cia << " - " << cia + to_string(number) << " prioridade(2) - solicitando pouso!" << endl;
                        P1 = insereFP(P1, 2, cia, number);
                        break;
                    case 5:
                        cout << "Aviao - " << cia << " - " << cia + to_string(number) << " prioridade(1) - solicitando pouso!" << endl;
                        P1 = insereFP(P1, 1, cia, number);                
                }
            } else {
                string cia = cias[rand() % 8];
                int number = rand() % 9999 + 1;
                switch(prioridade) {
                    case 1 ... 4:
                        cout << "Aviao - " << cia << " - " << cia + to_string(number) << " prioridade(2) - solicitando decolagem!" << endl;
                        P2 = insereFP(P2, 2, cia, number);
                        break;
                    case 5:
                        cout << "Aviao - " << cia << " - " << cia + to_string(number) << " prioridade(1) - solicitando decolagem!" << endl;
                        P2 = insereFP(P2, 1, cia, number);                
                }          
            }
            dormir(1); // 500 - padrão normal * 1 - teste professora
            avioes++;
        }
        if(solicitacoes) {
            cout << endl;
            cout << "->NOVAS SOLICITACOES -- AEROPORTO (" << getCurrentTIme(tempo) << ") <-" << endl;
            cout << endl;
        }
        if(P1 != NULL && ut % 2 == 0) {
            cout << endl;
            cout << "Proximos pousos -> " << endl;
            exibe(P1, tempo, 1); 
            cout << endl;
            cout << "--------PISTA DE POUSOS (AIRPORT-78A)-------- (" << getCurrentTIme(tempo) << ")" << endl;
            if(pousando) {
                animarAviao(voos[0].nome_voo, voos[0].companhia);
                cout << endl;
                cout << "Pouso " << voos[0].nome_voo << " concluido com sucesso! (passageiros liberados)." << endl;
                cout << endl;
            } 
            P1 = removeFP(P1, &voos[0].prioridade, &voos[0].nome_voo, &voos[0].companhia);
            cout << endl;
            cout << "Voo pousando atualmente: " << voos[0].nome_voo << " - " << voos[0].companhia << " - prioridade: " << voos[0].prioridade << endl;
            cout << endl;
            pousando = true;
        } else {
            if(P1 == NULL && pousando == true) {
                animarAviao(voos[0].nome_voo, voos[0].companhia);
                cout << endl;
                cout << "Pouso " << voos[0].nome_voo << " concluido com sucesso! (passageiros liberados)." << endl;
                cout << endl;
                cout << endl;
                cout << "[ FILA DE POUSOS CONCLUIDA ]" << endl;
                cout << endl;
                pousando = false;
            }  
        }
        if(P2 != NULL && ut % 3 == 0) {
            cout << endl;
            cout << "Proximas decolagens -> " << endl;
            exibe(P2, tempo, 2); 
            cout << endl;
            cout << "--------PISTA DE DECOLAGENS (AIRPORT-78B)-------- (" << getCurrentTIme(tempo) << ")" << endl;   
            if(decolando) {
                animarAviao(voos[1].nome_voo, voos[1].companhia);
                cout << endl;
                cout << "Decolagem " << voos[1].nome_voo << " concluida com sucesso! (aviao em seguranca)." << endl;
                cout << endl;
            } 
            P2 = removeFP(P2, &voos[1].prioridade, &voos[1].nome_voo, &voos[1].companhia);
            cout << endl;
            cout << "Voo decolando atualmente: " << voos[1].nome_voo << " - " << voos[1].companhia << " - prioridade: " << voos[1].prioridade << endl;
            cout << endl;
            decolando = true;
        } else {
            if(P2 == NULL && decolando == true) {
                animarAviao(voos[1].nome_voo, voos[1].companhia);
                cout << endl;
                cout << "Decolagem " << voos[1].nome_voo << " concluida com sucesso! (aviao em seguranca)." << endl;
                cout << endl;
                cout << endl;
                cout << "[ FILA DE DECOLAGENS CONCLUIDA ]" << endl;
                cout << endl;
                decolando = false;
            }  
        }
        tempo+=60;
        ut++;
        dormir(1); // 2000 - padrão normal * 1 - teste professora
    }
    cout << "[ AEROPORTO REPORTS ] Todos os voos foram atendidos! " << endl;
    return 0;
}