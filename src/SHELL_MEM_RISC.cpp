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
        lw(address,constante);
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
		lh(address,constante);
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
		lhu(address,constante);
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
		lb(address,constante);
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
		lbu(address,constante);
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
		sw(address,constante,dado);
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
		sh(address,constante,dado);
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
		sb(address,constante,dado);
	} else {// se não retornar o dado
		cout << "OK! " << endl;
	}
}

int32_t shell_mem_risc::read(const uint32_t address){
	if ((address) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}
	return mem_ptr[address];
}

void shell_mem_risc::write_mem(const unsigned address, uint32_t data){
	mem_ptr[address] = data;

}

void shell_mem_risc::dump_mem(int inicio, int fim, char formato){
	switch (formato) {
		case 'h':
		case 'H':
			for (int32_t i = inicio; i <= fim; i+=4)
				printf("%d\t%8x\n", i, lw(i, 0));
			break;
		case 'd':
		case 'D':
			for (int32_t i = inicio; i <= fim; i+=4)
				printf("%d\t%8d\n", i, lw(i, 0));
			break;
		default:
			break;
	}
}




