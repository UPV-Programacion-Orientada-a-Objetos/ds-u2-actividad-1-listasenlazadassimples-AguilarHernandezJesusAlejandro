/**
 * @file ListaGestion.cpp
 * @brief Implementación de la lista de gestión polimórfica
 */

#include "ListaGestion.h"
#include <cstring>
#include <iostream>

ListaGestion::ListaGestion() : cabeza(nullptr), tamano(0) {
    std::cout << "[ListaGestion] Sistema de gestión inicializado.\n";
}

ListaGestion::~ListaGestion() {
    std::cout << "\n--- Liberación de Memoria en Cascada ---\n";
    
    NodoSensor* actual = cabeza;
    while (actual != nullptr) {
        NodoSensor* temp = actual;
        actual = actual->siguiente;
        
        std::cout << "[Destructor General] Liberando Nodo: " 
                  << temp->sensor->obtenerNombre() << "\n";
        
        // CRÍTICO: delete llama al destructor virtual, ejecutando
        // el destructor de la clase derivada correcta
        delete temp->sensor;
        delete temp;
    }
    
    std::cout << "Sistema cerrado. Memoria limpia.\n";
}

void ListaGestion::insertarSensor(SensorBase* sensor) {
    NodoSensor* nuevoNodo = new NodoSensor(sensor);
    
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        NodoSensor* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    
    tamano++;
    std::cout << "[ListaGestion] Sensor '" << sensor->obtenerNombre() 
              << "' insertado en la lista de gestión.\n";
}

SensorBase* ListaGestion::buscarSensor(const char* nombre) {
    NodoSensor* actual = cabeza;
    
    while (actual != nullptr) {
        if (strcmp(actual->sensor->obtenerNombre(), nombre) == 0) {
            return actual->sensor;
        }
        actual = actual->siguiente;
    }
    
    return nullptr;
}

void ListaGestion::procesarTodosSensores() {
    if (cabeza == nullptr) {
        std::cout << "[ListaGestion] No hay sensores para procesar.\n";
        return;
    }
    
    std::cout << "\n========================================\n";
    std::cout << "  EJECUTANDO PROCESAMIENTO POLIMÓRFICO  \n";
    std::cout << "========================================\n";
    
    NodoSensor* actual = cabeza;
    int contador = 1;
    
    while (actual != nullptr) {
        std::cout << "\n[" << contador << "/" << tamano << "] ";
        
        // POLIMORFISMO EN ACCIÓN:
        // Aunque sensor es un puntero a SensorBase*, la llamada
        // a procesarLectura() ejecutará el método de la clase derivada
        // gracias al método virtual puro
        actual->sensor->procesarLectura();
        
        actual = actual->siguiente;
        contador++;
    }
    
    std::cout << "\n========================================\n";
}

void ListaGestion::imprimirTodosSensores() const {
    if (cabeza == nullptr) {
        std::cout << "[ListaGestion] No hay sensores registrados.\n";
        return;
    }
    
    std::cout << "\n========================================\n";
    std::cout << "     SENSORES REGISTRADOS (" << tamano << ")     \n";
    std::cout << "========================================\n";
    
    NodoSensor* actual = cabeza;
    
    while (actual != nullptr) {
        actual->sensor->imprimirInfo();
        actual = actual->siguiente;
    }
}

int ListaGestion::obtenerTamano() const {
    return tamano;
}

bool ListaGestion::estaVacia() const {
    return cabeza == nullptr;
}
