/*
 * minheap.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef MINHEAP_H_
#define MINHEAP_H_

#include "node.h"

#include <vector>
#include <climits>

using std::vector;

class minheap {

private:
    unsigned int heapsize;
    unsigned int capacity;
    vector<node *> buffer;

    static void destruct(vector<node*> &rbuffer);

public:
	minheap():heapsize(0), capacity(0){
		this->buffer = vector<node*>(UCHAR_MAX + 0x1, (node *)nullptr);
	}
	~minheap();

    void minHeapify(unsigned int);

    node* getNodeAt(int);

    void buildMinHeap(vector<int> &frequencies);

    int getParentIdx(int);
    int getLeftChildIdx(int);
    int getRightChildIdx(int);

    void removeNodeAt(int);

    void enqueue(node *);

    node *extractMin();

    void insertNode(node *);
    void siftUp(int);

    int getSize() const;

    bool isLeafNode(int);

    void printBuffer();
};

#endif /* MINHEAP_H_ */
