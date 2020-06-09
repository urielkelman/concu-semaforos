//
// Created by urielkelman on 8/6/20.
//

#include "HerramientaDeCorte.h"

HerramientaDeCorte::HerramientaDeCorte(Semaforo semaforoProduccionMasa, Semaforo semaforoConsumoMasa,
        Semaforo semaforoConsumoIngredientes, Semaforo semaforoProduccionIngredientes, int pizzas) :
semaforoProduccionMasa(semaforoProduccionMasa),
semaforoConsumoMasa(semaforoConsumoMasa),
semaforoProduccionIngredientes(semaforoProduccionIngredientes),
semaforoConsumoIngredientes(semaforoConsumoIngredientes),
pizzasACondimentar(pizzas){
    LOG_DEBUG("Inicializando proceso encargado de cortar y agregar ingredientes. Id de proceso: " + to_string(getpid()));
    this->comenzarAConsumir();
}

void HerramientaDeCorte::comenzarAConsumir() {
    MemoriaCompartidaBuffer<MASA> bufferMasas('a', BUFFIZE_MASA);
    for(int i = 0; i < this->pizzasACondimentar; i++){
        LOG_DEBUG("Esperando por masa.");
        this->semaforoProduccionMasa.p();
        int posicionALeer = i % BUFFIZE_MASA;
        LOG_DEBUG("Se espera para leer masa de la posicion: " + to_string(posicionALeer));
        MASA masa = bufferMasas.leerPosicion(posicionALeer);
        LOG_DEBUG("Se leyo masa: " + to_string(masa));
    }

    exit(0);
}
