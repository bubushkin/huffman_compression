/*
 * huffman.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <vector>
#include <climits>
#include "bitstreamer.h"
#include "node.h"

class huffman {

private:
    static void destruct(node *proot);
    node *proot;

    vector<node*> reftable;

    node *pnode;

public:

    explicit huffman() : proot(nullptr){
            this->reftable = vector<node*>(UCHAR_MAX + 0x1, (node *)nullptr);
    }
    ~huffman();

    void encode(byte symbol, bitstreamer &os, unsigned long &usedbits) const;
    int decode(bitstreamer &in) const;

    void buildTreeComp(const vector<int> &rfreqs, unsigned int length, bitstreamer &rbout);
    void buildTree(const vector<int> &rfreqs, unsigned int length, bitstreamer &rout );

    void writeHeader(node *pnode, bitstreamer &rbout);

    void writeCharCount(unsigned int length, bitstreamer &rbout);

    unsigned int  buildTreeUncomp(bitstreamer &rin);

    void readHeader(node *par, node* &pnode, bitstreamer &rbitIn);

    unsigned int  readCharCount(bitstreamer &bitIn);


};


class comparator {
public:
  bool operator()(node* &plhs, node* &prhs ) const {
    return *plhs < *prhs;
  }

};


#endif /* HUFFMAN_H_ */
