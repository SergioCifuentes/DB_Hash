#include <iostream>


#include "Columna.cpp"
class elemento;
#include <vector>

using namespace std;

class Tabla
{
private:
public:
    std::vector<Columna> columnas;
    Tabla(string nombre, std::vector<string> nombresColumna, vector<string> tipos);
    string nombre;
    void insertarFila(std::vector<std::string> &campos, std::vector<std::string> &valores);

    ~Tabla();
};

Tabla::Tabla(string nombre, std::vector<string> nombresColumna, vector<string> tipos)
{
    this->nombre = nombre;
    columnas.clear();
    for (size_t i = 0; i < nombresColumna.size(); i++)
    {
        Columna c = Columna(nombresColumna.at(i), tipos.at(i));
        columnas.insert(columnas.end(), c);
    }
}
void Tabla::insertarFila(std::vector<std::string> &campos, std::vector<std::string> &valores)
{
    cout << columnas.size() << " " << campos.size() << " " << valores.size();
    if (columnas.size() != campos.size() || columnas.size() != valores.size())
    {
        cout << "Error Tabla cuenta con " << columnas.size() << " Columnas";
    }
    else
    {
        
        std::vector<elemento*> elementos;
        for (size_t i = 0; i < campos.size(); i++)
        {
            for (size_t j = 0; j < columnas.size(); j++)
            {
                
                if (campos.at(i) == columnas.at(j).nombre)
                {
                    string dato = valores.at(i);
                    
                    elemento *el = new elemento(dato,columnas.at(j).nombre);
                   elementos.insert(elementos.end(), el);
                    
                }
            }
        }




        for (size_t i = 0; i < campos.size(); i++)
        {
            for (size_t j = 0; j < columnas.size(); j++)
            {
                if (campos.at(i) == columnas.at(j).nombre)
                {
                    string dato = valores.at(i);
                    TablaHash *th = &columnas.at(j).tablaHash;
                    elementos.at(i)->insertarElementoDeFilas(elementos);
                    th->insertar(elementos.at(i), th->obtenerPosicion(dato));
                    
                }
            }
        }
    }
}

Tabla::~Tabla()
{
}