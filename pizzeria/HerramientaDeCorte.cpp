//
// Created by urielkelman on 8/6/20.
//

#include "HerramientaDeCorte.h"
#include "Fabricante.h"
#include <unistd.h>

HerramientaDeCorte::HerramientaDeCorte(Semaforo semaforoProduccionMasa, Semaforo semaforoConsumoMasa,
        Semaforo semaforoConsumoIngredientes, Semaforo semaforoProduccionIngredientes, int pizzas) :
semaforoProduccionMasa(semaforoProduccionMasa),
semaforoConsumoMasa(semaforoConsumoMasa),
semaforoProduccionIngredientes(semaforoProduccionIngredientes),
semaforoConsumoIngredientes(semaforoConsumoIngredientes),
pizzasACondimentar(pizzas),
bufferMasas('a', BUFFIZE_MASA),
bufferMasasConIngredientes('b', BUFFSIZE_INGREDIENTES){
    LOG_DEBUG("Inicializando proceso encargado de cortar y agregar ingredientes. Id de proceso: " + to_string(getpid()));
    this->comenzarACondimentar();
}

void HerramientaDeCorte::comenzarACondimentar() {
    for(int i = 0; i < this->pizzasACondimentar; i++){
        usleep(NumeroAleatorio::Obtener());
        LOG_DEBUG("Esperando por masa.");
        this->semaforoProduccionMasa.p();
        int posicionALeer = i % BUFFIZE_MASA;
        Masa masa = this->bufferMasas.leerPosicion(posicionALeer);
        LOG_DEBUG("Se leyo masa: " + to_string(masa) + " de la posicion: " + to_string(posicionALeer) + " del buffer");
        this->semaforoConsumoMasa.v();
        this->agregarIngredientesYPasarARayador(masa);
    }

    this->semaforoProduccionIngredientes.w();
    LOG_DEBUG("Elminando semaforo de produccion de ingredientes");
    this->semaforoProduccionIngredientes.eliminar();
    LOG_DEBUG("Eliminando semaforo de consumo de ingredientes");
    this->semaforoConsumoIngredientes.eliminar();

    this->bufferMasas.liberar();
    this->bufferMasasConIngredientes.liberar();

    exit(0);
}

void HerramientaDeCorte::agregarIngredientesYPasarARayador(Masa masa) {
    LOG_DEBUG("Cortando y agregando ingredientes a la masa recibida.");
    usleep(NumeroAleatorio::Obtener());
    MasaConIngredientes masaConIngredientes = masa;
    int posicionAEscribir = this->cantidadCondimentada % BUFFSIZE_INGREDIENTES;
    this->cantidadCondimentada++;
    this->semaforoConsumoIngredientes.p();
    LOG_DEBUG("Se deposita masa con ingredientes " + to_string(masaConIngredientes)
    + " en la posicion " + to_string(posicionAEscribir) + " del buffer");
    this->bufferMasasConIngredientes.escribirPosicion(masaConIngredientes, posicionAEscribir);
    this->semaforoProduccionIngredientes.v();

}

HerramientaDeCorte::~HerramientaDeCorte() {

}
