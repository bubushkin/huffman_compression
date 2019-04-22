/*
 * node.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "udef.h"

using namespace std;



class node{

public:
        bool isLeaf;
        int count;
        byte symbol;
        node *leftChild;
        node *rightChild;
        node *parent;

        node(byte symbol, int count, node *left, node *right, node *parent, bool isLeaf):
                symbol(symbol), count(count), leftChild(left), rightChild(right), parent(parent), isLeaf(isLeaf){}

        bool operator<(const node &rnode);
};

ostream & operator<<( ostream &, const node & ) __attribute__((weak));

ostream & operator<<( ostream &stm, const node &rn ) {
  stm << "[" << rn.symbol << "," << rn.count << "," << (int) (rn.symbol) << "]";
  return stm;
}

#endif /* NODE_H_ */
