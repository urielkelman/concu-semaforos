cmake_minimum_required(VERSION 3.16)
project(concu_semaforos)

set(CMAKE_CXX_STANDARD 11)

add_executable(concu_semaforos main.cpp logging/Logging.cpp logging/Logging.h concurrencia/MemoriaCompartida.h concurrencia/Semaforo.cpp concurrencia/Semaforo.h)