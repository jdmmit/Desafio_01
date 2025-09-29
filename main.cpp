/*
  Desafío 1 - Implementación simple sin librerías adicionales
  Solo usa <iostream>, punteros y memoria dinámica
  NO usa std::string ni STL (según requisitos del PDF)
*/


#include <iostream>
#include "algoritmos.h"

using namespace std;

// ====== UTILIDADES BÁSICAS ======

// Longitud de cadena C

int longitud(const char *str)
{
    if (!str)
        return 0;
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

// Copiar n bytes de src a dest

void copiar(char *dest, const char *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

// Comparar dos cadenas

bool comparar(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return false;
    int i = 0;
    while (s1[i] !='\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return false;
        i++;
    }
    return s1[i] == s2[i];
}

// Buscar subcadena en cadena

bool contiene(const char *texto, int lenTexto, const char *buscar, int lenBuscar)
{
    if (lenBuscar > lenTexto)
        return false;
    for (int i = 0; i <= lenTexto - lenBuscar; i++)
    {
        bool encontrado = true;
        for (int j = 0; j  < lenBuscar; j++)
        {
            if (texto[i + j] != buscar[j])
            {
                encontrado = false;
                break;
            }
        }
        if (encontrado)
            return true;
    }
    return false;
}

// ====== OPERACIONES DE BITS ======

// Rotación a la izquierda

unsigned char rotarIzquierda(unsigned char byte, int n)
{
    n = n & 7; // n mod 8
    return (byte << n) | (byte >> (8 - n));
}

// Rotación a la derecha
unsigned char rotarDerecha(unsigned char byte, int n)
{
    n = n & 7; // n mod 8
    return (byte >> n) | (byte << (8 - n));
}


// ====== ENCRIPTACIÓN/DESENCRIPTACIÓN ======

// Encriptar: Rotación izquierda + XOR

void encriptar(const char *entrada, int tam, int n, unsigned char k, char *salida)
{
    for (int i = 0; i < tam; i++)
    {
        unsigned char byte = (unsigned char)entrada[i];
        byte = rotarIzquierda(byte, n);
        byte = byte ^ k;
        salida[i] = (char)byte;
    }
}

// Desencriptar: XOR + Rotación derecha (operaciones inversas)
void desencriptar(const char *entrada, int tam, int n, unsigned char k, char *salida)
{
    for (int i = 0; i < tam; i++)
    {
        unsigned char byte = (unsigned char)entrada[i];
        byte = byte ^ k;
        byte = rotarDerecha(byte, n);
        salida[i] = (char)byte;
    }
}

// ====== LECTURA DE ARCHIVOS ======

// Lee archivo binario completo

char *leerArchivoBinario(const char *nombreArchivo, int &tamano)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        cout << "Error: No se pudo abrir " << nombreArchivo << endl;
        tamano = 0;
        return nullptr;
    }

    // Obtener tamaño
    fseek(archivo, 0, SEEK_END);
    tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Leer contenido
    char *buffer = new char[tamano + 1];
    fread(buffer, 1, tamano, archivo);
    buffer[tamano] = '\0';
    fclose(archivo);

    return buffer;
}

// Lee archivo de texto

char *leerArchivoTexto(const char *nombreArchivo, int &tamano)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo)
    {
        tamano = 0;
        return nullptr;
    }

    // Obtener tamaño

    fseek(archivo, 0, SEEK_END);
    tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Leer contenido

    char *buffer = new char[tamano + 1];
    fread(buffer, 1, tamano, archivo);
    buffer[tamano] = '\0';

    // Eliminar saltos de línea al final

    while (tamano > 0 && (buffer[tamano - 1] == '\n' || buffer[tamano - 1] == '\r'))
    {
        buffer[--tamano] = '\0';
    }

    fclose(archivo);
    return buffer;
}

// ====== FUNCIONES DE PRUEBA ======

// Probar descompresión RLE simple

void probarRLE()
{
    cout << "\n=== Prueba RLE ===" << endl;
    const char *comprimido = "5A3B2C1D";
    int tamComprimido = 8;
    int tamSalida = 0;

    char *resultado = descomprimirRLE(comprimido, tamComprimido, tamSalida);

    if (resultado)
    {
        cout << "Entrada: " << comprimido << endl;
        cout << "Salida: ";
        for (int i = 0; i < tamSalida; i++)
        {
            cout << resultado[i];
        }
        cout << endl;
        cout << "Tamaño salida: " << tamSalida << endl;
        delete[] resultado;
    }
    else
    {
        cout << "Error en descompresión RLE" << endl;
    }
}

// Probar descompresión LZ78 simple

void probarLZ78()
{
    cout << "\n=== Prueba LZ78 ===" << endl;

    // Ejemplo: (0,'A')(0,'B')(1,'A') -> "ABA"

    char comprimido[] = {0, 0, 'A', 0, 0, 'B', 1, 0, 'A'};
    int tamComprimido = 9;
    int tamSalida = 0;

    char *resultado = descomprimirLZ78(comprimido, tamComprimido, tamSalida);

    if (resultado)
    {
        cout << "Salida: ";
        for (int i = 0; i < tamSalida; i++)
        {
            cout << resultado[i];
        }
        cout << endl;
        cout << "Tamaño salida: " << tamSalida << endl;
        delete[] resultado;
    }
    else
    {
        cout << "Error en descompresión LZ78" << endl;
    }
}

// Probar encriptación/desencriptación

void probarCrypto()
{
    cout << "\n=== Prueba Encriptación/Desencriptación ===" << endl;

    const char *original = "HOLA";
    int tam = 4;
    int n = 3;              // Rotación 3 bits
    unsigned char k = 0x5A; // Clave XOR

    char *encriptado = new char[tam + 1];
    char *desencriptado = new char[tam + 1];

    encriptar(original, tam, n, k, encriptado);
    encriptado[tam] = '\0';

    desencriptar(encriptado, tam, n, k, desencriptado);
    desencriptado[tam] = '\0';

    cout << "Original: " << original << endl;
    cout << "Encriptado (hex): ";
    for (int i = 0; i < tam; i++)
    {
        cout << hex << (int)(unsigned char)encriptado[i] << " ";
    }
    cout << dec << endl;
    cout << "Desencriptado: " << desencriptado << endl;

    delete[] encriptado;
    delete[] desencriptado;
}

// ====== FUNCIÓN PRINCIPAL DE PROCESAMIENTO ======

void procesarArchivo(int caso)
{
    cout << "\n=== Procesando caso " << caso << " ===" << endl;

    // Construir nombres de archivos
    char rutaEncriptado[100] = "datasetDesarrollo/datasetDesarrollo/Encriptado";
    char rutaPista[100] = "datasetDesarrollo/datasetDesarrollo/pista";

    // Agregar número de caso
    rutaEncriptado[48] = '0' + caso;
    rutaEncriptado[49] = '.';
    rutaEncriptado[50] = 't';
    rutaEncriptado[51] = 'x';
    rutaEncriptado[52] = 't';
    rutaEncriptado[53] = '\0';

    rutaPista[42] = '0' + caso;
    rutaPista[43] = '.';
    rutaPista[44] = 't';
    rutaPista[45] = 'x';
    rutaPista[46] = 't';
    rutaPista[47] = '\0';

    // Leer archivos

    int tamEncriptado = 0;
    char *datosEncriptados = leerArchivoBinario(rutaEncriptado, tamEncriptado);
    if (!datosEncriptados)
    {
        cout << "No se pudo leer archivo encriptado" << endl;
        return;
    }

    int tamPista = 0;
    char *pista = leerArchivoTexto(rutaPista, tamPista);

    cout << "Archivo encriptado leído: " << tamEncriptado << " bytes" << endl;
    if (pista)
    {
        cout << "Pista: " << pista << endl;
    }

    // Parámetros conocidos del dataset

    int n = 3; // Rotación

    unsigned char k;
    int tipoCompresion; // 1=RLE, 2=LZ78

    if (caso == 1 || caso == 2)
    {
        k = 0x5A;
        tipoCompresion = (caso == 1) ? 1 : 2;
    }
    else
    {
        k = 0x40;
        tipoCompresion = (caso == 3) ? 1 : 2;
    }

    cout << "Parámetros: n=" << n << ", k=0x" << hex << (int)k << dec;
    cout << ", tipo=" << (tipoCompresion == 1 ? "RLE" : "LZ78") << endl;

    // Desencriptar

    char *datosDesencriptados = new char[tamEncriptado];
    desencriptar(datosEncriptados, tamEncriptado, n, k, datosDesencriptados);

    // Descomprimir

    int tamSalida = 0;
    char *textoFinal = nullptr;

    if (tipoCompresion == 1)
    {
        textoFinal = descomprimirRLE(datosDesencriptados, tamEncriptado, tamSalida);
    }
    else
    {
        textoFinal = descomprimirLZ78(datosDesencriptados, tamEncriptado, tamSalida);
    }

    if (textoFinal)
    {
        cout << "Texto descomprimido: " << tamSalida << " caracteres" << endl;

        // Mostrar primeros 100 caracteres

        cout << "Primeros 100 caracteres: ";
        for (int i = 0; i < tamSalida && i < 100; i++)
        {
            cout << textoFinal[i];
        }
        cout << "..." << endl;

        // Verificar pista
        if (pista)
        {
            if (contiene(textoFinal, tamSalida, pista, tamPista))
            {
                cout << "✓ La pista aparece en el texto!" << endl;
            }
            else
            {
                cout << "✗ La pista NO aparece en el texto" << endl;
            }
        }

        delete[] textoFinal;
    }
    else
    {
        cout << "Error en descompresión" << endl;
    }

    // Liberar memoria

    delete[] datosEncriptados;
    delete[] datosDesencriptados;
    if (pista)
        delete[] pista;
}






// ====== MENÚ PRINCIPAL ======

void mostrarMenu()
{
    cout << "\n========== MENÚ DESAFÍO 1 ==========" << endl;
    cout << "1. Probar RLE básico" << endl;
    cout << "2. Probar LZ78 básico" << endl;
    cout << "3. Probar Encriptación/Desencriptación" << endl;
    cout << "4. Procesar caso 1 (RLE + 0x5A)" << endl;
    cout << "5. Procesar caso 2 (LZ78 + 0x5A)" << endl;
    cout << "6. Procesar caso 3 (RLE + 0x40)" << endl;
    cout << "7. Procesar caso 4 (LZ78 + 0x40)" << endl;
    cout << "8. Procesar todos los casos" << endl;
    cout << "0. Salir" << endl;
    cout << "=====================================" << endl;
    cout << "Opción: ";
}

int main()
{
    int opcion;

    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            probarRLE();
            break;
        case 2:
            probarLZ78();
            break;
        case 3:
            probarCrypto();
            break;
        case 4:
            procesarArchivo(1);
            break;
        case 5:
            procesarArchivo(2);
            break;
        case 6:
            procesarArchivo(3);
            break;
        case 7:
            procesarArchivo(4);
            break;
        case 8:
            for (int i = 1; i <= 4; i++)
            {
                procesarArchivo(i);
            }
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción inválida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
