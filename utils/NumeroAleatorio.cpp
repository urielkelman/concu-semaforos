//
// Created by urielkelman on 10/6/20.
//

#include "NumeroAleatorio.h"
#include <stdlib.h>

int NumeroAleatorio::Obtener() {
    return  (rand() % 10) * 10000;
}
