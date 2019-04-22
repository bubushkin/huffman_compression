/*
 * bitstreamer.h
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#ifndef BITSTREAMER_H_
#define BITSTREAMER_H_

#include <iostream>

using std::istream;
using std::ostream;

class bitstreamer {

private:
	istream &ifp;
	unsigned char inbuffer;
	int inbitcount;
	ostream &ofp;
	unsigned char outbuffer;
	int outbitcount;


public:
	bitstreamer(istream &is, ostream &os):
		ifp(is), ofp(os), inbuffer(0), outbuffer(0), inbitcount(8), outbitcount(0) {}

	void padding();

	void flush();

	void writeBit(unsigned int bit);

	void fill();

	unsigned int readBit();
};

#endif /* BITSTREAMER_H_ */
