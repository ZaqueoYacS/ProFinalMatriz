#include <iostream>
#include <cstdlib> // Para numeros aleatorios
#include <ctime>   // Para manejo del tiempo
using namespace std;

void imprimirTablaNumeros(int espacio) {
    cout << "Tabla de posicion " << espacio << "x" << espacio << endl;
    for (int i = 0; i < espacio; i++) {
        cout << string(espacio * 5 + 1, '_') << endl;
        for (int j = 0; j < espacio; j++) {
            cout << "| " << (i * espacio + j + 1);
            if (i * espacio + j + 1 < 10) { //Espacio para los numeros de la tabla, que se vea ordenado
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << string(espacio * 5 + 1, '_') << endl;
}

void imprimirTablaRandom(int espacio) {
    cout << "Tabla de numeros aleatorios " << espacio << "x" << espacio << endl;
    srand(time(0)); // Semilla para los números aleatorios
    for (int i = 0; i < espacio; i++) {
        cout << string(espacio * 5 + 1, '_') << endl;
        for (int j = 0; j < espacio; j++) {
            cout << "| " << (rand() % 10); // Números aleatorios entre 0 y 10
            if ((rand() % 100) < 10) {       // Ajuste del espaciado para números de un solo dígito
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << string(espacio * 5 + 1, '_') << endl;
}

int main() {
    int espacio;
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> espacio;

    imprimirTablaNumeros(espacio);
    imprimirTablaRandom(espacio);

    return 0;
}

