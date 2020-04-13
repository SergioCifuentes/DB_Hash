#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;
void manejarQueryEntrada(string text, bool &salirQuerys);
#include "DataBase.cpp"

DataBase dataBase;
int main()
{
    bool salir = false;
    bool salirQuerys;
    int opcion;
    do
    {
        opcion = 0;
        cout << "[1] Querys \n";
        cout << "[2] Reportes\n";
        cout << "[3] Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:

            salirQuerys = false;

            do
            {
                cin.get();
                cout << "Ingrese el query\n";
                cout << "'QUIT' para salir\n";
                cout << "";

                string query;
                getline(cin, query);

                manejarQueryEntrada(query, salirQuerys);
            } while (!salirQuerys);

            break;
        case 2:

            break;
        case 3:
            salir=true;
            break;
        default:
            cout << "Opcion Invalida\n";
            break;
        }
    } while (!salir);

    return 0;
}
/*template <class Container>
void split1(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}*/

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

void dump(std::ostream &out, const std::vector<std::string> &v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        out << '\'' << v[i] << '\'' << ' ';
    }

    out << std::endl;
}
bool obtenerValoresEnParentesis(std::vector<std::string> &valores, std::vector<std::string> &words, int &inicio);
bool obtenerColumnas(std::vector<std::string> &nombres, std::vector<std::string> &tipos, std::vector<std::string> &words);
bool obtenerColumnasDeSelect(std::vector<std::string> &columnas, std::vector<std::string> &words, int &inicio);
void manejarQueryEntrada(string text, bool &salirQuerys)
{
    std::vector<std::string> words;
    split(text, words, ' ');
    if (words.at(0) == "SELECT")
    {
        std::vector<std::string> columnas;
        int inicio = 1;
        if (obtenerColumnasDeSelect(columnas, words, inicio))
        {
            inicio++;
            string nombre = words.at(inicio);
            
            if (dataBase.verificarSiExisteTabla(nombre))
            {   cout<<"si existe la tabla\n";
                inicio++;
                if (words.size() > inicio)
                {
                    cout<<words.at(inicio);
                    if (words.at(inicio) == "WHERE")
                    {
                        dataBase.selectTabla(nombre,columnas,words.at(inicio+1),words.at(inicio+3));  
                    }
                }else{
                        dataBase.selectTabla(nombre,columnas,"NULL","NULL");
                }
            }

            
        }
    }
    else if (words.at(0) == "INSERT")
    {
        std::vector<std::string> campos;
        std::vector<std::string> valores;
        int indice = 3;
        if (obtenerValoresEnParentesis(campos, words, indice))
        {
            if ((obtenerValoresEnParentesis(valores, words, indice)))
            {
                for (size_t i = 0; i < campos.size(); i++)
                {
                    cout << campos.at(i) << "CC\n";
                }
                for (size_t i = 0; i < valores.size(); i++)
                {
                    cout << valores.at(i) << "VV\n";
                }
                if (dataBase.verificarSiExisteTabla(words.at(2)))
                {
                    dataBase.insertarATabla(words.at(2), campos, valores);
                }
            }
        }
    }
    else if (words.at(0) == "DELETE")
    {
    }
    else if (words.at(0) == "CREATE")
    {
        std::vector<std::string> tipos;
        std::vector<std::string> nombres;
        if (obtenerColumnas(nombres, tipos, words))
        {

            Tabla tabla = Tabla(words.at(2), nombres, tipos);
            dataBase.insertarTabla(tabla);
        }
    }
    else if (words.at(0) == "QUIT")
    {

        salirQuerys = true;
    }
    else
    {
        cout << "Query Invalido!!\n";
    }
}

bool obtenerColumnas(std::vector<std::string> &nombres, std::vector<std::string> &tipos, std::vector<std::string> &words)
{
    for (size_t i = 3; i < words.size(); i++)
    {

        if (words.at(i) == "(")
        {
            nombres.push_back(words.at(i + 1));
            i++;
        }
        else if (words.at(i).rfind("(", 0) == 0)
        {
            string aux = words.at(i).substr(1, words.at(i).size() - 1);
            nombres.push_back(aux);
        }
        else if (words.at(i) == ",")
        {
            nombres.push_back(words.at(i + 1));
            i++;
        }
        else if (words.at(i).rfind(",", 0) == 0)
        {
            string aux = words.at(i + 1).substr(1, words.at(i + 1).size() - 1);
            nombres.push_back(aux);
        }
        else if (words.at(i).rfind(",") == words.at(i).size() - 1)
        {

            string aux = words.at(i).substr(0, words.at(i).size() - 1);
            tipos.push_back(aux);
            nombres.push_back(words.at(i + 1));
            i++;
        }
        else if (words.at(i).rfind(")") == words.at(i).size() - 1)
        {
            string aux = words.at(i).substr(0, words.at(i).size() - 1);
            tipos.push_back(aux);
            break;
        }
        else if (words.at(i) == ")")
        {

            break;
        }
        else
        {
            tipos.push_back(words.at(i));
        }
    }

    return true;
}

bool obtenerColumnasDeSelect(std::vector<std::string> &columnas, std::vector<std::string> &words, int &inicio)
{
    for (size_t i = inicio; i < words.size(); i++)
    {
        if (words.at(i) == "*")
        {
            columnas.push_back(words.at(i));
            inicio++;
            break;
        }
        else if (words.at(i) == "FROM")
        {
            inicio = i + 1;
            break;
        }
        else if (words.at(i) == ",")
        {
        }
        else if (words.at(i).rfind(",") == words.at(i).size() - 1)
        {

            string aux = words.at(i).substr(0, words.at(i).size() - 1);
            columnas.push_back(aux);
        }
        else
        {
            if (words.at(i + 1) == "FROM")
            {
                split(words.at(i), columnas, ',');
                break;
            }
            else
            {
                columnas.push_back(words.at(i));
            }
        }
    }
    return true;
}

bool obtenerValoresEnParentesis(std::vector<std::string> &valores, std::vector<std::string> &words, int &inicio)
{
    for (size_t i = inicio; i < words.size(); i++)
    {
        if (words.at(i) == "(")
        {
        }
        else if (words.at(i) == "VALUES")
        {
        }
        else if (words.at(i) == ")" || words.at(i) == ";" || words.at(i) == ");")
        {
            inicio = i + 1;
            break;
        }
        else if (words.at(i).rfind("(", 0) == 0)
        {
            if (words.at(i).rfind(")") == words.at(i).size() - 1 || words.at(i).rfind(");") == words.at(i).size() - 2)
            {
                split(words.at(i), valores, ',');
                valores.at(0) = valores.at(0).substr(1, valores.at(0).size() - 1);
                if (words.at(i).rfind(")") == words.at(i).size() - 1)
                {
                    valores.at(valores.size() - 1) = valores.at(valores.size() - 1).substr(0, valores.at(valores.size() - 1).size() - 1);
                }
                else
                {
                    valores.at(valores.size() - 1) = valores.at(valores.size() - 1).substr(0, valores.at(valores.size() - 1).size() - 2);
                }

                inicio = i + 1;
                break;
            }else if (words.at(i).rfind(",") == words.at(i).size() - 1)
            {
                string aux = words.at(i).substr(1, words.at(i).size() - 1);
                aux = aux.substr(0, words.at(i).size() - 2);
            valores.push_back(aux);
            }
            
            else
            {

                string aux = words.at(i).substr(1, words.at(i).size() - 1);
                valores.push_back(aux);
            }
        }
        else if (words.at(i) == ",")
        {
            valores.push_back(words.at(i + 1));
            i++;
        }
        else if (words.at(i).rfind(",", 0) == 0)
        {
            string aux = words.at(i + 1).substr(1, words.at(i + 1).size() - 1);
            valores.push_back(aux);
        }
        else if (words.at(i).rfind(",") == words.at(i).size() - 1)
        {

            string aux = words.at(i).substr(0, words.at(i).size() - 1);
            valores.push_back(aux);
        }
        else if (words.at(i).rfind(")") == words.at(i).size() - 1)
        {
            string aux = words.at(i).substr(0, words.at(i).size() - 1);
            valores.push_back(aux);
            inicio = i + 1;
            break;
        }
        else if (words.at(i).rfind(");") == words.at(i).size() - 2)
        {
            string aux = words.at(i).substr(0, words.at(i).size() - 2);
            valores.push_back(aux);
            inicio = i + 1;
            break;
        }

        else
        {
            valores.push_back(words.at(i));
        }
    }
    return true;
}
