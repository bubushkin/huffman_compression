/*
 * node.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: iskandar
 */

#include "node.h"

bool node::operator<( const node &rn ) {
  if( this->count != rn.count )
    return (this->count > rn.count);

  return (this->symbol < rn.symbol);
}
