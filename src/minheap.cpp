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
        delete buffer[i];
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
    this->buffer.erase(this->buffer.begin() + index, this->buffer.begin() + index + 0x1);
    this->heapsize--;
    this->minHeapify(0x0);
}

void minheap::siftUp(int index) {

    int parentIdx;
    if(index != 0x0){
        parentIdx = this->getParentIdx(index);
        if(this->buffer.at(parentIdx)->frequency > this->buffer.at(index)->frequency){
            std::swap(this->buffer.at(parentIdx), this->buffer.at(index));
            this->siftUp(parentIdx);
        }
    }
}

void minheap::insertNode(node *pnode) {

    this->buffer.push_back(pnode);
    this->heapsize++;
    this->siftUp(this->heapsize - 0x1);

}

void minheap::buildMinHeap(vector<int> &rfreqs){

	for( int i = 0; i < UCHAR_MAX + 1; i++ ) {
	  if( rfreqs[i] ) {
		  node *p = new node((byte) i, rfreqs[i], nullptr, nullptr, nullptr, true);
		  this->buffer[i] = p;
		  this->heapsize++;
		  this->capacity++;
	  }
	}

    for(int idx = floor((this->heapsize - 0x1) / 2); idx >= 0x0; idx--){
        minHeapify(idx);
    }
}

void minheap::minHeapify(unsigned int index) {

    unsigned int min_idx = index;
    unsigned int left_idx = this->getLeftChildIdx(index);
    unsigned int right_idx = this->getRightChildIdx(index);

    if((left_idx < this->heapsize) && (this->buffer.at(left_idx)->frequency < this->buffer.at(index)->frequency)){
        min_idx = left_idx;
    } else{
        min_idx = index;
    }
    if((right_idx < this->heapsize) && (this->buffer.at(right_idx)->frequency < this->buffer.at(min_idx)->frequency)){
        min_idx = right_idx;
    }

    if(min_idx != index){
        std::swap(this->buffer.at(index), this->buffer.at(min_idx));
        this->minHeapify(min_idx);
    }
}

node* minheap::getNodeAt(int index) {
    return this->buffer.at(index);

}

node* minheap::extractMin() {
    node *node = this->getNodeAt(0x0);
    this->removeNodeAt(0x0);
    return node;
}

void minheap::enqueue(node *pnode) {
    this->insertNode(pnode);
}

