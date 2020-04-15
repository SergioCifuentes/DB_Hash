#include <iostream>
#define SIZE 5;
#define fac 0.6;
#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

class elemento;
#include "Arbol.cpp"
class TablaHash
{
public:
  TablaHash();
  TablaHash(int tipo,string columna);
  int obtenerPosicion(string dato);
  bool verificarSobreCarga();
  void ReHash();
  vector<elemento *> buscarELemento(string el);
  int tipo;
  int elementos;
  string columna;
  void insertar(elemento *dato, int posicion);
  int size;
  std::vector<elemento *> tabla;
  std::vector<Arbol *> arboles;
};
TablaHash::TablaHash()
{
}

vector<elemento *> TablaHash::buscarELemento(string el)
{
  vector<elemento *> elEncontrados;
  int pos = obtenerPosicion(el);
  elemento *elPun = tabla.at(pos);
  while (true)
  {
    if (elPun->dato == "NULL")
    {
      cout<<"No Existe este elemetno";
     break;
    }
    else
    {
      if (elPun->dato == el)
      {
        cout<<"elemento Encontrado";
        return elPun->elementos;
      }else{
        elPun=elPun->siguiente;
      }
    }
  }

  return elEncontrados;
}
TablaHash::TablaHash(int tipo,string columna)
{
  size = SIZE;
  this->columna=columna;
  this->tipo = tipo;
  elementos = 0;
  //tabla->clear();
  for (size_t i = 0; i < size; i++)
  {

    tabla.push_back(new elemento("NULL",columna));
    arboles.push_back(new Arbol(tipo));
  }
}

int funcionHashInt(int dato, int size)
{
  return (dato % size);
}
int funcionHashFloat(float dato, int size)
{
  return ((int)dato % size);
}
int funcionHashString(string dato, int size)
{
  int hashval, j;
  hashval = (int)(dato.at(0));
  for (j = 1; j < dato.size(); j++)
    hashval += (int)dato.at(j);

  return (hashval % size);
}
int funcionHashChar(char dato, int size)
{
  int hashval = (int)(dato);
  return (hashval % size);
}
int TablaHash::obtenerPosicion(string dato)
{

  switch (tipo)
  {
  case 1:
    int in;
    try
    {

      stringstream ss;
      ss << dato;
      ss >> in;
      ss.clear();
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }

    return funcionHashInt(in, size);
  case 2:
    float fl;
    try
    {

      stringstream ss;
      ss << dato;
      ss >> fl;
      ss.clear();
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    return funcionHashFloat(fl, size);
  case 3:

    return funcionHashString(dato, size);
  case 4:

    return funcionHashChar((dato.at(0)), size);
  default:
    break;
  }
}

#include <cstddef>
void TablaHash ::insertar(elemento *dato, int posicion)
{
  elemento *el = tabla.at(posicion);
  cout << "\nElemento " << dato->dato << "\n";
  cout << "Posicion " << posicion << "\n";
  //cout << "Espaci2 " << tabla.at(posicion).dato << "\n";
  if (el->dato == "NULL")
  {
    elementos++;

    *tabla.at(posicion) = *dato;
    arboles.at(posicion)->agregarDatos(dato);
    
  }
  else
  {
    while (true)
    {
      //cout << "Espacio " << tabla->at(posicion).siguiente->dato<< "\n";
      if (el->dato == "NULL")
      {
        elementos++;
        *el = *dato;
        arboles.at(posicion)->agregarDatos(dato);
        break;
      }
      else
      {
        el = el->siguiente;
      }
    }
  }
  if (verificarSobreCarga())
  {
    ReHash();
  }

}
bool TablaHash::verificarSobreCarga()
{

  float factorDeCarga = (float)elementos / (float)size;
  return factorDeCarga > 0.6;
}
void TablaHash::ReHash()
{
  for (size_t i = 0; i < size; i++)
  {
    tabla.push_back(new elemento("NULL",columna));
    //arboles.push_back(new Arbol(tipo));
  }
  size = size * 2;

  /* elemento *arrayFl1;
  
 
  size=size*2;
  arrayFl1=(elemento*)malloc(size*sizeof(elemento));
  for (size_t i = 0; i < size; i++)
  {
    arrayFl1[i]=tabla[i];
  }
  
  
  tabla =(elemento*)realloc(arrayFl1, sizeof(elemento)*size);
*/
}
