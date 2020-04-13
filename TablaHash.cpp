#include <iostream>
#define SIZE 5;
#define fac  0.6;
#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include <stdlib.h> 
#include "Arbol.cpp"
using namespace std;




class elemento;

class TablaHash
{
public:
  TablaHash();
  TablaHash(int tipo);
  int obtenerPosicion(string dato);
  bool verificarSobreCarga();
  void ReHash();
  int tipo;
  int elementos;
  void insertar(elemento *dato, int posicion);
  int size;
  std::vector<elemento*>tabla;
  std::vector<Arbol*>arboles;
};
TablaHash::TablaHash()
{
}
TablaHash::TablaHash(int tipo)
{
  size = SIZE;
  this->tipo = tipo;
  //tabla->clear();
  for (size_t i = 0; i < size; i++)
  {
    //elemento e =  elemento("NULL");
    tabla.push_back(new elemento("NULL")); 
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
  cout << "Elementos " << elementos << "\n";
  cout << "Espacio " << el->dato << "\n";
  //cout << "Espaci2 " << tabla.at(posicion).dato << "\n";
  if (el->dato == "NULL")
  {
    elementos++;

    *tabla.at(posicion) = *dato;
    //cout << "Espacio " << tabla.at(posicion).dato << "\n";
  }
  else
  {
    while (true)
    {
      cout << "=====================";
      cout << "Espacio " << el->dato << "\n";
      //cout << "Espacio " << tabla->at(posicion).siguiente->dato<< "\n";
      if (el->dato == "NULL")
      {
        elementos++;
        *el = *dato;
        break;
      }
      else
      {
        el = el->siguiente;
      }
    }
  }
  cout<<"->"<<(tabla.size());
  if (verificarSobreCarga())
  {
    ReHash();
  }
  cout<<"->"<<(tabla.size());
  

}
bool TablaHash::verificarSobreCarga(){

  float factorDeCarga=(float)elementos/(float)size;
  return factorDeCarga>0.6;
  
}
void TablaHash::ReHash(){
  for (size_t i = 0; i < size; i++)
  {
    tabla.push_back(new elemento("NULL"));
    arboles.push_back(new Arbol(tipo)); 
  }
  size=size*2;
  
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
