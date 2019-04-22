/*
 * minheap.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#include "minheap.h"
#include "node.h"
#include <tgmath.h>

minheap::~minheap() {
	destruct(this->buffer);
}

void minheap::destruct(vector<node*> &rbuffer){
    for(int i = 0; i < rbuffer.size(); i++){
        delete rbuffer[i];
    }
}

int minheap::getParentIdx(int index) {
    return (int)floor(index >> 0x1);
}

int minheap::getLeftChildIdx(int index) {
    return (index << 0x1) + 0x1;
}

int minheap::getRightChildIdx(int index) {
    return (index << 0x1) + 0x2;
}

int minheap::getSize() const {
    return this->heapsize;
}

void minheap::removeNodeAt(int index) {
    this->buffer.erase(this->buffer.begin() + index, this->buffer.begin() + index + 1);
    this->heapsize--;
    this->minHeapify(0);
}

void minheap::siftUp(int index) {

    int parentIdx;
    if(index != 1){
        parentIdx = this->getParentIdx(index);
        if(this->buffer[parentIdx]->count > this->buffer[index]->count){
            std::swap(this->buffer[parentIdx], this->buffer[index]);
            this->siftUp(parentIdx);
        }
    }
}

void minheap::insertNode(node *pnode) {

    this->buffer.push_back(pnode);
    this->heapsize++;
    this->siftUp(this->heapsize - 1);

}

void minheap::buildMinHeap(const vector<int> &rfreqs){

	for( int i = 0; i < UCHAR_MAX + 1; i++ ) {
	  if( rfreqs[i] ) {
		  node *p = new node((byte) i, rfreqs[i], nullptr, nullptr, nullptr, true);
		  this->buffer[i] = p;
		  this->heapsize++;
		  this->capacity++;
	  }
	}

    for(int i = floor((this->heapsize - 1) / 2); i >= 0; i--){
        this->minHeapify(i);
    }
}

void minheap::minHeapify(unsigned int index) {

    unsigned int min_idx = index;
    unsigned int left_idx = this->getLeftChildIdx(index);
    unsigned int right_idx = this->getRightChildIdx(index);

    if((left_idx < this->heapsize) && (this->buffer[left_idx]->count < this->buffer[index]->count)){
        min_idx = left_idx;
    } else{
        min_idx = index;
    }
    if((right_idx < this->heapsize) && (this->buffer[right_idx]->count < this->buffer[min_idx]->count)){
        min_idx = right_idx;
    }

    if(min_idx != index){
        std::swap(this->buffer[index], this->buffer[min_idx]);
        this->minHeapify(min_idx);
    }
}

node* minheap::getNodeAt(int index) {
    return this->buffer[index];

}

node* minheap::extractMin() {
    node *node = this->getNodeAt(0);
    this->removeNodeAt(0);
    return node;
}

void minheap::enqueue(node *pnode) {
    this->insertNode(pnode);
}
