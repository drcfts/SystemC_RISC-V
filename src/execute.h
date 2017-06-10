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

			e_rs2 = recebimento->rs2;
			e_rs1 = recebimento-> rs1;
			e_rd = recebimento->rd;
			e_op = recebimento-> opcode;
			e_funct7 = recebimento->funct7;
			e_funct3 = recebimento->funct3;
			e_imm_I = recebimento->Imm_I;
			e_imm_U = recebimento->Imm_U;
			e_imm_J = recebimento->Imm_J;
			e_imm_B = recebimento->Imm_B;
			e_shamt = recebimento->shamt;
			// switch
			switch(e_op){

				case  u_LUI: 
						// operacao lui
				break;	
				case  u_AUIPC: 
						// operacao AUIPC
				break;
				case  TIPO_JAL: 
						// operacao JAL
				break;
				case  TIPO_I_JALR: 
						// operacao JAL
						if(e_funct3 == 0x0){
							// operacao JAL				
						}
				break;
				case  TIPO_B: 
				// branches -> tipo B
					switch(e_funct3){
						case f3_BEQ:
						// funcao beq
						break;
						case f3_BNE:
						// funcao bne
						break;
						case f3_BLT:
						// funcao bLT
						break;
						case f3_BGE:
						// funcao bGe
						break;
						case f3_BLTU:
						// funcao bLTU
						break;
						case f3_BGEU:
						// funcao bGeU
						break; // default?
									}// fim SWITCHh funct3 - Branch		
				break;
				case TIPO_I_REST0 :
				// operacoes loads
					switch(e_funct3){
						case f3_LB: 
						// load byte
						break;
						case f3_LH: 
						// load half
						break;
						case f3_LW: 
						// load word
						break;	
						case f3_LBU: 
						// load byte unsigned
						break;
						case f3_LHU: 
						// load half unsigned
						break;
							// default?
					} // fim switch funct3 - loads
				break;
				case TIPO_S:
				// funcoes do tipo store
					switch(e_funct3){
						case f3_SB: 
						// store byte
						break;
						case f3_SH: 
						// store half
						break;
						case f3_SW: 
						// store word
						break;	
						// default?	
					} // fim switch funct3 - STORE
				break;
				case TIPO_I2_SHAMT:
				// tipos i e shifts
					switch(e_funct3){
						case f3_ADDI:
						// addi 	
						break;
						case f3_SLTI:
						// slti
						break;
						case f3_SLTIU:
						// sltiu
						break;
						case f3_XORI:
						// XORI
						break;
						case f3_ORI:
						// ORI
						break;
						case f3_ANDI:
						// ANDI
						break;
						case f3_SRLI_SRAI:
						// srli ou srai
							if(e_funct7 == f7_SRAI){
								// srai
							}
							if(e_funct7 == f7_RESTO_I){
								// SRLI
							}
						break;
						case f3_SLLI:
						// SLLI
							if(e_funct7 == f7_RESTO_I ){
								// SLLI
							}
						break;
				case TIPO_R:

					switch(e_funct7){

							case f7_RESTO:
								switch(e_funct3){
									case f3_ADD_SUB:
									// add
									break;	
									case f3_SLL:
									// Sll
									break;	
									case f3_SLT:
									// SlT
									break;
									case f3_SLTU:
									// SlTU
									break;
									case f3_XOR:
									// xor
									break;
									case f3_SRL_SRA:
									// SRL
									break;
									case f3_OR:
									// or
									break;
									case f3_AND:
									// or
									break;
									
								} // fim funct 3 -> f7 resto
							break;
							case f7_SRA_SUB:
								switch(e_funct3){
         							case f3_ADD_SUB:
									// sub
									break;
									case f3_SRL_SRA:
									// SRA
									break;
								}// fim funct 3 -> f7 SRA_SUB

							break;

					}// fim switch funct 7


				break;		
					
					}// fim switch funct3 - imediato




								}// FIM SWITCH 		
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
		unsigned short e_rs1, e_rs2, e_rd, e_op,e_funct3,e_funct7,e_shamt;
		short e_imm_I,e_imm_U,e_imm_S,e_imm_B,e_imm_J;


};

/*	
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
*/
