# ============================================================================
# CMakeLists.txt - Sistema de Gestión Polimórfica de Sensores IoT
# ============================================================================

cmake_minimum_required(VERSION 3.10)

# Definición del proyecto
project(SistemaIoTSensores 
        VERSION 1.0
        DESCRIPTION "Sistema de Gestión Polimórfica de Sensores para IoT"
        LANGUAGES CXX)

# Estándar de C++ requerido
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configuración de compilación
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Opciones de compilación
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Mensajes informativos
message(STATUS "==============================================")
message(STATUS "  Sistema IoT de Sensores - Configuración")
message(STATUS "==============================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "==============================================")

# Archivos fuente
set(SOURCES
    main.cpp
    SensorBase.cpp
    SensorTemperatura.cpp
    SensorPresion.cpp
    ListaGestion.cpp
    ArduinoSimulador.cpp
)

# Archivos de cabecera
set(HEADERS
    SensorBase.h
    SensorTemperatura.h
    SensorPresion.h
    ListaSensor.h
    ListaGestion.h
    ArduinoSimulador.h
)

# Crear ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Configuración de include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Opciones de compilación específicas
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Instalación
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Documentación con Doxygen (opcional)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    if(EXISTS ${DOXYGEN_IN})
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen configurado - ejecute 'make doc' para generar documentación")
        
        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generando documentación con Doxygen"
            VERBATIM
        )
    endif()
else()
    message(STATUS "Doxygen no encontrado - documentación no disponible")
endif()

# Testing (opcional)
enable_testing()

# Resumen de configuración
message(STATUS "")
message(STATUS "Configuración completada exitosamente")
message(STATUS "Para compilar, ejecute:")
message(STATUS "  mkdir build && cd build")
message(STATUS "  cmake ..")
message(STATUS "  make")
message(STATUS "")
