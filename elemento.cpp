#include <iostream>
#include <vector>
using namespace std;


class elemento
{
private:
    
public:
    elemento(string dato,string columna);
    elemento();
    string columna;
    std::vector<elemento*> elementos;
    void insertarElementoDeFilas(std::vector<elemento*> elementos);
    string dato;
    elemento *siguiente;

    ~elemento();
};
elemento::elemento(){
    
}
elemento::elemento(string dato,string columna)
{
    this->columna=columna;
    this->dato=dato;
    siguiente=new elemento();
    siguiente->dato="NULL";
    
}

void elemento::insertarElementoDeFilas(std::vector<elemento*> elementos){
    cout<<"qqq"<<elementos.size();
    this->elementos=elementos;
}

elemento::~elemento()
{
}
