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
                cout<<campos.at(i)<<" IGUAL " << columnas.at(j).nombre;
                if (campos.at(i) == columnas.at(j).nombre)
                {
                    string dato = valores.at(i);
                    TablaHash *th = &columnas.at(j).tablaHash;
                    elemento *el = new elemento(dato,columnas.at(j).nombre);
                   elementos.insert(elementos.end(), el);
                    th->insertar(elementos.at(i), th->obtenerPosicion(dato));
                }
            }
        }
        cout<<"))"<<elementos.size()<<"))";
        for (size_t i = 0; i < elementos.size(); i++)
        {
            cout<<elementos.at(i)->dato<<"**";
            elementos.at(i)->insertarElementoDeFilas(elementos);
        }
        TablaHash *th = &columnas.at(0).tablaHash;
        cout<<th->tabla.at(3)->dato<<"$$";
        cout<<th->tabla.at(3)->elementos.size()<<"$$";
    }
}

Tabla::~Tabla()
{
}