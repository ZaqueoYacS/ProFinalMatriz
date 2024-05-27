#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void generarMatriz(int  matriz, int n) {
    srand(time(0));//números aleatorios

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = rand() % 100; // 0 y 99
        }
    }
}

// Función para mostrar la matriz
void mostrarMatriz(int matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matriz[i][j] ;
        }
        cout << endl;
    }
}

int generarOperacion() {
    int operadores;
    float resultado;

    switch (operadores) {
        case 1: // Suma
            break;
        case 2: // Resta
            break;
        case 3: // Multiplicación
            break;
        case 4: // División
            break;
    }
}

int main() {
    int n, fila, columna;
    cout << "Ingrese el tamaño de la matriz (n x n): ";
    cin >> n;
    if(n < 3){
        cout"el tamaño de la matriz no es válido";}
  
  mostrarMatriz(int matriz, int n);

    return 0;
}
