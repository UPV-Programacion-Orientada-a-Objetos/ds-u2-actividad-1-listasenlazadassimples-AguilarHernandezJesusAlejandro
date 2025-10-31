/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión
 */

#include "SensorPresion.h"
#include <cstdlib>

SensorPresion::SensorPresion(const char* nombre) 
    : SensorBase(nombre) {
    std::cout << "[Sensor Presion] " << nombre << " creado.\n";
}

SensorPresion::~SensorPresion() {
    std::cout << "[Destructor SensorPresion] " << nombre 
              << " - Liberando historial de presiones...\n";
    // El destructor de ListaSensor se encarga automáticamente de liberar memoria
}

void SensorPresion::registrarLectura(int presion) {
    historial.insertarAlFinal(presion);
    std::cout << "[" << nombre << "] Presión registrada: " << presion << " kPa\n";
}

void SensorPresion::procesarLectura() {
    std::cout << "\n-> Procesando Sensor " << nombre << " (Presión)...\n";
    
    if (historial.estaVacia()) {
        std::cout << "[" << nombre << "] No hay lecturas para procesar.\n";
        return;
    }
    
    // Calcular promedio de todas las lecturas
    int promedio = historial.calcularPromedio();
    std::cout << "[Sensor Presion] Promedio de " << historial.obtenerTamano() 
              << " lecturas: " << promedio << " kPa\n";
}

void SensorPresion::imprimirInfo() const {
    std::cout << "\n=== Sensor de Presión: " << nombre << " ===\n";
    std::cout << "Tipo: PRESIÓN (int)\n";
    std::cout << "Número de lecturas: " << historial.obtenerTamano() << "\n";
    
    if (!historial.estaVacia()) {
        std::cout << "Lecturas actuales: ";
        historial.imprimir();
    } else {
        std::cout << "Sin lecturas registradas.\n";
    }
    std::cout << "=====================================\n";
}

void SensorPresion::registrarLecturaDesdeString(const char* valor) {
    int presion = atoi(valor);  // Convierte string a int
    registrarLectura(presion);
}
