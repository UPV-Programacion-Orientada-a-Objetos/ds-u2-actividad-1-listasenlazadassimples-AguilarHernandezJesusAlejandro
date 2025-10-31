/**
 * @file arduino_sensor_example.ino
 * @brief Código de ejemplo para Arduino que envía datos de sensores por Serial
 * @note Este archivo es SOLO de referencia, no se compila con el proyecto C++
 * 
 * HARDWARE NECESARIO:
 * - Arduino Uno/Nano/Mega
 * - Sensor de temperatura DS18B20 o DHT22
 * - Sensor de presión BMP180 o BMP280
 * - Sensor de vibración SW-420 o similar
 * 
 * CONEXIONES:
 * - Temperatura: Pin Digital 2
 * - Presión: I2C (A4=SDA, A5=SCL)
 * - Vibración: Pin Analógico A0
 */

// ========== BIBLIOTECAS ==========
// Descomentar según el hardware real disponible
// #include <DHT.h>           // Para sensor DHT22
// #include <Adafruit_BMP280.h>  // Para sensor BMP280
// #include <OneWire.h>       // Para DS18B20
// #include <DallasTemperature.h>

// ========== CONFIGURACIÓN DE PINES ==========
#define PIN_TEMPERATURA 2
#define PIN_VIBRACION A0
#define BAUDRATE 9600

// ========== VARIABLES GLOBALES ==========
unsigned long ultimaLectura = 0;
const unsigned long INTERVALO_LECTURA = 1000;  // 1 segundo

// ========== SETUP ==========
void setup() {
  // Inicializar comunicación serial
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // Esperar a que se conecte el puerto serial (solo para Leonardo/Micro)
  }
  
  Serial.println("Arduino Sensor IoT - Inicializado");
  Serial.println("Formato de paquetes: TIPO:VALOR");
  Serial.println("T = Temperatura (Celsius)");
  Serial.println("P = Presion (kPa)");
  Serial.println("V = Vibracion (0-100)");
  Serial.println("========================================");
  
  // Configurar pines
  pinMode(PIN_VIBRACION, INPUT);
  
  // Inicializar sensores aquí
  // (código específico según el sensor)
  
  delay(2000);
}

// ========== LOOP PRINCIPAL ==========
void loop() {
  unsigned long tiempoActual = millis();
  
  // Leer sensores cada INTERVALO_LECTURA
  if (tiempoActual - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = tiempoActual;
    
    // Leer y enviar temperatura
    float temperatura = leerTemperatura();
    enviarPaquete('T', temperatura);
    delay(100);
    
    // Leer y enviar presión
    int presion = leerPresion();
    enviarPaquete('P', presion);
    delay(100);
    
    // Leer y enviar vibración
    int vibracion = leerVibracion();
    enviarPaquete('V', vibracion);
    delay(100);
  }
  
  // Procesar comandos desde el PC (opcional)
  if (Serial.available() > 0) {
    procesarComando();
  }
}

// ========== FUNCIONES DE LECTURA ==========

/**
 * Lee el sensor de temperatura
 * @return Temperatura en grados Celsius
 */
float leerTemperatura() {
  // OPCIÓN 1: Simulación para pruebas
  return 20.0 + random(-50, 150) / 10.0;  // 15°C a 35°C
  
  // OPCIÓN 2: Lectura real de DHT22
  // DHT dht(PIN_TEMPERATURA, DHT22);
  // return dht.readTemperature();
  
  // OPCIÓN 3: Lectura real de DS18B20
  // OneWire oneWire(PIN_TEMPERATURA);
  // DallasTemperature sensors(&oneWire);
  // sensors.requestTemperatures();
  // return sensors.getTempCByIndex(0);
}

/**
 * Lee el sensor de presión
 * @return Presión en kPa
 */
int leerPresion() {
  // OPCIÓN 1: Simulación para pruebas
  return 95 + random(0, 11);  // 95 kPa a 105 kPa
  
  // OPCIÓN 2: Lectura real de BMP280
  // Adafruit_BMP280 bmp;
  // return (int)(bmp.readPressure() / 1000.0);  // Pa a kPa
}

/**
 * Lee el sensor de vibración
 * @return Nivel de vibración (0-100)
 */
int leerVibracion() {
  // OPCIÓN 1: Simulación para pruebas
  return random(0, 101);  // 0 a 100
  
  // OPCIÓN 2: Lectura real de sensor analógico
  // int lecturaRaw = analogRead(PIN_VIBRACION);
  // return map(lecturaRaw, 0, 1023, 0, 100);
}

// ========== FUNCIONES DE COMUNICACIÓN ==========

/**
 * Envía un paquete de datos por Serial
 * @param tipo Tipo de sensor ('T', 'P', 'V')
 * @param valor Valor a enviar (se formateará según el tipo)
 */
void enviarPaquete(char tipo, float valor) {
  Serial.print(tipo);
  Serial.print(":");
  
  if (tipo == 'T') {
    Serial.println(valor, 2);  // 2 decimales para temperatura
  } else {
    Serial.println((int)valor);  // Sin decimales para presión/vibración
  }
}

/**
 * Procesa comandos recibidos desde el PC
 */
void procesarComando() {
  String comando = Serial.readStringUntil('\n');
  comando.trim();
  
  if (comando == "STATUS") {
    Serial.println("OK:Sistema funcionando correctamente");
  }
  else if (comando == "RESET") {
    Serial.println("OK:Reiniciando sistema...");
    delay(100);
    asm volatile ("  jmp 0");  // Reinicio por software
  }
  else if (comando.startsWith("INTERVAL:")) {
    // Cambiar intervalo de lectura
    int nuevoIntervalo = comando.substring(9).toInt();
    if (nuevoIntervalo > 0) {
      // INTERVALO_LECTURA = nuevoIntervalo;  // Requiere variable no const
      Serial.print("OK:Intervalo cambiado a ");
      Serial.print(nuevoIntervalo);
      Serial.println("ms");
    }
  }
  else {
    Serial.println("ERROR:Comando no reconocido");
  }
}

// ========== FUNCIONES AUXILIARES ==========

/**
 * Función de depuración - imprime estado del sistema
 */
void imprimirEstado() {
  Serial.println("========== ESTADO DEL SISTEMA ==========");
  Serial.print("Tiempo de ejecución: ");
  Serial.print(millis() / 1000);
  Serial.println(" segundos");
  Serial.print("Temperatura actual: ");
  Serial.print(leerTemperatura());
  Serial.println(" °C");
  Serial.print("Presión actual: ");
  Serial.print(leerPresion());
  Serial.println(" kPa");
  Serial.print("Vibración actual: ");
  Serial.println(leerVibracion());
  Serial.println("========================================");
}
