/**
 * @file ListaGestion.h
 * @brief Lista de gestión polimórfica para sensores
 * @author Sistema IoT
 * @date 2025
 */

#ifndef LISTAGESTION_H
#define LISTAGESTION_H

#include "SensorBase.h"

/**
 * @brief Nodo para almacenar punteros a SensorBase
 */
struct NodoSensor {
    SensorBase* sensor;        ///< Puntero polimórfico a la clase base
    NodoSensor* siguiente;     ///< Puntero al siguiente nodo

    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor
     */
    NodoSensor(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @class ListaGestion
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * 
 * Esta lista almacena punteros a SensorBase*, permitiendo almacenar
 * diferentes tipos de sensores (SensorTemperatura, SensorPresion, etc.)
 * en una única estructura de datos.
 */
class ListaGestion {
private:
    NodoSensor* cabeza;  ///< Primer nodo de la lista
    int tamano;          ///< Número de sensores en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    ListaGestion();

    /**
     * @brief Destructor - Libera todos los sensores y nodos
     * 
     * IMPORTANTE: Este destructor es crítico ya que debe:
     * 1. Liberar cada objeto sensor (llamando a su destructor virtual)
     * 2. Liberar cada nodo de la lista
     */
    ~ListaGestion();

    /**
     * @brief Inserta un nuevo sensor en la lista
     * @param sensor Puntero al sensor a insertar
     */
    void insertarSensor(SensorBase* sensor);

    /**
     * @brief Busca un sensor por nombre
     * @param nombre Nombre del sensor a buscar
     * @return Puntero al sensor o nullptr si no se encuentra
     */
    SensorBase* buscarSensor(const char* nombre);

    /**
     * @brief Procesa todos los sensores de forma polimórfica
     * 
     * Itera sobre todos los sensores y llama a procesarLectura()
     * de cada uno, ejecutando la implementación específica de cada clase.
     */
    void procesarTodosSensores();

    /**
     * @brief Imprime información de todos los sensores
     */
    void imprimirTodosSensores() const;

    /**
     * @brief Obtiene el número de sensores en la lista
     * @return Número de sensores
     */
    int obtenerTamano() const;

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTAGESTION_H
