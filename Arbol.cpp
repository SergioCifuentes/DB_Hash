class Arbol
{
private:
    /* data */
public:
    Arbol(int tipo);
    int tipo;
    ~Arbol();
};

Arbol::Arbol(int tipo)
{
    this->tipo=tipo;
}

Arbol::~Arbol()
{
}
