#include "encriptacion.h"

unsigned char rotarDerecha(unsigned char byte, int n)
{
    return (byte >> n) | (byte << (8 - n));
}

unsigned char xoiByte(unsigned char byte, unsigned char clave)
{
    return byte ^ clave;
}

void desencriptar(unsigned char *data, int len, int n, unsigned char clave)
{
    for (int i = 0; i < len; i++)
    {
        // Aplicar XOR inverso (la operación XOR es su propia inversa)
        data[i] = xoiByte(data[i], clave);

        // Aplicar rotación derecha (inversa de la rotación izquierda)
        data[i] = rotarDerecha(data[i], n);
    }
}
