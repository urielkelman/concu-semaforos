//
// Created by urielkelman on 8/6/20.
//

#include "Horneador.h"

Horneador::Horneador(Semaforo semaforoProduccionHorno, Semaforo semaforoConsumoHorno, int pizzasAHornear) :
semaforoProduccionHorno(semaforoProduccionHorno),
semaforoConsumoHorno(semaforoConsumoHorno),
pizzasAHornear(pizzasAHornear),
bufferHorno('c', BUFFSIZE_HORNO)
{

}
