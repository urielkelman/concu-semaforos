//
// Created by urielkelman on 7/6/20.
//

#include "Logging.h"
#include <sys/time.h>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

NivelDeLogging Logging::nivelDeLogging;
vector<string> Logging::nivelLogStrings = {"INFO", "DEBUG"};
int Logging::numeroMagicoDePadding = 30;
string Logging::ruta = "log.txt";
Semaforo Logging::semaforoEscritura = Semaforo('Z', 1);
ofstream Logging::file;

NivelDeLogging Logging::ObtenerNivelDeLogging(string nivelDeLog) {
    if(nivelLogStrings[INFO] == nivelDeLog){
        return INFO;
    } else if (nivelLogStrings[DEBUG] == nivelDeLog){
        return DEBUG;
    } else {
        throw "Valor de nivel de logging invalido. Utilice DEBUG o INFO";
    }
}

void Logging::Inicializar(NivelDeLogging _nivelDeLogging) {
    nivelDeLogging = _nivelDeLogging;
    file.open(ruta);
    LOG_INFO("Inicializando log.");
}

void Logging::Loggear(NivelDeLogging _nivelDeLogging, string mensaje, string pathArchivo, long numeroDelinea) {
    if(_nivelDeLogging > nivelDeLogging) return;
    else {
        string archivo = obtenerNombreArchivo(pathArchivo);
        string time = obtenerTiempo();
        stringstream linea;
        linea << "[" << nivelLogStrings[_nivelDeLogging] << "] ";
        string archivoMasLinea = archivo + ":" + to_string(numeroDelinea);
        string archivoMasLineaPaddeado = archivoMasLinea.append(numeroMagicoDePadding - archivoMasLinea.length(), ' ');
        linea << archivoMasLineaPaddeado;
        linea << time << " | ";
        linea << mensaje << "\n";
        string lineaString = linea.str();
        semaforoEscritura.p();
        file << lineaString;
        file.flush();
        cerr << lineaString;
        semaforoEscritura.v();
    }
}

string Logging::obtenerTiempo() {
    time_t ahora = time(nullptr);
    struct tm *timeinfo;
    char buffer[100];
    time(&ahora);
    timeinfo = localtime(&ahora);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    string tiempo = string(buffer);
    return tiempo;
}

void Logging::Finalizar() {
    Logging::semaforoEscritura.eliminar();
    file.close();
    LOG_INFO("Cerrando archivo de log.");
}

string Logging::obtenerNombreArchivo(string rutaArchivo) {
    istringstream ss(rutaArchivo);
    vector<string> routes;
    string buf;
    while(getline(ss, buf, '/')) {
        routes.push_back(buf);
    }

    return routes.back();
}