#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para time

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

class Dado {
public:
    Dado() {
        srand(static_cast<unsigned int>(time(0))); // Inicializar la semilla para aleatoriedad
    }

    int lanzar() const {
        return rand() % 6 + 1; // Genera un número entre 1 y 6
    }
};

class tablero {
private:
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    string rotulo[11] = {"2 : ", "3 : ", "4 : ", "5 : ", "6 : ", "7 : ", "8 : ", "9 : ", "10: ", "11: ", "12: "};
    vector<vector<celda>> ptr;
    vector<Ficha> fichas;
    vector<Ficha> pilares;

public:
    tablero() {
        ptr.resize(11);
        for (int i = 0; i < 11; ++i) {
            ptr[i].resize(guia[i], celda('1', '2', '3', '4'));
        }

        string colores[] = {"rojo", "azul", "verde", "amarillo"};
        for (const auto& color : colores) {
            for (int i = 0; i < 28; ++i) {
                fichas.emplace_back(color);
            }
        }

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

    bool colocarFicha(int posicion, const Ficha& ficha) {
        // Validar la posición
        if (posicion < 0 || posicion >= 11 || ptr[posicion].size() <= 0) {
            cout << "Posición inválida." << endl;
            return false;
        }

        // Colocar la ficha en la posición correspondiente
        ptr[posicion].emplace_back(celda(ficha.color[0], ficha.color[1], ficha.color[2], ficha.color[3]));
        return true;
    }
};

class Juego {
private:
    vector<Jugador> jugadores;
    tablero t;

public:
    void iniciar() {
        int numJugadores;
        do {
            cout << "Ingrese el número de jugadores (2-4): ";
            cin >> numJugadores;
        } while (numJugadores < 2 || numJugadores > 4);

        set<string> coloresSeleccionados;

        for (int i = 0; i < numJugadores; ++i) {
            string nombre, color;
            cout << "Ingrese el nombre del jugador " << (i + 1) << ": ";
            cin >> nombre;

            do {
                cout << "Ingrese el color (rojo, azul, amarillo, verde) para " << nombre << ": ";
                cin >> color;

                if (coloresSeleccionados.find(color) != coloresSeleccionados.end()) {
                    cout << "El color " << color << " ya ha sido escogido por otro jugador. Elija otro color." << endl;
                }
            } while (coloresSeleccionados.find(color) != coloresSeleccionados.end() || 
                     (color != "rojo" && color != "azul" && color != "amarillo" && color != "verde"));

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

    void jugar() {
        for (const auto& jugador : jugadores) {
            char continuar;
            cout << "Turno de " << jugador.nombre << ". Presione 'd' para lanzar los dados: ";
            cin >> continuar;

            if (continuar == 'd' || continuar == 'D') {
                Dado dado;
                int total = dado.lanzar() + dado.lanzar(); // Lanzamos dos dados
                cout << "Resultado de lanzar dos dados: " << total << endl;

                int posicion;
                cout << "Elija una posición en el tablero (0-10): ";
                cin >> posicion;

                // Colocar la ficha en el tablero
                Ficha ficha(jugador.color);
                if (t.colocarFicha(posicion, ficha)) {
                    cout << "Ficha colocada en la posición " << posicion << " por " << jugador.nombre << endl;
                }
            } else {
                cout << "Lanzamiento de dados cancelado." << endl;
            }
            t.mostrar(); // Mostrar el tablero después de cada turno
        }
    }
};

int main() {
    Juego juego;
    juego.iniciar();
    juego.mostrarJugadores();

    juego.jugar(); // Iniciar el turno de los jugadores
    
    return 0;
}

