# Explicacion Sencilla de los Algoritmos: Desencriptar y Descomprimir

Hola de nuevo. Aqui te cuento, como si estuvieramos charlando, como funcionan las partes clave de nuestro proyecto. Vamos a quitar la encriptacion (XOR y rotacion de bits) y luego expandir la compresion (RLE o LZ78). Tambien, como buscar una pista en el texto. Todo explicado paso a paso, sin complicar.

##  Antes de empezar
Reglas básicas:
- Sin std::string, sin STL, sin structs. Solo char*, new, delete[].
- Para bits, usa unsigned char (evita líos con signos).
- Orden para desencriptar: primero XOR con la clave K, luego rota a la derecha n posiciones.

Rotar no es mover y perder; es girar como una rueda: lo que sale por un lado vuelve por el otro. 

##  XOR: Quitar o Poner un "Candado" Mágico
¿Qué es? Una operación que mezcla bits con una clave. Como si cada bit dijera: "¿Me invierto o no?". Aplicas dos veces con la misma clave, y ¡pum!, vuelve igual. Es como un truco de magia. 

Ejemplo mental:
- Dato: 10101010
- Clave: 11110000
- Resultado: 01011010
- Aplicar clave otra vez: 10101010 (¡regresa!)

En C++:
```cpp
void aplicarXOR(char* datos, int tamano, unsigned char clave) {
    for (int i = 0; i < tamano; ++i) {
        datos[i] = datos[i] ^ clave;  // Mezcla bit a bit
    }
}
```

Prueba: Aplica XOR dos veces con la misma clave. Debe quedar igual. ¡Fácil de chequear!

##  Rotación de Bits a la Derecha
Imagina un byte como 8 lucecitas en fila. Giras todo hacia la derecha n pasos. Lo último va al principio. Nada se pierde. 

Función:
```cpp
unsigned char rotarDerecha(unsigned char b, int n) {
    n = n % 8;  // Máximo 7 giros
    return (b >> n) | (b << (8 - n));  // Gira y combina
}
```

Si tu byte es char (puede ser negativo), conviértelo a unsigned char primero. No uses char normal para esto, ¡da dolores de cabeza!

##  RLE: Expansión de Repeticiones (Run-Length Encoding)
¿Qué hace? Comprime secuencias largas. En vez de "AAAAA", guarda "5A". Para descomprimir, lees el número y repites la letra. Como inflar un globo. 

Cómo funciona paso a paso:
1. Lee dígitos para formar el número (puede ser 12, 103, etc.).
2. Lee la letra siguiente.
3. Repite la letra tantas veces como el número.
4. Sigue hasta el final.

Primero, calcula el tamaño total (para pedir memoria exacta). Luego, expande de verdad.

Ejemplo: "11W1B12W" → WWWWWWWWWWWBW... (11 W, 1 B, 12 W).

Código simple (sin usar atoi ni string):
```cpp
char* descomprimirRLE(const char* in, int nIn, int& nOut) {
    // Paso 1: Calcular nOut
    nOut = 0;
    for (int i = 0; i < nIn; ) {
        char buf[10] = {0}; int k = 0;
        while (i < nIn && in[i] >= '0' && in[i] <= '9' && k < 9) {
            buf[k++] = in[i++];
        }
        if (k > 0) nOut += parseEntero(buf, k);  // Función propia para convertir
        i++;  // Saltar la letra
    }
    if (nOut == 0) return nullptr;

    // Paso 2: Expandir
    char* out = new char[nOut + 1];
    int j = 0;
    // ... (similar, pero escribiendo)
    out[nOut] = '\0';
    return out;
}
```

Errores comunes: Olvidar calcular nOut primero → memoria insuficiente o desperdicio. Números largos sin límite → usa buffer con tope.

##  LZ78: Diccionario que Crece Solo
Esto es más avanzado: construye un diccionario de frases mientras lee. Como aprender palabras nuevas en un idioma. 

Entrada: Tokens de 3 bytes: 2 para índice (puntero a frase previa), 1 para letra nueva. En nuestro código, leemos como unsigned short para el índice.

Proceso:
- Si índice 0: nueva frase = solo la letra.
- Si índice > 0: nueva frase = diccionario[indice-1] + letra.
- Escribe la frase en salida, agrégala al diccionario.
- Diccionario crece: usa char** (arreglo de cadenas), duplica tamaño si se llena.

Al final, libera cada entrada del diccionario y el arreglo mismo. ¡Importante, no dejes basura!

Código base:
```cpp
char* descomprimirLZ78(const char* in, int nIn, int& nOut) {
    char** dic = new char*[100];  // Empieza con 100
    int lenDic = 0;
    char* out = new char[1024];  // Salida inicial
    nOut = 0;
    // ... (leer tokens, construir diccionario, escribir salida)
    // Liberar: for(int i=0; i<lenDic; i++) delete[] dic[i]; delete[] dic;
    return out;
}
```

Advertencia: Endianness (orden de bytes) en unsigned short. Si no funciona, arma el índice manual: in[i] + (in[i+1] << 8).

## 🔍 Buscar una Pista en el Texto
¿La pista está dentro del texto grande? Como buscar una aguja en un pajar. 🧶

Función:
```cpp
bool contieneSubcadena(const char* pajar, int nPajar, const char* aguja, int nAguja) {
    for (int i = 0; i <= nPajar - nAguja; ++i) {
        bool igual = true;
        for (int j = 0; j < nAguja; ++j) {
            if (pajar[i + j] != aguja[j]) { igual = false; break; }
        }
        if (igual) return true;
    }
    return false;
}
```

Búsqueda directa, suficiente para esto.

##  Pruebas Rápidas
- XOR doble: vuelve igual.
- Rotación: n=0,1,7 con byte conocido.
- RLE: "3A4B1C" → "AAABBBBC".
- LZ78: Tokens cortos → "ABA".

##  Errores Comunes y Cómo Evitarlos
- Char con signo en bits: usa unsigned char.
- No liberar memoria: cada new[] → delete[].
- Copias en lugar de modificar original.
- Formato LZ78 malo: verifica 2 bytes índice + 1 byte char.



