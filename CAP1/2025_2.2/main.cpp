#include <iostream>
#include <vector>
using namespace std;

struct Solucion {
    int x;
    int y;
    int z;
};

void imprimirSolucion(const Solucion &solucion) {
    cout << "p " << solucion.x << " " << solucion.y << " " << solucion.z << " 1 2" << endl;
}

// Verifica si los números son positivos y distintos
bool esValido(const Solucion &sol) {
    return (sol.x > 0 && sol.y > 0 && sol.z > 0 &&
            sol.x != sol.y && sol.x != sol.z && sol.y != sol.z);
}

// Backtracking recursivo
void encontrarContraseña(int pos, int S, Solucion &sol, vector<bool> &usados) {
    if (pos == 3) { // Caso base: ya tenemos x,y,z
        if (sol.x + sol.y + sol.z == S && esValido(sol))
            imprimirSolucion(sol);
        return;
    }

    for (int i = 1; i <= S; i++) { // numeros posibles
        if (!usados[i]) { // si no esta usado el número
            usados[i] = true; // ahora lo usamos

            // donde lo asignamos
            if (pos == 0) sol.x = i;
            else if (pos == 1) sol.y = i;
            else sol.z = i;

            encontrarContraseña(pos + 1, S, sol, usados); // siguiente posicion
            usados[i] = false; // backtrack
        }
    }
}

int main() {
    int S;
    cout << "Ingrese el numero de seguridad S: ";
    cin >> S;

    Solucion sol = {0, 0, 0};
    vector<bool> usados(S + 1, false); // para evitar números repetidos

    cout << "Posibles combinaciones de la contrasena:"<<endl;
    encontrarContraseña(0, S, sol, usados);

    return 0;
}