#include "algoritmos.h"

// Incluimos nuestro propio archivo de cabecera.

// --- Utilidades locales
static inline bool esDigito(char c) { return c >= '0' && c <= '9'; }
static int parseEnteroPositivo(const char *s, int len)
{
    int v = 0;
    for (int i = 0; i < len; ++i)
    {
        char c = s[i];
        if (c < '0' || c > '9')
            break;
        v = v * 10 + (c - '0');
    }
    return v;
}
static int myStrLen(const char *s)
{
    if (!s)
        return 0;
    int n = 0;
    while (s[n] != '\0')
        ++n;
    return n;
}
static void myMemCopy(char *dest, const char *src, int n)
{
    for (int i = 0; i < n; ++i)
        dest[i] = src[i];
}

// --- Implementación de la Descompresión RLE ---

char *descomprimirRLE(const char *datosComprimidos, int tamanoComprimido, int &tamanoSalida)
{
    // --- PASO 1: Pre-calcular el tamaño final ---

    // Recorremos los datos una vez solo para saber cuánto espacio vamos a necesitar.

    // Esto es mucho más eficiente que ir agrandando el buffer poco a poco.

    tamanoSalida = 0;
    for (int i = 0; i < tamanoComprimido;)
    {

        // Creamos un pequeño buffer temporal para guardar los dígitos del número.

        char bufferNumero[10] = {0}; // Inicializado a ceros.
        int k = 0;

        // Mientras el caracter actual sea un dígito, lo guardamos en nuestro buffer.

        while (i < tamanoComprimido && esDigito(datosComprimidos[i]) && k < 9)
        {
            bufferNumero[k++] = datosComprimidos[i++];
        }

        // Si encontramos al menos un dígito...

        if (k > 0)
        {
            // Convertimos el buffer de texto (ej: "12") a un número entero (12) y lo sumamos al total.

            tamanoSalida += parseEnteroPositivo(bufferNumero, k);
        }

        // Avanzamos el índice `i` para saltar el caracter que no es un dígito (ej: la 'A' en "12A").

        i++;
    }

    // Si por alguna razón el tamaño de salida es 0, no hay nada que hacer.

    if (tamanoSalida == 0)
    {
        return nullptr; // Devolvemos un puntero nulo.
    }

    // --- PASO 2: Reservar memoria y descomprimir de verdad ---

    // Pedimos la cantidad exacta de memoria que calculamos. +1 para el caracter nulo `\0` al final.

    char *datosSalida = new char[tamanoSalida + 1];
    int indiceSalida = 0;

    // Este será nuestro contador para saber dónde escribir en el buffer de salida.

    // Repetimos el mismo proceso de antes, pero esta vez sí escribimos los datos.

    for (int i = 0; i < tamanoComprimido;)
    {
        char bufferNumero[10] = {0};
        int k = 0;
        while (i < tamanoComprimido && esDigito(datosComprimidos[i]) && k < 9)
        {
            bufferNumero[k++] = datosComprimidos[i++];
        }

        if (i < tamanoComprimido)
        {
            // Convertimos el número a entero. Si no había número, asumimos que es 1.

            int conteo = (k > 0) ? parseEnteroPositivo(bufferNumero, k) : 1;

            // El caracter a repetir es el que viene justo después de los dígitos.

            char caracter = datosComprimidos[i++];

            // Escribimos el caracter en la salida `conteo` veces.

            for (int j = 0; j < conteo; ++j)
            {
                // Verificamos que no nos pasemos del tamaño que reservamos.

                if (indiceSalida < tamanoSalida)
                {
                    datosSalida[indiceSalida++] = caracter;
                }
            }
        }
    }

    // ¡Muy importante! Agregamos el caracter nulo al final para que sea una cadena de texto válida en C++.

    datosSalida[tamanoSalida] = '\0';

    // Devolvemos el puntero a la memoria recién creada con los datos descomprimidos.

    return datosSalida;
}

// --- Implementación de la Descompresión LZ78 ---

// OJO! Esta implementacion es mas compleja porque no podemos usar STL (como std::map o std::vector).

// Lo haremos todo manualmente con punteros y memoria dinámica.

char *descomprimirLZ78(const char *datosComprimidos, int tamanoComprimido, int &tamanoSalida)

{
    // --- GESTIÓN DEL DICCIONARIO (LA PARTE DIFÍCIL) ---

    int capacidadDiccionario = 100;

    // Empezamos con espacio para 100 "palabras".

    // `char**` significa "puntero a un puntero de char". Lo usamos como un arreglo de cadenas (char*).

    char **diccionario = new char *[capacidadDiccionario];
    int tamanoDiccionario = 0;

    // Al principio, nuestro diccionario está vacío.

    // --- GESTIÓN DEL BUFFER DE SALIDA ---

    int capacidadSalida = 1024; // Empezamos con un buffer de 1KB.

    char *datosSalida = new char[capacidadSalida];
    tamanoSalida = 0;

    // Al principio, la salida está vacía.

    // Recorremos los datos de 3 en 3 bytes (2 para el índice, 1 para el caracter).

    for (int i = 0; i < tamanoComprimido; i += 3)
    {

        // Nos aseguramos de que haya al menos 3 bytes para leer.

        if (i + 2 >= tamanoComprimido)
            break;

        // Leemos el token (formato: 2 bytes de indice en little-endian + 1 byte de caracter).

        // Interpretacion portable sin reinterpret_cast (evita problemas de alineamiento/endianness):

        unsigned short indice = static_cast<unsigned short>(
            static_cast<unsigned char>(datosComprimidos[i]) |
            (static_cast<unsigned char>(datosComprimidos[i + 1]) << 8));
        char caracter = datosComprimidos[i + 2];

        // Buscamos el prefijo en el diccionario.

        const char *prefijo = "";

        // Por defecto, es una cadena vacía.

        if (indice > 0 && indice <= tamanoDiccionario)
        {
            prefijo = diccionario[indice - 1];

            // Los índices del diccionario empiezan en 1.
        }

        int lenPrefijo = (indice == 0) ? 0 : myStrLen(prefijo);
        int lenNuevaFrase = lenPrefijo + 1;

        // --- Escribimos en la salida, agrandando el buffer si es necesario ---
        if (tamanoSalida + lenNuevaFrase >= capacidadSalida)
        {
            capacidadSalida *= 2;

            // Duplicamos el tamaño.

            char *nuevoBuffer = new char[capacidadSalida];
            myMemCopy(nuevoBuffer, datosSalida, tamanoSalida);

            // Copiamos lo que ya teníamos.

            delete[] datosSalida;

            // Liberamos la memoria vieja.

            datosSalida = nuevoBuffer;
            // Apuntamos al nuevo buffer más grande.
        }

        // Copiamos el prefijo y luego el nuevo caracter a la salida.

        if (lenPrefijo > 0)
            myMemCopy(datosSalida + tamanoSalida, prefijo, lenPrefijo);
        datosSalida[tamanoSalida + lenPrefijo] = caracter;
        tamanoSalida += lenNuevaFrase;

        // --- Agregamos la nueva frase al diccionario, agrandándolo si es necesario ---

        if (tamanoDiccionario >= capacidadDiccionario)
        {
            capacidadDiccionario *= 2;
            char **nuevoDiccionario = new char *[capacidadDiccionario];
            for (int j = 0; j < tamanoDiccionario; ++j)
                nuevoDiccionario[j] = diccionario[j];
            delete[] diccionario;
            diccionario = nuevoDiccionario;
        }

        // Creamos la nueva entrada para el diccionario.

        char *nuevaEntrada = new char[lenNuevaFrase + 1];
        if (lenPrefijo > 0)
        {
            myMemCopy(nuevaEntrada, prefijo, lenPrefijo);
        }
        nuevaEntrada[lenPrefijo] = caracter;
        nuevaEntrada[lenPrefijo + 1] = '\0';
        diccionario[tamanoDiccionario++] = nuevaEntrada;
    }

    // Agregamos el terminador nulo a la salida.

    datosSalida[tamanoSalida] = '\0';

    // --- LIMPIEZA FINAL (CRUCIAL!) ---

    // Liberamos la memoria de cada una de las "palabras" que guardamos en el diccionario.

    for (int i = 0; i < tamanoDiccionario; ++i)
    {
        delete[] diccionario[i];
    }

    // Y finalmente, liberamos el arreglo de punteros que era el diccionario en sí.

    delete[] diccionario;

    return datosSalida;
}
