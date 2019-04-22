/*
 * bitstreamer.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#include "bitstreamer.h"

void bitstreamer::padding() {
  if( this->bitcount )
    for(int i = this->bitcount; i <= 8; i++)
      this->writeBit(0);
}

void bitstreamer::flush() {

  this->fp.put(this->buffer);
  this->buffer  = 0;
  this->bitcount = 0;

}

void bitstreamer::writeBit( unsigned int bit ) {
  if( this->bitcount == 8 )
	  this->flush();
  int mask = ~(1 << this->bitcount);
  this->buffer = (this->buffer & mask) | (bit << this->bitcount);
  this->bitcount++;
}

void bitstreamer::fill() {
  this->buffer = this->fp.get();
  if(this->fp.eof()) {
	  this->bitcount = -1;
	  return;
  }
  this->bitcount = 0;
}

unsigned int bitstreamer::readBit() {
  if(this->bitcount == 8 )
    this->fill();

  if(this->bitcount == -1)
    return 2;

  unsigned int nextBit = ((this->buffer & (1 << this->bitcount)) >> this->bitcount);
  this->bitcount++;

  return nextBit;
}
