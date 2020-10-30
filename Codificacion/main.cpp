#include <iostream>
#include <string.h>// libreria para la clase string
#include <fstream>// libreria para el manejo de archivos
#include<bits/stdc++.h>//libreria para utilizar la funcion reverse

using namespace std;

string Stringabinario(string);// combierte la cadena de caracteres a binario
unsigned int Multiplo(int,int);// mira si la longitude la cadena es multiplo de la semilla y si no, calcula el siguiente multiplo
int Contarunos(string);// cuenta la cantidad de unos en la cadena de caracteres
string Invertirbits(string,string);// contiene las reglas del primer metodo de encriptacion
string Encriptacion1(string, unsigned int);// aplica el primer metodo de encriptacion
string Desplazarbits(string);// contiene las reglas del segundo metodo de encriptacion
string Encriptacion2(string,unsigned int);// aplica el segundo metodo de encriptacion

int main()
{
    unsigned int semilla,metodo;
    string archivo,binaria,encriptada,nombrearchivo,escritura;
    ifstream lectura;// abrir archivo en modo lectira
    ofstream codificado;// escribir un archivo
    cout<<"Escriba la direccion del archivo de entrada(recuerde escribir la extension del archivo):";
    cin>>nombrearchivo;
    cout<<"Escriba la direccion del archivo de salida(recuerde escribir la extension del archivo):";
    cin>>escritura;
    lectura.open(nombrearchivo.c_str(),ios::in);
    if(!lectura.is_open()){// se verifica si el archivo abre exitosamente
        std::cout<<"Error abriendo el archivo"<<endl;
        exit(1);
    }
    while(!lectura.eof()){// lee mientras no sea el final del archivo
        getline(lectura,archivo);
    }
    lectura.close();// cerrar archivo
    cout<<"1.Metodo 1(escribir 1)"<<endl<<"2.Metodo 2(escribir 2)"<<endl;
    cout<<"Escribe el metodo que desea usar:";
    cin>>metodo;
    cout<<"Escribe el numero de la semilla que desea utilizar:";
    cin>>semilla;
    binaria=Stringabinario(archivo);// cadena que guarda la cadena convertida a binario
    if(metodo==1)encriptada=Encriptacion1(binaria,semilla);// primer metodo de encriptacion
    else encriptada=Encriptacion2(binaria,semilla);
    codificado.open(escritura.c_str(),ios::out);
    if(!codificado.is_open()){// se verifica si el archivo abre exitosamente
        std::cout<<"Error creando el archivo"<<endl;
        exit(1);
    }
    else{
        codificado<<encriptada;
        codificado.close();// cerrar el archivo
        cout<<"Archivo encriptado con exito"<<endl;
    }
    return 0;
}

string Stringabinario(string _archivo)
{
    string bin="";
    int num;
    for(unsigned int i=0;i<_archivo.length();i++){
        num=int(_archivo.at(i));//valor del caracter
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
unsigned int Multiplo(int _num,int _len)
{
    while(_len%_num!=0)_len++;// si es multiplo su la operacion modulo sera igual a 0
    return _len;
}
int Contarunos(string tex){
    int count;
    for(unsigned int i=0;i<tex.length();i++){
        if(tex.at(i)=='1')count++;// si el caracter es 1 le suma uno a count
    }
    return count;
}
string Invertirbits(string binario,string aux)
{
    int unos,ceros;
    string encrip="";// cadena que se reorna con la regla aplicada
    unos=Contarunos(aux);// cantidad de unos que tiene el bloque de bits anterior
    ceros=aux.length()-unos;// cantidad de ceros que tiene el bloque de bits anterior
    if(unos==ceros){//regla de encriptacion
        for(unsigned int i=0;i<binario.length();i++){
            if(binario.at(i)=='1')encrip=encrip+'0';// concatenamos la cadena
            else encrip=encrip+'1';
        }
    }
    else if(ceros>unos){//regla de encriptacion
        int cont=1;
        for(unsigned int i=0;i<binario.length();i++){
            if(cont==2){// se invierte un bit cada 3 bits
                cont=1;
                if(binario.at(i)=='1')encrip=encrip+'0';// concatenamos la cadena
                else encrip=encrip+'1';
            }
            else {
                encrip=encrip+binario.at(i);
                cont++;
            }
        }
    }
    else {//regla de encriptacion
        int cont=1;
        for(unsigned int i=0;i<binario.length();i++){
            if(cont==3){// se invierte un bit cada 3 bits
                cont=1;
                if(binario.at(i)=='1')encrip=encrip+'0';// concatenamos la cadena
                else encrip=encrip+'1';
            }
            else {
                encrip=encrip+binario.at(i);
                cont++;
            }
        }
    }
    return encrip;
}
string Encriptacion1(string _binaria,unsigned int _semilla)
{
    unsigned int cont=0;// contador que permite agregar bits a la cadena mientras sea menor que la semilla
    string aux,encriptada="",copia;
    for(unsigned int i=0;i<_semilla;i++){// aplicamos el primer paso para la encriptacion
        if(_binaria.at(i)=='1')encriptada=encriptada+'0';
        else encriptada=encriptada+'1';
        copia=copia+_binaria.at(i);//cadena de bits del bloque anterior
    }
    for(unsigned int i=_semilla;i<_binaria.length();i++){
        cont++;
        if(cont<=_semilla){
            aux=aux+_binaria.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==_semilla){
            encriptada=encriptada+Invertirbits(aux,copia);
            copia=aux; // actualizamos el bloque de bits anterior
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    cont=0;
    unsigned int diferencia=Multiplo(_semilla,_binaria.length())-_binaria.length();// cantidad de ceros a agregar
    while(cont<diferencia){// se agregan los numeros faltantes
        aux=aux+'0';// completamos con ceros si es necesario el bloque de bits
        cont++;
    }
    encriptada=encriptada+Invertirbits(aux,copia);
    return encriptada;
}
string Desplazarbits(string binario)
{
    string encrip;
    encrip=binario.at(binario.length()-1);// pongo el ultimo bit en la primera pocision del nuevo arreglo encriptado
    for(unsigned int i=0;i<binario.length()-1;i++){
        encrip=encrip+binario.at(i);// voy llenando el arreglo encriptado
    }
    return encrip;
}
string Encriptacion2(string _binaria,unsigned int _semilla)
{
    unsigned int cont=0;
    string aux,encriptada;
    for(unsigned int i=0;i<_binaria.length()-1;i++){
        cont++;
        if(cont<=_semilla){
            aux=aux+_binaria.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==_semilla){
            encriptada=encriptada+Desplazarbits(aux);
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    aux=aux+_binaria.at(_binaria.length()-1);// asigno el ulrimo bit de la cadena de caracteres
    encriptada=encriptada+Desplazarbits(aux);
    cont=0;
    unsigned int diferencia=Multiplo(_semilla,_binaria.length())-_binaria.length();// cantidad de ceros a agregar
    while(cont<diferencia){// se agregan los numeros faltantes
        aux=aux+'0';// completamos con ceros si es necesario el bloque de bits
        cont++;
    }
    encriptada=encriptada+Desplazarbits(aux);
    return encriptada;
}
