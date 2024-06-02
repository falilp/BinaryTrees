#include <iostream>
#include "abin.hpp"

#pragma region ABIN
/**
 * Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario, 
 * definido como el máximo desequilibrio de todos sus nodos. 
 * ! El desequilibrio de un nodo se define como la diferencia entre las alturas de los subárboles del mismo  
*/
template <typename tValue>
unsigned int alturaNodo(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return 1 + std::max(alturaNodo(abin,abin.hijoIzqdo(node)),alturaNodo(abin,abin.hijoDrcho(node)));
}

template <typename tValue>
unsigned int calcularDesequilibrio(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else{
        unsigned int desequilibrio = std::abs((alturaNodo(abin,abin.hijoIzqdo(node))-1) - (alturaNodo(abin,abin.hijoIzqdo(node))-1));
        return std::max(desequilibrio,std::max(calcularDesequilibrio(abin,abin.hijoIzqdo(node)), calcularDesequilibrio(abin,abin.hijoIzqdo(node))));
    }
}

template <typename tValue>
unsigned int desequilibrioAbin(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return calcularDesequilibrio(abin,abin.raiz());
}


/**
 * Dado un árbol binario de tipo genérico tValue, calcular el número de nodos que, al ser hermanos,
 * tienen la misma raíz y sus subárboles se reflejan.
 * Se refleja que tiene la misma estructura ramificada.
*/

template <typename tValue>
bool dosHijos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node1, const typename Abin<tValue>::nodo node2){
    if(node1 == abin.NODO_NULO && node2 == abin.NODO_NULO) return true;
    else if(node1 != abin.NODO_NULO && node2 != abin.NODO_NULO) return true && 
        dosHijos(abin,abin.hijoIzqdo(node1),abin.hijoIzqdo(node2)) &&
        dosHijos(abin,abin.hijoDrcho(node1),abin.hijoDrcho(node2));
    else return false;
}

template <typename tValue>
unsigned int reflejados(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(dosHijos(abin,abin.hijoIzqdo(node),abin.hijoDrcho(node))) return 1 + 
        reflejados(abin,abin.hijoIzqdo(node)) + 
        reflejados(abin,abin.hijoDrcho(node));
    else return reflejados(abin,abin.hijoIzqdo(node)) + reflejados(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int subArbolesReflejados(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return reflejados(abin,abin.raiz());
}


/**
 * Cuente el número de nodos en un árbol binario que tiene el doble de nietos que bisnietos. 
*/

template <typename tValue>
unsigned int numeroHijos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    unsigned int hijos = 0;
    if(abin.hijoIzqdo(node) != abin.NODO_NULO) hijos++;
    if(abin.hijoDrcho(node) != abin.NODO_NULO) hijos++;
    return hijos;
}

template <typename tValue>
unsigned int numeroNietos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return numeroHijos(abin,abin.hijoIzqdo(node)) + numeroHijos(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int numeroBisnietos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return numeroNietos(abin,abin.hijoIzqdo(node)) + numeroNietos(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int dobleNietos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(numeroBisnietos(abin,node)*2 == numeroNietos(abin,node)) return 1 + 
        dobleNietos(abin,abin.hijoIzqdo(node)) + dobleNietos(abin,abin.hijoDrcho(node));
    else return dobleNietos(abin,abin.hijoIzqdo(node)) + dobleNietos(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int dobleNietosAbin(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return dobleNietos(abin,abin.raiz());
}


/**
 * Saber si un abin es abb
*/

template <typename tValue>
bool orden(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return abin.elemento(node) > abin.elemento(abin.hijoIzqdo(node)) && abin.elemento(node) < abin.elemento(abin.hijoDrcho(node));
}

template <typename tValue>
bool comprobarAbb(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(orden(abin,node)) return true && comprobarAbb(abin,abin.hijoIzqdo(node)) && comprobarAbb(abin,abin.hijoDrcho(node));
    else return false;
}

template <typename tValue>
bool abinEsAbb(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return true;
    else return comprobarAbb(abin,abin.raiz());
}


/**
 * Implementa un subprograma que, dado un árbol binario, cuenta el número de nodos que tienen más de 4 descendientes.
*/

template <typename tValue>
unsigned int contarDescendientes(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else{
        unsigned int contador = 0;
        contador = contarDescendientes(abin,abin.hijoIzqdo(node));
        if(contador >= 5) return contador;
        else return 1 + contador + contarDescendientes(abin,abin.hijoDrcho(node));
    } 
    /*else return 1 + contarDescendientes(abin,abin.hijoIzqdo(node)) + 
        contarDescendientes(abin,abin.hijoDrcho(node));*/
}

template <typename tValue>
unsigned int CuatroDescendientes(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(contarDescendientes(abin,node)-1 >= 4) return 1 + 
        CuatroDescendientes(abin,abin.hijoIzqdo(node)) + 
        CuatroDescendientes(abin,abin.hijoDrcho(node));
    else return CuatroDescendientes(abin,abin.hijoIzqdo(node)) + CuatroDescendientes(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int masDeCuatroDescendientes(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return CuatroDescendientes(abin,abin.raiz());
}

/**
 * Construya una función que, dado un árbol binario, devuelva verdadero si es un AVL y falso en caso contrario.
*/

template <typename tValue>
unsigned int noElementoRepetido(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node, tValue elemento){
    if(node == abin.NODO_NULO) return 0;
    else if(abin.elemento(node) == elemento) return 1 + noElementoRepetido(abin,abin.hijoIzqdo(node),elemento) + 
        noElementoRepetido(abin,abin.hijoDrcho(node),elemento);
    else return noElementoRepetido(abin,abin.hijoIzqdo(node),elemento) + 
        noElementoRepetido(abin,abin.hijoDrcho(node),elemento);
}

template <typename tValue>
unsigned int alturaSubarbol(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return -1;
    else return 1 + std::max(alturaSubarbol(abin,abin.hijoIzqdo(node)),alturaSubarbol(abin,abin.hijoDrcho(node)));
}

template <typename tValue>
bool equilibrio(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    unsigned int alturaSubarbolIzquierdo = alturaSubarbol(abin,abin.hijoIzqdo(node));
    unsigned int alturaSubarbolDerecho = alturaSubarbol(abin,abin.hijoDrcho(node));
    int diferencia = alturaSubarbolDerecho-alturaSubarbolIzquierdo;
    return -1 >= diferencia && diferencia <= 1;
}

template <typename tValue>
bool ordenElementos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    bool valor = true;
    if(abin.hijoIzqdo(node) != abin.NODO_NULO) valor &= abin.elemento(abin.hijoIzqdo(node)) < abin.elemento(node);
    if(abin.hijoDrcho(node) != abin.NODO_NULO) valor &= abin.elemento(node) < abin.elemento(abin.hijoDrcho(node));
    return valor;
}

template <typename tValue>
bool comprobarAvl(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(ordenElementos(abin,node) && equilibrio(abin,node) && (noElementoRepetido(abin,abin.raiz(),abin.elemento(node)) < 2)) return true && 
        esAvl(abin,abin.hijoIzqdo(node)) && 
        esAvl(abin,abin.hijoDrcho(node));
    else return false;
}

template <typename tValue>
bool esAbinAvl(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return true;
    else return comprobarAvl(abin,abin.raiz());
}


/** 
 * TODO: Implementa un subprograma que determina si un árbol binario es pseudocompleto o no. 
 * ! En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel del mismo cada uno de los nodos tiene dos hijos o ninguno.
*/

template <typename tValue>
int alturaAbin(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return -1;
    else return 1 + std::max(AlturaNodo(abin,abin.hijoIzqdo(node)),AlturaNodo(abin,abin.hijoDrcho(node)));
}

template <typename tValue>
unsigned int profundidadNodo(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(abin.arbolVacio() || abin.padre(node) == abin.NODO_NULO) return 0;
    else return 1 + profundidadNodo(abin,abin.padre(node));
}

template <typename tValue>
bool dosHijos(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return abin.hijoIzqdo(node) != abin.NODO_NULO && abin.hijoDrcho(node) != abin.NODO_NULO;
}

template <typename tValue>
bool ningunHijo(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return abin.hijoIzqdo(node) == abin.NODO_NULO && abin.hijoDrcho(node) == abin.NODO_NULO;
}

template <typename tValue>
bool comprobarPseudocompleto(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(alturaAbin(abin,abin.raiz())-1 == profundidadNodo(abin,node)){
        if(dosHijos(abin,node) || ningunHijo(abin,node)) return true && 
            comprobarPseudocompleto(abin,abin.hijoIzqdo(node)) && 
            comprobarPseudocompleto(abin,abin.hijoDrcho(node));
        else return false;
    }else return true && comprobarPseudocompleto(abin,abin.hijoIzqdo(node)) && comprobarPseudocompleto(abin,abin.hijoDrcho(node));
}

template <typename tValue>
bool pseudocompletoAbin(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return false;
    else return comprobarPseudocompleto(abin,abin.raiz());
}


/**
 * TODO: Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los subárboles izquierdo y derecho en cada nodo.
*/

template <typename tValue>
void reflejar(const Abin<tValue> &abin, Abin<tValue> &abinReflejo, const typename Abin<tValue>::nodo node, typename Abin<tValue>::nodo nodeReflejo){
    if(node != abin.NODO_NULO){
        abinReflejo.insertarHijoDrcho(nodeReflejo,abin.elemento(abin.hijoIzqdo(node)));
        abinReflejo.insertarHijoIzqdo(nodeReflejo,abin.elemento(abin.hijoDrcho(node)));
        reflejar(abin,abinReflejo,abin.hijoDrcho(node),abinReflejo.hijoIzqdo(nodeReflejo));
        reflejar(abin,abinReflejo,abin.hijoIzqdo(node),abinReflejo.hijoDrcho(nodeReflejo));
    }
}

template <typename tValue>
Abin<tValue> reflejarAbin(const Abin<tValue> &abin){
    Abin<tValue> abinReflejo;
    if(abin.arbolVacio()) return abinReflejo;
    else{
        abinReflejo.insertarRaiz(abin.elemento(abin.raiz()));
        return reflejar(abin,abinReflejo,abin.raiz());
    }
}


/**
 * TODO: El árbol binario TAD puede acomodar expresiones matemáticas utilizando un árbol de expresión. 
 * TODO: Dentro del árbol binario los nodos hoja contendrán los operandos, y el resto de los nodos los operadores.
 * 
 * !a) Define el tipo de elementos del árbol para que los nodos puedan almacenar operadores y operandos.
 * 
 * !b) Implementar una función que tome un árbol de expresiones binarias (aritmética) y devuelva el resultado del mismo. 
 * !Para simplificar el problema, se puede suponer que el árbol representa una expresión correcta. 
 * !Los posibles operadores binarios en la expresión aritmética serán la suma, la resta, la multiplicación y la división.
*/

typedef struct elementos{
    int elemento;
    char operador;
    elementos(int elem = 0, char operador = '#'):elemento(elem),operador(operador){}
}Elementos;

int expresion(const Abin<Elementos> &abin, const typename Abin<Elementos>::nodo node){
    if(abin.hijoIzqdo(node) == abin.NODO_NULO) return abin.elemento(node).elemento;
    else{
        switch(abin.elemento(node).operador){
            case '+': return expresion(abin,abin.hijoIzqdo(node)) + expresion(abin,abin.hijoDrcho(node));
            case '-': return expresion(abin,abin.hijoIzqdo(node)) - expresion(abin,abin.hijoDrcho(node));
            case '*': return expresion(abin,abin.hijoIzqdo(node)) * expresion(abin,abin.hijoDrcho(node));
            case '/': return expresion(abin,abin.hijoIzqdo(node)) / expresion(abin,abin.hijoDrcho(node));
        }
    }
}

int expresionMatematica(const Abin<Elementos> &abin){
    if(abin.arbolVacio()) return 0;
    else return expresion(abin,abin.raiz());
}


/**
 * TODO: Busca un nodo en un árbol, este será pasado en los parámetros de la función principal (buscaremos su elemento) 
*/

template <typename tValue>
bool buscarNodo(const Abin<Elementos> &abin, const typename Abin<Elementos>::nodo node, const tValue &elemento){
    if(node == abin.NODO_NULO) return true;
    else if(abin.elemento(node) == elemento) return false;
    else return true && buscarNodo(abin,abin.hijoIzqdo(node),elemento) && buscarNodo(abin,abin.hijoDrcho(node),elemento);
}

template <typename tValue>
bool buscarNodoAbin(const Abin<tValue> &abin, const tValue &elemento){
    if(abin.arbolVacio()) return false;
    else return !buscarNodo(abin,abin.raiz(),elemento);
}


/**
 * TODO: Implementa una funcion generica que transforme un arbol binario de un tipo generico tValue, 
 * TODO: eliminando los descendientes propios de todos aquellos nodos cuyo contenido sea, 
 * TODO: al mismo tiempo mayor o igual que sus ascendientes propios y menor o igual que sus descnedientes propios.
*/

template <typename tValue>
bool ascendentes(Abin<tValue> &abin, typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else return (abin.elemento(node) >= abin.elemento(abin.padre(node))) && ascendentes(abin,abin.padre(node));
}

template <typename tValue>
bool comprobarMenor(Abin<tValue> &abin, typename Abin<tValue>::nodo node, const tValue &valor){
    return (valor <= abin.elemento(abin.hijoIzqdo(node))) && (valor <= abin.elemento(abin.hijoIzqdo(node)));
}
template <typename tValue>
bool descendientes(Abin<tValue> &abin, typename Abin<tValue>::nodo node, const tValue &valor){
    if(node == abin.NODO_NULO) return true;
    else if(comprobarMenor(abin,node,abin.elemento(node))) return true && 
        descendientes(abin,abin.hijoIzqdo(node),valor) &&
        descendientes(abin,abin.hijoDrcho(node),valor);
    else return false;
}

template <typename tValue>
void podarNodo(Abin<tValue> &abin, typename Abin<tValue>::nodo node){
    if(node != abin.NODO_NULO){
        podarNodo(abin,abin.hijoIzqdo(node));
        abin.eliminarHijoIzqdo(node);
        podarNodo(abin,abin.hijoDrcho(node));
        abin.eliminarHijoDrcho(node);
    }
}

template <typename tValue>
void eliminacionNodos(Abin<tValue> &abin, typename Abin<tValue>::nodo node){
    //if(node != Abin<tValue>::NODO_NULO)
    if(node != abin.NODO_NULO){
        if(ascendentes(abin,node) && descendientes(abin,node,abin.elemento(node))) podarNodo(abin,node);
        else eliminacionNodos(abin,abin.hijoIzqdo(node)); eliminacionNodos(abin,abin.hijoDrcho(node));
    }
}

template <typename tValue>
void transformarAbin(Abin<tValue> &abin){
    if(!abin.arbolVacio()) eliminacionNodos(abin,abin.raiz());
}


/**
 * TODO: Cuantos nodos de un arbol son rebeldes, un nodo es rebelde si es distinto de la MAYORIA de sus ancestros, los nodos son booleanos
*/

unsigned int contarIguales(const Abin<bool> &abin, const typename Abin<bool>::nodo node, bool valor){
    if(node == abin.NODO_NULO || abin.padre(node) == abin.NODO_NULO) return 0;
    else if(valor == abin.elemento(abin.padre(node))) return 1 + contarIguales(abin,abin.padre(node),valor);
    else return contarIguales(abin,abin.padre(node),valor); 
}

unsigned int contarDistintos(const Abin<bool> &abin, const typename Abin<bool>::nodo node, bool valor){
    if(node == abin.NODO_NULO || abin.padre(node) == abin.NODO_NULO) return 0;
    else if(valor != abin.elemento(abin.padre(node))) return 1 + contarDistintos(abin,abin.padre(node),valor);
    else return contarDistintos(abin,abin.padre(node),valor); 
}

unsigned int nodosRebeldes(const Abin<bool> &abin, const typename Abin<bool>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(contarDistintos(abin,node,abin.elemento(node)) > contarIguales(abin,node,abin.elemento(node)))
        return 1 + nodosRebeldes(abin,abin.hijoIzqdo(node)) + nodosRebeldes(abin,abin.hijoDrcho(node));
    else return nodosRebeldes(abin,abin.hijoIzqdo(node)) + nodosRebeldes(abin,abin.hijoDrcho(node));
}

unsigned int numeroNodosRebeldes(const Abin<bool> &abin){
    if(abin.arbolVacio()) return 0;
    else return nodosRebeldes(abin,abin.raiz());
}

#pragma endregion