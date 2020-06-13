//
// Created by urielkelman on 8/6/20.
//

#include "Fabricante.h"
#include <unistd.h>
#include <wait.h>

Fabricante::Fabricante(int pizzasAFabricar) :
semaforoProduccionMasa('a', 0),
semaforoConsumoMasa('b', BUFFIZE_MASA),
pizzasAFabricar(pizzasAFabricar){
    LOG_DEBUG("Inicializando proceso de fabricacion de masas. Id de proceso: " + to_string(getpid()));
    Semaforo semaforoProduccionIngredientes('c', 0);
    Semaforo semaforoConsumoIngredientes('d', BUFFSIZE_INGREDIENTES);
    Semaforo semaforoProduccionHorno('e', 0);
    Semaforo semaforoConsumoHorno('f', BUFFSIZE_HORNO);
    this->generarHerramientaDeCorte(semaforoProduccionIngredientes, semaforoConsumoIngredientes);
    this->generarRayadorDeQueso(semaforoProduccionIngredientes, semaforoConsumoIngredientes,
                                semaforoProduccionHorno, semaforoConsumoHorno);
    this->generarHorneador(semaforoProduccionHorno, semaforoConsumoHorno);
}

Fabricante::~Fabricante() {

}

void Fabricante::generarHerramientaDeCorte(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes) {
    pid_t id = fork();
    if(id == 0){
        HerramientaDeCorte herramientaDeCorte(this->semaforoProduccionMasa, this->semaforoConsumoMasa,
                semaforoConsumoIngredientes, semaforoProduccionIngredientes, this->pizzasAFabricar);
    }
}

void Fabricante::generarRayadorDeQueso(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes,
                                       Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno) {
    pid_t id = fork();
    if(id == 0){
        RayadorDeQueso rayadorDeQueso(semaforoProduccionIngredientes, semaforoConsumoIngredientes,
                                      semaforoProduccionHorno, semaforoConsumoHorno, this->pizzasAFabricar);
    }
}

void Fabricante::generarHorneador(Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno) {
    pid_t id = fork();
    if(id == 0){
        Horneador horneador(semaforoProduccionHorno, semaforoConsumoHorno, this->pizzasAFabricar);
    }
}

void Fabricante::comenzarSimulacion() {
    MemoriaCompartidaBuffer<Masa> bufferMasas('a', BUFFIZE_MASA);
    for(int i = 0; i < this->pizzasAFabricar; i++){
        Masa masa = i;
        LOG_DEBUG("Moldeando masa..");
        usleep(NumeroAleatorio::Obtener());
        int posicionAEscribir = i % BUFFIZE_MASA;
        this->semaforoConsumoMasa.p();
        LOG_DEBUG("Se deposita masa " + to_string(masa) + " en la posicion " + to_string(posicionAEscribir) + " del buffer");
        bufferMasas.escribirPosicion(masa, posicionAEscribir);
        this->semaforoProduccionMasa.v();
    }
    this->semaforoProduccionMasa.w();
    LOG_DEBUG("Eliminado semaforo de produccion de masa.");
    this->semaforoProduccionMasa.eliminar();
    LOG_DEBUG("Eliminando semaforo de consumo de masa");
    this->semaforoConsumoMasa.eliminar();

    int status;
    while ((wait(&status)) > 0);

    bufferMasas.liberar();

    LOG_INFO("Terminando simulacion.");

    Logging::Finalizar();

    exit(0);
}


