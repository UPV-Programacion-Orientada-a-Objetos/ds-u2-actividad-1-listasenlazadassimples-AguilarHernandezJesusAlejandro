/**
 * @file SensorPresion.h
 * @brief Sensor especializado para mediciones de presión
 * @author Sistema IoT
 * @date 2025
 */

#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorPresion
 * @brief Sensor que maneja lecturas de presión en formato int
 * 
 * Este sensor almacena lecturas de presión y puede:
 * - Calcular promedios
 * - Procesar datos de forma específica para presión
 * - Manejar valores enteros (kPa, PSI, etc.)
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;  ///< Lista de lecturas de presión

public:
    /**
     * @brief Constructor del sensor de presión
     * @param nombre Identificador del sensor
     */
    SensorPresion(const char* nombre);

    /**
     * @brief Destructor - Libera el historial de lecturas
     */
    ~SensorPresion() override;

    /**
     * @brief Registra una nueva lectura de presión
     * @param presion Valor de presión (unidad arbitraria)
     */
    void registrarLectura(int presion);

    /**
     * @brief Implementación del procesamiento polimórfico
     * 
     * Calcula el promedio de todas las lecturas de presión
     */
    void procesarLectura() override;

    /**
     * @brief Imprime información del sensor y sus lecturas
     */
    void imprimirInfo() const override;

    /**
     * @brief Registra una lectura desde una cadena de texto
     * @param valor Cadena con el valor de presión
     */
    void registrarLecturaDesdeString(const char* valor) override;
};

#endif // SENSORPRESION_H
