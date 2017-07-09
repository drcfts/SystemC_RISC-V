/*
 * fetch.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts
 */

#ifndef FETCH_H_
#define FETCH_H_

#include <systemc.h>
#include "shared.h"
#include "mem_if.h"
#include "breg_if.h"
#include "SHELL_MEM_RISC_if.h"
#define RASTREIA_PC

//Criar uma classe memoria que implementa interface com metodos de leitura
//e escrita para ser acessado (por ponteiro) pelos metodos fetch
//e execute
SC_MODULE(fetch){
	//sc_port <mem_if> p_mem;
	sc_port <breg_if> p_breg;
	sc_port<shell_mem_risc_if> p_mem;

	sc_fifo_in < contexto*> execute_fetch;
	sc_fifo_out < contexto* > fetch_decode;

	void fetch_method(){
		while(true){
			recebimento = execute_fetch.read();
			escrita = recebimento;
			PC = (p_breg->read(31));

			#ifdef RASTREIA_PC
					cout << "PC = " << PC << endl;
			#endif
					escrita->ri = p_mem->read(PC);
					//Registrador 31 = PC
					p_breg->write(31, PC +1);
					//Instrucao que nao faz sentido lw $0, $0
					//Interrompe execucao
					if(escrita->ri == 0){
						p_breg->dump_breg();
						sc_stop();
						exit(0);
					} //if
			fetch_decode.write(escrita);
		} // while
	}


	SC_CTOR(fetch){
		recebimento = new contexto();
		escrita = new contexto();
		SC_THREAD(fetch_method);
	}

private:
		contexto *escrita;
		contexto *recebimento;
		uint32_t PC;
};



#endif /* FETCH_H_ */
