# Libreto Sencillo para el Video — Desafio 1 (C++ Basico)

Hola equipo. Este es el guion para nuestro video. Lo hicimos amigable, como si estuvieramos explicando a un amigo. Duracion: 7-9 minutos. Todos participamos, hablamos despacio y claro. Vamos a divertirnos.

##  Objetivo del Video
Contar cómo resolvimos el Desafío 1, mostrar el programa corriendo, y explicar partes del código sin tecnicismos. Como principiantes, pero orgullosos. 

Duración total: 7-9 min.
Participantes: 2-3 (todos hablan al menos una vez).

##  Estructura (3 Partes)
1. Presentación (máx. 3 min).
2. Demostración (máx. 3 min).
3. Explicación del código (máx. 5 min).
Cierre: 10-15 seg.

##  Preparación (Checklist)
- [ ] Código compila y corre sin errores.
- [ ] Dataset listo para mostrar 1-2 casos.
- [ ] Consola con letra grande (fácil de leer).
- [ ] Slides simples: títulos claros, pocos textos.
- [ ] Reparto: quién habla qué.

##  Guion Detallado

### Parte 1 — Presentación (2:30-3:00)
Apoyo visual: Slides con título, esquema problema, estrategia.

**Integrante 1 habla:**
- "¡Hola! Somos Camilo y Juan. Hoy mostramos cómo resolvimos el Desafío 1."
- "El problema: archivo encriptado y comprimido, solo una pista del texto original."
- "Meta: encontrar compresión (RLE o LZ78), rotación n, clave XOR K, y reconstruir el mensaje."
- "Nuestra idea: para este dataset, usamos params conocidos. n=3, k=0x5A o 0x40 según caso, tipo basado en número. Desencriptamos, descomprimimos y verificamos pista."

### Parte 2 — Demostración (2:00-3:00)
Apoyo visual: Qt Creator o terminal, corriendo el programa.

**Integrante 2 habla:**
- "Vamos a ver el programa. Elegimos un caso del dataset."
- "Corre, lee archivos, procesa con params fijos, y muestra params encontrados y texto completo."
- "Aquí está: caso X, params, y el mensaje. ¡Funciona!"

Nota: Si tarda, usa caso corto. Muestra inicio/final del texto.

### Parte 3 — Código Explicado (3:30-4:30)
Apoyo visual: Fragmentos de código (letra grande), esquemas de módulos.

**Repartir entre Integrante 1 y 3:**

Bloque 1 — Cripto (XOR y rotación)
- "Funciones simples: encriptar (rotar izquierda + XOR), desencriptar (XOR + rotar derecha)."
- "Usamos unsigned char, orden correcto para quitar encriptación."

Bloque 2 — RLE y LZ78
- "RLE: lee números + letra, expande. Calcula tamaño antes."
- "LZ78: diccionario con char**, lee tokens de 3 bytes, crece dinámicamente. Libera memoria bien."

Bloque 3 — Búsqueda de pista
- "contieneSubcadena: busca pista en texto. Fácil y directo."

Bloque 4 — Principal (procesarArchivo)
- "procesarArchivo(caso): params fijos por caso, lee, desencripta, descomprime, verifica."
- "Menú en main: elige caso, corre pruebas o procesamiento."

Buenas prácticas:
- "Sin STL, solo char* y memoria dinámica. Liberamos todo."
- "Probamos por partes: pruebas de RLE, LZ78, etc."
- "Fue como construir un rompecabezas, pieza por pieza."

##  Cierre (10-15 seg)
Apoyo visual: Slide de gracias con nombres y enlaces.

**Integrante 1 o todos:**
- "Eso fue nuestro Desafío 1. Explicamos, mostramos, explicamos código. ¡Gracias por ver!"

##  Sugerencias de Estilo
- Habla despacio, frases cortas.
- Términos simples (evita jerga).
- Muestra código mínimo.
- Pantalla limpia, zoom in.
- Practica una vez para tiempos.

##  Referencias
- Algoritmos: [02_Explicacion_Algoritmos_Descompresion.md](02_Explicacion_Algoritmos_Descompresion.md)
- Informe: [03_Informe_Desafio.md](03_Informe_Desafio.md)

