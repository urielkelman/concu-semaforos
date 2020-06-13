//
// Created by urielkelman on 8/6/20.
//

#include "Horneador.h"

Horneador::Horneador(Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno, int pizzasAHornear) :
semaforoProduccionHorno(semaforoProduccionHorno),
semaforoConsumoHorno(semaforoConsumoHorno),
pizzasAHornear(pizzasAHornear),
bufferHorno('c', BUFFSIZE_HORNO){
    LOG_DEBUG("Inicializando proceso horneador. Id del proceso: " + to_string(getpid()));
    this->retirarPizzasHorneadas();
}

Horneador::~Horneador() {

}

void Horneador::retirarPizzasHorneadas() {
    for(int i = 0; i < this->pizzasAHornear; i++){
        LOG_DEBUG("Esperando para retirar la proxima pizza del horno");
        usleep(NumeroAleatorio::Obtener());
        this->semaforoProduccionHorno.p();
        int posicionALeer = i % BUFFSIZE_HORNO;
        MasaHorneada masaHorneada = this->bufferHorno.leerPosicion(posicionALeer);
        LOG_DEBUG("Se leyo masa horneada: " + to_string(masaHorneada) + " de la posicion: " +
        to_string(posicionALeer) + " del horno.");
        this->semaforoConsumoHorno.v();
    }

    this->bufferHorno.liberar();

    exit(0);
}
