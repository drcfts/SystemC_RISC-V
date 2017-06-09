/*
 * breg.h
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#ifndef BREG_H_
#define BREG_H_

#include "systemc.h"
#include "breg_if.h"
#include "shared.h"

using namespace std;

//Implementacao da interface de memoria, para se conectar
//com os modulos do RISC16
struct breg : public sc_module, public breg_if {

	int16_t read(const unsigned short address);

	void write(const unsigned short address, int16_t dado);

	void dump_breg();

	void inicializa(){
		for(int i =0; i<16; i++){
			breg_ptr[i] = 0;
		}
	}

	SC_CTOR(breg){
		breg_ptr = new int16_t[16];
		SC_THREAD(inicializa);
	}

private:
	int16_t *breg_ptr;
};



#endif /* BREG_H_ */
