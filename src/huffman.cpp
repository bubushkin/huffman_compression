/*
 * huffman.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#include "huffman.h"
#include <queue>
#include <tgmath.h>
#include <algorithm>
#include "minheap.h"

huffman::~huffman() {
	// TODO Auto-generated destructor stub
	destruct(this->proot);
}

void huffman::destruct(node *proot) {

  node *pcurrent = proot;
  if( pcurrent == nullptr )
    return;

  if(pcurrent->leftChild != nullptr){
          destruct(pcurrent->leftChild);
  }
  if(pcurrent->rightChild != nullptr){
          destruct(pcurrent->rightChild);
  }
  delete pcurrent;
  pcurrent = nullptr;
}

unsigned int huffman::buildTreeUncomp(bitstreamer &bin) {

  this->readHeader( nullptr, this->proot, bin );

  return (this->readCharCount( bin ));
}

unsigned int huffman::readCharCount( bitstreamer &bitIn ) {
  unsigned long long int count  = 0;
  byte ch                       = 0;

  for( int i = 32; i > 0; i -= 8 ) {
    ch = 0;

    for( int j = 0; j < 8; j++ )
      ch = ch | (bitIn.readBit() << j);

    count += (unsigned int) ch * pow( 2, i );
  }

  count /= pow( 2, 8 );
  return ((unsigned int) count);
}


void huffman::readHeader( node *par, node* &rnode, bitstreamer &bitIn ) {

	unsigned int bit = bitIn.readBit();

	if( !bit ) {
		node *p = new node(0, 0, nullptr, nullptr, nullptr, false);
		p->parent = par;
		rnode = p;
		this->readHeader( p, p->leftChild, bitIn );
		this->readHeader( p, p->rightChild, bitIn );
	}

	else {
		byte ch = 0;
		for( int i = 0; i < 8; i++ )
			ch = ch | (bitIn.readBit() << i);

		node *p = new node(ch, 0, nullptr, nullptr, nullptr, true);
		p->parent = par;
		rnode      = p;
	}
}

void huffman::buildTree(const vector<int> &rfreqs, unsigned int length, bitstreamer &rout ) {

  minheap heap;

  heap.buildMinHeap(rfreqs, this->reftable);

  while(heap.getSize() > 0x1){
      node *pleft = heap.extractMin();
      node *pright = heap.extractMin();
      node *pparent = new node( 0, (pleft->count + pright->count), nullptr, nullptr, nullptr, false);
      pparent->leftChild = pleft;
      pparent->rightChild = pright;
      pleft->parent = pparent;
      pright->parent = pparent;

      heap.enqueue(pparent);
  }
  this->pnode = heap.extractMin();


  this->writeHeader(this->pnode, rout);

  this->writeCharCount(length, rout);
}


void huffman::writeHeader( node *pnode, bitstreamer &rout ) {
  if(pnode == nullptr)
    return;

  if(pnode->isLeaf) {
    rout.writeBit(1);

    for(int i = 0; i < 8; i++)
      rout.writeBit((pnode->symbol & (1 << i)) >> i);
  }
  else {
    rout.writeBit(0);
    this->writeHeader(pnode->leftChild, rout);
    this->writeHeader(pnode->rightChild, rout);
  }
}

void huffman::writeCharCount(unsigned int length, bitstreamer &rout) {

	byte ch = 0;
	for(int i = 24; i >= 0; i -= 8) {
		ch = (length >> i) & ~0;
		for(int j = 0; j < 8; j++)
			rout.writeBit((ch & (1 << j)) >> j);
  }
}


void huffman::encode(byte symbol, bitstreamer &rout, unsigned long &usedbits) const {

  int index = (int) symbol;

  unsigned long tmp = 0;
  if(this->reftable[index] && this->reftable[index]->count ) {
    string code = "";

    node *pcurrent = this->reftable[index];
    tmp = pcurrent->count;

    while(pcurrent->parent != nullptr) {
      if(pcurrent->parent->leftChild == pcurrent)
        code += "0";
      else if( pcurrent->parent->rightChild == pcurrent)
        code += "1";
      else
        return;
      pcurrent = pcurrent->parent;
    }

    reverse(code.begin(), code.end());

    tmp *= code.length();
    usedbits += tmp;


    for(byte ch : code) {
      if( ch == '0')
    	  rout.writeBit( 0 );
      else if( ch == '1')
    	  rout.writeBit(1);
      else {
        cout << "Something went wrong while encoding " << symbol << endl;
        break;
      }
    }
  }
}

int huffman::decode(bitstreamer &in) const {
  node *pcurrent = this->proot;
  unsigned int ch;

  if(pcurrent == nullptr)
    return -1;

  while(pcurrent->leftChild != nullptr && pcurrent->rightChild != nullptr) {
    ch = in.readBit();

    if(ch == 0)
    	pcurrent = pcurrent->leftChild;
    else if(ch == 1)
    	pcurrent = pcurrent->rightChild;
    else if(ch == 2)
      return -1;
  }

  return ((int) pcurrent->symbol);
}



