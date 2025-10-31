#!/bin/bash

# ============================================================================
# Script de Compilación Rápida - Sistema IoT de Sensores
# ============================================================================

echo "╔═══════════════════════════════════════════════════════╗"
echo "║   Sistema IoT - Script de Compilación Automática     ║"
echo "╚═══════════════════════════════════════════════════════╝"
echo ""

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Función para imprimir con color
print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_info() {
    echo -e "${YELLOW}→${NC} $1"
}

# Verificar si existe CMake
if ! command -v cmake &> /dev/null; then
    print_error "CMake no está instalado"
    echo "Por favor instale CMake:"
    echo "  Ubuntu/Debian: sudo apt-get install cmake"
    echo "  macOS: brew install cmake"
    echo "  Windows: Descargar desde https://cmake.org"
    exit 1
fi

print_success "CMake encontrado: $(cmake --version | head -n1)"

# Verificar compilador
if command -v g++ &> /dev/null; then
    print_success "Compilador encontrado: $(g++ --version | head -n1)"
elif command -v clang++ &> /dev/null; then
    print_success "Compilador encontrado: $(clang++ --version | head -n1)"
else
    print_error "No se encontró compilador C++"
    exit 1
fi

echo ""
print_info "Iniciando proceso de compilación..."
echo ""

# Crear directorio build si no existe
if [ -d "build" ]; then
    print_info "Limpiando directorio build existente..."
    rm -rf build
fi

print_info "Creando directorio build..."
mkdir build
cd build

print_success "Directorio build creado"
echo ""

# Configurar con CMake
print_info "Configurando proyecto con CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -eq 0 ]; then
    print_success "Configuración completada"
else
    print_error "Error en la configuración"
    exit 1
fi

echo ""

# Compilar
print_info "Compilando proyecto..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

if [ $? -eq 0 ]; then
    print_success "Compilación exitosa"
    echo ""
    print_success "Ejecutable generado: build/SistemaIoTSensores"
    echo ""
    echo "Para ejecutar el programa:"
    echo "  ./build/SistemaIoTSensores"
    echo ""
    echo "Para generar documentación (requiere Doxygen):"
    echo "  cd build && make doc"
else
    print_error "Error en la compilación"
    exit 1
fi
