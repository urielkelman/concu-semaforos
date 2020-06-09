//
// Created by urielkelman on 7/6/20.
//

#ifndef CONCU_SEMAFOROS_MEMORIACOMPARTIDABUFFER_H
#define CONCU_SEMAFOROS_MEMORIACOMPARTIDABUFFER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>


template <class T> class MemoriaCompartidaBuffer {

private:
    int	shmId;
    T*	datos;
    int	cantidadProcesosAdosados() const;
    std::string archivo = "/bin/echo";

public:
    MemoriaCompartidaBuffer();
    MemoriaCompartidaBuffer(const char letra, int longitud);
    ~MemoriaCompartidaBuffer();

    void crear(const char letra, int longitud);
    void liberar();

    void escribirPosicion (const T& dato, int posicion);
    T leerPosicion (int posicion) const;
};

template <class T> MemoriaCompartidaBuffer<T> :: MemoriaCompartidaBuffer(): shmId(0), datos(NULL) {
}

template <class T> MemoriaCompartidaBuffer <T> :: MemoriaCompartidaBuffer(const char letra, int longitud): shmId(0), datos(NULL) {
    this->crear(letra, longitud);
}

template <class T> void MemoriaCompartidaBuffer<T> :: crear(const char letra, int longitud) {
    key_t clave = ftok(archivo.c_str(), 'D');

    if (clave > 0) {
        this->shmId = shmget (clave, sizeof(T) * longitud, 0644|IPC_CREAT);
        if (this->shmId > 0) {
            void* tmpPtr = shmat (this->shmId, NULL, 0);
            if (tmpPtr != (void*) -1) {
                this->datos = static_cast<T*> (tmpPtr);
            } else {
                std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
                throw mensaje;
            }
        } else {
            std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
            throw mensaje;
        }
    } else {
        std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}



template <class T> void MemoriaCompartidaBuffer<T> :: liberar() {
    int errorDt = shmdt ((void *) this->datos);

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if(procAdosados == 0) {
            shmctl (this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::string mensaje = std::string("Error en shmdt(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template <class T> MemoriaCompartidaBuffer<T> :: ~MemoriaCompartidaBuffer () {
    int errorDt = shmdt (static_cast<void*> (this->datos));

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
    }
}

template <class T> void MemoriaCompartidaBuffer<T> :: escribirPosicion (const T& dato, int posicion) {
    *(this->datos + posicion * sizeof(T)) = dato;
}

template <class T> T MemoriaCompartidaBuffer<T> :: leerPosicion(int posicion) const {
    return *(this->datos + posicion * sizeof(T));
}

template <class T> int MemoriaCompartidaBuffer<T> :: cantidadProcesosAdosados () const {
    shmid_ds estado;
    shmctl ( this->shmId,IPC_STAT,&estado );
    return estado.shm_nattch;
}


#endif //CONCU_SEMAFOROS_MEMORIACOMPARTIDABUFFER_H
