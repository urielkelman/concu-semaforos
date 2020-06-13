//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_HERRAMIENTADECORTE_H
#define CONCU_SEMAFOROS_HERRAMIENTADECORTE_H

#include "../concurrencia/Semaforo.h"
#include "../logging/Logging.h"
#include "../concurrencia/MemoriaCompartidaBuffer.h"

typedef int Masa;
typedef int MasaConIngredientes ;

class HerramientaDeCorte {
public:
    HerramientaDeCorte(Semaforo semaforoProduccionMasa, Semaforo semaforoConsumoMasa,
            Semaforo semaforoConsumoIngredientes, Semaforo semaforoProduccionIngredientes,
            int pizzasACondimentar);
    ~HerramientaDeCorte();

private:
    int cantidadCondimentada = 0;

    Semaforo semaforoProduccionMasa;
    Semaforo semaforoConsumoMasa;
    Semaforo semaforoProduccionIngredientes;
    Semaforo semaforoConsumoIngredientes;

    int pizzasACondimentar;

    MemoriaCompartidaBuffer<int> bufferMasas;
    MemoriaCompartidaBuffer<int> bufferMasasConIngredientes;

    void comenzarACondimentar();
    void agregarIngredientesYPasarARayador(Masa masa);
};


#endif //CONCU_SEMAFOROS_HERRAMIENTADECORTE_H
