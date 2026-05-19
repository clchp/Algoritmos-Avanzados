#include <iostream>

using namespace std;

#define REGIONES 8
#define VALIDACIONES 3

void resolver_validaciones(int data[REGIONES]) {
    /*
        data[0] = Lima
        data[1] = Costa Sur
        data[2] = Costa Norte
        data[3] = Sierra Centro
        data[4] = Sierra Norte
        data[5] = Sierra Sur
        data[6] = Extranjero
        data[7] = Oriente
    */
    // MATRIZ DP (tabla de resultados)
    int dp[VALIDACIONES][2];
    // VALIDACION 1: Que se cumpla la suma total que me piden
    int total = 0;
    for (int i = 0; i < REGIONES; i++) {
        total += data[i];
    }

    dp[0][0] = total;
    dp[0][1] = (total == 95000);

    // VALIDACION 2: la suma de extranjero y oriente debe cumplir con uan cantidad
    int suma_oriente_extranjero =data[7] + data[6];
    dp[1][0] = suma_oriente_extranjero;
    dp[1][1] = (suma_oriente_extranjero == 7000);

    // VALIDACION 3: que la diferencia entre grupo1 y grupo2 debe ser segun como me la indican
    int grupo1 =
        data[6] + // extranjero
        data[7] + // oriente
        data[1] + // costa sur
        data[3];  // sierra centro

    int grupo2 =
        data[2] + // costa norte
        data[4];  // sierra norte

    int diferencia = grupo2 - grupo1;

    dp[2][0] = diferencia;
    dp[2][1] = (diferencia == 3000);

    // MOSTRAR RESULTADOS

    cout << "VALIDACION 1" << endl;
    cout << "Total actas: "<< dp[0][0] << endl;
    if (dp[0][1]) {
        cout << "Cantidad total correcta"<< endl;
    }
    else {
        cout << "Cantidad total incorrecta"<< endl;
    }

    cout << endl;
    cout << "VALIDACION 2" << endl;
    cout << "Oriente + Extranjero: "<< dp[1][0] << endl;
    if (dp[1][1]) {
        cout << "Suma correcta"<< endl;
    }
    else {
        cout << "Suma incorrecta"<< endl;
    }

    cout << endl;
    cout << "VALIDACION 3" << endl;
    cout << "Diferencia grupos: "<< dp[2][0] << endl;

    if (dp[2][1]) {
        cout << "Diferencia correcta"<< endl;
    }
    else {
        cout << "Diferencia incorrecta"<< endl;
    }

    if (dp[0][1] and dp[1][1] and dp[2][1]) {
        cout<<"Por tal motivo se declaran las actas correctas"<<endl;
    }
    else {
        cout<<"Por tal motivo se declaran las actas incorrectas"<<endl;
    }
}

int main() {
    /*
        Lima = 35000
        Extranjero = 2500
    */
    int data[REGIONES] = {
        35000, // Lima
        6000,  // Costa Sur
        12000, // Costa Norte
        8000,  // Sierra Centro
        12000, // Sierra Norte
        15000, // Sierra Sur
        2500,  // Extranjero
        4500   // Oriente
    };

    resolver_validaciones(data);
    //nota: si tienes que ordenar, los dos ultimos siempre seran los que tengan menos y los otros funcion par abuscar y que retorne idx

    return 0;
}