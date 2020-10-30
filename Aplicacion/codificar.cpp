#include "codificar.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include<bits/stdc++.h>//libreria para utilizar la funcion reverse

using namespace std;

Codificar::Codificar(string _archivo,unsigned int _semilla)//constructor
{
    archivo=_archivo;
    semilla=_semilla;
}
Codificar::~Codificar() //Destructor
{ }
string Codificar::Stringabinario()
{
    string bin="";
    int num;
    for(unsigned int i=0;i<archivo.length();i++){
        num=int(archivo.at(i));//valor del caracter
        string aux="";// cadena auxiliar que guarda la conversion a binario
        int cont=0;
        while(cont<8){
            if(num%2==1)aux=aux+'1';// agrega un 1 a la cadena de caracteres
            else aux=aux+'0';// agrega un 0 a la cadena de caracteres
            num=num/2;
            cont++;
        }
        reverse(aux.begin(),aux.end());// invertir cadena de caracteres
        bin=bin+aux;
    }
    return bin;
}
unsigned int Codificar:: SiguienteMultiplo(int _num,int _len)
{
    while(_len%_num!=0)_len++;// si es multiplo su la operacion modulo sera igual a 0
    return _len;
}
int Codificar::Contarunos(string tex)
{
    int count;
    for(unsigned int i=0;i<tex.length();i++){
        if(tex.at(i)=='1')count++;// si el caracter es 1 le suma uno a count
    }
    return count;
}
string Codificar:: Desplazarbits(string binario)
{
    string encrip;
    encrip=binario.at(binario.length()-1);// pongo el ultimo bit en la primera pocision del nuevo arreglo encriptado
    for(unsigned int i=0;i<binario.length()-1;i++){
        encrip=encrip+binario.at(i);// voy llenando el arreglo encriptado
    }
    return encrip;
}
string Codificar:: Encriptacion()
{
    string _binaria=Stringabinario();
    unsigned int cont=0;
    string aux,encriptada;
    for(unsigned int i=0;i<_binaria.length()-1;i++){
        cont++;
        if(cont<=semilla){
            aux=aux+_binaria.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==semilla){
            encriptada=encriptada+Desplazarbits(aux);
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    aux=aux+_binaria.at(_binaria.length()-1);// asigno el ulrimo bit de la cadena de caracteres
    encriptada=encriptada+Desplazarbits(aux);
    cont=0;
    unsigned int diferencia=SiguienteMultiplo(semilla,_binaria.length())-_binaria.length();// cantidad de ceros a agregar
    while(cont<diferencia){// se agregan los numeros faltantes
        aux=aux+'0';// completamos con ceros si es necesario el bloque de bits
        cont++;
    }
    encriptada=encriptada+Desplazarbits(aux);
    return encriptada;
}
unsigned int Codificar::AnteriorMultiplo(int _num, int _len)
{
    while(_len%_num!=0)_len--;// busco el ultimo multiplo de 8
    return _len;
}
char Codificar::Binarioastring(string _letra){
    int valor,car,j=7;
    char caracter;
    for(unsigned int i=0;i<_letra.length();i++){
        valor=_letra.at(i)-48;// convierto cada caracter a un numero entero
        car=car+valor*pow(2,j);// multiplico el valor por las potencias de 2 para convertir de binario a entero
        j--;
    }
    caracter=char(car);// creo el caracter con el numero entero obtenido
    return caracter;
}
string Codificar::Desplazarbits2(string binario)
{
    string encrip="";
    for(unsigned int i=1;i<binario.length();i++){
        encrip=encrip+binario.at(i);// voy llenando el arreglo encriptado
    }
    encrip=encrip+binario.at(0);// pongo el primer bit en la ultima pocision del nuevo arreglo decodificado
    return encrip;
}
string Codificar::Desencriptacion()
{
    unsigned int cont;
    string cadena,aux,desencriptada,convertir;
    for(unsigned int i=0;i<archivo.length()-1;i++){
        cont++;
        if(cont<=semilla){
            aux=aux+archivo.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==semilla){
            desencriptada=desencriptada+Desplazarbits2(aux);
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    aux=aux+archivo.at(archivo.length()-1);// asigno el ulrimo bit de la cadena de caracteres
    desencriptada=desencriptada+Desplazarbits2(aux);
    unsigned int diferencia=AnteriorMultiplo(8,archivo.length());// valor del ultimo multiplo de 8 para saber cuales son los bits de interes
    aux="";//reutilizo aux, creando una nuvea cadena con longitud de la variable diferencia( asi dejo por fuera los ceros agregados)
    for (unsigned int i=0;i<diferencia;i++)aux=aux+desencriptada.at(i);// lleno la nueva cadena
    for(unsigned int i=0;i<aux.length();i++){
        convertir=convertir+aux.at(i);//creo cadena de 8 bits correspondientes a cada letra
        if((i+1)%8==0){
            cadena=cadena+Binarioastring(convertir);//Convierto el caracter binario
            convertir="";// actualizo la cadena
        }
    }
    return cadena;
}
