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
    int pizzasAQuesear;
    int cantidadQueseada = 0;

    MemoriaCompartidaBuffer<int> bufferMasasConIngredientes;
    MemoriaCompartidaBuffer<int> bufferHorno;

    Semaforo semaforoProduccionIngredientes;
    Semaforo semaforoConsumoIngredientes;
    Semaforo semaforoProduccionHorno;
    Semaforo semaforoConsumoHorno;

    void comenzarAQuesear();
    void agregarQuesoYHornear(MasaConIngredientes masaConIngredientes);

};


#endif //CONCU_SEMAFOROS_RAYADORDEQUESO_H
