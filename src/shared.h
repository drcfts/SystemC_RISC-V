/*
 * shared.h
 *
 *  Created on: 4 de mai de 2017
 *      Author: drcfts e litlle toin
 */

#ifndef SHARED_H_
#define SHARED_H_

#include <stdint.h>
#include <vector>

const short MAX_MEM=1024;

#define MEM_WORD_SIZE 1024
#define CACHE_WORDS 16
#define CACHE_BLOCKS 256

typedef struct{
	uint32_t ri;
	short ic,
		  opcode,
		  //PC eh um registrador, n precisa de campo
		  //pc,
		  funct7,
		  funct3,
		  shamt,	
		  rs1,
		  rs2,
		  rd;
	int32_t Imm_I,
	  	    Imm_U,
		    Imm_S,
		    Imm_B,
		    Imm_J;

	//bool
		// wren;

} contexto;


// OPCODES QUE NÃO SE ALTERAM ....
enum FORMAT {
	TIPO_R=0x33,
	TIPO_S= 0x23,
	TIPO_I2_SHAMT=0x13,	
	TIPO_B = 0x63,
	TIPO_I_REST0 =0x3,
	//TIPO_I_JALR =0x43,
	TIPO_JAL =0x6F,
	TIPO_JALR = 0x67,
	TIPO_LUI = 0x37,
	TIPO_AUIPC=0X17
	 	
};
/*// Opcodes referentes ao tipo J - notar que o opcode já resolve
enum Opcode_U{
	TIPO_LUI = 0x37,
	TIPO_AUIPC=0X17
};*/

//Opcode 0x63
// func3 para definir tipoB
enum funct3_tipoB{
f3_BEQ = 0x0,
f3_BNE = 0x1,
f3_BLT = 0x4,
f3_BGE = 0x5,
f3_BLTU = 0x6,
f3_BGEU = 0x7
};

//Opcode 0x13
// definir tipoI,ADDI ...
enum funct3_tipoI_2{
f3_ADDI = 0x0,
f3_SLTI = 0x2,
f3_SLTIU = 0x3,
f3_XORI = 0x4,
f3_ORI = 0x6,
f3_ANDI = 0x7,
f3_SLLI = 0x1,
f3_SRLI_SRAI = 0x5
};

enum funct7_tipoI_shamt{
f7_RESTO_I = 0x00,
f7_SRAI = 0x20
};


//Opcode 0x3
// definir tipoI, lw
enum funct3_tipoI_1{
f3_LB = 0x0,
f3_LH = 0x1,
f3_LW = 0x2,
f3_LBU = 0x4,
f3_LHU = 0x5
};

//Opcode 0x13
// funções stores
enum funct3_tipoS{
f3_SB = 0x0,
f3_SH = 0x1,
f3_SW = 0x2
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

//Funct 7 para tipo R
enum funct7_tipoR{
f7_RESTO = 0x00,
f7_SRA_SUB = 0x20
};
// por simplicidade será
// propostos os mesmos opcodes do MIPS 

enum opcodes_func_stores_loads {	
	_LW=0x23, 
	_LB=0x20,
	_LH=0x21, 
	_LBU=0x24,
	_LHU=0x25,	
	_SW=0x2B,	
	_SB=0x28, 
	_SH=0x29,	
};

inline std::vector<uint32_t> monta_send_load(uint32_t comando,uint32_t adress,uint32_t constante)
    		{
	std::vector<uint32_t> ans;
	// inserindo comando na primeira posicao do vector
	ans.push_back(comando);
	// inserindo adress + cte na segunda posicao do vector
	ans.push_back(adress + constante);

	return ans;
    		}


inline std::vector<uint32_t> monta_send_store(uint32_t comando,uint32_t adress,uint32_t constante,uint32_t dado)
    		{
	std::vector<uint32_t> ans;
	// inserindo comando na primeira posicao do vector
	ans.push_back(comando);
	// inserindo adress + cte na segunda posicao do vector
	ans.push_back(adress + constante);
	// por fim insere o dado
	ans.push_back(dado);

	return ans;
    		}


#endif /* SHARED_H_ */
