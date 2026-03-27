#include <iostream>

using namespace std;

#define N 8

/* PROBLEMA A RESOLVER: N-REINAS DEBEN SER UBICADAS Y QUE NO SE CHOQUEN
 * ENTRE SÍ, ES DECIR (NO MISMA FILA, NO MISMA COLUMNA, NO MISMA DIAGONALES)
 */
char tablero[N][N]={'.'}; // EL TABLERO ESTA LIMPIO SIN NADA, DONDE SE UBIQUE LA REINA SERÁ Q
int contador_soluciones=0;

void inicializar_tablero() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = '.';
        }
    }
}

void imprimir_tabla() {
    cout<<"Tabla con "<<N<<"-Reinas: "<<endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}
bool es_valido(int fila, int col) {
    //Ahora vemos misma columna
    for (int i = 0; i < fila; i++) {
        if (tablero[i][col] == 'Q') return false;
    }
    //Ahora vemos misma diagonal. Hay dos diagonales, diagonal derecha e izquierda
    //DIAGONAL IZQUIERDA
    for (int i = fila-1, j = col-1; i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j] == 'Q') return false;
    }
    // DIAGONAL DERECHA
    for (int i = fila-1, j = col+1; i >= 0 && j < N; i--, j++) {
        if (tablero[i][j] == 'Q') return false;
    }
    return true;

}
void colocar_reinas(int fila) {
    if(fila==N) { // SI PUSIERON A TODAS LAS REINAS
        imprimir_tabla();
        contador_soluciones++;
        return;
    }
    for (int col = 0; col < N; col++) {
        if (es_valido(fila, col)) {
            tablero[fila][col] = 'Q';
            colocar_reinas(fila + 1);
        }
        tablero[fila][col] = '.';
    }
}
int main() {
    inicializar_tablero();
    colocar_reinas(0);
    cout<<endl<<"SOLUCIONES ENCONTRADAS: "<<contador_soluciones<<endl;
    return 0;
}