#include <iostream>

using namespace std;

int resolver_fibonacci(int n) {
    int fibonacci[n+1];
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    for (int i = 2; i <= n; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }
    return fibonacci[n];
}

int main(){
    cout<<"Ingrese el valor de fibonnaci que quiere calcular: ";
    int n;
    cin>>n;
    cout<<"El valor de fibonnaci de ["<<n<<"] es "<<resolver_fibonacci(n)<<endl;
    return 0;
}