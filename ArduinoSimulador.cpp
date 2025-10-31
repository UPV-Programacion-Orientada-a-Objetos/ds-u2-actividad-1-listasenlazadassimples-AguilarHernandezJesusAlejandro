/**
 * @file ArduinoSimulador.cpp
 * @brief Implementación del simulador de Arduino
 */

#include "ArduinoSimulador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>

ArduinoSimulador::ArduinoSimulador() 
    : conectado(false), contadorLecturas(0) {
    // Inicializa el generador de números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));
}

bool ArduinoSimulador::conectar(const char* puerto) {
    std::cout << "\n[Arduino] Intentando conectar al puerto: " << puerto << "...\n";
    std::cout << "[Arduino] Configurando baudrate: 9600...\n";
    std::cout << "[Arduino] Estableciendo timeout: 1000ms...\n";
    
    // Simulamos un delay de conexión
    for (int i = 0; i < 3; i++) {
        std::cout << "." << std::flush;
    }
    std::cout << "\n";
    
    conectado = true;
    std::cout << "[Arduino] ✓ Conexión establecida exitosamente!\n";
    std::cout << "[Arduino] Dispositivo listo para enviar datos.\n\n";
    
    return true;
}

void ArduinoSimulador::desconectar() {
    if (conectado) {
        std::cout << "\n[Arduino] Cerrando conexión serial...\n";
        conectado = false;
        std::cout << "[Arduino] Desconectado.\n";
    }
}

bool ArduinoSimulador::hayDatosDisponibles() {
    // En un sistema real, verificaríamos el buffer serial
    // Simulamos que siempre hay datos disponibles cuando está conectado
    return conectado;
}

float ArduinoSimulador::leerTemperatura() {
    if (!conectado) {
        return 0.0f;
    }
    
    // Simula lecturas de temperatura entre 15°C y 35°C
    float temperatura = 15.0f + (rand() % 2001) / 100.0f;  // 15.0 a 35.0
    contadorLecturas++;
    
    return temperatura;
}

int ArduinoSimulador::leerPresion() {
    if (!conectado) {
        return 0;
    }
    
    // Simula lecturas de presión entre 95 kPa y 105 kPa
    int presion = 95 + (rand() % 11);  // 95 a 105
    contadorLecturas++;
    
    return presion;
}

int ArduinoSimulador::leerVibracion() {
    if (!conectado) {
        return 0;
    }
    
    // Simula lecturas de vibración entre 0 y 100
    int vibracion = rand() % 101;  // 0 a 100
    contadorLecturas++;
    
    return vibracion;
}

bool ArduinoSimulador::estaConectado() const {
    return conectado;
}

bool ArduinoSimulador::recibirPaquete(char* buffer, char tipo) {
    if (!conectado) {
        return false;
    }
    
    // Simula recepción de un paquete de datos
    switch (tipo) {
        case 'T':
        case 't': {
            float temp = leerTemperatura();
            sprintf(buffer, "T:%.2f", temp);
            std::cout << "[Arduino→PC] Paquete recibido: " << buffer << "\n";
            break;
        }
        case 'P':
        case 'p': {
            int pres = leerPresion();
            sprintf(buffer, "P:%d", pres);
            std::cout << "[Arduino→PC] Paquete recibido: " << buffer << "\n";
            break;
        }
        case 'V':
        case 'v': {
            int vib = leerVibracion();
            sprintf(buffer, "V:%d", vib);
            std::cout << "[Arduino→PC] Paquete recibido: " << buffer << "\n";
            break;
        }
        default:
            return false;
    }
    
    return true;
}
