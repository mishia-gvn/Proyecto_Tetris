# Tetris - Estructuras de Datos

## Descripción

Este proyecto consiste en una versión simplificada del juego Tetris,
desarrollada en C++ como parte del curso EIF207 - Estructuras de Datos.

El juego utiliza diferentes estructuras de datos implementadas
manualmente para gestionar las piezas, el tablero, la pieza en espera,
los eventos y la tabla de mejores puntuaciones.

El tablero está compuesto por 10 columnas y 20 filas, y el objetivo es
acomodar las piezas para completar líneas horizontales que posteriormente
son eliminadas.

## Tecnologías utilizadas

- C++
- SFML 3.1.0
- Visual Studio 2022
- Git / GitHub

## Estructuras de datos

El proyecto utiliza estructuras de datos implementadas manualmente para
cumplir con los requerimientos del proyecto:

- **Cola FIFO:** utilizada para administrar las piezas siguientes. Las
  piezas se agregan al final y se extraen desde el frente. También se
  utiliza una bolsa de 7 piezas para generar las piezas del juego.

- **Pila:** utilizada para implementar la función Hold, permitiendo
  almacenar una pieza. Su capacidad es de una pieza.

- **Lista enlazada:** utilizada para representar las filas del tablero.
  Cada nodo contiene las celdas de una fila y un enlace hacia la siguiente.

- **Cola de eventos ordenada:** utilizada para administrar eventos según
  su tiempo de activación. Los eventos se insertan directamente en su
  posición correspondiente para mantener la cola ordenada. 

- **Arreglos:** utilizados como estructuras auxiliares para almacenar
  las puntuaciones y permitir la aplicación de los algoritmos de
  ordenamiento. La tabla almacena hasta 10 puntuaciones.
  
## Funcionalidades

- Generación de piezas mediante bolsas de 7 piezas.
- Visualización de las próximas piezas.
- Movimiento horizontal de las piezas.
- Rotación de las piezas.
- Descenso normal y caída rápida.
- Sistema de Hold.
- Eliminación de líneas completas con animación.
- Aumento progresivo de la velocidad.
- Sistema de eventos temporizados.
- Oscurecimiento progresivo del juego mediante eventos.
- Sistema de puntuación.
- Tabla de las 10 mejores puntuaciones.
- Dos algoritmos de ordenamiento: Insertion Sort y Quick Sort.
- Visualización de comparaciones y movimientos realizados por los
  algoritmos de ordenamiento.

## Controles

| Tecla | Acción |
|-------|--------|
| ← | Mover la pieza a la izquierda |
| → | Mover la pieza a la derecha |
| ↓ | Bajar la pieza |
| ↑ | Rotar la pieza |
| Espacio | Caída rápida de la pieza |
| H | Guardar/intercambiar la pieza en Hold |

## Ejecución del proyecto

Para ejecutar el proyecto se requiere:

- Visual Studio 2022.
- C++.
- SFML 3.1.0.
- Los archivos y recursos incluidos en el proyecto.

El proyecto debe abrirse desde Visual Studio y ejecutarse desde la
configuración correspondiente del proyecto.

## Estudiante

- Mishia Valverde Narváez

