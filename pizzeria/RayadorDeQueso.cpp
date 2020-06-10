//
// Created by urielkelman on 8/6/20.
//

#include "RayadorDeQueso.h"

RayadorDeQueso::RayadorDeQueso(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes,
Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno, int pizzasAQuesear) :
        semaforoProduccionIngredientes(semaforoProduccionIngredientes),
        semaforoConsumoIngredientes(semaforoConsumoIngredientes),
        semaforoProduccionHorno(semaforoProduccionHorno),
        semaforoConsumoHorno(semaforoConsumoHorno),
        pizzasAQuesear(pizzasAQuesear),
        bufferMasasConIngredientes('b', BUFFSIZE_INGREDIENTES),
        bufferHorno('c', BUFFSIZE_HORNO){
    LOG_DEBUG("Inicializando proceso rayador de queso. Id del proceso: " + to_string(getpid()));
    this->comenzarAQuesear();
}

void RayadorDeQueso::comenzarAQuesear() {
    for(int i = 0; i < this->pizzasAQuesear; i++){
        LOG_DEBUG("Esperando por masa con ingredientes agregados");
        this->semaforoProduccionIngredientes.p();
        int posicionALeer = i % BUFFSIZE_INGREDIENTES;
        MasaConIngredientes masaConIngredientes = this->bufferMasasConIngredientes.leerPosicion(posicionALeer);
        LOG_DEBUG("Se leyo masa: " + to_string(masaConIngredientes) + " de la posicion: " + to_string(posicionALeer) + ""
                  " del buffer");
        this->semaforoConsumoIngredientes.v();
        this->agregarQuesoYHornear(masaConIngredientes);
    }

    this->bufferMasasConIngredientes.liberar();
    this->bufferHorno.liberar();

    exit(0);
}

void RayadorDeQueso::agregarQuesoYHornear(MasaConIngredientes masaConIngredientes){
    LOG_DEBUG("Agregando queso a la masa con ingredientes recibida");
    sleep(1);

    MasaConQueso masaConQueso = masaConIngredientes;
    int posicionAEscribir = this->cantidadQueseada % BUFFSIZE_HORNO;
    this->cantidadQueseada++;
    this->semaforoConsumoHorno.p();
    LOG_DEBUG("Se deposita masa con queso " + to_string(masaConQueso)
              + " en la posicion " + to_string(posicionAEscribir) + " del horno");
    this->bufferHorno.escribirPosicion(masaConQueso, posicionAEscribir);
    this->semaforoProduccionHorno.v();
}

RayadorDeQueso::~RayadorDeQueso() {

}




