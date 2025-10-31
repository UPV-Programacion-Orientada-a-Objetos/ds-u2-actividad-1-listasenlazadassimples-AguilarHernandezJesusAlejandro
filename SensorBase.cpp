/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base abstracta SensorBase
 */

#include "SensorBase.h"
#include <cstring>

SensorBase::SensorBase(const char* nombre) {
    // Copia segura del nombre del sensor
    strncpy(this->nombre, nombre, 49);
    this->nombre[49] = '\0';  // Asegura terminación nula
}

SensorBase::~SensorBase() {
    std::cout << "[Destructor Base] Sensor " << nombre << " liberado.\n";
}

const char* SensorBase::obtenerNombre() const {
    return nombre;
}
