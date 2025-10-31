/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los tipos de sensores
 * @author Sistema IoT
 * @date 2025
 */

#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <iostream>

/**
 * @class SensorBase
 * @brief Clase abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase establece el contrato que todas las clases derivadas deben cumplir.
 * Utiliza métodos virtuales puros para forzar la implementación en las subclases.
 */
class SensorBase {
protected:
    char nombre[50];  ///< Identificador único del sensor

public:
    /**
     * @brief Constructor de la clase base
     * @param nombre Identificador del sensor
     */
    SensorBase(const char* nombre);

    /**
     * @brief Destructor virtual para asegurar limpieza polimórfica
     * 
     * CRÍTICO: El destructor debe ser virtual para garantizar que se llame
     * al destructor de la clase derivada cuando se elimine a través de un
     * puntero a la clase base.
     */
    virtual ~SensorBase();

    /**
     * @brief Método virtual puro para procesar las lecturas del sensor
     * 
     * Cada clase derivada debe implementar su propia lógica de procesamiento.
     * Por ejemplo:
     * - SensorTemperatura: eliminar valor más bajo
     * - SensorPresion: calcular promedio
     */
    virtual void procesarLectura() = 0;

    /**
     * @brief Método virtual puro para imprimir información del sensor
     */
    virtual void imprimirInfo() const = 0;

    /**
     * @brief Método virtual puro para registrar una lectura desde cadena
     * @param valor Valor de la lectura en formato string
     */
    virtual void registrarLecturaDesdeString(const char* valor) = 0;

    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero al array de caracteres con el nombre
     */
    const char* obtenerNombre() const;
};

#endif // SENSORBASE_H
