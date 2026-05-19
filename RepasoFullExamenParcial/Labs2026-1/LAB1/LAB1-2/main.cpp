#include <iostream>

using namespace std;

#define N 5
#define M 5

void imprimir(int matriz[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void copiar(int origen[N][M], int destino[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

bool posicion_valida(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

bool colocar(int matriz[N][M], int direccionesCorte[4][2], int dir,int c, int x, int y, int numero,int& fin_x, int& fin_y) {
    // VALIDAR
    int nx = x;
    int ny = y;
    for (int k = 0; k < c; k++) {
        if (!posicion_valida(nx, ny) || matriz[nx][ny] != 0) {
            return false;
        }
        nx += direccionesCorte[dir][0];
        ny += direccionesCorte[dir][1];
    }
    // COLOCAR
    nx = x;
    ny = y;
    for (int k = 0; k < c; k++) {
        matriz[nx][ny] = numero;
        fin_x = nx;
        fin_y = ny;
        nx += direccionesCorte[dir][0];
        ny += direccionesCorte[dir][1];
    }

    return true;
}

void descolocar(int matriz[N][M], int direccionesCorte[4][2],int dir, int c, int x, int y) {
    int nx = x;
    int ny = y;

    for (int k = 0; k < c; k++) {
        matriz[nx][ny] = 0;

        nx += direccionesCorte[dir][0];
        ny += direccionesCorte[dir][1];
    }
}

void backtracking(int matriz[N][M],int direcciones[8][2],int c,int x,int y,int numero_actual,int& mejor_cantidad,int mejor_matriz[N][M],int direccionesCorte[4][2]) {

    // ACTUALIZAR MEJOR SOLUCION
    if (numero_actual - 1 > mejor_cantidad) {
        mejor_cantidad = numero_actual - 1;
        copiar(matriz, mejor_matriz);
    }

    // PROBAR LAS 4 DIRECCIONES PARA EL LISTON
    for (int dir = 0; dir < 4; dir++) {
        int fin_x;
        int fin_y;

        if (colocar(matriz, direccionesCorte, dir, c,
                     x, y, numero_actual,
                     fin_x, fin_y)) {
            // DESDE LA PUNTA FINAL
            // BUSCAMOS NUEVOS INICIOS ADYACENTES
            bool encontro = false;
            for (int i = 0; i < 8; i++) {
                int nx = fin_x + direcciones[i][0];
                int ny = fin_y + direcciones[i][1];
                if (posicion_valida(nx, ny) &&
                    matriz[nx][ny] == 0) {
                    encontro = true;
                    backtracking(matriz,direcciones,c,nx,ny,numero_actual + 1,mejor_cantidad,mejor_matriz,direccionesCorte);
                }
            }

            // SI YA NO HAY DONDE CONTINUAR
            if (!encontro) {
                if (numero_actual > mejor_cantidad) {
                    mejor_cantidad = numero_actual;
                    copiar(matriz, mejor_matriz);
                }
            }
            // BACKTRACKING
            descolocar(matriz, direccionesCorte, dir, c, x, y);
        }
    }
}

int main() {

    int direcciones[8][2] = {
        {1,0},
        {1,-1},
        {0,-1},
        {-1,-1},
        {-1,0},
        {-1,1},
        {0,1},
        {1,1}
    };

    int direccionesCorte[4][2] = {
        {1,0},
        {0,-1},
        {-1,0},
        {0,1}
    };

    int matriz[N][M] = {};
    int mejor_matriz[N][M] = {};

    int mejor_cantidad = 0;
    int c = 3;

    // EMPEZAR DESDE ESQUINA
    backtracking(matriz,direcciones,c,0,0,1,mejor_cantidad,mejor_matriz,direccionesCorte);

    cout << "MEJOR SOLUCION" << endl;
    imprimir(mejor_matriz);

    cout << endl;

    cout << "TOTAL LISTONES: "
         << mejor_cantidad << endl;

    return 0;
}