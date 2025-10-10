# Desafio 1: De Archivo Encriptado a Mensaje Completo

Hola. Imagina que tienes un archivo que parece un lio total: esta comprimido y encriptado, y solo tienes una pista chiquita del contenido original. Suena como un rompecabezas, verdad. Bueno, este desafio es justo eso. Vamos a armar el texto original paso a paso, como si fueramos detectives resolviendo un misterio.

## Que queremos lograr
Recuperar un mensaje que alguien escondio. El archivo esta encriptado con rotacion de bits y XOR, y ademas comprimido con RLE o LZ78. Con una pista (como una palabra clave), descubrimos como descifrarlo y boom, el texto completo aparece.

Piensa en esto como quitar capas: primero quitas la encriptacion, luego expandes la compresion, y al final verificas con la pista. Es como pelar una cebolla, pero mas divertido.

## Que nos dan para trabajar
- **EncriptadoX.txt**: El archivo misterioso, en binario, con datos cifrados y comprimidos.
- **pistaX.txt**: Un trocito del texto original, como "hola" o algo asi.
- **README.txt**: Las respuestas correctas (solo para chequear si lo hiciste bien).

Hay 4 casos (X = 1 a 4), cada uno con su propio archivo y pista. Es como niveles en un videojuego.

## Que debemos entregar
- El mensaje original completo (el texto real).
- Los "trucos" que usamos: tipo de compresion (RLE o LZ78), cuantas rotaciones (n=3), y la clave XOR (como 0x5A o 0x40).

## Reglas del juego
- Lenguaje: C++ (nos gusta porque es rapido y poderoso).
- Nada de librerias fancy: sin std::string, sin STL, sin structs. Solo punteros crudos: char*, new, delete[].
- Leemos archivos del disco y trabajamos todo en memoria.
- Para las operaciones de bits, usamos unsigned char, porque char normal puede dar dolores de cabeza con signos.

## Plan para resolverlo (paso a paso)
No hay que inventar magia. Seguimos estos pasos logicos.

**Paso 1: Preparar las herramientas de desencriptado**
- **aplicarXOR**: Pones un "candado" o lo quitas con una clave K (0-255). Es como mezclar bits.
- **rotarIzquierda/rotarDerecha**: Giras los bits de un byte, como mover letras en un circulo. Para desencriptar, giramos a la derecha.

**Nota**: Encriptamos con rotar izquierda + XOR, pero desencriptamos al reves: XOR primero, luego rotar derecha.

**Paso 2: Expandir con RLE**
RLE es como decir "5 A's seguidas" en vez de escribir AAAAA. Para descomprimir:
- Lees numeros (como 12) y luego la letra (como W).
- Repites la letra tantas veces como el numero.
- Calculas primero cuanto espacio necesitas, para no desperdiciar memoria.

**Paso 3: Expandir con LZ78**
Esto es mas tricky: arma un "diccionario" de frases mientras lee.
- Usa tokens de 3 bytes: 2 para el indice + 1 para la letra nueva.
- Construye frases una por una, como LEGO.
- Manejas memoria con char** (arreglos dinamicos), duplicas el tamano cuando se llena, y limpias todo al final.

**Paso 4: Procesar cada caso**
En nuestro codigo, para cada caso (1-4), sabemos los parametros del dataset:
- Casos 1-2: k=0x5A, caso 3-4: k=0x40, n=3 siempre.
- Tipo: RLE para 1 y 3, LZ78 para 2 y 4.
- Lees el archivo encriptado, desencriptas con esos params, descomprimes, y verificas si la pista aparece.

**Paso 5: Juntar todo en main**
- Un menu para elegir caso (1-4).
- Lee archivos, procesa, muestra resultados claros.
- Libera toda la memoria (importante, no queremos leaks).

## Como organizamos el codigo
Archivos principales:
- **main.cpp**: El cerebro, con el menu y funciones de test.
- **algoritmos.cpp**: Las implementaciones de RLE y LZ78.
- **algoritmos.h**: Las declaraciones (como el "contrato" de las funciones).

Funciones clave:
- Leer archivos: leerArchivoBinario, leerArchivoTexto.
- Cripto: encriptar/desencriptar (con rotar + XOR).
- Utilidades: longitud, copiar, comparar, contiene (para buscar pistas).

## Como probar (facil y rapido)
- Gira bits: Prueba rotarDerecha con valores pequenos.
- XOR: Aplica dos veces con la misma clave, debe volver igual.
- RLE: "5A3B" → "AAAAABBB". Facil.
- LZ78: Tokens como (0,'A')(0,'B')(1,'A') → "ABA".
- Todo junto: Corre los 4 casos y compara con README.txt.

Compilar: `g++ main.cpp algoritmos.cpp -o desafio` (o con Qt Creator).

## Checklist final
- [ ] Compila sin errores (C++17).
- [ ] Maneja los 4 casos bien.
- [ ] Sin STL ni std::string.
- [ ] Memoria bien manejada (new/delete[]).
- [ ] Maneja errores de archivos.
- [ ] Consola clara: params y mensaje.

## Errores comunes (y como no caer)
- **Rotar vs desplazar**: Rotar no pierde bits; desplazar si. Siempre rota.
- **Char con signo**: Usa unsigned char para bits.
- **Memoria leaks**: Cada new[] necesita delete[]. Revisa!
- **No calcular tamano en RLE**: Terminas con memoria insuficiente.
- **Modificar original**: Trabaja con copias siempre.

