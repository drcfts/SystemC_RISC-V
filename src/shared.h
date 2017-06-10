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
		  ri,
		  opcode,
		  pc,
		  funct7,
		  funct3,
		  Imm_I,
		  Imm_U,
		  Imm_S,
		  Imm_B,
		  Imm_J,
		  shamt,	
		  rs1,
		  rs2,
		  rd;
	bool
		wr_men, // acho que nao precisa
		rd_men, // acho que nao precisa 
		wr_breg; // acho que nao precisa
	//bool
		// wren;

} contexto;


// OPCODES QUE NÃO SE ALTERAM ....
enum i_FORMAT {
	TIPO_R=0x33,
	TIPO_S= 0x23,
	TIPO_I2_SHAMT=0x13,	
	TIPO_B = 0x63,
	TIPO_I_REST0 =0x3,
	TIPO_I_JALR =0x43,
	TIPO_JAL =0x6F,
	TIPO_JALR = 0x67
	 	
};
// Opcodes referentes ao tipo J - notar que o opcode já resolve
enum Opcode_U{
u_LUI = 0x37,
u_AUIPC=0X17
};
// func3 para definir tipoB
enum funct3_tipoB{
f3_BEQ = 0x0,
f3_BNE = 0x1,
f3_BLT = 0x4,
f3_BGE = 0x5,
f3_BLTU = 0x6,
f3_BGEU = 0x7
};
// definir tipoI,ADDI ...
enum funct3_tipoI_2{
f3_ADDI = 0x0,
f3_SLTI = 0x2,
f3_SLTIU = 0x3,
f3_XORI = 0x4,
f3_ORI = 0x6,
f3_ANDI = 0x7
};
// definir tipoI, lw
enum funct3_tipoI_1{
f3_LB = 0x0,
f3_LH = 0x1,
f3_LW = 0x2,
f3_LBU = 0x4,
f3_LHU = 0x5
};
// funções stores
enum funct3_tipoS{
f3_SB = 0x0,
f3_SH = 0x1,
f3_SW = 0x2
};
enum funct7_tipoR{
f7_RESTO = 0x00,
f7_SRA_SUB = 0x20
};
enum funct7_tipoI_shamt{
f7_RESTO_I = 0x00,
f7_SRAI = 0x20
};
enum funct3_tipoI_shamt{
f3_SLLI = 0x1,
f3_SRLI_SRAI = 0x5
};
enum funct3_tipoR{
f3_ADD_SUB = 0x0,
f3_SLL = 0x1,
f3_SLT = 0x2,
f3_SLTU = 0x3,
f3_XOR = 0x4,
f3_SRL_SRA = 0x5,
f3_OR = 0x6,
f3_AND = 0x7
};

#endif /* SHARED_H_ */
