# ============================================================================
# Makefile - Sistema IoT de Sensores
# Alternativa simple a CMake
# ============================================================================

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
DEBUGFLAGS = -g -O0 -DDEBUG

# Nombre del ejecutable
TARGET = SistemaIoTSensores

# Archivos fuente
SOURCES = main.cpp \
          SensorBase.cpp \
          SensorTemperatura.cpp \
          SensorPresion.cpp \
          ListaGestion.cpp \
          ArduinoSimulador.cpp

# Archivos objeto (se generan automáticamente)
OBJECTS = $(SOURCES:.cpp=.o)

# Archivos de cabecera
HEADERS = SensorBase.h \
          SensorTemperatura.h \
          SensorPresion.h \
          ListaSensor.h \
          ListaGestion.h \
          ArduinoSimulador.h

# ============================================================================
# Reglas
# ============================================================================

# Regla por defecto
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	@echo "🔗 Enlazando $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Compilación exitosa: $(TARGET)"

# Compilar archivos objeto
%.o: %.cpp $(HEADERS)
	@echo "🔨 Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilación en modo debug
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: clean all
	@echo "✓ Compilado en modo DEBUG"

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Limpieza completada"

# Limpiar y recompilar
rebuild: clean all

# Ejecutar el programa
run: $(TARGET)
	@echo "▶️  Ejecutando $(TARGET)..."
	@echo ""
	./$(TARGET)

# Verificar dependencias
check:
	@echo "Verificando dependencias..."
	@command -v $(CXX) >/dev/null 2>&1 || { echo "❌ $(CXX) no encontrado"; exit 1; }
	@echo "✓ Compilador: $(shell $(CXX) --version | head -n1)"

# Ayuda
help:
	@echo "Sistema IoT de Sensores - Makefile"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make         - Compilar el proyecto"
	@echo "  make debug   - Compilar en modo debug"
	@echo "  make clean   - Limpiar archivos generados"
	@echo "  make rebuild - Limpiar y recompilar"
	@echo "  make run     - Compilar y ejecutar"
	@echo "  make check   - Verificar dependencias"
	@echo "  make help    - Mostrar esta ayuda"

# Instalar (opcional)
install: $(TARGET)
	@echo "📦 Instalando $(TARGET)..."
	install -m 755 $(TARGET) /usr/local/bin/
	@echo "✓ Instalado en /usr/local/bin/$(TARGET)"

# Desinstalar (opcional)
uninstall:
	@echo "🗑️  Desinstalando $(TARGET)..."
	rm -f /usr/local/bin/$(TARGET)
	@echo "✓ Desinstalado"

.PHONY: all debug clean rebuild run check help install uninstall
