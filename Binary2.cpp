#include <iostream>
#include "abin.hpp"

/* exercise 1: Two binary trees are similar when they have identical branching structure, that is, both are empty, or otherwise, 
they have left and right subtrees Similar. Implements an applet that determines whether two binary trees are similar. */
#pragma region Exercise1

template <typename tValue>
bool similars(const Abin<tValue> &abin1, const Abin<tValue> &abin2, const typename Abin<tValue>::nodo node1, const typename Abin<tValue>::nodo node2){
    if(node1 == abin1.NODO_NULO && node2 == abin2.NODO_NULO) return true;
    else if(node1 != abin1.NODO_NULO && node2 != abin2.NODO_NULO) return true 
                                                                            && similars(abin1,abin2,abin1.hijoIzqdo(node1),abin2.hijoIzqdo(node2))
                                                                            && similars(abin1,abin2,abin1.hijoDrcho(node1),abin2.hijoDrcho(node2));
    else return false;
}

template <typename tValue>
bool similarTrees(const Abin<tValue> &abin1, const Abin<tValue> &abin2){
    if(abin1.arbolVacio() && abin2.arbolVacio()) return true;
    else if(!abin1.arbolVacio() && !abin2.arbolVacio()) return similars(abin1,abin2);
    else return false;
}

#pragma endregion

/* exercise 2: For a binary tree B, we can construct the mirrored binary tree BR by changing the left and right subtrees at each node. 
Implement an applet that returns the binary tree reflected from a given one. */
#pragma region Exercise2

template <typename tValue>
void mirrored(const Abin<tValue> &abin, const Abin<tValue> &mirror, const typename Abin<tValue>::nodo nodeAbin, const typename Abin<tValue>::nodo nodeMirror){
    if(nodeAbin != abin.NODO_NULO){
        mirror.insertarHijoIzqdo(nodeMirror,abin.elemento(abin.hijoDrcho(nodeAbin)));
        mirror.insertarHijoDrcho(nodeMirror,abin.elemento(abin.hijoIzqdo(nodeAbin)));
        mirrored(abin,mirror,abin.hijoIzqdo(nodeAbin),mirror.hijoDrcho(nodeMirror));
        mirrored(abin,mirror,abin.hijoDrcho(nodeAbin),mirror.hijoIzqdo(nodeMirror));
    }
}

template <typename tValue>
Abin<tValue> mirroedTree(const Abin<tValue> &abin){
    Abin<tValue> mirror;
    if(!abin.arbolVacio()){
        mirror.insertarRaiz(abin.elemento(abin.raiz()));
        mirrored(abin,mirror,abin.raiz(),mirror.raiz());
    }
    return mirror;
}

#pragma endregion

/* Exercise 3: The TAD binary tree can accommodate mathematical expressions using an expression tree. Within the binary tree the leaf nodes will contain the operands, and the rest
of the nodes the operators.

a) Defines the type of the tree elements so that the nodes can store operators and operands.

b) Implement a function that takes a binary expression tree (arithmetic) and returns the result of it. To simplify the problem, it can be assumed that the
tree represents a correct expression. The possible binary operators in the arithmetic expression will be addition, subtraction, multiplication and division.*/
#pragma region Exercise3

typedef struct elemento{
    double operando;
    char operador;
    elemento(char ope='#', double op=0):operando(op),operador(ope){}
}Elemento;

double expression(const Abin<Elemento> &abin,const typename Abin<Elemento>::nodo node){
    if(node != abin.NODO_NULO){
        switch (abin.elemento(node).operador){
            case '+': return expression(abin,abin.hijoIzqdo(node))+expression(abin,abin.hijoDrcho(node));
            case '-': return expression(abin,abin.hijoIzqdo(node))-expression(abin,abin.hijoDrcho(node));
            case '*': return expression(abin,abin.hijoIzqdo(node))*expression(abin,abin.hijoDrcho(node));
            case '/': return expression(abin,abin.hijoIzqdo(node))/expression(abin,abin.hijoDrcho(node));
            default: return abin.elemento(node).operando;
        }
    }else return abin.elemento(node).operando;
}

double expressionTree(const Abin<Elemento> &abin){
    if(abin.arbolVacio()) return 0;
    else return expression(abin,abin.raiz());
}

#pragma endregion

/* Exercise 4: RENEGADES: A node is said to be renegade when it goes against the others. Given a Binary Tree, calculate the number of renegade nodes in said tree.
Note: I consider that renegade is from the root. */
#pragma region Exercise4

template <typename tValue>
unsigned int renagades(const Abin<tValue> &abin,const typename Abin<Elemento>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(abin.elemento(node) == abin.elemento(abin.raiz())) return 1 + renagades(abin,abin.hijoIzqdo(node)) + renegades(abin,abin.hijoDrcho(node));
    else return renagades(abin,abin.hijoIzqdo(node)) + renegades(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int NodeRenegades(const Abin<tValue>& abin){
    if(abin.arbolVacio()) return 0;
    else return renagades(abin,abin.hijoIzqdo(abin.raiz())) + renagades(abin,abin.hijoDrcho(abin.raiz()));
}

#pragma endregion

/* Exercise 5: Find a node in the tree.
NOTE: i will assume that the exercise refers to finding the, that is, does it exist in the tree. */
#pragma region Exercise5

template <typename tValue>
bool find(const Abin<tValue>& abin, const typename Abin<tValue>::nodo nodeToFind, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(node == nodeToFind) return false;
    else return true && find(abin,nodeToFind,abin.hijoIzqdo(node)) && find(abin,nodeToFind,abin.hijoDrcho(node));
}

template <typename tValue>
bool findNode(const Abin<tValue>& abin, const typename Abin<tValue>::nodo node){
    if(abin.arbolVacio() || node == abin.NODO_NULO) return false;
    else return !find(abin,node,abin.raiz());
}

#pragma endregion

/* Exercise 6: Count the number of nodes in a binary tree that has exactly 3 grandchildren. */
#pragma region Exercise6

template <typename tValue>
unsigned int numChilds(const Abin<tValue>& abin, const typename Abin<tValue>::nodo node){
    unsigned int aux = 0;
    if(abin.hijoIzqdo(node) != abin.NODO_NULO) aux++;
    if(abin.hijoDrcho(node) != abin.NODO_NULO) aux++;
    return aux;
}

template <typename tValue>
bool threeG(const Abin<tValue>& abin, const typename Abin<tValue>::nodo node){
    if(numChilds(abin,abin.hijoIzqdo(node)) + numChilds(abin,abin.hijoDrcho(node)) >= 3 ) return true;
    else return false;
}

template <typename tValue>
unsigned int countThreeGrandchildren(const Abin<tValue>& abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else if(threeG(abin,node)) return 1 + countThreeGrandchildren(abin,abin.hijoIzqdo(node)) + countThreeGrandchildren(abin,abin.hijoDrcho(node));
    else return countThreeGrandchildren(abin,abin.hijoIzqdo(node)) + countThreeGrandchildren(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int threeGrandchildren(const Abin<tValue>& abin){
    if(abin.arbolVacio()) return 0;
    else return countThreeGrandchildren(abin,abin.raiz());
}

#pragma endregion