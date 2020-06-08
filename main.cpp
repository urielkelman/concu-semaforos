#include <iostream>

using namespace std;

#include <string.h>


const string DESCRIPCION_DE_USO = "Uso: ./concupizza -p $CANTIDAD_DE_PIZZAS";

int determinarCantidadDeParametros(char* argv[]) {
    int i = 0;
    while(argv[i]) i++;
    return i - 1;
}

int popularPizzas(char* argv[]){
    if(strcmp(argv[1], "2") != 0){
        return -1;
    } else {
        try {
            int cantidadDePizzas = stoi(argv[2]);
            return cantidadDePizzas;
        } catch (const invalid_argument &e) {
            cout << e.what() << "\n";
            return -1;
        }
    }
}

int main(int argc, char* argv[]) {
    int cantidadDeParametros = determinarCantidadDeParametros(argv);

    if(cantidadDeParametros !=  2){
        cout << DESCRIPCION_DE_USO << "\n";
        return 0;
    }

    int cantidadDePizzas = popularPizzas(argv);
    if(cantidadDePizzas < 0){
        cout << DESCRIPCION_DE_USO << "\n";
    }


    return 0;
}
