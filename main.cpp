#include <iostream>
#include <cstdlib>

/*


Lote
{
nome
custo
quantidade
}

Programa de custo
{
Nome
Custo
}

Preço varia

*/

// Formatação
#include <iomanip>

// Tempo
#include <chrono>
#include <ctime>

// Threads
#include <thread>

// Sincronização
#include <atomic>

#include <conio.h>


#include <functional>
#include <unordered_map>

using namespace std;


struct category {
    int id;
    string name;
};

struct cost
{
    int id;
    float value;
};

atomic<bool> running(true);
atomic<short int> select(0);

void clear() {
    #if defined(_WIN64) || defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}

// Move o cursor para a coordenada (x, y)

void load() {
    cout << setCursor(0, 2)                          << "_____________[Lystra]_____________" << setColor(0);
    cout << setCursor(0, 3) << selected(select == 1) << "1." << setColor(0);
    cout << setCursor(0, 4) << selected(select == 2) << "2." << setColor(0);
    cout << setCursor(0, 5) << selected(select == 3) << "3." << setColor(0);
    cout << setCursor(0, 6) << selected(select == 4) << "4." << setColor(0);
    cout << setCursor(0, 7) << selected(select == 5) << "5." << setColor(0);
    cout << setCursor(0, 8)                          << "________________________" << setColor(0);
}

void keyPress() {

    load();
    
    while (true) {
        if (_kbhit()) { // Verifica se uma tecla foi pressionada
            int ch = _getch(); // Lê o primeiro byte
            
            if (ch == 224) { // Prefixo de tecla especial
                ch = _getch(); // Lê o segundo byte

                switch (ch) {
                    case 72:
                        //std::cout << "Seta para CIMA\n";
                        if (select > 2) select--;
                        load();
                        break;
                    case 80:
                        //std::cout << "Seta para BAIXO\n";
                        if (select < 5) select++;
                        load();
                        break;
                    case 75:
                        //std::cout << "Seta para ESQUERDA\n";
                        break;
                    case 77:
                        //std::cout << "Seta para DIREITA\n";
                        break;
                    default:
                        //std::cout << "Outra tecla especial: " << ch << '\n';
                        break;
                }
            } else if (ch == 27) { // ESC
                break;
            } else {
                //std::cout << "Tecla comum: " << (char)ch << '\n';
            }
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void showClock() {
    while (running) {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        tm* t = localtime(&time);

        cout << setCursor(24, 8) << put_time(t, "[%d/%m/%Y] - [%H:%M:%S]") << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Funções de tela
void telaInicial() {
    cout << "Bem-vindo à tela inicial!" << endl;
}

void telaCadastro() {
    cout << "Você está na tela de cadastro." << endl;
}

void telaRelatorio() {
    cout << "Relatório sendo exibido." << endl;
}

// Sistema de controle de telas
unordered_map<string, function<void()>> telas;

// Tela atual
function<void()> funcaoAtual;

int main() {
    clear();
    // Inicia a thread para o relógio
    
    
    thread CLOCK(showClock);
    thread KEY(keyPress);
    KEY.join();
    
    string input;
    
    // Informa o usuário sobre o que fazer
    //cout << "\033[2;1H" << "Digite algo e pressione Enter: " << endl;
    
    // Exibe um valor de input, sem afetar o relógio
    //getline(cin, input);

    CLOCK.join(); // Espera o relógio terminar


    //cout << "Você digitou: " << input << endl;
    return 0;
}
