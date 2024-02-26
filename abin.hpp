#ifndef ABIN_H
#define ABIN_H
#include <cassert>

template <typename T> class Abin {
    struct celda; // declaración adelantada privada
    public:
        typedef celda* nodo;
        static const nodo NODO_NULO;

        //Post: Crea y devuelve un árbol vacío
        Abin(); // constructor

        //Pre: El árbol está vacío.
        //Post: Inserta el nodo raíz cuyo contenido será e.
        void insertarRaiz(const T& e);

        //Pre: n es un nodo del árbol que no tiene hijo izquierdo.
        //Post: Inserta el elemento e como hijo izquierdo del nodo n.
        void insertarHijoIzqdo(nodo n, const T& e);

        //Pre: n es un nodo del árbol que no tiene hijo derecho.
        //Post: Inserta el elemento e como hijo derecho del nodo n.
        void insertarHijoDrcho(nodo n, const T& e);

        //Pre: n es un nodo del árbol.
        //Post: Destruye el hijo izquierdo del nodo n.
        void eliminarHijoIzqdo(nodo n);

        //Pre: n es un nodo del árbol.
        //Post: Destruye el hijo derecho del nodo n.
        void eliminarHijoDrcho(nodo n);

        //Pre: El árbol no está vacío y raizB() es una hoja.
        //Post: Destruye el nodo raíz. El árbol queda vacío
        void eliminarRaiz();

        //Post: Devuelve true si el árbol está vacío y false en caso contrario.
        bool arbolVacio() const;

        //Pre: n es un nodo del árbol.
        //Post: Devuelve el elemento del nodo n.
        const T& elemento(nodo n) const; // acceso a elto, lectura
        T& elemento(nodo n); // acceso a elto, lectura/escritura

        //Post: Devuelve el nodo raíz del árbol. Si el árbol está vacío, devuelve NODO_NULO.
        nodo raiz() const;

        //Pre: n es un nodo del árbol.
        //Post: Devuelve el padre del nodo n. Si n es el nodo raíz, devuelve NODO_NULO.
        nodo padre(nodo n) const;

        //Pre: n es un nodo del árbol
        //Post: Devuelve el nodo hijo izquierdo del nodo n. Si no existe, devuelve NODO_NULO.
        nodo hijoIzqdo(nodo n) const;

        //Pre: n es un nodo de A.
        //Post: Devuelve el nodo hijo derecho del nodo n. Si no existe, devuelve NODO_NULO.
        nodo hijoDrcho(nodo n) const;
        
        Abin(const Abin<T>& a); // ctor. de copia
        Abin<T>& operator =(const Abin<T>& A); // asig.de árboles
        ~Abin(); // destructor
    private: 
        struct celda {
            T elto;
            nodo padre, hizq, hder;
            celda(const T& e, nodo p = NODO_NULO): elto(e),
            padre(p), hizq(NODO_NULO), hder(NODO_NULO) {}
        };
        nodo r; // nodo raíz del árbol
        void destruirNodos(nodo& n);
        nodo copiar(nodo n);
};

/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(nullptr);

/*--------------------------------------------------------*/
/* Métodos públicos */
/*--------------------------------------------------------*/
template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}

template <typename T>
inline void Abin<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); // Árbol vacío
    r = new celda(e);
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO); // No existe hijo izqdo.
    n->hizq = new celda(e, n);
}

template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // No existe hijo drcho.
    n->hder = new celda(e, n);
}

template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); // Existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && // Hijo izqdo. 
    n->hizq->hder == NODO_NULO); // es hoja.
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); // Existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO && // Hijo drcho.
    n->hder->hder == NODO_NULO); // es hoja
    delete n->hder;
    n->hder = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // Árbol no vacío.
    assert(r->hizq == NODO_NULO &&
    r->hder == NODO_NULO); // La raíz es hoja.
    delete r;
    r = NODO_NULO;
}

template <typename T> inline bool Abin<T>::arbolVacio() const
{ return (r == NODO_NULO); }

template <typename T>
inline const T& Abin<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Abin<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{ return r; }


template <typename T> inline
typename Abin<T>::nodo Abin<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}

template <typename T>
inline Abin<T>::Abin(const Abin<T>& A)
{
    r = copiar(A.r); // Copiar raíz y descendientes.
}

template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& A)
{
    if (this != &A) // Evitar autoasignación.
    {
    this->~Abin(); // Vaciar el árbol.
    r = copiar(A.r); // Copiar raíz y descendientes.
    }
    return *this;
}

/*--------------------------------------------------------*/
/* Métodos privados */
/*--------------------------------------------------------*/
// Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO)
    {
        destruirNodos(n->hizq);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto); // Copiar n.
        m->hizq = copiar(n->hizq); // Copiar subárbol izqdo.
        if (m->hizq != NODO_NULO) m->hizq->padre = m;
        m->hder = copiar(n->hder); // Copiar subárbol drcho.
        if (m->hder != NODO_NULO) m->hder->padre = m;
    }
    return m;
}

#endif // ABIN_H