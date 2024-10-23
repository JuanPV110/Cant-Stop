#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class celda {
public:
    char c_[4];

    celda(char a, char b, char c, char d) {
        c_[0] = a;
        c_[1] = b;
        c_[2] = c;
        c_[3] = d;
    }

    void mostrar() const {
        cout << c_[0] << c_[1] << c_[2] << c_[3] << "|";
    }
};

class Ficha {
public:
    string color;

    Ficha(const string& color) : color(color) {}

    void mostrar() const {
        cout << color << " ";
    }
};

class Jugador {
public:
    string nombre;
    string color;

    Jugador(const string& nombre, const string& color) : nombre(nombre), color(color) {}

    void mostrar() const {
        cout << "Jugador: " << nombre << ", Color: " << color << endl;
    }
};

class Juego {
private:
    vector<Jugador> jugadores;

public:
    void iniciar() {
        int numJugadores;
        do {
            cout << "Ingrese el número de jugadores (2-4): ";
            cin >> numJugadores;
        } while (numJugadores < 2 || numJugadores > 4);

        set<string> coloresSeleccionados; // Usamos un set para rastrear colores únicos

        for (int i = 0; i < numJugadores; ++i) {
            string nombre, color;
            cout << "Ingrese el nombre del jugador " << (i + 1) << ": ";
            cin >> nombre;

            do {
                cout << "Ingrese el color (rojo, azul, amarillo, verde) para " << nombre << ": ";
                cin >> color;

                // Verificar si el color ya ha sido seleccionado
                if (coloresSeleccionados.find(color) != coloresSeleccionados.end()) {
                    cout << "El color " << color << " ya ha sido escogido por otro jugador. Elija otro color." << endl;
                }
            } while (coloresSeleccionados.find(color) != coloresSeleccionados.end() || 
                     (color != "rojo" && color != "azul" && color != "amarillo" && color != "verde"));

            // Añadir color a la lista de seleccionados
            coloresSeleccionados.insert(color);
            jugadores.emplace_back(nombre, color);
        }
    }

    void mostrarJugadores() const {
        cout << "\nLista de jugadores:" << endl;
        for (const auto& jugador : jugadores) {
            jugador.mostrar();
        }
    }
};

class tablero {
private:
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    string rotulo[11] = {"2 : ", "3 : ", "4 : ", "5 : ", "6 : ", "7 : ", "8 : ", "9 : ", "10: ", "11: ", "12: "};
    vector<vector<celda>> ptr;  // Usa vector para gestión automática de memoria
    vector<Ficha> fichas;        // Fichas del juego
    vector<Ficha> pilares;       // Pilares

public:
    tablero() {
        ptr.resize(11);
        for (int i = 0; i < 11; ++i) {
            ptr[i].resize(guia[i], celda('1', '2', '3', '4'));
        }

        // Crear 28 fichas para cada color
        string colores[] = {"rojo", "azul", "verde", "amarillo"};
        for (const auto& color : colores) {
            for (int i = 0; i < 28; ++i) {
                fichas.emplace_back(color);
            }
        }

        // Crear 4 fichas llamadas pilares
        for (int i = 0; i < 4; ++i) {
            pilares.emplace_back("pilar");
        }
    }

    void mostrar() const {
        cout << "                                 TABLERO" << endl;

        for (int i = 0; i < 11; ++i) {
            cout << rotulo[i];
            for (int k = 0; k < (13 - guia[i]) / 2; ++k) {
                cout << "     ";
            }
            cout << "|";
            for (int j = 0; j < guia[i]; ++j) {
                ptr[i][j].mostrar();
            }
            cout << endl;
        }
    }
};

int main() {
    Juego juego;
    juego.iniciar();
    juego.mostrarJugadores();

    tablero t;
    t.mostrar();
    
    return 0;
}
