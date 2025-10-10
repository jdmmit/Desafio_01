#ifndef ALGORITMOS_H
#define ALGORITMOS_H

// --- Declaraciones de las Funciones de Descompresión ---

// Este es el archivo de cabecera (.h). Aquí solo "declaramos" las funciones.

// Es como decir: "Oye, C++, estas funciones existen en alguna parte de mi proyecto,

// y se ven así". La implementación real (el código que hace el trabajo)

// está en el archivo algoritmos.cpp.

/**
 * @brief Descomprime una cadena de datos usando el algoritmo RLE (Run-Length Encoding).

 * @param datosComprimidos Un puntero a un arreglo de caracteres que contiene los datos en formato RLE (ej: "4A3B2C").

 * @param tamanoComprimido El número de bytes en el arreglo de datosComprimidos.

 * @param tamanoSalida Una variable pasada por referencia donde la función guardará el tamaño del resultado descomprimido.

 * @return Un nuevo puntero a un arreglo de caracteres (`char*`) que contiene los datos descomprimidos.
 *
 * ¡OJO! Es tu responsabilidad liberar esta memoria con `delete[]` cuando ya no la necesites.
 */

char *descomprimirRLE(const char *datosComprimidos, int tamanoComprimido, int &tamanoSalida);

/**
 * @brief Descomprime una cadena de datos usando el algoritmo LZ78.

 * @param datosComprimidos Un puntero a un arreglo de caracteres con los datos comprimidos.

 * El formato esperado es una secuencia de tokens de 3 bytes:

 * - 2 bytes para el índice del diccionario (un `unsigned short`).

 * - 1 byte para el siguiente caracter (un `char`).

 * @param tamanoComprimido El número total de bytes en el arreglo de datosComprimidos.

 * @param tamanoSalida Una variable pasada por referencia donde la función guardará el tamaño del resultado descomprimido.

 * @return Un nuevo puntero a un arreglo de caracteres (`char*`) con los datos descomprimidos.

 * ¡IMPORTANTE! Debes liberar esta memoria con `delete[]` para evitar fugas de memoria.
 */

char *descomprimirLZ78(const char *datosComprimidos, int tamanoComprimido, int &tamanoSalida);

#endif // ALGORITMOS_H

