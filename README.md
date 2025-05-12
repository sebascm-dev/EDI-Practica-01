# Sistema de Gestión de Torneos de Golf

## Descripción General
Este proyecto es una práctica para la asignatura Estructura de Datos I de la Ingeniería Informática en la Universidad de Huelva. Consiste en un sistema de gestión de torneos de golf que permite crear, administrar y simular torneos, así como gestionar las inscripciones de golfistas participantes.

El programa está desarrollado en C++ y utiliza archivos binarios para almacenar de forma persistente la información de los torneos y los golfistas.

## Estructura del Proyecto

### Clases Principales

#### Clase Torneo
Gestiona la información relacionada con un torneo de golf y sus participantes:
- Almacena el nombre del torneo y el nombre del archivo asociado
- Maneja la lista de golfistas inscritos
- Proporciona métodos para añadir, modificar, buscar y eliminar inscripciones
- Permite simular la realización del torneo y obtener clasificaciones
- Trabaja con archivos binarios para almacenar datos de forma persistente

#### Clase Clasificación
Gestiona la tabla dinámica de clasificación de un torneo:
- Implementa una tabla dinámica que se redimensiona automáticamente
- Permite añadir jugadores a la clasificación
- Proporciona métodos para ordenar la clasificación por resultados
- Ofrece funcionalidad para consultar y eliminar posiciones en la tabla

### Estructura de Datos

#### Estructura Golfista
Almacena la información de cada participante:
- Licencia (identificador único)
- Nombre y apellidos
- Handicap (nivel del golfista)
- Golpes (número total en el torneo)
- Resultado (calculado respecto al par del campo)

#### Estructura Jugador
Utilizada para la clasificación:
- Índice (posición en el archivo original)
- Resultado (puntuación final)

## Funcionalidades Principales

### 1. Gestión de Torneos
- **Listado de Torneos**: Muestra todos los torneos disponibles
- **Alta de Torneo**: Crea un nuevo torneo con su correspondiente archivo de datos
- **Selección de Torneo**: Permite elegir un torneo para trabajar con él

### 2. Gestión de Inscripciones
- **Consulta de Inscripciones**: Lista todos los golfistas inscritos, con filtrado opcional por handicap
- **Inscripción al Torneo**: Añade un nuevo golfista al torneo seleccionado
- **Búsqueda de Inscripción**: Localiza un golfista por su número de licencia
- **Modificación de Inscripción**: Actualiza los datos de un golfista inscrito
- **Eliminación de Inscripción**: Elimina un golfista del torneo

### 3. Simulación y Resultados
- **Simulación del Torneo**: Genera aleatoriamente los golpes de cada jugador y calcula sus resultados
- **Clasificación**: Ordena los jugadores según su resultado y muestra la clasificación final
- **Ganadores**: Permite identificar y exportar los ganadores de los torneos

## Almacenamiento de Datos

### Archivos Binarios
- **torneo.dat**: Almacena la información general de todos los torneos
- **[nombreTorneo].dat**: Para cada torneo se crea un archivo específico con los datos de los golfistas inscritos
- **ganadoresTorneo.dat**: Almacena información sobre los ganadores de los torneos

### Estructura de los Archivos
1. **Archivo de Torneos**: Almacena registros con:
   - Número de golfistas
   - Nombre del torneo
   - Nombre del archivo asociado

2. **Archivo específico de un Torneo**: Contiene:
   - En la primera posición: número de golfistas inscritos
   - A continuación: registros de tipo Golfista ordenados por handicap

## Interfaz de Usuario
El programa presenta una interfaz de consola con menús interactivos:
- Menú principal para la gestión general de torneos
- Submenú específico para cada torneo seleccionado
- Mensajes informativos y de error para guiar al usuario

## Características Técnicas
- Uso de memoria dinámica para gestionar colecciones de tamaño variable
- Manejo de archivos binarios para almacenamiento persistente
- Uso de estructuras de datos y algoritmos (ordenación, búsqueda)
- Implementación de clases con sus respectivos métodos
- Gestión de errores y validación de datos

## Compilación y Ejecución
Este proyecto está configurado para compilarse con Code::Blocks (archivo .cbp incluido).

Para ejecutar el programa:
1. Abrir el proyecto P1.cbp con Code::Blocks
2. Compilar el proyecto (F9)
3. Ejecutar el programa (F10)

## Autor
Sebastián Contreras Marín - spanolocabo@gmail.com 