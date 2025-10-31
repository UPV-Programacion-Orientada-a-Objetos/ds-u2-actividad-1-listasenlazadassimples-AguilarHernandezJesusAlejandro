/**
 * @file ListaSensor.h
 * @brief Implementación de Lista Enlazada Simple Genérica para almacenar lecturas
 * @author Sistema IoT
 * @date 2025
 */

#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream>

/**
 * @brief Estructura de nodo genérico para la lista enlazada
 * @tparam T Tipo de dato a almacenar (int, float, double, etc.)
 */
template <typename T>
struct Nodo {
    T dato;              ///< Dato almacenado en el nodo
    Nodo<T>* siguiente;  ///< Puntero al siguiente nodo

    /**
     * @brief Constructor del nodo
     * @param valor Valor a almacenar en el nodo
     */
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @class ListaSensor
 * @brief Lista Enlazada Simple Genérica para gestionar lecturas de sensores
 * @tparam T Tipo de dato de las lecturas
 * 
 * Esta clase implementa manualmente una lista enlazada simple sin usar STL.
 * Gestiona la memoria de forma dinámica con punteros.
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;  ///< Puntero al primer nodo de la lista
    int tamano;       ///< Número de elementos en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    ListaSensor();

    /**
     * @brief Destructor - Libera toda la memoria de los nodos
     */
    ~ListaSensor();

    /**
     * @brief Constructor de copia (Regla de los Tres)
     * @param otra Lista a copiar
     */
    ListaSensor(const ListaSensor<T>& otra);

    /**
     * @brief Operador de asignación (Regla de los Tres)
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor<T>& operator=(const ListaSensor<T>& otra);

    /**
     * @brief Inserta un nuevo elemento al final de la lista
     * @param valor Valor a insertar
     */
    void insertarAlFinal(T valor);

    /**
     * @brief Elimina el primer nodo que contenga el valor especificado
     * @param valor Valor a eliminar
     * @return true si se eliminó, false si no se encontró
     */
    bool eliminar(T valor);

    /**
     * @brief Busca un valor en la lista
     * @param valor Valor a buscar
     * @return true si se encontró, false en caso contrario
     */
    bool buscar(T valor) const;

    /**
     * @brief Calcula el promedio de todos los valores en la lista
     * @return Promedio como tipo T
     */
    T calcularPromedio() const;

    /**
     * @brief Encuentra y retorna el valor mínimo en la lista
     * @return Valor mínimo encontrado
     */
    T encontrarMinimo() const;

    /**
     * @brief Elimina el nodo con el valor mínimo
     * @return Valor que fue eliminado
     */
    T eliminarMinimo();

    /**
     * @brief Obtiene el tamaño actual de la lista
     * @return Número de elementos
     */
    int obtenerTamano() const;

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;

    /**
     * @brief Imprime todos los elementos de la lista
     */
    void imprimir() const;

    /**
     * @brief Libera toda la memoria de la lista
     */
    void limpiar();
};

// ========== IMPLEMENTACIÓN DE LOS MÉTODOS (En el .h por ser template) ==========

template <typename T>
ListaSensor<T>::ListaSensor() : cabeza(nullptr), tamano(0) {
}

template <typename T>
ListaSensor<T>::~ListaSensor() {
    limpiar();
}

template <typename T>
ListaSensor<T>::ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr), tamano(0) {
    // Copia profunda de todos los nodos
    Nodo<T>* actual = otra.cabeza;
    while (actual != nullptr) {
        insertarAlFinal(actual->dato);
        actual = actual->siguiente;
    }
}

template <typename T>
ListaSensor<T>& ListaSensor<T>::operator=(const ListaSensor<T>& otra) {
    if (this != &otra) {
        limpiar();  // Libera memoria actual
        
        // Copia profunda
        Nodo<T>* actual = otra.cabeza;
        while (actual != nullptr) {
            insertarAlFinal(actual->dato);
            actual = actual->siguiente;
        }
    }
    return *this;
}

template <typename T>
void ListaSensor<T>::insertarAlFinal(T valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    
    if (cabeza == nullptr) {
        // Lista vacía - el nuevo nodo es la cabeza
        cabeza = nuevoNodo;
    } else {
        // Recorre hasta el último nodo
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    
    tamano++;
    std::cout << "[Log] Nodo<" << typeid(T).name() << "> insertado con valor: " << valor << "\n";
}

template <typename T>
bool ListaSensor<T>::eliminar(T valor) {
    if (cabeza == nullptr) {
        return false;
    }
    
    // Caso especial: el valor está en la cabeza
    if (cabeza->dato == valor) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamano--;
        std::cout << "[Log] Nodo con valor " << valor << " eliminado.\n";
        return true;
    }
    
    // Buscar en el resto de la lista
    Nodo<T>* actual = cabeza;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->dato == valor) {
            Nodo<T>* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            tamano--;
            std::cout << "[Log] Nodo con valor " << valor << " eliminado.\n";
            return true;
        }
        actual = actual->siguiente;
    }
    
    return false;
}

template <typename T>
bool ListaSensor<T>::buscar(T valor) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template <typename T>
T ListaSensor<T>::calcularPromedio() const {
    if (cabeza == nullptr) {
        return T(0);
    }
    
    T suma = T(0);
    Nodo<T>* actual = cabeza;
    
    while (actual != nullptr) {
        suma += actual->dato;
        actual = actual->siguiente;
    }
    
    return suma / T(tamano);
}

template <typename T>
T ListaSensor<T>::encontrarMinimo() const {
    if (cabeza == nullptr) {
        throw std::runtime_error("Lista vacía - no se puede encontrar mínimo");
    }
    
    T minimo = cabeza->dato;
    Nodo<T>* actual = cabeza->siguiente;
    
    while (actual != nullptr) {
        if (actual->dato < minimo) {
            minimo = actual->dato;
        }
        actual = actual->siguiente;
    }
    
    return minimo;
}

template <typename T>
T ListaSensor<T>::eliminarMinimo() {
    if (cabeza == nullptr) {
        throw std::runtime_error("Lista vacía - no se puede eliminar mínimo");
    }
    
    T minimo = encontrarMinimo();
    eliminar(minimo);
    return minimo;
}

template <typename T>
int ListaSensor<T>::obtenerTamano() const {
    return tamano;
}

template <typename T>
bool ListaSensor<T>::estaVacia() const {
    return cabeza == nullptr;
}

template <typename T>
void ListaSensor<T>::imprimir() const {
    std::cout << "[";
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato;
        if (actual->siguiente != nullptr) {
            std::cout << ", ";
        }
        actual = actual->siguiente;
    }
    std::cout << "]\n";
}

template <typename T>
void ListaSensor<T>::limpiar() {
    while (cabeza != nullptr) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        std::cout << "[Log] Nodo<" << typeid(T).name() << "> " << temp->dato << " liberado.\n";
        delete temp;
    }
    tamano = 0;
}

#endif // LISTASENSOR_H
