cmake_minimum_required(VERSION 3.16)
project(concu_semaforos)

set(CMAKE_CXX_STANDARD 14)

include_directories(concurrencia)
include_directories(logging)
include_directories(pizzeria)

add_executable(concu_semaforos
        concurrencia/MemoriaCompartidaBuffer.h
        concurrencia/Semaforo.cpp
        concurrencia/Semaforo.h
        logging/Logging.cpp
        logging/Logging.h
        pizzeria/Fabricante.cpp
        pizzeria/Fabricante.h
        pizzeria/HerramientaDeCorte.cpp
        pizzeria/HerramientaDeCorte.h
        pizzeria/Horneador.cpp
        pizzeria/Horneador.h
        pizzeria/RayadorDeQueso.cpp
        pizzeria/RayadorDeQueso.h
        main.cpp)
