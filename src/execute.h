/*
 * execute.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts
 */

#include <systemc.h>
#include "breg_if.h"
#include "mem_if.h"
#include "shared.h"

SC_MODULE(execute){
	sc_port <mem_if> p_mem;
	sc_port <breg_if> p_breg;

	sc_fifo_in < contexto* > decode_execute;
	sc_fifo_out < contexto*> execute_fetch;

	void execute_method(){
		while(true){
			recebimento = decode_execute.read();
			escrita = recebimento;

			e_rs = recebimento->rs;
			e_rt = recebimento-> rt;
			e_rd = recebimento->rd;
			e_op = recebimento-> op;
			e_k8 = recebimento->k8;
			e_k4 = recebimento->k4;

			switch (e_op) {
					case i_ADD:   p_breg->write(e_rd, (p_breg->read(e_rs)+ p_breg->read(e_rt)));
								  break;
					case i_SUB:   p_breg->write(e_rd, (p_breg->read(e_rs)- p_breg->read(e_rt)));
									break;
					case i_AND:   p_breg->write(e_rd, (p_breg->read(e_rs)& p_breg->read(e_rt)));
								break;
					case i_OR :   p_breg->write(e_rd, (p_breg->read(e_rs)| p_breg->read(e_rt)));
								break;
					case i_XOR:   p_breg->write(e_rd, (p_breg->read(e_rs)^ p_breg->read(e_rt)));
								break;
					case i_NOT:   p_breg->write(e_rs, ~(p_breg->read(e_rs)));
								break;
					//case i_NOT:   breg[rd] = ~breg[rs]; break;
					case i_ADDi:  p_breg->write(e_rs, (p_breg->read(e_rs)+ e_k8));
								break;
					case i_SHIFT:
								  if (e_k8 < 0) p_breg->write(e_rs, (p_breg->read(e_rs))<< (-e_k8));
								  else p_breg->write(e_rs, (p_breg->read(e_rs)) >> (e_k8));
								  break;

					case i_SLT:  p_breg->write(e_rd, (p_breg->read(e_rs)<p_breg->read(e_rt)));
								break;

					case i_LW:   p_breg->write(e_rd, p_mem->lw(p_breg->read(e_rs) + p_breg->read(e_rt), 0));
					break;

					case i_SW:  p_mem->sw((p_breg->read(e_rs)+p_breg->read(e_rt)), 0, p_breg->read(e_rd));
					break;
					case i_LUI:  p_breg->write(e_rs, e_k8<<8);
					break;
					case i_BEQ:	 if (p_breg->read(e_rs) == p_breg->read(e_rt)) recebimento->pc = recebimento->pc + e_k4;
					break;
					case i_BNE:	 if (p_breg->read(e_rs) != p_breg->read(e_rt)) recebimento->pc = recebimento->pc + e_k4;
					break;
					case i_J:	 recebimento->pc = p_breg->read(e_rs) + e_k8;
					break;
					case i_JAL:	 p_breg->write(15, recebimento->pc);
								 recebimento->pc = p_breg->read(e_rs) + e_k8;
								 break;
				} // switch
				p_breg->write(0, 0);
				escrita->pc = recebimento-> pc;
				execute_fetch.write(escrita);
			} //while

		} // execute_method()

	SC_CTOR(execute){
		recebimento = new contexto();
		escrita = new contexto();
		SC_THREAD(execute_method);
	}

private:
		contexto *recebimento, *escrita;
		unsigned short e_rs, e_rt, e_rd, e_op;
		short e_k4, e_k8;
};


