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
//com os modulos do RISC-V
struct breg : public sc_module, public breg_if {

	int32_t read(const unsigned address);

	void write(const unsigned address, int32_t dado);

	void dump_breg();

	void inicializa(){
		for(int i =0; i<32; i++){
			breg_ptr[i] = 0;
		}
	}

	SC_CTOR(breg){
		breg_ptr = new int32_t[32];
		SC_THREAD(inicializa);
	}

private:
	int32_t *breg_ptr;
};



#endif /* BREG_H_ */
