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
            //probarRLE();
            break;
        case 2:
            //probarLZ78();
            break;
        case 3:
            //probarCrypto();
            break;
        case 4:
            //procesarArchivo(1);
            break;
        case 5:
            //procesarArchivo(2);
            break;
        case 6:
            //procesarArchivo(3);
            break;
        case 7:
            //procesarArchivo(4);
            break;
        case 8:
            for (int i = 1; i <= 4; i++)
            {
                //procesarArchivo(i);
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
