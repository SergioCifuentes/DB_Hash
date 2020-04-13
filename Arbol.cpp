#include <iostream>
#include <stdio.h>
class elemento;
#include "Nodo.cpp"

class Arbol
{
private:
    /* data */
public:
    Arbol(int tipo);
    int tipo;
    void insertarNuevo(Nodo *recorrer, Nodo *nuevo, Nodo *PadreAB);
    void agregarDatos(elemento *el);
    Nodo* nuevoNodo(elemento *el);
    Nodo *raiz, *nuevo, *recorrer;
    Nodo *PadreAB, *sHijo, *predecesor, *abuelo, *hijoHijo;
    void necesidadEquilibrar(Nodo *recorrer);
    void rotarDD();
    int altura(Nodo *recorrer);
    void rotarID();
    void rotarDI();
    void rotarII();
    
    int exiteenArbol(Nodo *recorrer, string buscado, int tipo);
    ~Arbol();
};

Arbol::Arbol(int tipo)
{
    this->tipo = tipo;
}

Arbol::~Arbol()
{
}

Nodo* Arbol::nuevoNodo(elemento *el)
{
    nuevo = new Nodo; //Crea la reserva de espacio en memoria.
    nuevo->dato = el;
    nuevo->izq = NULL;                                //Punteros a tierra
    nuevo->dere = NULL;                               //Punteros a tierra
    nuevo->alturaIzq = 0;                             //Setea en cero la altura izquierda el nodo
    nuevo->alturaDere = 0;                            //Setea en cero la altura derecha el nodo
    nuevo->fe = nuevo->alturaDere - nuevo->alturaIzq; //Calculo del factor equilibrio, podría asignarse el valor cero desde la entrada.

    return nuevo;
}

int Arbol::exiteenArbol(Nodo *recorrer, string buscado, int tipo)
{
    

    if (recorrer == NULL)
    {
        return 1;
    }
    else
    {
        cout<<"\nbus="<<buscado;
    cout<<"\nrec="<<recorrer->dato->dato;
        if (buscado < recorrer->dato->dato)
        {
            return exiteenArbol(recorrer->izq, buscado, tipo);
        }
        else if (buscado > recorrer->dato->dato)
        {
            return exiteenArbol(recorrer->dere, buscado, tipo);
        }
        else
        {
            return 0;
        }
    }
}

void Arbol::insertarNuevo(Nodo *recorrer, Nodo *nuevo, Nodo *PadreAB)
{
    bool vacio=false;
    try
    {
        if (raiz == NULL)
    {                
        raiz = nuevo;
        raiz->padre = NULL;
        cout<<"sss"<<raiz;
    }else{
        vacio=true;
    }
    }
    catch(const std::exception& e)
    {
        cout<<"error";
        vacio=true;
    }
    
    
    if(vacio)
    {
        cout<<"nu"<<nuevo->dato->dato;
        cout<<"sawdawd\n\n";
        
        
        cout<<"re"<<recorrer->dato->dato;
        
        if (nuevo->dato->dato <= recorrer->dato->dato)
        {
            if (recorrer->izq != NULL)
            {
                PadreAB = recorrer->izq;
                //BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
                insertarNuevo(recorrer->izq, nuevo, PadreAB);
            }
            else
            {
                recorrer->izq = nuevo;
                nuevo->padre = PadreAB;
                return;
            }
        }
        else if (nuevo->dato->dato > recorrer->dato->dato)
        {
            if (recorrer->dere != NULL)
            {
                PadreAB = recorrer->dere;
                //BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
                insertarNuevo(recorrer->dere, nuevo, PadreAB);
            }
            else
            {
                recorrer->dere = nuevo;
                nuevo->padre = PadreAB;
                return;
            }
        }
    }
}

void Arbol:: rotarDD(){
	if (PadreAB==raiz){
		raiz=sHijo;
		
		//sHijo->dere=hijoHijo;
		//hijoHijo->padre=sHijo;
		//hijoHijo->dere=NULL;
		
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
		
		sHijo->padre=NULL;
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->dere=PadreAB->dere;
		sHijo->padre=abuelo;
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
	}
}

//Rotación  Izquierda Izquierda
void Arbol::rotarII(){
	if(PadreAB==raiz){
		raiz=sHijo;
		
		hijoHijo=sHijo->izq;
		
		sHijo->dere=PadreAB;
		PadreAB->izq=NULL;
		PadreAB->padre=sHijo;
		
		sHijo->padre=NULL;
		
		//PadreAB->dere=hijoHijo;
		//hijoHijo->padre=PadreAB;
		
		//sHijo->dere=PadreAB;
		
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->izq=PadreAB->izq;
		sHijo->padre=abuelo;
		sHijo->dere=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->izq=NULL;
	}	
}

int Arbol::altura(Nodo *recorrer){
	if (recorrer == NULL)//Si el nodo está vació entonces que salga.
		return 0 ; //Devuelve el valor cero.
	else{
		recorrer->alturaIzq=altura (recorrer->izq);
		recorrer->alturaDere=altura (recorrer->dere);
		recorrer->fe=recorrer->alturaDere-recorrer->alturaIzq;
		
		if (recorrer->alturaIzq > recorrer->alturaDere)
			return recorrer->alturaIzq + 1;
		else
			return recorrer->alturaDere + 1;
	}
}


//Rotación Derecha Izquierda
void Arbol::rotarDI(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}

		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}

		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}
		
		//sHijo->dere=NULL; // Apuntar a Null la parte derecha del hijo, ya que ahora no tendrá Hijos...
		
		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		
		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
		
		abuelo->dere=hijoHijo;
	}
}


//Rotación  Izquierda Derecha
void Arbol::rotarID(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			

		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		abuelo->izq=hijoHijo;
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
				
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}
}




void Arbol::necesidadEquilibrar(Nodo *recorrer){ //Con esta función analizo si es necesario equilibrar el árbol, esta función busca el valor -2 o 2.
	if (recorrer != NULL) {
		
		necesidadEquilibrar(recorrer->izq);
	    necesidadEquilibrar(recorrer->dere);

		if ((recorrer->fe==2)||(recorrer->fe==-2)){
			system("cls");
			cout<<"Es necesario equilibrar el arbol"<<endl;
			
			PadreAB=recorrer;
			sHijo=PadreAB->dere;
			
			//Identificar Si es el caso  RDD, Rotación Derecha, Derecha.
			if ((PadreAB->fe>1)&&(sHijo->fe>0)){
				cout<<"Rotacion derecha derecha."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				
				rotarDD();
				altura(raiz);
				return;
			//Identificar Si es el caso  RDI, Rotación Derecha, Izquierda.
			}else if((PadreAB->fe>1)&&(sHijo->fe<0)){
				cout<<"Rotacion derecha izquierda."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				rotarDI();
				altura(raiz);
				return;
			}else{
				
				PadreAB=recorrer;
				sHijo=PadreAB->izq;
				
				//Identificar Si es el caso  RII, Rotación Izquierda, Izquierda.
				if((PadreAB->fe<-1)&&(sHijo->fe<0)){
					cout<<"Rotacion izquierda izquierda."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					rotarII();
					altura(raiz);
					return;
				//Identificar Si es el caso  RID, Rotación Izquierda, Derecha.	
				}else if((PadreAB->fe<-1)&&(sHijo->fe>0)){
					cout<<"Rotacion izquierda Derecha."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					rotarID();
					altura(raiz);
					return;
				}
			}
			return;
		}	
	}
}






void Arbol::agregarDatos(elemento *el)
{
    cout<<"raiz"<<raiz;
    nuevo = nuevoNodo(el);
    nuevo->tipo = tipo;
    cout<<"ar"<<nuevo->dato->dato;
    cout<<"raiz"<<raiz;
    recorrer=raiz;
    if (nuevo->dato->dato != "NULL")
    {
        if (exiteenArbol(recorrer, nuevo->dato->dato, tipo) == 1)
        { //Evalua si el nodo ya existe en el arbol.
            PadreAB = raiz;
            cout<<"nuevo"<<nuevo;
            insertarNuevo(recorrer,nuevo, PadreAB);

            //BBaltura(recorrer);
            //necesidadEquilibrar(recorrer);
        }
        else
        {
            cout << "El numero ya existe en el arbol" << endl;
        }
    }
    cout<<"La Altura del arbol es: "<<altura(recorrer)<<endl;
}
