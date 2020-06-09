//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_FABRICANTE_H
#define CONCU_SEMAFOROS_FABRICANTE_H

#define BUFFIZE_MASA 5
#define BUFFSIZE_INGREDIENTES 5

#include "HerramientaDeCorte.h"
#include "../concurrencia/Semaforo.h"
#include "../concurrencia/MemoriaCompartidaBuffer.h"
#include "../logging/Logging.h"

typedef int MASA;

class Fabricante {
public:
    Fabricante(int pizzasAFabricar);
    ~Fabricante();

    void comenzarSimulacion();

private:
    int pizzasAFabricar;

    Semaforo semaforoProduccionMasa;
    Semaforo semaforoConsumoMasa;

    void generarHerramientaDeCorte(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes);


};


#endif //CONCU_SEMAFOROS_FABRICANTE_H
