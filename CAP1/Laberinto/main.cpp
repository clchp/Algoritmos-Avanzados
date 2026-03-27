#include <format>
#include <iostream>
using namespace std;

const int FILAS = 10;
const int COLUMNAS = 10;

int NUM_SOLUCIONES=0;

const int DIRECCIONES[4][2]= {
    {0,-1},
    {1,0},
    {0,1},
    {-1,0}
};

void imprimir_laberinto(char laberinto[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << laberinto[i][j]<<" ";
        }
        cout << endl;
    }
}

bool esValidaSolucion(int x, int y, char laberinto[FILAS][COLUMNAS], bool solucion[FILAS][COLUMNAS]) {
    return (x >= 0 && x < FILAS &&
            y >= 0 && y < COLUMNAS &&
            laberinto[x][y] != '#' &&
            !solucion[x][y]);
}

bool enontrar_solucion_laberinto(int x, int y, char laberinto[FILAS][COLUMNAS], bool solucion[FILAS][COLUMNAS]) {

// CASO DONDE SE ENCUENTRA UNA SOLUCIÓN CORRECTA
    if (laberinto[x][y] == 'E') {
        cout<<"SOLUCION ENCONTRADA"<<endl;
        imprimir_laberinto(laberinto);
        return true;
    }

    // Sino, se asume siempre que se da esa opción, y se coloca como verdadero
    solucion[x][y] = true;
    // Maracamos cuando no sea S para mantener la marca del inicio
    if (laberinto[x][y] != 'S')
        laberinto[x][y] = '.';

    // Despues, vamos a ir por las 4 diferentes direcciones
    for (int i = 0; i < 4; i++) {
        // Obtenemos las siguientes direcciones
        int nx = x + DIRECCIONES[i][0];
        int ny = y + DIRECCIONES[i][1];

        // Comprobamos si las nuevas direcciones son validas
        if (esValidaSolucion(nx, ny, laberinto, solucion)) {
            // Si llegan a ser la solución, se promulga y se sigue por ese camino
            if (enontrar_solucion_laberinto(nx, ny, laberinto, solucion)) {
                return true;
            }
        }
    }
    // Si termina de ver por las 4 opciones, se va y hace backtracking
    // BACKTRACKING
    if (laberinto[x][y] != 'S') // Solo se desmarca cuando no sea S
        laberinto[x][y] = ' ';

    solucion[x][y] = false; // Se hace como que no se visito
    //Se promulga la falsedad
    return false;
}

void encontrar_todas(int x, int y, char laberinto[FILAS][COLUMNAS], bool visitado[FILAS][COLUMNAS]) {

    // Caso base
    if (laberinto[x][y] == 'E') {
        imprimir_laberinto(laberinto);
        cout << "------------------" << endl;
        NUM_SOLUCIONES++;
        return;
    }

    visitado[x][y] = true;

    if (laberinto[x][y] != 'S')
        laberinto[x][y] = '.';

    for (int i = 0; i < 4; i++) {
        int nx = x + DIRECCIONES[i][0];
        int ny = y + DIRECCIONES[i][1];

        if (nx >= 0 && nx < FILAS &&
            ny >= 0 && ny < COLUMNAS &&
            laberinto[nx][ny] != '#' &&
            !visitado[nx][ny]) {

            encontrar_todas(nx, ny, laberinto, visitado);
            }
    }

    // 🔥 BACKTRACKING (CLAVE)
    if (laberinto[x][y] != 'S')
        laberinto[x][y] = ' ';

    visitado[x][y] = false;
}


int main() {
    char laberinto[FILAS][COLUMNAS] = {
        {'S','#',' ',' ','#',' ','#',' ',' ',' '},
        {' ','#',' ','#','#',' ','#',' ','#',' '},
        {' ',' ',' ','#',' ',' ',' ',' ','#',' '},
        {'#','#',' ','#',' ','#','#',' ','#',' '},
        {' ',' ',' ',' ',' ','#',' ',' ',' ',' '},
        {' ','#','#','#',' ','#',' ','#','#',' '},
        {' ','#',' ',' ',' ',' ',' ','#',' ',' '},
        {' ','#',' ','#','#','#',' ','#',' ','#'},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'#','#','#','#','#','#','#','#','#','E'}
    };
    bool solucion[FILAS][COLUMNAS]= {false};
    // Imprimir al inicio
    imprimir_laberinto(laberinto);
    cout<<endl;
    // Encontrar una SOLA solución
    //enontrar_solucion_laberinto(0,0, laberinto, solucion);
    //encontrar todas las soluciones
    encontrar_todas(0, 0,laberinto, solucion);
    cout<<endl<<"Las soluciones totales son: "<<NUM_SOLUCIONES<<endl;
    return 0;
}