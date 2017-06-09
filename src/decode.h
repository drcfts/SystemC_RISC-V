/*
 * decode.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts
 */

#ifndef DECODE_H_
#define DECODE_H_

#include <systemc.h>
#include "breg_if.h"
#include "mem_if.h"
#include "shared.h"

SC_MODULE(decode){

	sc_port <breg_if> p_breg;

	sc_fifo_in < contexto* > fetch_decode;
	sc_fifo_out< contexto* > decode_execute;

	void decode_method(){
		while(true){
			recebimento = fetch_decode.read();
			escrita = recebimento;

			ri = recebimento->ri;
			rd = recebimento->rd;

			escrita->op = (ri >> 12) & 0xF;
			escrita->rs = (ri >> 8) & 0xF;
			escrita->rt = (ri >> 4) & 0xF;
			escrita->rd = ri & 0xF;
			escrita->k4 = (ri & 0x8)?(0xFFF0 | escrita->rd) : escrita->rd;
			escrita->k8 = (char) (ri & 0xFF);

			decode_execute.write(escrita);
		}
	}

	SC_CTOR(decode){
		recebimento = new contexto();
		escrita = new contexto();
		SC_THREAD(decode_method);
	}

private:
		contexto *recebimento, *escrita;
		unsigned short ri, rd;
};



#endif /* DECODE_H_ */
