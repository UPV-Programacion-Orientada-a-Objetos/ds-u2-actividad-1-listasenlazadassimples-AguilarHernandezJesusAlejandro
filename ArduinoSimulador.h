/**
 * @file ArduinoSimulador.h
 * @brief Simulador de captura de datos desde Arduino vía puerto serial
 * @author Sistema IoT
 * @date 2025
 */

#ifndef ARDUINOSIMULADOR_H
#define ARDUINOSIMULADOR_H

/**
 * @class ArduinoSimulador
 * @brief Simula la captura de señales desde un dispositivo Arduino
 * 
 * En un sistema real, esta clase se conectaría al puerto serial
 * (COM1, /dev/ttyUSB0, etc.) y leería datos del Arduino.
 * En esta simulación, generamos datos aleatorios.
 */
class ArduinoSimulador {
private:
    bool conectado;     ///< Estado de la conexión simulada
    int contadorLecturas; ///< Contador de lecturas simuladas

public:
    /**
     * @brief Constructor del simulador
     */
    ArduinoSimulador();

    /**
     * @brief Simula la conexión al puerto serial
     * @param puerto Nombre del puerto (ej: "COM3", "/dev/ttyUSB0")
     * @return true si la conexión fue exitosa
     */
    bool conectar(const char* puerto);

    /**
     * @brief Desconecta del puerto serial
     */
    void desconectar();

    /**
     * @brief Verifica si hay datos disponibles en el puerto
     * @return true si hay datos disponibles
     */
    bool hayDatosDisponibles();

    /**
     * @brief Lee un valor de temperatura simulado
     * @return Temperatura en grados Celsius
     */
    float leerTemperatura();

    /**
     * @brief Lee un valor de presión simulado
     * @return Presión en kPa
     */
    int leerPresion();

    /**
     * @brief Lee un valor de vibración simulado
     * @return Nivel de vibración (0-100)
     */
    int leerVibracion();

    /**
     * @brief Obtiene el estado de la conexión
     * @return true si está conectado
     */
    bool estaConectado() const;

    /**
     * @brief Simula recepción de un paquete de datos
     * @param buffer Buffer donde se almacenarán los datos
     * @param tipo Tipo de sensor ('T'=Temp, 'P'=Presion, 'V'=Vibración)
     * @return true si se recibió correctamente
     * 
     * Formato del paquete: "TIPO:VALOR"
     * Ejemplo: "T:25.4" o "P:101"
     */
    bool recibirPaquete(char* buffer, char tipo);
};

#endif // ARDUINOSIMULADOR_H
