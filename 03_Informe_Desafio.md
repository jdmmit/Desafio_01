# Informe Amigable del Desafio 1 — Como Lo Hicimos Paso a Paso

Hola. Aqui te cuento todo sobre nuestro proyecto, como si estuvieramos tomando un cafe. Resolvimos un desafio donde un archivo esta encriptado y comprimido, y usamos una pista para recuperarlo. Fue como ser detectives en una pelicula. Vamos a ver que hicimos, como pensamos y que aprendimos.

##  Resumen en Una Frase
Recuperamos un texto original que fue comprimido (RLE o LZ78) y encriptado (rotación de bits + XOR), usando una pista pequeña. ¡Misión cumplida!

##  ¿Cuál Es el Problema?
- Archivo encriptado: EncriptadoX.txt (X=1 a 4).
- Pista: pistaX.txt, un fragmento del texto real.
- Desconocidos: método de compresión, rotación n, clave XOR K.
- Meta: descubrir esos y reconstruir el mensaje completo.

##  Reglas del Proyecto
- C++ (C++17 ideal).
- Sin std::string, STL o structs.
- Solo char*, new, delete[].
- Leer de disco, procesar en memoria.
- unsigned char para bits (evita problemas).

##  Idea General de la Solución
En este proyecto, no usamos "fuerza bruta" general (probar todo). En cambio, el dataset nos da pistas sobre los parámetros. Para cada caso:
- Casos 1-2: k=0x5A, casos 3-4: k=0x40.
- n=3 siempre (rotación).
- Tipo: RLE para 1 y 3, LZ78 para 2 y 4.

Proceso: lee archivo, desencripta con params fijos, descomprime, verifica pista. ¡Simple y directo!

##  Algoritmos Usados (Resumen)
- **XOR**: Mezcla bits con clave; aplica dos veces y vuelve igual.
- **Rotación**: Gira bits sin perder nada.
- **RLE**: Expande números + letras (ej: 5A → AAAAA).
- **LZ78**: Diccionario dinámico de frases.
- Detalles en [02_Explicacion_Algoritmos_Descompresion.md](02_Explicacion_Algoritmos_Descompresion.md)

##  Estructura del Proyecto
- Código: main.cpp (lógica principal), algoritmos.cpp (descompresión), algoritmos.h (declaraciones).
- Datos: datasetDesarrollo/ con archivos de prueba.
- Docs: Este informe y guías.

##  Quién Hace Qué
- Lector: lee EncriptadoX.txt y pistaX.txt a memoria.
- Cripto: encriptar/desencriptar (rotar + XOR).
- Descompresores: descomprimirRLE, descomprimirLZ78.
- Búsqueda: contieneSubcadena para pista.
- Principal: procesarArchivo(caso), con menú en main.

##  Decisiones Técnicas
- unsigned char: evita signos raros en bits.
- for: para bucles con conteo conocido.
- while: para leer números variables en RLE.
- Memoria: calcula tamaño antes (RLE), redimensiona por duplicación (LZ78), libera todo.

##  Pruebas Hechas
- Unitarias: XOR doble, rotación con n=1-7, RLE "3A4B" → "AAABBBBC", LZ78 cortos.
- Integración: procesar 4 casos, comparar con README.txt.

##  Problemas y Soluciones
- Rotación vs desplazamiento: rotación no pierde bits.
- Char con signo: siempre unsigned char.
- Memoria: delete[] por cada new[].
- Copias: nunca modificar original.
- Formato LZ78: 2 bytes índice + 1 char.

##  Guía para el Video
- Parte A: explicar problema y estrategia (3 min).
- Parte B: demo con un caso (3 min).
- Parte C: código clave (5 min).
- Todos hablan, duración 7-9 min.
- Libreto en [04_Libreto_Video_Proyecto_Desafio1.md](04_Libreto_Video_Proyecto_Desafio1.md)

##  Cronograma
- Semana 1: análisis y borrador.
- Semana 2: código y pruebas.
- Fin: video y entrega.

##  Checklist Final
- [ ] Compila sin warnings (C++17).
- [ ] Resuelve 4 casos correctos.
- [ ] Sin STL.
- [ ] Memoria limpia.
- [ ] Salida clara.
- [ ] Docs y video listos.
- [ ] Commits frecuentes.

