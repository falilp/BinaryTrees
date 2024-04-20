#include <iostream>
#include "abin.hpp"

/* Exercise 1: Given a binary tree of a generic type tValue, calculate the number of nodes that, being siblings, 
have the same root and their subtrees are reflected.
Reflected is that it has the same branching structure. */
#pragma region Exercise1

template <typename tValue>
bool areSiblings(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node1, const typename Abin<tValue>::nodo node2){
    if(node1 == abin.NODO_NULO && node2 == abin.NODO_NULO) return true;
    else if(node1 != abin.NODO_NULO && node2 != abin.NODO_NULO) return true && areSiblings(abin,abin.hijoIzqdo(node1),abin.hijoIzqdo(node2)) && areSiblings(abin,abin.hijoDrcho(node1),abin.hijoDrcho(node2));
    else return false;
}

template <typename tValue>
unsigned int reflecteds(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(areSiblings(abin,abin.hijoIzqdo(node),abin.hijoDrcho(node))) return 1 + reflecteds(abin,abin.hijoIzqdo(node)) + reflecteds(abin,abin.hijoDrcho(node));
    else return reflecteds(abin,abin.hijoIzqdo(node)) + reflecteds(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int numberOfReflecteds(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return reflecteds(abin,abin.raiz());
}

#pragma endregion


/* Exercise 2: Count the number of nodes in a binary tree that has twice as many grandchildren as great-grandchildren. */
#pragma region Exercise2

template <typename tValue>
unsigned int sons(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    unsigned int sons = 0;
    if(abin.hijoIzqdo(node) != abin.NODO_NULO) sons++;
    if(abin.hijoDrcho(node) != abin.NODO_NULO) sons++;
    return sons;
}

template <typename tValue>
unsigned int grandchildren(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node != abin.NODO_NULO) return sons(abin,abin.hijoIzqdo(node)) + sons(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int greatGrandchildren(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node != abin.NODO_NULO) return grandchildren(abin,abin.hijoIzqdo(node)) + grandchildren(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int twiceGrandchildren(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(grandchildren(abin,node) == 2*greatGrandchildren(abin,node)) return 1 + twiceGrandchildren(abin,abin.hijoIzqdo(node)) + twiceGrandchildren(abin,abin.hijoDrcho(node));
    else return twiceGrandchildren(abin,abin.hijoIzqdo(node)) + twiceGrandchildren(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int numberOfTwiceGrandchildren(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return twiceGrandchildren(abin,abin.raiz());
}

#pragma endregion


/* Exercise 3: Know if an Abin is an ABB*/
#pragma region Exercise3

template <typename tValue>
bool checkSons(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return (abin.elemento(abin.hijoIzqdo(node)) < abin.elemento(node) && abin.elemento(abin.hijoDrcho(node)) > abin.elemento(node))? true : false;
}

template <typename tValue>
bool isABB(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(checkSons(abin,node)) return true && isABB(abin,abin.hijoIzqdo(node)) && isABB(abin,abin.hijoDrcho(node));
    else return false;
}

template <typename tValue>
bool abinIsABB(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return true;
    else return isABB(abin,abin.raiz());
}

#pragma endregion


/* Exercise 4: Implements an applet that, given a binary tree, counts the number of nodes that have more than 4 descendants. */
#pragma region Exercise4

template <typename tValue>
unsigned int numberOfDescendants(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return 1 + numberOfDescendants(abin,abin.hijoIzqdo(node)) + numberOfDescendants(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int moreThanFour(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(numberOfDescendants(abin,node) >= 4) return 1 + moreThanFour(abin,abin.hijoIzqdo(node)) + moreThanFour(abin,abin.hijoDrcho(node));
    else return moreThanFour(abin,abin.hijoIzqdo(node)) + moreThanFour(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int moreThanFourDescendants(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return moreThanFour(abin,abin.raiz());
}

#pragma endregion


/* Exercise 5: Construct a function that, given a Binary Tree, returns true if it is an AVL and false otherwise. */
#pragma region Exercise5

template <typename tValue>
unsigned int noRepeatElement(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node, tValue elemento){
    if(node == abin.NODO_NULO) return 0;
    else if(abin.elemento(node) == elemento) return 1 + noRepeatElement(abin,abin.hijoIzqdo(node),elemento) + 
        noRepeatElement(abin,abin.hijoDrcho(node),elemento);
    else return noRepeatElement(abin,abin.hijoIzqdo(node),elemento) + 
        noRepeatElement(abin,abin.hijoDrcho(node),elemento);
}

template <typename tValue>
bool checkOrden(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    bool value = true;
    if(abin.hijoIzqdo(node) != abin.NODO_NULO) value &= abin.elemento(abin.hijoIzqdo(node)) < abin.elemento(node);
    if(abin.hijoDrcho(node) != abin.NODO_NULO) valor &= abin.elemento(node) < abin.elemento(abin.hijoDrcho(node));
    return value;
}

template <typename tValue>
unsigned int heightAbin(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return 1 + std::max(heightAbin(abin,abin.hijoIzqdo(node)),heightAbin(abin,abin.hijoDrcho(node)));
}

template <typename tValue>
bool balanceFactor(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    int balance = (heightAbin(abin,abin.hijoDrcho(node))-1) - (heightAbin(abin,abin.hijoIzqdo(node))-1);
    return (-1 >= balance && balance <= 1);
}

template <typename tValue>
bool checkAVL(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(checkOrden(abin,node) && noRepeatElement(abin,node,abin.elemento(node) && balanceFactor(abin,node))) return true && 
        checkAVL(abin,abin.hijoIzqdo(node)) && 
        checkAVL(abin,abin.hijoDrcho(node));
    else return false;
}

template <typename tValue>
bool binaryIsAVL(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return true;
    else return checkAVL(abin,abin.raiz());
}

#pragma endregion


/* Exercise 6: Implements a generic function that transforms a binary tree of a generic type tValue, eliminating the proper 
descendants of all those nodes whose content be, at the same time greater than or equal to his own ancestors and 
less than or equal to his own descendants */
#pragma region Exercise6

#pragma endregion