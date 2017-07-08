/*
 * decode.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts e litlle toin
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

			escrita->opcode = ri & 0x7F;
			escrita->funct7 = (ri >> 25) & 0x7F;
			escrita->funct3 = (ri >> 12) & 0x7;
			
			escrita->Imm_I = (ri >> 20) & 0xFFF;
			escrita->Imm_U = (ri >> 12) & 0xFFFFF;
			escrita->rs1 = (ri >> 15) & 0x1F;
			escrita->rs2 = (ri >> 20) & 0x1F;
			escrita->rd =  (ri >> 7) & 0x1F;
			
			_bit12_tipoB =(ri >> 31) & 0x1;
			_bit11_tipoB =(ri >> 7) & 0x1;
			_bit20_tipoJ = _bit12_tipoB;
			_bit11_tipoJ =(ri >> 20) & 0x1;
		
			escrita->shamt = (ri >> 20) & 0x1F;
			
		   imm_B_10_5 = (ri >> 25) & 0x3F;
		   imm_B_4_1 = (ri >>8) & 0xF;

		   imm_J_10 = (ri >> 21) & 0x3FF;
		   imm_J_8 = (ri >>12) & 0xFF;

			//	Imm_S = (funct7,rd); // concatenação .... funciona?			
		    // Imm_B(_bit12_tipoB,_bit11_tipoB,Imm_B_4,Imm_B_6);// concatenação .... funciona?	
     	    // Imm_J(_bit20_tipoJ,Imm_J_8,_bit11_tipoJ,Imm_J_10);// concatenação .... funciona?
		  	

		    ax1 = ((_bit11_tipoJ << 10)  | imm_J_10) & 0x7FF;
		    ax2 = (((imm_J_8 << 11) | ax1)& 0xFFF) ;
		    escrita->Imm_J = ((_bit20_tipoJ << 19) | ax2) & 0xFFFFF;
			///////////////////////////////////	
			escrita->Imm_S = (((escrita->funct7 << 5 )|rd) & 0xFFF);
			/////////////////////////////////////		  	
			xa1  =  ((imm_B_10_5 << 4) | imm_B_4_1) & 0x3FF;
			xa2 = ((_bit11_tipoB << 10) | xa1) & 0x7FF; 
			escrita->Imm_B = ((_bit12_tipoB << 11) | xa2) & 0xFFF;
			
			
/*
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
		uint32_t ax1,ax2,xa1,xa2;
		unsigned short ri, rd;
		short 	imm_B_4_1,  imm_B_10_5,  imm_J_8,  imm_J_10, imm_B_12;
		short _bit11_tipoB;
		short _bit12_tipoB;//poderia ser bool
		short _bit20_tipoJ;//poderia ser bool
		short _bit11_tipoJ;//poderia ser bool

};



#endif /* DECODE_H_ */
