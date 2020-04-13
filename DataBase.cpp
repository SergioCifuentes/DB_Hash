#include <iostream>
#include <vector>
#include "Tabla.cpp"
class DataBase
{
private:
    
public:

    DataBase();
    bool verificarSiExisteTabla(string nombre);
    void insertarATabla(string nombre,std::vector<std::string> &campos,std::vector<std::string> &valores);
    std::vector<Tabla> tablas;
    void insertarTabla(Tabla tabla);
    void selectTabla(string nombre,std::vector<std::string> columnas,string columnaCondicion,string condicion);
    ~DataBase();
};

DataBase::DataBase(){

}
DataBase::~DataBase(){
    
}
bool DataBase:: verificarSiExisteTabla(string nombre){
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre)return true;
        
    }
    cout<<"\n tabla "<<nombre <<" no existe \n";
    return false;
}
void DataBase:: insertarATabla(string nombre,std::vector<std::string> &campos,std::vector<std::string> &valores){
    
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre){
            tablas.at(i).insertarFila(campos,valores);
            break;
        }
        
    }
    
}

void DataBase::insertarTabla(Tabla tabla){
    tablas.insert(tablas.end(),tabla);
}

void DataBase::selectTabla(string nombre,std::vector<std::string> columnas,string columnaCondicion,string condicion){
    int indiceTabla=0;
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre){
            indiceTabla=i;
        }
        
    }


    if (columnaCondicion=="NULL")
    {
    


    }else{
        int indiceColumna=-1;
        for (size_t i = 0; i < tablas.at(i).columnas.size(); i++)
        {
            if (tablas.at(i).columnas.at(i).nombre==columnaCondicion)
            {
                indiceColumna=i;
            }
            
        }
        
    }
    
            
}