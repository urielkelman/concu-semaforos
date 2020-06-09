//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_HERRAMIENTADECORTE_H
#define CONCU_SEMAFOROS_HERRAMIENTADECORTE_H

#include "../concurrencia/Semaforo.h"
#include "../logging/Logging.h"
#include "../concurrencia/MemoriaCompartidaBuffer.h"
#include "Fabricante.h"
#include <unistd.h>

class HerramientaDeCorte {
public:
    HerramientaDeCorte(Semaforo semaforoProduccionMasa, Semaforo semaforoConsumoMasa,
            Semaforo semaforoConsumoIngredientes, Semaforo semaforoProduccionIngredientes,
            int pizzasACondimentar);

private:
    int pizzasACondimentar;

    Semaforo semaforoProduccionMasa;
    Semaforo semaforoConsumoMasa;
    Semaforo semaforoProduccionIngredientes;
    Semaforo semaforoConsumoIngredientes;

    void comenzarAConsumir();
};


#endif //CONCU_SEMAFOROS_HERRAMIENTADECORTE_H
