/**
 * @file main.cpp
 * @brief Programa principal del Sistema de Gestión Polimórfica de Sensores IoT
 * @author Sistema IoT
 * @date 2025
 * 
 * Este programa demuestra:
 * - Jerarquía polimórfica con clases abstractas
 * - Listas enlazadas simples genéricas
 * - Uso de templates
 * - Gestión manual de memoria con punteros
 * - Simulación de captura de datos desde Arduino
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGestion.h"
#include "ArduinoSimulador.h"

using namespace std;

// ========== PROTOTIPOS DE FUNCIONES ==========
void mostrarMenu();
void crearSensor(ListaGestion& lista);
void registrarLectura(ListaGestion& lista, ArduinoSimulador& arduino);
void procesarSensores(ListaGestion& lista);
void mostrarSensores(ListaGestion& lista);
void capturarDesdeArduino(ListaGestion& lista, ArduinoSimulador& arduino);
void limpiarPantalla();
void pausar();

/**
 * @brief Función principal del sistema
 */
int main() {
    // Objeto de gestión polimórfica (almacena SensorBase*)
    ListaGestion sistemaGestion;
    
    // Simulador de Arduino para captura de datos
    ArduinoSimulador arduino;
    
    int opcion;
    bool salir = false;
    
    // Pantalla de bienvenida
    limpiarPantalla();
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║   SISTEMA IoT DE GESTIÓN POLIMÓRFICA DE SENSORES     ║\n";
    cout << "║              Caso de Estudio - C++                    ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    cout << "Demostrando:\n";
    cout << "  ✓ Herencia y Polimorfismo\n";
    cout << "  ✓ Listas Enlazadas Genéricas (Templates)\n";
    cout << "  ✓ Gestión Manual de Memoria\n";
    cout << "  ✓ Simulación de Arduino Serial\n\n";
    
    pausar();
    
    // Bucle principal del menú
    while (!salir) {
        mostrarMenu();
        
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        
        // Limpia el buffer de entrada
        cin.ignore(1000, '\n');
        
        limpiarPantalla();
        
        switch (opcion) {
            case 1:
                crearSensor(sistemaGestion);
                break;
            
            case 2:
                registrarLectura(sistemaGestion, arduino);
                break;
            
            case 3:
                procesarSensores(sistemaGestion);
                break;
            
            case 4:
                mostrarSensores(sistemaGestion);
                break;
            
            case 5:
                capturarDesdeArduino(sistemaGestion, arduino);
                break;
            
            case 6:
                cout << "\n╔═══════════════════════════════════════════════════╗\n";
                cout << "║         CERRANDO SISTEMA Y LIBERANDO MEMORIA       ║\n";
                cout << "╚═══════════════════════════════════════════════════╝\n";
                salir = true;
                break;
            
            default:
                cout << "❌ Opción inválida. Intente nuevamente.\n";
                break;
        }
        
        if (!salir) {
            pausar();
        }
    }
    
    // Al salir del programa, el destructor de ListaGestion
    // se ejecuta automáticamente, liberando toda la memoria
    
    cout << "\n✓ Sistema finalizado correctamente.\n\n";
    
    return 0;
}

/**
 * @brief Muestra el menú principal
 */
void mostrarMenu() {
    limpiarPantalla();
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║              MENÚ PRINCIPAL - SISTEMA IoT              ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
    cout << "\n";
    cout << "  1. 🔧 Crear nuevo sensor\n";
    cout << "  2. 📝 Registrar lectura manual\n";
    cout << "  3. ⚙️  Procesar todos los sensores (Polimorfismo)\n";
    cout << "  4. 📊 Mostrar información de sensores\n";
    cout << "  5. 📡 Capturar datos desde Arduino\n";
    cout << "  6. 🚪 Salir del sistema\n";
    cout << "\n";
}

/**
 * @brief Crea un nuevo sensor y lo agrega a la lista de gestión
 */
void crearSensor(ListaGestion& lista) {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║                 CREAR NUEVO SENSOR                     ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    char nombre[50];
    int tipo;
    
    cout << "Ingrese el nombre del sensor (ej: T-001, P-105): ";
    cin.getline(nombre, 50);
    
    cout << "\nSeleccione el tipo de sensor:\n";
    cout << "  1. Temperatura (float)\n";
    cout << "  2. Presión (int)\n";
    cout << "Opción: ";
    cin >> tipo;
    cin.ignore(1000, '\n');
    
    SensorBase* nuevoSensor = nullptr;
    
    switch (tipo) {
        case 1:
            // Polimorfismo: Se crea SensorTemperatura pero se almacena como SensorBase*
            nuevoSensor = new SensorTemperatura(nombre);
            break;
        
        case 2:
            // Polimorfismo: Se crea SensorPresion pero se almacena como SensorBase*
            nuevoSensor = new SensorPresion(nombre);
            break;
        
        default:
            cout << "❌ Tipo de sensor inválido.\n";
            return;
    }
    
    // Inserta el sensor en la lista de gestión polimórfica
    lista.insertarSensor(nuevoSensor);
    cout << "\n✓ Sensor creado e insertado exitosamente.\n";
}

/**
 * @brief Registra una lectura manual en un sensor específico
 */
void registrarLectura(ListaGestion& lista, ArduinoSimulador& arduino) {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║               REGISTRAR LECTURA MANUAL                 ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    if (lista.estaVacia()) {
        cout << "❌ No hay sensores registrados. Cree uno primero.\n";
        return;
    }
    
    lista.imprimirTodosSensores();
    
    char nombre[50];
    char valor[50];
    
    cout << "\nIngrese el nombre del sensor: ";
    cin.getline(nombre, 50);
    
    SensorBase* sensor = lista.buscarSensor(nombre);
    
    if (sensor == nullptr) {
        cout << "❌ Sensor no encontrado.\n";
        return;
    }
    
    cout << "Ingrese el valor de la lectura: ";
    cin.getline(valor, 50);
    
    // Polimorfismo en acción: registrarLecturaDesdeString
    // ejecuta el método específico de cada tipo de sensor
    sensor->registrarLecturaDesdeString(valor);
    
    cout << "\n✓ Lectura registrada exitosamente.\n";
}

/**
 * @brief Procesa todos los sensores usando polimorfismo
 */
void procesarSensores(ListaGestion& lista) {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║        PROCESAMIENTO POLIMÓRFICO DE SENSORES           ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
    
    if (lista.estaVacia()) {
        cout << "\n❌ No hay sensores para procesar.\n";
        return;
    }
    
    // DEMOSTRACIÓN DE POLIMORFISMO:
    // procesarTodosSensores() itera sobre la lista y llama a procesarLectura()
    // de cada sensor. Aunque todos son SensorBase*, cada uno ejecuta
    // su implementación específica (temperatura elimina mínimo, presión calcula promedio)
    lista.procesarTodosSensores();
}

/**
 * @brief Muestra información de todos los sensores
 */
void mostrarSensores(ListaGestion& lista) {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║          INFORMACIÓN DE SENSORES REGISTRADOS           ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";
    
    if (lista.estaVacia()) {
        cout << "\n❌ No hay sensores registrados.\n";
        return;
    }
    
    lista.imprimirTodosSensores();
}

/**
 * @brief Captura datos desde Arduino simulado
 */
void capturarDesdeArduino(ListaGestion& lista, ArduinoSimulador& arduino) {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout << "║           CAPTURA DE DATOS DESDE ARDUINO               ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    // Conectar al Arduino si no está conectado
    if (!arduino.estaConectado()) {
        cout << "El Arduino no está conectado. Intentando conectar...\n";
        if (!arduino.conectar("/dev/ttyUSB0")) {
            cout << "❌ Error al conectar con Arduino.\n";
            return;
        }
    }
    
    if (lista.estaVacia()) {
        cout << "❌ No hay sensores registrados. Cree sensores primero.\n";
        return;
    }
    
    cout << "Sensores disponibles:\n";
    lista.imprimirTodosSensores();
    
    char nombre[50];
    cout << "\nIngrese el nombre del sensor para capturar datos: ";
    cin.getline(nombre, 50);
    
    SensorBase* sensor = lista.buscarSensor(nombre);
    
    if (sensor == nullptr) {
        cout << "❌ Sensor no encontrado.\n";
        return;
    }
    
    int numLecturas;
    cout << "¿Cuántas lecturas desea capturar? ";
    cin >> numLecturas;
    cin.ignore(1000, '\n');
    
    cout << "\n📡 Capturando " << numLecturas << " lecturas desde Arduino...\n\n";
    
    for (int i = 0; i < numLecturas; i++) {
        char buffer[100];
        char tipo = nombre[0];  // Usa la primera letra del nombre como tipo
        
        if (arduino.recibirPaquete(buffer, tipo)) {
            // Extrae el valor del paquete (formato "TIPO:VALOR")
            char* valorStr = strchr(buffer, ':');
            if (valorStr != nullptr) {
                valorStr++;  // Salta el ':'
                sensor->registrarLecturaDesdeString(valorStr);
            }
        }
        
        // Pequeña pausa para simular tiempo entre lecturas
        for (volatile int j = 0; j < 10000000; j++);
    }
    
    cout << "\n✓ Captura completada. " << numLecturas << " lecturas registradas.\n";
}

/**
 * @brief Limpia la pantalla de la consola
 */
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Pausa el programa hasta que el usuario presione Enter
 */
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}
