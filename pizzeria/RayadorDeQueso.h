//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_RAYADORDEQUESO_H
#define CONCU_SEMAFOROS_RAYADORDEQUESO_H

#include "Fabricante.h"

typedef int MasaConQueso;

class RayadorDeQueso {
public:
    RayadorDeQueso(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes,
                   Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno, int pizzasAQuesear);
    ~RayadorDeQueso();

private:
    int cantidadQueseada = 0;

    Semaforo semaforoProduccionIngredientes;
    Semaforo semaforoConsumoIngredientes;
    Semaforo semaforoProduccionHorno;
    Semaforo semaforoConsumoHorno;

    int pizzasAQuesear;

    MemoriaCompartidaBuffer<int> bufferMasasConIngredientes;
    MemoriaCompartidaBuffer<int> bufferHorno;

    void comenzarAQuesear();
    void agregarQuesoYHornear(MasaConIngredientes masaConIngredientes);
};


#endif //CONCU_SEMAFOROS_RAYADORDEQUESO_H
