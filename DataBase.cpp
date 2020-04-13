#include <iostream>
#include <vector>
#include "elemento.cpp"
#include "Tabla.cpp"

class DataBase
{
private:
    
public:

    DataBase();
    bool verificarSiExisteTabla(string nombre);
    void insertarATabla(string nombre,std::vector<std::string> &campos,std::vector<std::string> &valores);
    std::vector<Tabla> tablas;
    int obtenerNumeroDeElementos();
    int obtenerNumeroDeElementosEnTabla(string nombre);
    int obtenerNumeroDeColumnasEnTabla(string nombre);
    int obtenerNumeroDeFilasEnTabla(string nombre);
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
        for (size_t i = 0; i < tablas.at(indiceTabla).columnas.size(); i++)
        {
            if (tablas.at(indiceTabla).columnas.at(i).nombre==columnaCondicion)
            {
                indiceColumna=i;
            }
            
        }
        cout<<"buscando...\n";
        vector<elemento*> elEn=tablas.at(indiceTabla).columnas.at(indiceColumna).tablaHash.buscarELemento(condicion);
        if (columnas.at(0)=="*")
        {
            cout<<"\n";
            for (size_t i = 0; i < tablas.at(indiceTabla).columnas.size(); i++)
           {
               cout<<tablas.at(indiceTabla).columnas.at(i).nombre<<"\t";
           }
           cout<<"\n";
           for (size_t i = 0; i < tablas.at(indiceTabla).columnas.size(); i++)
           {
               for (size_t j = 0; j < elEn.size(); j++)
               {
                   
                   if (tablas.at(indiceTabla).columnas.at(i).nombre==elEn.at(j)->columna)
                   {
                       cout<<elEn.at(j)->dato<<"\t";
                   }
                   
               }
               
           }
           
        }else{
            for (size_t i = 0; i < columnas.size(); i++)
            {
                cout<<columnas.at(i)<<"\t";
            }
            cout<<"\n";
            for (size_t i = 0; i < columnas.size(); i++)
           {
               for (size_t j = 0; j < elEn.size(); j++)
               {
                   
                   if (columnas.at(i)==elEn.at(j)->columna)
                   {
                       cout<<elEn.at(j)->dato<<"\t";
                   }
                   
               }
               
           }


        }
        
        
    }
    
            
}
int DataBase::obtenerNumeroDeElementos(){
    int ele =0;
    for (size_t i = 0; i < tablas.size(); i++)
    {
        for (size_t j = 0; j < tablas.at(i).columnas.size(); j++)
        {
            ele+=tablas.at(i).columnas.at(j).tablaHash.elementos;
        }
        
    }
    return ele;
}

int DataBase::obtenerNumeroDeFilasEnTabla(string nombre){
    int ele =obtenerNumeroDeElementosEnTabla(nombre);
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre){
            return (int)ele/(int)tablas.at(i).columnas.size();
            
        };
        
    }
    return 0;
}
int DataBase::obtenerNumeroDeColumnasEnTabla(string nombre){
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre){
            return (int)tablas.at(i).columnas.size();
            
        };
        
    }
    return 0;
}

int DataBase::obtenerNumeroDeElementosEnTabla(string nombre){
    int ele =0;
    for (size_t i = 0; i < this->tablas.size(); i++)
    {
        if (tablas.at(i).nombre==nombre){
            for (size_t j = 0; j < tablas.at(i).columnas.size(); j++)
            {
                ele+=tablas.at(i).columnas.at(j).tablaHash.elementos;
            }
            
        };
        
    }
    return ele;
}