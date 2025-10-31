/**
 * @file SensorTemperatura.h
 * @brief Sensor especializado para mediciones de temperatura
 * @author Sistema IoT
 * @date 2025
 */

#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorTemperatura
 * @brief Sensor que maneja lecturas de temperatura en formato float
 * 
 * Este sensor almacena lecturas de temperatura y puede:
 * - Calcular promedios
 * - Eliminar el valor más bajo (outlier)
 * - Procesar datos de forma específica para temperatura
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;  ///< Lista de lecturas de temperatura

public:
    /**
     * @brief Constructor del sensor de temperatura
     * @param nombre Identificador del sensor
     */
    SensorTemperatura(const char* nombre);

    /**
     * @brief Destructor - Libera el historial de lecturas
     */
    ~SensorTemperatura() override;

    /**
     * @brief Registra una nueva lectura de temperatura
     * @param temperatura Valor de temperatura en grados
     */
    void registrarLectura(float temperatura);

    /**
     * @brief Implementación del procesamiento polimórfico
     * 
     * Elimina la lectura más baja y calcula el promedio de las restantes
     */
    void procesarLectura() override;

    /**
     * @brief Imprime información del sensor y sus lecturas
     */
    void imprimirInfo() const override;

    /**
     * @brief Registra una lectura desde una cadena de texto
     * @param valor Cadena con el valor de temperatura
     */
    void registrarLecturaDesdeString(const char* valor) override;
};

#endif // SENSORTEMPERATURA_H
