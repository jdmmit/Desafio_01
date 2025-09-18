#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

unsigned char rotarDerecha(unsigned char byte, int n);
unsigned char xoiByte(unsigned char byte, unsigned char clave);

void desencriptar(unsigned char* data, int len, int n, unsigned char clave);

#endif // ENCRIPTACION_H
