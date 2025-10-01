# Enlace de Video 

## https://www.youtube.com/watch?v=52HZfbozqqQ

# Desafio 01: Recuperacion de Texto Encriptado y Comprimido

Hola. Bienvenido a nuestro proyecto para el Desafio 1 de Informatica II en la Universidad de Antioquia. Aqui resolvimos un reto de ingenieria inversa: dado un archivo encriptado y comprimido, con una pista pequena, reconstruimos el texto original usando C++ basico.

## Que es este proyecto
Es un programa en C++ que lee archivos cifrados, los desencripta (con rotacion de bits y XOR), los descomprime (RLE o LZ78), y verifica con una pista. No usa librerias fancy como STL o string; todo con punteros y memoria dinamica.

El desafio simula ingenieria inversa: con info limitada, deducimos algoritmos y parametros para recuperar datos.

Curso: Informatica II – Universidad de Antioquia
Semestre: 2025-2
Fecha: 28 de septiembre de 2025
Autores: Juan David Murillo Mejia & Camilo Medina

## Como esta estructurado (orden para revisar)
Para entender y usar el proyecto, lee en este orden. Es como armar un rompecabezas: empezamos con la idea general, luego detalles, luego codigo, luego resumen, y al final el video.

1. **Primero: Analisis del Abordaje** ([01_Analisis_Abordaje_Desafio_1.md](01_Analisis_Abordaje_Desafio_1.md))
   - Idea general del problema y solucion.
   - Plan paso a paso para resolverlo.
   - Estructura del codigo y como probar.
   - Lee esto para entender el reto antes de nada.

2. **Segundo: Explicacion de Algoritmos** ([02_Explicacion_Algoritmos_Descompresion.md](02_Explicacion_Algoritmos_Descompresion.md))
   - Detalles de XOR, rotacion de bits, RLE y LZ78.
   - Ejemplos simples y codigo basico.
   - Aqui ves como funcionan las piezas clave.

3. **Tercero: El Codigo (como funciona y como se ejecuta)**
   - Archivos principales:
     - **main.cpp**: Menu principal, pruebas y procesamiento de casos.
     - **algoritmos.cpp**: Funciones de descompresion RLE y LZ78.
     - **algoritmos.h**: Declaraciones de funciones.
     - **Desafio_01.pro**: Proyecto para Qt Creator.
   - Como ejecutar:
     - Compila con g++: `g++ main.cpp algoritmos.cpp -o desafio` (o usa Qt Creator).
     - Corre `./desafio` (en Linux/Mac) o `desafio.exe` (en Windows).
     - Elige opcion en el menu: pruebas de RLE/LZ78, o procesar casos 1-4 con dataset.
     - Necesitas la carpeta datasetDesarrollo/ con archivos EncriptadoX.txt y pistaX.txt.
     - Salida: Muestra params encontrados y texto descomprimido.

4. **Cuarto: Informe del Proyecto** ([03_Informe_Desafio.md](03_Informe_Desafio.md))
   - Resumen de decisiones, pruebas y problemas resueltos.
   - Checklist final y cronograma.
   - Lee despues de entender el codigo, para ver el proceso completo.

5. **Quinto: Libreto para el Video** ([04_Libreto_Video_Proyecto_Desafio1.md](04_Libreto_Video_Proyecto_Desafio1.md))
   - Guion para explicar el proyecto en video.
   - Partes: presentacion, demo, explicacion de codigo.
   - Opcional, para presentaciones.

.gitignore: Archivos a ignorar en Git.

## Como empezar (facil de implementar)
1. Clona o descarga el repositorio.
2. Abre en Qt Creator o compila manualmente.
3. Asegura tener datasetDesarrollo/ (con archivos de prueba).
4. Corre y prueba con casos 1-4.
5. Compara resultados con README.txt del dataset.

Hay una carpeta adicional dataset_practica/ con 10 ejemplos simples de RLE para practicar. Cada practicaX.txt tiene entrada, pista y salida esperada.


