/*
 * bitstreamer.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef BITSTREAMER_H_
#define BITSTREAMER_H_

#include <iostream>

using std::fstream;

class bitstreamer {

private:
	unsigned char buffer;
	int bitcount;
	fstream &fp;

public:
	bitstreamer(fstream &stream) :fp(stream), buffer(0), bitcount(0) {}

	void padding();

	void flush();

	void writeBit(unsigned int bit);

	void fill();

	unsigned int readBit();
};

#endif /* BITSTREAMER_H_ */
