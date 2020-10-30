#include <iostream>
#include <codificar.h>
#include <string.h>// libreria para la clase string
#include <fstream>// libreria para el manejo de archivos
#include <sstream>

unsigned int TAM=4;// numero de la semilla para la encriptacion y la desencriptacion
string dirsudo="../Aplicacion/sudo.txt"; //direccion del archivo de texto con la clave encriptada
string dirusuarios="../Aplicacion/usuarios.txt";//direccion del archivo con los usuarios
string dirtemp="../Aplicacion/temporal.txt";// direccion del archivo temporal

using namespace std;

string Leerarchivo(string);//extrae la informacion del archivo ingresado
bool ValidacionClave(string,string);// mira si la clave ingresada es correcta
bool Validarnumeros(string);//Valida si los caracteres ingresados son numericos
void Escribirarchivo(string,string);//escribe el archivo con la informacion de los usarios
void MenuAdmin();// realiza las operaciones del administrador
string Numeriocatring(string);// convierto un numero a cadena de caracteres
void Infousuarios(string);// muestra al usuario su informacion de su saldo
void Eliminararchivo(); //elimina el archivo usuarios para ser actualizado
void Renombrararchivo();// elimino el archivo existente y renombra un archivo temporal
void Retirardinero(string);//realiza la segunda funcion del usuario

int main()
{
    // este programa usa el segundo metodo de codificacion
    char opcion='0';
    while(opcion!='3'){
        cout<<"Bienvenido al cajero"<<endl<<endl;
        cout<<"Ingrese:"<<endl<<endl;
        cout<<"1.Entrar como administrador"<<endl<<"2.Entrar como usuario"<<endl<<"3.Salir"<<endl<<endl;
        cout<<"Escriba la operacion a realizar:";
        cin>>opcion;
        if(opcion=='1')MenuAdmin();//operaciones de administrador
        else if(opcion=='2'){//operaciones de usuario
            cout<<endl<<"Ha ingresado como usuario"<<endl<<endl;
            opcion='0';
            while(opcion!='3'){// opcion de salida
                cout<<"Ingrese:"<<endl<<endl;
                cout<<"1.Consultar saldo"<<endl<<"2.Retirar dinero"<<endl<<"3.Salir"<<endl<<endl;
                cout<<"Cada operacion tiene un costo de $1000"<<endl<<endl;
                cout<<"Escriba la operacion a realizar:";
                cin>>opcion;
                if(opcion=='1'){//consultar estado de la cuenta
                    string claveusu;
                    cout<<endl<<"Porfavor ingrese su clave:";
                    cin>>claveusu;
                    bool _ayuda=false;
                    while(_ayuda==false){
                        if(Validarnumeros(claveusu)==false){
                            cout<<endl<<"Por favor digite solo caracteres numericos"<<endl;
                            cout<<endl<<"Porfavor ingrese su clave:";
                            cin>>claveusu;
                        }
                        else if(claveusu.length()!=4){
                            cout<<endl<<"Por favor solo digite 4 digitos"<<endl;
                            cout<<endl<<"Porfavor ingrese su clave:";
                            cin>>claveusu;
                        }
                        else _ayuda=true;
                    }
                    Infousuarios(claveusu);
                }
                else if(opcion=='2'){//retirar dinero
                    string claveusu2;
                    bool ayuda=false;
                    cout<<endl<<"Porfavor ingrese su clave:";
                    cin>>claveusu2;
                    while(ayuda==false){
                        if(Validarnumeros(claveusu2)==false){
                            cout<<endl<<"Por favor digite solo caracteres numericos"<<endl;
                            cout<<endl<<"Porfavor ingrese su clave:";
                            cin>>claveusu2;
                        }
                        else if(claveusu2.length()!=4){
                            cout<<endl<<"Por favor solo digite 4 digitos"<<endl;
                            cout<<endl<<"Porfavor ingrese su clave:";
                            cin>>claveusu2;
                        }
                        else ayuda=true;
                    }
                    Retirardinero(claveusu2);
                }
                else if(opcion=='3')cout<<endl;//salir del modo de usuario
                else cout<<endl<<"Operacion incorrecta, intenta nuevamente"<<endl;// en caso de no ser ninguna de las opciones
            }
            opcion='0';
        }
    }
    cout<<endl;
    return 0;
}
string Leerarchivo(string direccion)
{
    ifstream lectura;
    string archivo;
    lectura.open(direccion.c_str(),ios::in);
    if(!lectura.is_open()){// se verifica si el archivo abre exitosamente
        std::cout<<"Error abriendo el archivo"<<endl;
        exit(1);
    }
    while(!lectura.eof()){// lee mientras no sea el final del archivo
        getline(lectura,archivo);
    }
    lectura.close();// cerrar archivo
    return archivo;
}
bool ValidacionClave(string direccion,string _clave)
{
    string arch=Leerarchivo(direccion);// string que contiene la clave encriptada
    string claveencrip;// string que contiene la clave ingresada por el usuario encriptada
    Codificar encrip(_clave,TAM);
    claveencrip=encrip.Encriptacion();//Clave encriptada
    for(unsigned int i=0; i<arch.length() ;i++){// comparamos termino a termino la clave para saber si es correcta
        if(claveencrip.at(i)!=arch.at(i))return false;// si no son iguales retornamos falso
    }
    return true;
}
bool Validarnumeros(string cadena){
    for(unsigned int i=0;i<cadena.length();i++){// miramos si la cadena de caracteres tiene caracteres no validos
        // rango de caracteres numericos en el codigo ASCII
        if(cadena.at(i)<=47)return false;
        if(cadena.at(i)>=58)return false;
    }
    return true;
}
void Escribirarchivo(string escribir,string direccion)
{
    ofstream codificado;
    codificado.open(direccion,ios::app);
    if(!codificado.is_open()){// se verifica si el archivo abre exitosamente
        std::cout<<"Error creando el archivo"<<endl;
        exit(1);
    }
    else{
        codificado<<escribir<<endl;
    }
    codificado.close();// cerrar el archivo
}
string Numericoastring(int valor)
{
    string aux = "";
    string saldo="";
    int i = 0;
    while(valor>0){
        aux+=((valor%10)+48);//Voy creando una cadena de caracteres con los numeros
        valor /=10;// divido para ir bajando de posicion
        i++;
    }
    for (i--;i>=0;i--)saldo += aux[unsigned(i)];// le invierto el orden
    return saldo;

}
void MenuAdmin()
{
    char opcion='0';
    string clave;
    cout<<endl<<"Ha ingresado como administrador"<<endl<<endl;
    cout<<"Por favor digite la clave:";
    cin>>clave;
    while(ValidacionClave(dirsudo,clave)==false){//miramos si la clave ha sido ingresada correctamente
        cout<<endl<<"Clave incorrecta,intenta nuevamente"<<endl<<endl;
        cout<<"Por favor digite la clave:";
        cin>>clave;
    }
    opcion='0';
    while(opcion!='2'){// opcion de salida
        cout<<endl<<"Ingrese:"<<endl<<endl;
        cout<<"1.Ingresar usuarios"<<endl<<"2.Salir"<<endl<<endl;
        cout<<"Escriba la operacion a realizar:";
        cin>>opcion;
        if(opcion=='1'){
            string cedula="",claveusu="",saldo="",datos="",encrip="";
            cout<<endl<<"Ingresar Usuario"<<endl<<endl;
            cout<<"Escriba la cedula:";
            cin>>cedula;
            while(Validarnumeros(cedula)==false){// verificamos que los caracteres sean numericos
                cout<<endl<<"Caracteres incorrectos,solo caracteres numericos"<<endl<<endl;
                cout<<"Escriba la cedula:";
                cin>>cedula;
            }
            datos=datos+cedula+',';
            cout<<"Escriba la clave(4 numeros):";
            cin>>clave;
            bool aux=false;
            while(aux==false){// verificamos que los caracteres sean numericos
                if (Validarnumeros(clave)==false){
                    cout<<endl<<"Por favor escriba caracteres numericos"<<endl<<endl;
                    cout<<"Escriba la clave:";
                    cin>>clave;
                }
                else if((clave.length()!=4)){
                    cout<<endl<<"Por favor solo escriba 4 caracteres"<<endl<<endl;
                    cout<<"Escriba la clave:";
                    cin>>clave;
                }
                else aux=true;
            }
            datos=datos+clave+',';
            cout<<"Escriba el saldo:";
            cin>>saldo;
            while(Validarnumeros(saldo)==false){// verificamos que los caracteres sean numericos
                cout<<endl<<"Caracteres incorrectos,solo caracteres numericos"<<endl<<endl;
                cout<<"Escriba el saldo:";
                cin>>saldo;
            }
            datos=datos+saldo; // creamos una cadena con los datos completos del usuario
            Codificar infousuarios(datos,TAM);// se inicializa un objeto para codificar la informacion
            encrip=infousuarios.Encriptacion();// se encripta la informacion
            Escribirarchivo(encrip,dirusuarios);// escribimos la informacion en el archivo de usuarios
            cout<<endl<<"Inscripcion exitosa"<<endl;

        }
        else if(opcion=='2'){
            cout<<endl;// salida de la opcion de administrador
        }
        else cout<<endl<<"Operacion incorrecta, intenta nuevamente"<<endl;// en caso de no ser ninguna de las opciones
    }
}
void Renombrararchivo()
{
    int resultado;
    resultado=rename(dirtemp.c_str(),dirusuarios.c_str());// renombrar archivo
    if (resultado != 0)perror("Error al renombrar archivo.");
}
void Eliminararchivo()
{
    if(remove(dirusuarios.c_str()) != 0 )// eliminar archivo
       perror("Error al borrar archivo!.");
}
void Infousuarios(string claveusu)
{
    int valor=0,cont=0;
    string clave="",cedula="",saldo="",encriptar="";
    bool aux=false;
    std::ifstream input(dirusuarios);// abro el archivo para leerlo linea por linea
    for( std::string line; getline( input, line ); )
    {
        clave="";
        cedula="";
        saldo="";
        string ayuda="";//llevara la infor,acion desencriptada
        Codificar encrip(line,TAM);// creo un objeto para encriptar la informacion
        ayuda=encrip.Desencriptacion();// encripto la informacion
        for(unsigned int i=0;i<ayuda.find(",");i++)cedula=cedula+ayuda.at(i);// creo una cadena con la cedula del usuario hasta que encuentre la primera coma
        for(unsigned int i=ayuda.find(",")+1;i<ayuda.find(",")+5;i++)clave=clave+ayuda.at(i);
        for(unsigned int i=0;i<4;i++){ //comparo la clave del usuario con las claves ya ingresadas, la clave será hasta que encuentre la segunda coma
            if(clave.at(i)!=claveusu.at(i))break;
            if(i==3)aux=true;
        }
        for(unsigned int i=ayuda.find(",")+6;i<ayuda.length();i++)saldo=saldo+ayuda.at(i);// el saldo sera lo que encuentre despues de la segunda coma
        if(aux==true){// es verdadero si la clave esta en el sistema
            aux=false;
            cont=1;
            cout<<endl<<"Cedula:"<<cedula<<endl;
            cout<<"Saldo:"<<saldo<<endl<<endl;
            valor=stoi(saldo)-1000;// combierto una estring a un valor entero
            saldo=Numericoastring(valor);// convierto un numero a estring
            encriptar=cedula+','+clave+','+saldo;// creo cadena cin la estructura de datos pedida para guardar la informacion
            Codificar codigo(encriptar,TAM);// creo objeto para encriptar la informacion
            encriptar=codigo.Encriptacion();// encripto la informacion
            Escribirarchivo(encriptar,dirtemp);//actualizo la informacion en el archivo
        }
        else Escribirarchivo(line,dirtemp);
    }
    input.close();// cierra el archivo
    if(cont==0)cout<<endl<<"El usuario no se encuentra en el sistema,intenta nuevamente"<<endl<<endl;
    else{
        Eliminararchivo();// elimina el archivo de usuario
        Renombrararchivo();//cambio el archivo temporal por el de usuarios
    }
}
void Retirardinero(string claveusu)
{
    int valor=0,cont=0;
    string clave="",cedula="",saldo="",encriptar="";
    bool aux=false;
    std::ifstream input(dirusuarios);// abro el archivo para leerlo linea por linea
    for( std::string line; getline( input, line ); )
    {
        clave="";
        cedula="";
        saldo="";
        string ayuda="";//llevara la infor,acion desencriptada
        Codificar encrip(line,TAM);// creo un objeto para encriptar la informacion
        ayuda=encrip.Desencriptacion();// encripto la informacion
        for(unsigned int i=0;i<ayuda.find(",");i++)cedula=cedula+ayuda.at(i);// creo una cadena con la cedula del usuario
        for(unsigned int i=ayuda.find(",")+1;i<ayuda.find(",")+5;i++)clave=clave+ayuda.at(i);
        for(unsigned int i=0;i<4;i++){ //comparo la clave del usuario con las claves ya ingresadas
            if(clave.at(i)!=claveusu.at(i))break;
            if(i==3)aux=true;
        }
        for(unsigned int i=ayuda.find(",")+6;i<ayuda.length();i++)saldo=saldo+ayuda.at(i);
        if(aux==true){// es verdadero si la clave esta en el sistema
            aux=false;
            cont=1;
            cout<<endl<<"el usuario "<<cedula<<" puede retirar maximo:"<<stoi(saldo)-1000<<endl;
            valor=stoi(saldo)-1000;// combierto una estring a un valor entero
            bool _aux=false;
            int retiro=0;
            while(_aux==false){
                cout<<endl<<"Escriba la cantidad de dinero que desea retirar:";
                cin>>retiro;
                if(retiro<0) cout<<endl<<"Cantidad incorrecta"<<endl;
                else if(retiro>valor)cout<<endl<<"El valor ingresado supera su saldo disponible"<<endl;
                else{
                    valor=valor-retiro;// resto la cantidad de dinero
                    _aux=true;
                }
            }
            cout<<endl<<"Transaccion exitosa"<<endl;
            cout<<endl<<"Nuevo saldo:"<<valor<<endl<<endl;
            saldo=saldo=Numericoastring(valor);// convierto el saldo a una string
            encriptar=cedula+','+clave+','+saldo;// creo cadena cin la estructura de datos pedida para guardar la informacion
            Codificar codigo(encriptar,TAM);// creo objeto para encriptar la informacion
            encriptar=codigo.Encriptacion();// encripto la informacion
            Escribirarchivo(encriptar,dirtemp);//actualizo la informacion en el archivo
        }
        else Escribirarchivo(line,dirtemp);
    }
    input.close();// cierro el archivo
    if(cont==0)cout<<endl<<"El usuario no se encuentra en el sistema,intenta nuevamente"<<endl<<endl;
    else{
        Eliminararchivo();// elimina el archivo de usuario
        Renombrararchivo();//cambio el archivo temporal por el de usuarios
    }
}
