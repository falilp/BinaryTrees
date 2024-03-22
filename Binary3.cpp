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
    else isABB(abin,abin.raiz());
}

#pragma endregion