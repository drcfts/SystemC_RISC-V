/*
' * execute.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts e litlle toin
 */


#include <systemc.h>
#include "breg_if.h"
#include "shared.h"
#include "SHELL_MEM_RISC_if.h"

SC_MODULE(execute){
	sc_port <shell_mem_risc_if> p_mem;
	sc_port <breg_if> p_breg;

	// sc_port<shell_mem_risc_if> p_shell;

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
			e_imm_S = recebimento->Imm_S;
			e_shamt = recebimento->shamt;
			// switch
			//Caso R:
			//	Caso Funct 3:
			//		Caso Funct 7:
			//Caso I:
			//	Caso Funct 3:
			//		Caso Func 7:
			//Caso B:
			//	Caso Funct 3:
			//Caso S/ADDI...:
			//	Caso Funct 3:
			switch(e_op){

				case  TIPO_LUI:
						// operacao lui
						//20 MSB pro reg, 12 LSB = 0
						p_breg->write(e_rd, (e_imm_U<<20) & 0xFFFFF000);
				break;	
				case  TIPO_AUIPC:
						// operacao AUIPC
						//PC = reg(31)
						_t1 = ((e_imm_U<<20) & 0xFFFFF000) +
						p_breg->read(31);
						//Adiciona offset e escreve no PC e no Rd
						p_breg->write(31, _t1);
						p_breg->write(e_rd, _t1);
				break;
				case  TIPO_JAL: 
						// operacao JAL
						p_breg->write(e_rd, p_breg->read(31));
						p_breg->write(31, e_imm_J);
				break;
				case  TIPO_JALR:
						// operacao JALR
						if(e_funct3 == 0x0){
							// operacao JALR
							_t1 = e_imm_I + p_breg->read(e_rs1);
							//Seta BIT0 como 0
							_t1 = _t1 & 0xFFFFFFFE;
							p_breg->write(e_rd, p_breg->read(31));
							p_breg->write(31, _t1);
						}
				break;
				case  TIPO_B: 
				// branches -> tipo B
					switch(e_funct3){
						case f3_BEQ:
						// funcao beq
							if (p_breg->read(e_rs1) == p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						case f3_BNE:
						// funcao bne
							if (p_breg->read(e_rs1) != p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						case f3_BLT:
						// funcao bLT
							if (p_breg->read(e_rs1) < p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						case f3_BGE:
						// funcao bGe
							if (p_breg->read(e_rs1) >= p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						case f3_BLTU:
						// funcao bLTU
							if ((unsigned)p_breg->read(e_rs1) < (unsigned)p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						case f3_BGEU:
						// funcao bGeU
							if ((unsigned)p_breg->read(e_rs1) >= (unsigned)p_breg->read(e_rs2)) {
								_t1 = e_imm_B << 1;
								_t1 += p_breg->read(31);
								p_breg->write(31, _t1);
							}
						break;
						default:
						break;
									}// fim SWITCHh funct3 - Branch		
				break;
				case TIPO_I_REST0 :
				// operacoes loads
					switch(e_funct3){
						case f3_LB: 
							// load byte
							p_breg->write(e_rd, p_mem->lb(p_breg->read(e_rs1), e_imm_I));
						//	p_breg->write(e_rd, p_shell->lb(p_breg->read(e_rs1), e_imm_S));

							break;
						case f3_LH: 
							// load half
							p_breg->write(e_rd, p_mem->lh(p_breg->read(e_rs1), e_imm_I));
						//	p_breg->write(e_rd, p_shell->lh(p_breg->read(e_rs1), e_imm_S));
							break;
						case f3_LW: 
							// load word
							p_breg->write(e_rd, p_mem->lw(p_breg->read(e_rs1), e_imm_I));
					   //	p_breg->write(e_rd, p_shell->lw(p_breg->read(e_rs1), e_imm_S));

							break;
						case f3_LBU: 
							// load byte unsigned
							p_breg->write(e_rd, p_mem->lbu(p_breg->read(e_rs1), e_imm_I));
						//	p_breg->write(e_rd, p_shell->lbu(p_breg->read(e_rs1), e_imm_S));

							break;
						case f3_LHU: 
							// load half unsigned
							p_breg->write(e_rd, p_mem->lhu(p_breg->read(e_rs1), e_imm_I));
						//  p_breg->write(e_rd, p_shell->lhu(p_breg->read(e_rs1), e_imm_S));

							break;
							// default?
					} // fim switch funct3 - loads
				break;
				case TIPO_S:
				// funcoes do tipo store
					switch(e_funct3){
						case f3_SB: 
						// store byte
						p_mem->sb((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));
						//p_shell->sb((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));

						break;
						case f3_SH: 
						// store half
						p_mem->sh((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));
						//p_shell->sh((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));

						break;
						case f3_SW: 
						// store word
						p_mem->sw((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));
						//p_shell->sw((p_breg->read(e_rs1)), e_imm_S, p_breg->read(e_rs2));

						break;	
						// default?	
					} // fim switch funct3 - STORE
				break;
				case TIPO_I2_SHAMT:
				// tipos i e shifts
					switch(e_funct3){
						case f3_ADDI:
							//Se for NOP
							if(!e_rs1 && !e_rd && !e_imm_I){
								break;
							}
						// addi
						_t1 = e_imm_I + p_breg->read(e_rs1);
						p_breg->write(e_rd, _t1);
						break;

						case f3_SLTI:
						// slti
							if(p_breg->read(e_rs1) < e_imm_I){
								p_breg->write(e_rd, 1);
							}
							else{
								p_breg->write(e_rd, 0);
							}
						break;

						case f3_SLTIU:
						// sltiu
							//Primeiro faz extensao de sinal p/ 32 bits,
							//dps trata os dois como sem sinal
							_t1 = e_imm_I;
							if((unsigned)p_breg->read(e_rs1) < (unsigned)_t1){
								p_breg->write(e_rd, 1);
							}
							else{
								p_breg->write(e_rd, 0);
							}
						break;

						case f3_XORI:
						// XORI
						_t1 = e_imm_I ^ p_breg->read(e_rs1);
						p_breg->write(e_rd, _t1);
						break;

						case f3_ORI:
						// ORI
						_t1 = e_imm_I | p_breg->read(e_rs1);
						p_breg->write(e_rd, _t1);
						break;

						case f3_ANDI:
						// ANDI
						_t1 = e_imm_I & p_breg->read(e_rs1);
						p_breg->write(e_rd, _t1);
						break;

						case f3_SRLI_SRAI:
						// srli ou srai
							if(e_funct7 == f7_SRAI){
								// srai
								p_breg->write(e_rd, (p_breg->read(e_rs1)) >> e_shamt);
							}
							if(e_funct7 == f7_RESTO_I){
								// SRLI
								_t1 =	(unsigned)(p_breg->read(e_rs1)) >> e_shamt;
								p_breg->write(e_rd, _t1);
							}
						break;

						case f3_SLLI:
						// SLLI
							if(e_funct7 == f7_RESTO_I ){
								// SLLI
								p_breg->write(e_rd, (p_breg->read(e_rs1))<< e_shamt);
							}
						break;
					} //switch funct 3
					break;
				case TIPO_R:

					switch(e_funct7){
							case f7_RESTO:
								switch(e_funct3){
									case f3_ADD_SUB:
									// add
									p_breg->write(e_rd, (p_breg->read(e_rs1)+ p_breg->read(e_rs2)));
									break;	

									case f3_SLL:
									// Sll
										//Shamt = 5 LSB do registrador RS2
									p_breg->write(e_rd, (p_breg->read(e_rs1))<< (p_breg->read(e_rs2) & 0x1F));
									break;	

									case f3_SLT:
									// SlT
									p_breg->write(e_rd, (p_breg->read(e_rs1)< p_breg->read(e_rs2)));
									break;

									case f3_SLTU:
									// SLT unsigned
									p_breg->write(e_rd, ((unsigned)p_breg->read(e_rs1)<(unsigned)p_breg->read(e_rs2)));
									break;

									case f3_XOR:
									// xor
									p_breg->write(e_rd, (p_breg->read(e_rs1) ^ p_breg->read(e_rs2)));
									break;

									case f3_SRL_SRA:
									// SRL
									_t1 =	(unsigned)(p_breg->read(e_rs1)) >> (p_breg->read(e_rs2) & 0x1F);
									p_breg->write(e_rd, _t1);
									break;

									case f3_OR:
									// or
									p_breg->write(e_rd, (p_breg->read(e_rs1) | p_breg->read(e_rs2)));
									break;

									case f3_AND:
									// and
									p_breg->write(e_rd, (p_breg->read(e_rs1) & p_breg->read(e_rs2)));
									break;

								} // fim funct 3 -> f7 resto
							break;
							case f7_SRA_SUB:
								switch(e_funct3){
         							case f3_ADD_SUB:
									// sub
         							p_breg->write(e_rd, (p_breg->read(e_rs1) - p_breg->read(e_rs2)));
									break;
									case f3_SRL_SRA:
									// SRA
									p_breg->write(e_rd, (p_breg->read(e_rs1)) >> (p_breg->read(e_rs2) & 0x1F));
									break;
								}// fim funct 3 -> f7 SRA_SUB

							break;
					} //fim e_funct 7
					break;
				}// fim switch e_op
				//p_breg->write(0, 0);
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
		int32_t e_imm_I,e_imm_U,e_imm_S,e_imm_B,e_imm_J;
		int32_t _t1;


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
