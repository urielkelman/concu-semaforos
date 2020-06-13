//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_HORNEADOR_H
#define CONCU_SEMAFOROS_HORNEADOR_H

#include "Fabricante.h"

typedef int MasaHorneada ;

class Horneador {
public:
    Horneador(Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno, int pizzasAHornear);
    ~Horneador();
private:
    Semaforo semaforoProduccionHorno;
    Semaforo semaforoConsumoHorno;

    int pizzasAHornear;

    MemoriaCompartidaBuffer<int> bufferHorno;

    void retirarPizzasHorneadas();
};


#endif //CONCU_SEMAFOROS_HORNEADOR_H
