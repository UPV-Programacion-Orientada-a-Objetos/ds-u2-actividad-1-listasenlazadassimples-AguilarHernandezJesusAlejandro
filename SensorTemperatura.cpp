/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura
 */

#include "SensorTemperatura.h"
#include <cstdlib>
#include <iomanip>

SensorTemperatura::SensorTemperatura(const char* nombre) 
    : SensorBase(nombre) {
    std::cout << "[Sensor Temp] " << nombre << " creado.\n";
}

SensorTemperatura::~SensorTemperatura() {
    std::cout << "[Destructor SensorTemperatura] " << nombre 
              << " - Liberando historial de temperaturas...\n";
    // El destructor de ListaSensor se encarga automáticamente de liberar memoria
}

void SensorTemperatura::registrarLectura(float temperatura) {
    historial.insertarAlFinal(temperatura);
    std::cout << "[" << nombre << "] Temperatura registrada: " 
              << std::fixed << std::setprecision(2) << temperatura << "°C\n";
}

void SensorTemperatura::procesarLectura() {
    std::cout << "\n-> Procesando Sensor " << nombre << " (Temperatura)...\n";
    
    if (historial.estaVacia()) {
        std::cout << "[" << nombre << "] No hay lecturas para procesar.\n";
        return;
    }
    
    if (historial.obtenerTamano() == 1) {
        float promedio = historial.calcularPromedio();
        std::cout << "[Sensor Temp] Solo hay 1 lectura. Promedio: " 
                  << std::fixed << std::setprecision(2) << promedio << "°C\n";
        return;
    }
    
    // Eliminar el valor más bajo (posible outlier)
    float minimo = historial.eliminarMinimo();
    std::cout << "[Sensor Temp] Lectura más baja eliminada: " 
              << std::fixed << std::setprecision(2) << minimo << "°C\n";
    
    // Calcular promedio de las lecturas restantes
    if (!historial.estaVacia()) {
        float promedio = historial.calcularPromedio();
        std::cout << "[Sensor Temp] Promedio de lecturas restantes (" 
                  << historial.obtenerTamano() << "): " 
                  << std::fixed << std::setprecision(2) << promedio << "°C\n";
    }
}

void SensorTemperatura::imprimirInfo() const {
    std::cout << "\n=== Sensor de Temperatura: " << nombre << " ===\n";
    std::cout << "Tipo: TEMPERATURA (float)\n";
    std::cout << "Número de lecturas: " << historial.obtenerTamano() << "\n";
    
    if (!historial.estaVacia()) {
        std::cout << "Lecturas actuales: ";
        historial.imprimir();
    } else {
        std::cout << "Sin lecturas registradas.\n";
    }
    std::cout << "=====================================\n";
}

void SensorTemperatura::registrarLecturaDesdeString(const char* valor) {
    float temperatura = atof(valor);  // Convierte string a float
    registrarLectura(temperatura);
}
