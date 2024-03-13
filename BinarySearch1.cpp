#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "abb.hpp"

#pragma region Exercise1
/* exercise 1: Implements a new operation of the TAD abb that, taking an element of it, completely
   eliminates the subtree that hangs from it */

// The solution is on the TAD abb.hpp
// if we want a functions them:
template <typename tValue>
void eliminateSubTree(Abb<tValue> &abb, const tValue &element){
    if(!abb.vacio()){
        const Abb<tValue> &auxiliarAbb = abb.buscar(element);
        if(!auxiliarAbb.vacio()) eliminateSub(auxiliarAbb.r);
    }
}

template <typename tValue>
void eliminateSub(typename Abb<tValue>::arbol* &abb){
    if(abb != nullptr){
        eliminateSub(abb->izq.r);
        eliminateSub(abb->drc.r);

        delete abb;
        abb = nullptr;
    }
}
#pragma endregion

#pragma region Exercise2
/* exercise 2: A binary search tree can be balanced by traversing inorder
of the tree to obtain the ordered list of its elements and then distribute
equally the elements on the left and right, placing the median at the root and
recursively building the left and right subtrees of each node.
Implement this algorithm to balance an ABB.*/
template <typename tValue>
Abb<tValue> buildBalancedTree(const std::vector<tValue> &elements, int begin, int end){
    if(begin > end) return Abb<tValue>();

    Abb<tValue> abb;
    abb.insertar(elements[(begin+end)/2]);
    abb.izqdo() = buildBalancedTree(elements, begin, ((begin+end)/2)-1);
    abb.drcho() = buildBalancedTree(elements, ((begin+end)/2)+1, end);

    return abb;
}
#pragma endregion

#pragma region Exercise3
/* exercise 3: Given two sets represented by binary search trees,
implements the union operation of two sets that returns another result
set that is the union of both, represented by a balanced ABB.*/
template <typename tValue>
void inorden(const Abb<tValue> &abb, std::vector<tValue> &elements){
    if(!abb.vacio()){
        inorden(abb.izqdo(), elements);
        elements.push_back(abb.elemento());
        inorden(abb.drcho(), elements);
    }
}

template <typename tValue>
Abb<tValue> unionOfBinary(const Abb<tValue> &abb1, const Abb<tValue> &abb2){
    if(!abb1.vacio() && !abb2.vacio()){
        std::vector<tValue> elements1, elements2, binaryUnion;
        inorden(abb1,elements1);
        inorden(abb2,elements2);

        std::merge(elements1.begin(), elements1.end(), elements2.begin(), elements2.end(), std::back_inserter(binaryUnion));
        std::sort(binaryUnion.end(),binaryUnion.end());
        binaryUnion.erase(std::unique(binaryUnion.begin(),binaryUnion.end()), binaryUnion.end());

        return buildBalancedTree(binaryUnion, 0, binaryUnion.size()-1);
    }
}
#pragma endregion

#pragma region Exercise4
/* exercise 4: Given two sets represented by binary search trees,
implements the intersection operation of two sets, which returns as a result
another set that is the intersection of both. The result must be in a tree
balanced.*/
template <typename tValue>
Abb<tValue> intersectionOfBinary(const Abb<tValue> &abb1, const Abb<tValue> &abb2){
    if(!abb1.vacio() && !abb2.vacio()){
        std::vector<tValue> elements1, elements2, binaryIntersection;
        std::set<tValue> repeatElements;
        inorden(abb1,elements1);
        inorden(abb2,elements2);

        for(tValue element : elements1) repeatElements.insert(element);
        for(tValue element : elements2) if(repeatElements.find(element) != repeatElements.end()) binaryIntersection.push_back(element);

        std::sort(binaryIntersection.begin(),binaryIntersection.end());
        binaryIntersection.erase(std::unique(binaryIntersection.begin(),binaryIntersection.end()), binaryIntersection.end());

        return buildBalancedTree(binaryIntersection, 0, binaryIntersection.size()-1); 
    }
}
#pragma endregion

#pragma region Exercise5
/* exercise 5: Implements the ◆ operator for sets defined as A ◆ B = (A ∪ B) - (A ∩ B).
The implementation of the ◆ operator must be carried out using the
operation ∈, which tells us whether or not a given element belongs to a set. The
representation of type Set must be such that the membership operation is in the
average case in O(log n).*/
template <typename tValue>
Abb<tValue> diamondOperator(const Abb<tValue> &abb1, const Abb<tValue> &abb2){
    Abb<tValue> auxiliarAbb1, auxiliarAbb2, diamond;
    auxiliarAbb1 = unionOfBinary(abb1,abb2);
    auxiliarAbb2 = intersectionOfBinary(abb1,abb2);

    std::vector<tValue> elements1, elements2;
    inorden(auxiliarAbb1,elements1);
    inorden(auxiliarAbb2,elements2);
    
    auto iterator=elements1.begin();
    while(iterator != elements1.end()){
        if(std::find(elements2.begin(), elements2.end(), *iterator) != elements2.end()) iterator = elements1.erase(iterator);
        else ++iterator;
    }

    std::sort(diamondVector.begin(),diamondVector.end());
    //diamondVector.erase(std::unique(diamondVector.begin(),diamondVector.end()), diamondVector.end());
    return buildBalancedTree(diamondVector, 0, diamondVector.size()-1); 
}
#pragma endregion