#include <iostream>
#include "TablaHash.cpp"

using namespace std;
class Columna
{
private:
    
public:
    string nombre;
    Columna(string nombre,string tipo);
    int tipo;
    TablaHash tablaHash;
    /*1 Integer
    2 Decimal
    3 String 
    4 char*/

};

Columna::Columna(string nombre,string tipo){

  
this->nombre=nombre;
if (tipo=="INT")
{
    this->tipo=1;
}else if (tipo=="FLOAT")
{
    this->tipo=2;
}else if (tipo=="STRING")
{
    this->tipo=3;
}else if (tipo=="CHAR")
{
    this->tipo=4;
}
tablaHash=TablaHash(this->tipo,this->nombre);  
}

