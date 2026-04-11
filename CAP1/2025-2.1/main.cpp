#include <iostream>
#include <vector>

#define N 8
using namespace std;

vector<pair<int,int>> direcciones = {
    {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}
};


void imprimir_tablero(vector<vector<int>> &tablero) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j] <<" "; // Usamos \t para que se vea ordenado
        }
        cout << endl;
    }
}

void inicializar_tablero(vector<vector<int>> &tablero) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }
}

bool valido(int nx, int ny, vector<vector<int>> &tablero) {
    if (!(nx >= 0 && nx < N && ny >= 0 && ny < N)) return false;
    if (tablero[nx][ny]!=0) return false;
    return true;
}


bool resolver_rey(int x, int y, vector<vector<int>> &tablero, int number_position) {
    if (number_position == N * N+1) {
        return true;
    }

    for (auto m: direcciones) {
        int nx = x + m.first;
        int ny = y + m.second;

        // Si es válido y tiene exactamente la cantidad de salidas que estamos buscando en este turno
        if (valido(nx, ny, tablero)) {
            tablero[nx][ny] = number_position;
            if (resolver_rey(nx, ny, tablero, number_position + 1)) {
                return true;
            }
            tablero[nx][ny] = 0;
        }
    }

    return false;
}
int sumaFila(vector<vector<int>> &tablero, int x, int y) {
    if (y<N-1) {
        return tablero[x][y] + sumaFila(tablero, x,y+1);
    }
    else {
        return tablero[x][y];
    }
}
int sumaColumna(vector<vector<int>> &tablero, int x, int y) {
    if (x<N-1) {
        return tablero[x][y] + sumaFila(tablero, x+1,y);
    }
    else {
        return tablero[x][y];
    }
}

int sumaDigonalDerecha(vector<vector<int>> &tablero, int x, int y) {
    if (x==N-1 and y==N-1) {
        return tablero[x][y];
    }
    else {
        return tablero[x][y] + sumaDigonalDerecha(tablero, x+1,y+1);
    }
}
int sumaDigonalIzquierda(vector<vector<int>> &tablero, int x, int y) {
    if (x==0 and y==N-1) {
        return tablero[x][y];
    }
    else {
        return tablero[x][y] + sumaDigonalIzquierda(tablero, x-1,y+1);
    }
}

bool esCuadradoMagico(vector<vector<int>> &tablero) {
    int cte=sumaFila(tablero,0,0);
    cout<<"CTE:"<<cte<<endl;

    //FILA
    for (int i = 0; i < N; i++) {
        if (cte!=sumaFila(tablero, i,0)) {
            return false;
        }
    }

    //COLUMNA
    for (int i = 0; i < N; i++) {
        if (cte!=sumaColumna(tablero, 0,i)) {
            return false;
        }
    }

    //DIAGONALEs
    if (sumaDigonalDerecha(tablero,0,0)!=cte) {

        return false;
    }
    if (sumaDigonalIzquierda(tablero,N-1,0)!=cte) {
        return false;
    }
}

int main() {
    vector<vector<int>> tablero(N, vector<int>(N,0));
    inicializar_tablero(tablero);
    tablero[0][0] = 1;
    if (resolver_rey(0, 0, tablero, 2)) {
        cout << "SOLUCION ENCONTRADA" << endl;
        imprimir_tablero(tablero);
        if (esCuadradoMagico(tablero)) {
            cout<<"ES CUADRADO MAGICO"<<endl;
        }
        else {
            cout<<"NO ES CUADRADO MAGICO"<<endl;
        }
    }
    else {
        cout<<"NO HAY SOLUCUON ENCOMTRADA"<<endl;
    }

    return 0;
}