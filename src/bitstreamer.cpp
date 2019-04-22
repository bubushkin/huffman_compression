/*
 * bitstreamer.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#include "bitstreamer.h"
#include <typeinfo>

void bitstreamer::padding() {
  if( this->outbitcount )
    for(int i = this->outbitcount; i <= 8; i++)
      this->writeBit(0);
}

void bitstreamer::flush() {

  this->ofp.put(this->outbuffer);
  this->outbuffer  = 0;
  this->outbitcount = 0;

}

void bitstreamer::writeBit( unsigned int bit ) {
  if( this->outbitcount == 8 )
	  this->flush();
  int mask = ~(1 << this->outbitcount);
  this->outbuffer = (this->outbuffer & mask) | (bit << this->outbitcount);
  this->outbitcount++;
}

void bitstreamer::fill() {

  this->inbuffer = this->ifp.get();
  if(this->ifp.eof()) {
	  this->inbitcount = -1;
	  return;
  }
  this->inbitcount = 0;
}

unsigned int bitstreamer::readBit() {
  if(this->inbitcount == 8 )
    this->fill();

  if(this->inbitcount == -1)
    return 2;

  unsigned int nextBit = ((this->inbuffer & (1 << this->inbitcount)) >> this->inbitcount);
  this->inbitcount++;

  return nextBit;
}
