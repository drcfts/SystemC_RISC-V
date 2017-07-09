#include "shared.h"
#include "SHELL_MEM_RISC.h"
using namespace std;

int32_t shell_mem_risc :: lw(const unsigned address, int32_t constante){


std::vector<uint32_t> aux_send,word_tmp;
uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_load(_LW,address,constante);
    for(int i=0; i < aux_send.size(); i++){
    	shellMEM_RISC_Out.write(aux_send.at(i));
    }
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = shellMEM_RISC_In.read();
    _dado = shellMEM_RISC_In.read();
    if(!_flag){ // se tiver erro retransmite
        lw(address,0);
    } else {// se não retornar o dado
        return (int32_t)_dado; 
    }

}

int32_t shell_mem_risc :: lh(const unsigned address, int32_t constante)
{

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_load(_LH,address,constante);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	_dado = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		lh(address,0);
	} else {// se não retornar o dado
		return (int32_t)_dado;
	}


}

int32_t shell_mem_risc :: lhu(const unsigned address, int32_t constante){
	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_load(_LHU,address,constante);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	_dado = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		lhu(address,0);
	} else {// se não retornar o dado
		return (int32_t)_dado;
	}

}

int32_t shell_mem_risc :: lb(const unsigned address, int32_t constante){
	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_load(_LB,address,constante);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	_dado = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		lb(address,0);
	} else {// se não retornar o dado
		return (int32_t)_dado;
	}
}

int32_t shell_mem_risc :: lbu(const unsigned address, int32_t constante){

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_load(_LBU,address,constante);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	_dado = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		lbu(address,0);
	} else {// se não retornar o dado
		return (int32_t)_dado;
	}

	// se flag erro
	exit(0);

}

void shell_mem_risc ::sw(const unsigned address, int32_t constante, int32_t dado){
	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_store(_SW,address,constante, dado);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		sw(address,0,dado);
	} else {// se não retornar o dado
		cout << "OK! " << endl;
	}
}

void shell_mem_risc ::sh(const unsigned address, int32_t constante, int32_t dado){
	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_store(_SH,address,constante, dado);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		sh(address,0,dado);
	} else {// se não retornar o dado
		cout << "OK! " << endl;
	}
}

void shell_mem_risc :: sb(const unsigned address, int32_t constante, int32_t dado)
{
	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
	// enviando o payload
	aux_send = monta_send_store(_SB,address,constante, dado);
	for(int i=0; i < aux_send.size(); i++){
		shellMEM_RISC_Out.write(aux_send.at(i));
	}
	// supondo que recebe dois argumentos --- flag e ok ;
	_flag = shellMEM_RISC_In.read();
	if(!_flag){ // se tiver erro retransmite
		sb(address,0,dado);
	} else {// se não retornar o dado
		cout << "OK! " << endl;
	}
}
