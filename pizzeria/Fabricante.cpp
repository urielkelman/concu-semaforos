//
// Created by urielkelman on 8/6/20.
//

#include "Fabricante.h"
#include <unistd.h>

Fabricante::Fabricante(int pizzasAFabricar) :
semaforoProduccionMasa('a', 0),
semaforoConsumoMasa('b', BUFFIZE_MASA),
pizzasAFabricar(pizzasAFabricar){
    Semaforo semaforoConsumoIngredientes('c', 0);
    Semaforo semaforoProduccionIngredientes('d', BUFFSIZE_INGREDIENTES);
    this->generarHerramientaDeCorte(semaforoProduccionIngredientes, semaforoConsumoIngredientes);
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

void Fabricante::comenzarSimulacion() {
    MemoriaCompartidaBuffer<MASA> bufferMasas('a', BUFFIZE_MASA);
    for(int i = 0; i < this->pizzasAFabricar; i++){
        MASA masa = i;
        LOG_DEBUG("Moldeando masa..");
        sleep(1);
        int posicionAEscribir = i % BUFFIZE_MASA;
        LOG_DEBUG("Se deposita masa en la posicion " + to_string(posicionAEscribir) + " del buffer");
        bufferMasas.escribirPosicion(masa, posicionAEscribir);
        this->semaforoProduccionMasa.v();
    }
}
