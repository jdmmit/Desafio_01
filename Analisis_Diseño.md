# Informe de Análisis y Diseño Inicial – Desafío 1  
**Curso:** Informática II – Universidad de Antioquia  
**Semestre:** 2025-2  
**Fecha:** 16 de septiembre de 2025  
**Autor:** [Juan David Murillo Mejia & Camilo Medina]  

---

## 1. Introducción  
Este desafío consiste en un ejercicio de **ingeniería inversa**.  
Se nos entrega un **mensaje comprimido y encriptado**, junto con un **fragmento conocido del mensaje original**.  
El objetivo es **reconstruir el texto completo**, identificando los métodos y parámetros usados en el proceso de compresión y encriptación.  

El mensaje original fue transformado en dos etapas:  
1. **Compresión**: Usando **RLE** o **LZ78**.  
2. **Encriptación**: Aplicando una **rotación de bits a la izquierda (n posiciones)** y una **operación XOR con una clave K**.  

Nuestra tarea es **invertir el proceso** para recuperar el mensaje original.

---

## 2. Objetivos  
- Determinar qué método de compresión se usó (**RLE o LZ78**).  
- Identificar los parámetros de encriptación:  
  - **n** = número de bits de rotación (1 a 7).  
  - **K** = clave de un byte (0 a 255).  
- Desencriptar el mensaje aplicando las operaciones inversas.  
- Descomprimir el resultado para obtener el mensaje original completo.  
- Mostrar en la salida:  
  - Texto original recuperado.  
  - Método de compresión identificado.  
  - Valores de `n` y `K`.  

---

## 3. Análisis del Problema  
### Entradas  
- **Mensaje encriptado y comprimido**: arreglo de bytes.  
- **Fragmento conocido del mensaje original**: arreglo de caracteres.  

### Salidas  
- Mensaje original completo.  
- Método de compresión utilizado.  
- Parámetros de encriptación (`n` y `K`).  

### Restricciones  
- Implementación en **C++ con Qt**.  
- **No usar `string` ni STL**, solo arreglos, punteros y memoria dinámica.  
- El texto contiene únicamente letras A–Z, a–z y dígitos 0–9.  
- Todo el desarrollo debe estar documentado en un repositorio con commits regulares.  

---

## 4. Estrategia de Solución  
El número de combinaciones posibles es bajo (2 métodos × 7 valores de `n` × 256 valores de `K` = 3584), por lo tanto el enfoque más práctico es un **algoritmo de fuerza bruta controlada**:  

1. **Probar todas las combinaciones posibles** de `n` y `K`.  
2. Para cada combinación:  
   - **Desencriptar** el mensaje (XOR inverso y rotación derecha).  
   - **Intentar descomprimir** con RLE y luego con LZ78.  
   - Verificar si el resultado contiene el **fragmento conocido**.  
3. Cuando se encuentre una coincidencia:  
   - Guardar el método, `n` y `K`.  
   - Reconstruir el mensaje completo.  

---

## 5. Esquema de Tareas  
1. **Lectura de datos**: Cargar mensaje y fragmento en arreglos dinámicos.  
2. **Desencriptación**:  
   - Función de rotación de bits (derecha).  
   - Función XOR por byte.  
3. **Descompresión**:  
   - Implementar RLE (contar repeticiones).  
   - Implementar LZ78 (diccionario dinámico con punteros).  
4. **Verificación**:  
   - Buscar si el fragmento conocido está en el texto generado.  
5. **Búsqueda de parámetros**:  
   - Triple bucle sobre método, `n`, `K`.  
6. **Reconstrucción final**:  
   - Desencriptar + descomprimir con parámetros correctos.  
   - Mostrar resultados.  
7. **Documentación y entrega**:  
   - Informe, repositorio y video explicativo.  

---

## 6. Posibles Problemas a Enfrentar  
- **Rotación de bits**: riesgo de errores si no se usan bien los 8 bits (solución: usar `unsigned char`).  
- **Conversión en RLE**: manejar números de más de un dígito (ej. 12A).  
- **Diccionario en LZ78**: gestionar cadenas sin `string` ni STL (usar `char**` y memoria dinámica).  
- **Memoria dinámica**: evitar fugas usando `delete[]`.  
- **Coincidencias falsas**: asegurar que el fragmento conocido sea suficientemente largo para validar.  

---

## 7. Evolución de la Solución  

- **Del 14 al 19 de septiembre (Análisis y Diseño):**  
  - Estudio del problema y lectura detallada del desafío.  
  - Elaboración del presente informe con el análisis inicial y diseño de la estrategia.  
  - Organización del plan de trabajo y definición de módulos.  
  - Primer commit en el repositorio con este documento.  

- **Del 20 al 25 de septiembre (Implementación y Pruebas):**  
  - Implementación de las funciones de desencriptación (rotación y XOR).  
  - Desarrollo del descompresor RLE (más sencillo).  
  - Desarrollo del descompresor LZ78 (más complejo, manejo de diccionario).  
  - Integración de los módulos en el programa principal.  
  - Ejecución de pruebas con ejemplos pequeños y luego con el mensaje del desafío.  
  - Commits regulares mostrando el progreso.  

- **26 de septiembre (Entrega final):**  
  - Reconstrucción completa del mensaje original con los parámetros correctos.  
  - Preparación y entrega del repositorio con todo el código y documentación.  
  - Grabación del video explicativo (análisis, demostración y explicación del código).  
  - Sustentación oral según indicaciones del profesor.  

---

## 8. Conclusión  
Aunque el desafío parece complejo, el problema se puede abordar con un plan paso a paso:  
1. Desencriptar.  
2. Descomprimir.  
3. Validar con el fragmento.  

Con este enfoque modular y el uso de herramientas básicas de C++ (punteros, arreglos, bucles), el reto es alcanzable incluso para quienes están comenzando en programación.  

---
