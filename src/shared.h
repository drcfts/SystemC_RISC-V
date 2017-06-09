/*
 * shared.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts
 */

#ifndef SHARED_H_
#define SHARED_H_

const short MAX_MEM=1024;

typedef struct{
	short ic,
		  k4,
		  k8;
	unsigned short pc,
				   ri,
				   op,
				   rs,
				   rt,
				   rd;

	//bool
		// wren;

} contexto;

enum i_FORMAT {
	TIPO_R=4, TIPO_J=3
};


enum INSTRUCTIONS {
	i_ADD	= 0x2,
	i_SUB	= 0x3,
	i_ADDi	= 0x8,
	i_SHIFT	= 0x9,
	i_AND	= 0x4,
	i_OR	= 0x5,
	i_NOT	= 0xA,
	i_XOR	= 0x6,
	i_SLT	= 0x7,
	i_LW	= 0,
	i_SW	= 0x1,
	i_LUI	= 0xB,
	i_BEQ	= 0xC,
	i_BNE	= 0xD,
	i_J		= 0xE,
	i_JAL	= 0xF
};


#endif /* SHARED_H_ */
