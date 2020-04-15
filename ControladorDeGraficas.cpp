#include <iostream>
#include <fstream>
#include <string.h>
#include<sstream>
#include <stdio.h>
using namespace std;
class Tabla;
class Columna;
class ControladorDeGraficas
{
private:
    /* data */
public:
    ControladorDeGraficas(/* args */);
    void graficarTabla(Tabla  *tabla, string nombreColumna);
    void graficarColumna(Columna columna);
    ~ControladorDeGraficas();
};

ControladorDeGraficas::ControladorDeGraficas(/* args */)
{
}

void ControladorDeGraficas::graficarTabla(Tabla *tabla, string nombreColumna)
{
    cout<<"graficando";
    if (nombreColumna == "NULL")
    {
        for (size_t i = 0; i < tabla->columnas.size(); i++)
        {
            cout << tabla->columnas.size();
            graficarColumna(tabla->columnas.at(i));
        }
    }
    else
    {
        for (size_t i = 0; i < tabla->columnas.size(); i++)
        {
            if (tabla->columnas.at(i).nombre == nombreColumna)
            {
                /* code */
            }
        }
    }
}

void ControladorDeGraficas::graficarColumna(Columna columna)
{

    ofstream file;
    file.open("./Graficas/grafica.dot");
    string texto = "digraph G { \n";
    texto += "nodesep=.05; \n   rankdir=LR; \n  node [shape=record,width=.1,height=.1];   \n";
    texto += "node0 [label = \"";
    for (int i = 0; i < columna.tablaHash.tabla.size(); i++)
    {
        if (i > 0)
        {
            texto += "|";
        }

        texto += "<f";
        int k=i+1;
        stringstream ss;
        ss << k;
        string s;
        ss >> s;
        texto += s;

        texto += ">";
    }
    texto += "\",height=2.5];";
    for (int i = 0; i < columna.tablaHash.arboles.size(); i++)
    {
        cout << columna.tablaHash.arboles.at(i)->raiz<<"{}{}{}{]";
        if (columna.tablaHash.arboles.at(i)->raiz != NULL)
        {
            cout << columna.tablaHash.arboles.at(i)->raiz->dato->dato;
            texto += "node0:f";
            int k=i+1;
        stringstream ss;
        ss << k;
        string s;
        ss >> s;
            texto += s;
            texto += "-> ";
            texto += columna.tablaHash.arboles.at(i)->raiz->dato->dato;
            texto += ";\n";
            texto += columna.tablaHash.arboles.at(i)->recorarParaGrafica(columna.tablaHash.arboles.at(i)->raiz);
        }
    }

    texto += "}";
    cout << texto;
    file << texto;
    file.close();
    int n = columna.nombre.length();

    char char_array[n + 1];
    strcpy(char_array, columna.nombre.c_str());
    cout << "\n"
         << char_array << "\n";

    char salida[] = "dot -Tpng ./Graficas/grafica.dot -o ./Graficas/";

    strcat(salida, char_array);
    strcat(salida, ".png");
    cout << salida << "\n";
    system(salida);

    char salida2[] = "nohup display ./Graficas/";
    int n2 = columna.nombre.length();

    strcat(salida2, char_array);

    strcat(salida2, ".png");
    cout << salida;
    system(salida2);
}

ControladorDeGraficas::~ControladorDeGraficas()
{
}
