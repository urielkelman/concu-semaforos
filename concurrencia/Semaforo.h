//
// Created by urielkelman on 7/6/20.
//

#ifndef CONCU_SEMAFOROS_SEMAFORO_H
#define CONCU_SEMAFOROS_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

using namespace std;

class Semaforo {

private:
    int id;
    int valorInicial;

    int inicializar () const;

public:
    Semaforo(char letra, const int valorInicial);
    ~Semaforo();

    string archivo = "/bin/bash";

    int p() const; // decrementa
    int v() const; // incrementa
    int w() const; // espera a que llegue a cero
    void eliminar () const;
};


#endif //CONCU_SEMAFOROS_SEMAFORO_H
