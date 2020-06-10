//
// Created by urielkelman on 7/6/20.
//

#include "Semaforo.h"

Semaforo::Semaforo(char letra, const int valorInicial) : valorInicial(valorInicial) {
    key_t clave = ftok(this->archivo.c_str(), letra );
    this->id = semget(clave, 1, 0666 | IPC_CREAT);
    this->inicializar();
}

Semaforo::~Semaforo() {
}

int Semaforo::inicializar () const {
    union semnum {
        int val;
        struct semid_ds* buf;
        ushort* array;
    };

    semnum init;
    init.val = this->valorInicial;
    int resultado = semctl(this->id, 0, SETVAL, init);
    return resultado;
}

int Semaforo::p() const {
    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = -1;	// restar 1 al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop(this->id, &operacion, 1 );
    return resultado;
}

int Semaforo:: v() const {
    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = 1;	// sumar 1 al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop (this->id, &operacion, 1 );
    return resultado;
}

void Semaforo::eliminar() const {
    semctl(this->id, 0, IPC_RMID);
}

int Semaforo::w() const {
    struct sembuf operacion;

    operacion.sem_num = 0;
    operacion.sem_op  = 0;
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop (this->id, &operacion, 1 );
    return resultado;
}
