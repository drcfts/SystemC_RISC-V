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

			escrita->opcode = ri & 0x7F;
			escrita->funct7 = (ri >> 25) & 0x7F;
			escrita->funct3 = (ri >> 12) & 0x7;
			
			escrita->Imm_I = (ri >> 21) & 0xFFF;
			escrita->Imm_S_4 = (ri >> 7) & 0x1F;
			escrita->Imm_S_7 = escrita->funct7;
			escrita->Imm_U = (ri >> 12) & 0xFFFFF;
						
			escrita->rs1 = (ri >> 15) & 0x1F;
			escrita->rs2 = (ri >> 20) & 0x1F;
			escrita->rd =  (ri >> 7) & 0x1F;
			
			escrita->_bit12_tipoB =(ri >> 31) & 0x1;
			escrita->_bit11_tipoB =(ri >> 7) & 0x1;
			escrita->_bit20_tipoJ = escrita->_bit12_tipoB;
			escrita->_bit11_tipoJ =(ri >> 20) & 0x1;
		
			escrita->Imm_B_6 =(escrita->funct7) & 0x7F;
			escrita->Imm_B_4 =(escrita->rd >> 1) & 0xF;
			escrita->Imm_J_8 =  (ri >> 12) & 0xFF;	
			escrita->Imm_J_10 = (ri >> 21) &	0x3FF
/*k
			escrita->op = (ri >> 12) & 0xF;
			escrita->rs = (ri >> 8) & 0xF;
			escrita->rt = (ri >> 4) & 0xF;
			escrita->rd = ri & 0xF;
			escrita->k4 = (ri & 0x8)?(0xFFF0 | escrita->rd) : escrita->rd;
			escrita->k8 = (char) (ri & 0xFF);
*/
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
