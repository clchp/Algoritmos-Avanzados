#include <iostream>
#include <iomanip>

using namespace std;

int main(){

    int n, cont=0;
    cout<<"Ingrese un número para la conjetura de Collatz: ";
    cin>>n;

    while(n!=1){
        cout<<n<<" ";
        if(n%2==0){//si es par
            n=n/2;
        }
        else{
            n=n*3+1;
        }
        cont++;
    }
    cout<<"1 "<<endl;
    cout<<"Se llego al numero 1 con: "<<cont<<" pasos";

    return 0;
}