#include <iostream>
#include "abin.hpp"

#pragma region Exercise1 
// exercise 1: Implement an applet that calculates the number of nodes in a binary tree
template <typename tValue>
unsigned int calculateNodes(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return 1 + calculateNodes(abin,abin.hijoIzqdo(node)) + calculateNodes(abin,abin.hijoDrcho(node));
}

template <typename tValue>
unsigned int calculateTotalNodes(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return calculateNodes(abin,abin.raiz());
}
#pragma endregion

#pragma region Exercise2
// exercise 2: Implement an applet that calculates the height of a binary tree
template <typename tValue>
unsigned int calculateHeightNode(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return calculateHeight(abin,abin.raiz())-1;
}

template <typename tValue>
unsigned int calculateHeight(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return 1 + std::max(calculateHeight(node,abin.hijoIzqdo(node)),calculateHeight(node,abin.hijoDrcho(node)));
}
#pragma endregion

#pragma region Exercise3
// exercise 3: Implements an applet that, given a binary tree and a node in it, determines the depth of this node in said tree.
template <typename tValue>
unsigned int depthNode(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(abin.arbolVacio() || abin.padre(node) == abin.NODO_NULO) return 0;
    else return 1 + depthNode(abin,abin.padre(node));
}
#pragma endregion

#pragma region Exercise4
// exercise 4: Implements a subprogram that determines the imbalance level of a binary tree, defined as the maximum imbalance of all its nodes. 
// The imbalance of a node is defines as the difference between the heights of the subtrees of the same.
template <typename tValue>
unsigned int maxImbalance(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return 0;
    else return std::max(std::abs(calculateHeight(abin,abin.hijoIzqdo(node))-calculateHeight(abin,abin.hijoDrcho(node))),
                std::max(maxImbalance(abin,abin.hijoIzqdo(node)),maxImbalance(abin,abin.hijoDrcho(node))));
}

template <typename tValue>
unsigned int imbalanceBinaryTree(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return 0;
    else return maxImbalance(abin,abin.raiz());
}
#pragma endregion

#pragma region Exercise5
// exercise 5: Implements an applet that determines whether or not a binary tree is pseudocomplete. 
// In this problem we will understand that a tree is pseudocomplete, if at the penultimate level
// of the same each of the nodes has two children or none.
template <typename tValue>
bool twoLeaf(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return (abin.hijoIzqdo(node) != abin.NODO_NULO && abin.hijoDrcho(node) != abin.NODO_NULO) ? true : false;
}

template <typename tValue>
bool nonTwoLeaf(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    return (abin.hijoIzqdo(node) == abin.NODO_NULO && abin.hijoDrcho(node) == abin.NODO_NULO) ? true : false;
}

template <typename tValue>
bool pseudocomplete(const Abin<tValue> &abin, const typename Abin<tValue>::nodo node){
    if(node == abin.NODO_NULO) return true;
    else if(calculateHeightNode(abin)-1 == depthNode(abin,node)) return (twoLeaf(abin,node) || nonTwoLeaf(abin,node)) 
                                                                        && pseudocomplete(abin,abin.hijoIzqdo(node)) 
                                                                        && pseudocomplete(abin,abin.hijoDrcho(node));
    else return pseudocomplete(abin,abin.hijoIzqdo(node)) && pseudocomplete(abin,abin.hijoDrcho(node));
}

template <typename tValue>
bool pseudocompleteBinaryTree(const Abin<tValue> &abin){
    if(abin.arbolVacio()) return false;
    else return pseudocomplete(abin,abin.raiz());
}
#pragma endregion