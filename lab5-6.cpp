#include <iostream>
using namespace std;

class Nodo
{
    int elemto;
    Nodo* next;
public:
    Nodo(int, Nodo*); //constructor
    int  obtElem();
    void estElem(int);
    Nodo*obtNext();
    void estNext(Nodo*);
};
class Iterador
{
    Nodo* posicion;
    friend class Listenlazada;
public:
    Iterador();
    bool operator==(const Iterador&);
    void nextPosicion();
    int getValue();
};
class Listenlazada
{
    int size;
    Nodo* head;
public:

    Listenlazada();
    ~Listenlazada();
    //Listenlazada(Listenlazada &);
    Iterador begin();
    Iterador end();
    void insert(int);
    void remove(int);
    void print();
};

Nodo::Nodo(int elemto, Nodo* next = nullptr) { //constructor del nodo recibe dos parametros
    this->elemto = elemto; this->next = next; //se ingresa valor y un puntero que apunta a otro nodo o al null si no hay nada
}
int Nodo::obtElem() { // getter para obtener el elemento del nodo
    return elemto;
}
Nodo* Nodo::obtNext() { //getter obtener el puntero que apunta al siguiente elemento
    return next;
}
void Nodo::estElem(int elemto) { //setter cambiar los valores privados del nodo
    this->elemto = elemto;
}
void Nodo::estNext(Nodo* next) {//cambiar puntero que apunta a otro nodo
    this->next = next;
}
Listenlazada::Listenlazada() { //constructor
    size = 0; //cantidad de nodos tamanio
    head = nullptr; //un puntero que apunta al primer nodo de la lista
}
Listenlazada::~Listenlazada() {  //destructor
    if (head != nullptr) //ver si no esta vacio si esta vacio salta el procedimiento
    {
        Nodo* tmp = head; //puntero temporal que apunta al nodo que esta apuntando al puntero head
        while(tmp->obtNext() != nullptr) //obtiene el puntero que apunta al siguiente nodo
        {
            tmp = tmp->obtNext(); //se cambia el tmp
            delete head;  //va por cada nodo eliminando el head
            head = tmp;
        }
        delete head;
    }
}
/*
Listenlazada::Listenlazada(Listenlazada &o) { //CONSTRUCTOR COPIA
    size = o.size;
    head = o.head;
}
*/
Iterador Listenlazada::begin() {
    Iterador i;
    i.posicion = head;
    return i;
}
Iterador Listenlazada::end() {
    Iterador i;
    i.posicion = nullptr;
    return i;
}

void Listenlazada::insert(int newValor) { //inserta un nuevo nodo
    Nodo* test = head;
    Nodo* newNodo = new Nodo(newValor);//se crea un puntero que apunta a un nodo nuevo con un nuevo valor

    if (test == nullptr) // apunta al vacio
        head = newNodo; //head apunta al nuevo nodo
    else if (newValor < test->obtElem()) { //compara con el head que sea menor
        newNodo->estNext(head); // el nuevo nodo cambia el puntero que apunta null por el head
        head = newNodo;
    }
    else {
        while (test->obtNext() != nullptr && test->obtNext()->obtElem() < newValor)// verifica el valor del siguientee nodo
            test = test->obtNext();
        if (test->obtNext() != nullptr)//verifica en que posicion esta
            newNodo->estNext(test->obtNext());//cambia el puntero al puntero que esta apuntando al siguiente nodo
        test->estNext(newNodo);//cambia al puntero next para que apunte al nuevo nodo
    }
    size++;
}
void Listenlazada::remove(int elemto) {
    Nodo* test = head;
    if (test == nullptr)
        cout << "esta vacio" << endl; // Se comprueba que la cadena no este vacia
    else if (test->obtElem() == elemto) {
        head = test->obtNext(); // se testea el primer elemento
        delete test;
        size--;
    }
    else {
        Nodo* tmp;
        while(test->obtNext() != nullptr) {
            tmp = test;
            test = test->obtNext(); // se va desplazando buscando el elmento, si marca null significa que no se encontro el valor
            if (test->obtElem() == elemto) {
                tmp->estNext(test->obtNext());
                delete test;
                size--;
                return;
            }
        }
        cout << "no se encontro" << endl;
    }
}
void Listenlazada::print() {
    Nodo* test = head;
    if (test == nullptr) { return; } //comprueba si la lista esta vacia
    do {
        cout << test->obtElem() << " ";
        test = test->obtNext();
    } while (test != nullptr);
    cout << endl;
}
Iterador::Iterador() {
    posicion = nullptr;
}
bool Iterador::operator==(const Iterador& i) {
    return posicion == i.posicion;
}
void Iterador::nextPosicion() {
    if (posicion == nullptr)
        return;
    posicion = posicion->obtNext();
}
int Iterador::getValue() {
    if (posicion == nullptr) {
        cout << "null" << endl;
        return -1;
    }
    return posicion->obtElem();
}

int main()
{
    Listenlazada lista;
    lista.insert(15);
    lista.insert(6);
    lista.insert(86);
    lista.insert(-5);
    lista.insert(0);
    lista.print(); //imprime -5 0 6 15 86
    /*lista.remove(-5);
    lista.print(); // quita el -5// 0 6 15 86
    lista.remove(4);//no se encuentra en la cadena
    lista.print();
    lista.remove(86);
    lista.remove(6);
    lista.remove(0);
    lista.print(); //imprime el 15
    lista.remove(15);
    lista.print(); // esta vacio
    lista.remove(6); //no existe
    lista.print(); //esta vacio
    */
    cout<< "Prueba de Iteradores"<<endl;
    for (Iterador i = lista.begin(); !(i == lista.end()); i.nextPosicion())
        cout << i.getValue() << " ";
}
/*
    if (true)
        Listenlazada p = lista;

    lista.print();
    return 0;
}
*/
//que es un constructor copia que hace y para que sirve
