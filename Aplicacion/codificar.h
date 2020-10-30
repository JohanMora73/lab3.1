#ifndef CODIFICAR_H
#define CODIFICAR_H

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;


class Codificar
{
private:
    string archivo;
    unsigned int semilla;

    //metodos privados
    string Stringabinario();// combierte la cadena de caracteres a binario
    unsigned int SiguienteMultiplo(int,int);// mira si la longitude la cadena es multiplo de la semilla y si no, calcula el siguiente multiplo
    int Contarunos(string);// cuenta la cantidad de unos en la cadena de caracteres
    string Desplazarbits(string);// contiene las reglas del segundo metodo de encriptacion
    unsigned int AnteriorMultiplo(int,int);//busca el ultimo multiplo de 8
    char Binarioastring(string _letra);// convierte una cadena binaria a su respectivo caracter
    string Desplazarbits2(string binario);// contiene las reglas del segundo metodo para desencriptar
public:
    Codificar(string,unsigned int);
    ~Codificar();

    //metodos publicos
    string Encriptacion();// aplica el segundo metodo de encriptacion
    string Desencriptacion();// aplica el segundo metodo de desencriptacion

};

#endif // CODIFICAR_H
