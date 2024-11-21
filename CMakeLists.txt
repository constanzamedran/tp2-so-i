cmake_minimum_required(VERSION 3.10)
project(shell_project)

# Establecer el tipo de construcción por defecto
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release) 
endif()

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

# Configurar CMAKE_PREFIX_PATH para encontrar dependencias en Release/generators
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/Release/generators" ${CMAKE_PREFIX_PATH})

# Habilitar testing
include(CTest)

# Flags para compilar
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-g3 -Wall -pedantic -Werror -Wextra -Wconversion")

# Flags para cobertura de código
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

# Añadir el subdirectorio del submódulo
add_subdirectory(lib/monitoring_project)

# Incluir directorios de encabezados
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(include lib/monitoring_project/include)

# Añadir el ejecutable para la shell
add_executable(shell
    src/main.c
    src/batch.c
    src/command.c    
    src/exec.c
    src/jobs.c
    src/pipes.c
    src/prompt.c
    src/redirection.c
    src/signals.c
    src/monitor.c
)

# Buscar dependencias
find_package(cJSON REQUIRED)
find_package(unity REQUIRED)

target_link_libraries(shell PRIVATE monitoring_project_lib)

# Vincula las librerías
target_link_libraries(shell PRIVATE cjson::cjson unity::unity)

# Configuracion para pruebas unitarias
add_executable(tests
    test/test_main.c
    test/test_command.c
    test/test_jobs.c
    test/test_exec.c
    test/test_pipes.c
    src/command.c
    src/monitor.c
    src/exec.c
    src/jobs.c
    src/pipes.c
)

target_link_libraries(tests PRIVATE monitoring_project_lib unity::unity cjson::cjson)

# Opcional: Añadir comandos para la ejecución de pruebas y cobertura
add_custom_target(run_tests
    COMMAND tests
    DEPENDS tests
)

add_custom_target(coverage
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out
    DEPENDS tests
)

