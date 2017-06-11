/*
 * breg_if.h
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#ifndef BREG_IF_H_
#define BREG_IF_H_

#include "systemc.h"
#include <stdint.h>

struct breg_if : public sc_interface{

	virtual int32_t
	read(const unsigned address) = 0;

	virtual void
	write(const unsigned address, int32_t dado) = 0;

	virtual void
	dump_breg() = 0;

};




#endif /* BREG_IF_H_ */
