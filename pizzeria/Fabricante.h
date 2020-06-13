//
// Created by urielkelman on 8/6/20.
//

#ifndef CONCU_SEMAFOROS_FABRICANTE_H
#define CONCU_SEMAFOROS_FABRICANTE_H

#define BUFFIZE_MASA 3
#define BUFFSIZE_INGREDIENTES 5
#define BUFFSIZE_HORNO 5

#include "HerramientaDeCorte.h"
#include "RayadorDeQueso.h"
#include "Horneador.h"
#include "../utils/NumeroAleatorio.h"
#include "../concurrencia/Semaforo.h"
#include "../concurrencia/MemoriaCompartidaBuffer.h"
#include "../logging/Logging.h"

typedef int Masa;

class Fabricante {
public:
    Fabricante(int pizzasAFabricar);
    ~Fabricante();

    void comenzarSimulacion();

private:
    Semaforo semaforoProduccionMasa;
    Semaforo semaforoConsumoMasa;

    int pizzasAFabricar;


    void generarHerramientaDeCorte(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes);
    void generarRayadorDeQueso(Semaforo semaforoProduccionIngredientes, Semaforo semaforoConsumoIngredientes,
                               Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno);
    void generarHorneador(Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno);
};


#endif //CONCU_SEMAFOROS_FABRICANTE_H
