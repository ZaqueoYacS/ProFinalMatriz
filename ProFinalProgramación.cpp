#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

const int PUNTOS_PARA_GANAR = 5; // Puntaje máximo necesario para ganar el juego

struct Jugador {
    string nombre;
    int puntos;
};

void ingresarNombres(Jugador& jugador1, Jugador& jugador2);
bool elegirPrimerTurno(Jugador& jugador1, Jugador& jugador2);
void generarMatriz(int matriz[10][10], int n);
void generarMatrizNumeracion(int matriz[10][10], int n);
void mostrarMatrices(int matrizNumeros[10][10], int matrizNumeracion[10][10], int visible[10][10], int n);
void revelarTemporalmente(int visible[10][10], int n, int fila, int columna);
void ocultarCircundantes(int visible[10][10], int n, int fila, int columna);
bool realizarTurno(Jugador& jugador, int matrizNumeros[10][10], int matrizNumeracion[10][10], int visible[10][10], int n);
bool verificarGanador(Jugador& jugador1, Jugador& jugador2);
int preguntarContinuar(); // Cambiado a retornar un entero

int main() {
    int n;
    cout << "Ingrese el tamaño de la matriz cuadrada (hasta 10): ";
    cin >> n;
    if (n > 10) {
        cout << "Tamaño máximo permitido es 10. Usando tamaño 10." << endl;
        n = 10;
    }
    int matrizNumeros[10][10];

    generarMatriz(matrizNumeros, n);

    int matrizNumeracion[10][10];

    generarMatrizNumeracion(matrizNumeracion, n);

    int visible[10][10] = {0};

    Jugador jugador1, jugador2;

    ingresarNombres(jugador1, jugador2);
    
    int turnos = 0;
    do {
        while (jugador1.puntos < PUNTOS_PARA_GANAR && jugador2.puntos < PUNTOS_PARA_GANAR) {
            bool turnoJugador1 = elegirPrimerTurno(jugador1, jugador2);
            while (true) {
                if (turnoJugador1) {
                    realizarTurno(jugador1, matrizNumeros, matrizNumeracion, visible, n);
                    turnoJugador1 = false;
                } else {
                    realizarTurno(jugador2, matrizNumeros, matrizNumeracion, visible, n);
                    turnoJugador1 = true;
                }
                turnos++;

                cout << "Puntuaciones:" << endl;
                cout << jugador1.nombre << ": " << jugador1.puntos << " puntos" << endl;
                cout << jugador2.nombre << ": " << jugador2.puntos << " puntos" << endl;

                if (verificarGanador(jugador1, jugador2)) {
                    break;
                }
            }
        }

        int continuar = preguntarContinuar();
        if (continuar == 1) {
            // Reiniciar los puntos y las matrices
            jugador1.puntos = 0;
            jugador2.puntos = 0;
            generarMatriz(matrizNumeros, n);
            generarMatrizNumeracion(matrizNumeracion, n);
            // Reiniciar la matriz visible
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    visible[i][j] = 0;
                }
            }
        } else {
            break; // Salir del bucle principal si no quieren continuar jugando
        }
    } while (true);

    cout << "¡Felicidades! " << (jugador1.puntos >= PUNTOS_PARA_GANAR ? jugador1.nombre : jugador2.nombre) << " ha ganado el juego." << endl;

    return 0;
}


void ingresarNombres(Jugador& jugador1, Jugador& jugador2) {
    cout << "Ingrese el nombre del Jugador 1: ";
    cin >> jugador1.nombre;
    jugador1.puntos = 0;

    cout << "Ingrese el nombre del Jugador 2: ";
    cin >> jugador2.nombre;
    jugador2.puntos = 0;
}

bool elegirPrimerTurno(Jugador& jugador1, Jugador& jugador2) {
    srand(time(0)); 
    int opcion = 1 + rand() % 2; 
    bool turnoJugador1 = (opcion == 1);
    cout << "El jugador ";
    if (turnoJugador1) {
        cout << jugador1.nombre;
    } else {
        cout << jugador2.nombre;
    }
    cout << " tiene el primer turno." << endl;

    return turnoJugador1;
}

void generarMatriz(int matriz[10][10], int n) {
    srand(time(0)); 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = 1 + rand() % 10; 
        }
    }
}

void generarMatrizNumeracion(int matriz[10][10], int n) {
 int contador = 1;
    for (int i = 0; i < n; ++i) { // Recorre las filas
        for (int j = 0; j < n; ++j) { // Recorre las columnas
            matriz[i][j] = contador++;
        }
    }
 }

void mostrarMatrices(int matrizNumeros[10][10], int matrizNumeracion[10][10], int visible[10][10], int n) {
    cout << "Matriz de Numeración:" << endl;
    cout << "+";
    for (int j = 0; j < n; ++j) {
        cout << "-----+";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "| " << (matrizNumeracion[i][j] < 10 ? " " : "") << (matrizNumeracion[i][j] < 100 ? " " : "") << matrizNumeracion[i][j] << " ";
        }
        cout << "|" << endl;

        cout << "+";
        for (int j = 0; j < n; ++j) {
            cout << "-----+";
        }
        cout << endl;
    }
    cout << "Matriz de Números Ocultos:" << endl;
    cout << "+";
    for (int j = 0; j < n; ++j) {
        cout << "----+";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visible[i][j] == 0) {
                cout << "|  X ";
            } else {
                cout << "| " << (matrizNumeros[i][j] < 10 ? " " : "") << matrizNumeros[i][j] << " ";
            }
        }
        cout << "|" << endl;
        cout << "+";
        for (int j = 0; j < n; ++j) {
            cout << "----+";
        }
        cout << endl;
    }
}

void revelarTemporalmente(int visible[10][10], int n, int fila, int columna) {
    for (int i = fila - 1; i <= fila + 1; ++i) {
        for (int j = columna - 1; j <= columna + 1; ++j) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                visible[i][j] = 1;
            }
        }
    }
}

void ocultarCircundantes(int visible[10][10], int n, int fila, int columna) {
    for (int i = fila - 1; i <= fila + 1; ++i) {
        for (int j = columna - 1; j <= columna + 1; ++j) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                visible[i][j] = 0;
            }
        }
    }
}

bool realizarTurno(Jugador& jugador, int matrizNumeros[10][10], int matrizNumeracion[10][10], int visible[10][10], int n) {
    int seleccion;
    mostrarMatrices(matrizNumeros, matrizNumeracion, visible, n);
    cout << jugador.nombre << ", selecciona una casilla (1-" << n * n << "): ";
    cin >> seleccion;
    if (seleccion < 1 || seleccion > n * n) {
        cout << "Selección inválida. Inténtalo de nuevo." << endl;
        return false;
    }

    int columna = (seleccion - 1) % n;
    int fila = (seleccion - 1) / n;

    revelarTemporalmente(visible, n, fila, columna);
    mostrarMatrices(matrizNumeros, matrizNumeracion, visible, n);

    int sumaSuperior = 0, sumaInferior = 0, resultadoFinal = 0;

    for (int i = fila - 1; i <= fila + 1; ++i) {
        for (int j = columna - 1; j <= columna + 1; ++j) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                sumaSuperior += (i < fila ? matrizNumeros[i][j] : 0);
                sumaInferior += (i > fila ? matrizNumeros[i][j] : 0);
            }
        }
    }

    int resultado1 = sumaSuperior * matrizNumeros[fila][columna + 1];
    int resultado2 = sumaInferior * matrizNumeros[fila][columna - 1];
    resultadoFinal = (resultado1 + resultado2) * matrizNumeros[fila][columna];
    Sleep(10000);
    system("CLS");
    ocultarCircundantes(visible, n, fila, columna);

    int entradaUsuario = 0;
    bool resultadoCorrecto = true;

    cout << jugador.nombre << ", ingresa el resultado final de las operaciones: ";
    cin >> entradaUsuario;
    if (entradaUsuario != resultadoFinal) {
        cout << "Respuesta incorrecta." << endl;
        resultadoCorrecto = false;
    }

    if (resultadoCorrecto) {
        jugador.puntos++;
        cout << "¡Respuesta correcta! " << jugador.nombre << " ha ganado un punto." << endl;
    }

    return resultadoCorrecto;
}

int preguntarContinuar() {
    int respuesta; // Cambiado a un entero
    cout << "¿Desean continuar jugando? 1=si 2=no: ";
    cin >> respuesta;
    return respuesta; // Retorna la respuesta del usuario
}

bool verificarGanador(Jugador& jugador1, Jugador& jugador2) {
    return (jugador1.puntos >= PUNTOS_PARA_GANAR || jugador2.puntos >= PUNTOS_PARA_GANAR);
}

