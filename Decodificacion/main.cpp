 #include <iostream>
#include <string.h>// libreria para la clase string
#include <fstream>// libreria para el manejo de archivos
#include <bits/stdc++.h>//libreria para utilizar la funcion reverse
#include <cmath>

using namespace std;

unsigned int Multiplo(int,int);//busca el ultimo multiplo de 8
int Contarunos(string);// cuenta la cantidad de unos en la cadena de caracteres
char Binarioastring(string);// convierte una cadena de 8 bits en su caracter correspondiente
string Invertirbits(string,string ); // contiene las reglas de desencriptacion del primer metodo
string Desencriptacion1(string,unsigned int);// aplica las reglas del primer metodo
string Desplazarbits(string);// contiene las reglas de desencriptacion del segundo metodo
string Desencriptacion2(string,unsigned int);// aplica las reglas del segundo metodo

int main()
{
    unsigned int semilla,metodo;
    string archivo,binaria,decodificado,nombrearchivo,escritura;
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
    if(metodo==1)decodificado=Desencriptacion1(archivo,semilla);// primer metodo de desencriptacion
    else decodificado=Desencriptacion2(archivo,semilla);
    codificado.open(escritura.c_str(),ios::out);
    if(!codificado.is_open()){// se verifica si el archivo abre exitosamente
        std::cout<<"Error creando el archivo"<<endl;
        exit(1);
    }
    else {
        codificado<<decodificado;
        codificado.close();
        cout<<"Archivo decodificado con exito"<<endl;
    }
    return 0;
}
unsigned int Multiplo(int _num,int _len)
{
    while(_len%_num!=0)_len--;// busco el ultimo multiplo de 8
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
    string encrip="";// cadena que se retorna con la regla aplicada
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
char Binarioastring(string _letra){
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
string Desencriptacion1(string binaria,unsigned int _semilla)
{
    unsigned int cont;
    string decodificada="",copia="",aux="",convertir="",cadena;
    for(unsigned int i=0;i<_semilla;i++){// aplicamos el primer paso para la desencriptacion
        if(binaria.at(i)=='1')decodificada=decodificada+'0';
        else decodificada=decodificada+'1';
        copia=copia+decodificada;//copia del primer bloque de bits decodificado
    }
    for(unsigned int i=_semilla;i<binaria.length();i++){
        cont++;
        if(cont<=_semilla){
            aux=aux+binaria.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==_semilla){
            decodificada=decodificada+Invertirbits(aux,copia);
            copia=Invertirbits(aux,copia); // actualizamos el bloque de bits anterior decodificado
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    unsigned int diferencia=Multiplo(8,binaria.length());// valor del ultimo multiplo de 8 para saber cuales son los bits de interes
    copia="";//reutilizo copia, creando una nuvea cadena con longitud de la variable diferencia( asi dejo por fuera los ceros agregados)
    for (unsigned int i=0;i<diferencia;i++)copia=copia+decodificada.at(i);// lleno la nueva cadena
    for(unsigned int i=0;i<copia.length();i++){
        convertir=convertir+copia.at(i);//creo cadena de 8 bits correspondientes a cada letra
        if((i+1)%8==0){
            cadena=cadena+Binarioastring(convertir);//Convierto el caracter binario
            convertir="";// actualizo la cadena
        }
    }
    return cadena;
}
string Desplazarbits(string binario)
{
    string encrip="";
    for(unsigned int i=1;i<binario.length();i++){
        encrip=encrip+binario.at(i);// voy llenando el arreglo encriptado
    }
    encrip=encrip+binario.at(0);// pongo el primer bit en la ultima pocision del nuevo arreglo decodificado
    return encrip;
}
string Desencriptacion2(string _binaria,unsigned int _semilla)
{
    unsigned int cont;
    string cadena,aux,desencriptada,convertir;
    for(unsigned int i=0;i<_binaria.length()-1;i++){
        cont++;
        if(cont<=_semilla){
            aux=aux+_binaria.at(i);//bloque bits del tamaño de la semilla
        }
        if(cont==_semilla){
            desencriptada=desencriptada+Desplazarbits(aux);
            aux="";// actualizamos el bloque de bits
            cont=0;// actualizamos el contador para llenar de nuevo la cadena de caracteres
        }
    }
    aux=aux+_binaria.at(_binaria.length()-1);// asigno el ulrimo bit de la cadena de caracteres
    desencriptada=desencriptada+Desplazarbits(aux);
    unsigned int diferencia=Multiplo(8,_binaria.length());// valor del ultimo multiplo de 8 para saber cuales son los bits de interes
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
