#include "shared.h"
#include "SHELL_MEM_RISC.h"
using namespace std;

int32_t shell_mem_risc :: lw(const unsigned address, int32_t constante){


std::vector<uint32_t> aux_send,word_tmp;
uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_load(_LW,address,constante);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = word_tmp.at(0);
    _dado = word_tmp.at(1);
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
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = word_tmp.at(0);
    _dado = word_tmp.at(1);
   if(!_flag){// se tiver erro retransmite
        lh(address,constante);  
    } else { // se não retornar o dado
        return (int16_t)_dado; 
    }
   
	}

	int32_t shell_mem_risc :: lhu(const unsigned address, int32_t constante){
std::vector<uint32_t> aux_send,word_tmp;
uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_load(_LHU,address,constante);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = word_tmp.at(0);
    _dado = word_tmp.at(1);
     if(!_flag){// se tiver erro retransmite
        lhu(address,constante);  
    } else {// se não retornar o dado
        return _dado; 
    }   

	}

	int32_t shell_mem_risc :: lb(const unsigned address, int32_t constante){

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_load(_LB,address,constante);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = word_tmp.at(0);
    _dado = word_tmp.at(1);
    if(!_flag){// se tiver erro retransmite
        lb(address,constante);  
    } else {// se não retornar o dado
        return (int8_t)_dado; 
    }   


	}
	int32_t shell_mem_risc :: lbu(const unsigned address, int32_t constante){

std::vector<uint32_t> aux_send,word_tmp;
uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_load(_LBU,address,constante);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe dois argumentos --- flag e ok ;
    _flag = word_tmp.at(0);
    _dado = word_tmp.at(1);
        if(!_flag){// se tiver erro retransmite
        lbu(address,constante);  
    } else {// se não retornar o dado
        return _dado; 
    }   


    // se flag erro
    	exit(0);

	}

	void shell_mem_risc ::sw(const unsigned address, int32_t constante, int32_t dado){

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_store(_SW,address,constante,dado);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe um argumento --- flag;
    _flag = word_tmp.at(0);

    if(_flag)
    	cout << "OK! " << endl;
    else{
          // se flag erro
		cout << " não OK! " << endl;
         sw(address,constante,dado);   
    }    

	}

	void shell_mem_risc ::sh(const unsigned address, int32_t constante, int32_t dado){

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_store(_SH,address,constante,dado);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe um argumento --- flag;
    _flag = word_tmp.at(0);

    if(_flag)
    	cout << "OK! " << endl;
    else{
          // se flag erro
        cout << " não OK! " << endl;
         sh(address,constante,dado);   
    }    
	}

	void shell_mem_risc :: sb(const unsigned address, int32_t constante, int32_t dado)
	{

	std::vector<uint32_t> aux_send,word_tmp;
	uint32_t _flag , _dado;
    // enviando o payload
    aux_send = monta_send_store(_SB,address,constante,dado);
    shellMEM_RISC_Out.write(aux_send);
    // recebendo o payload
    word_tmp = shellMEM_RISC_In.read();
    // supondo que recebe um argumento --- flag;
    _flag = word_tmp.at(0);

    if(_flag)
    	cout << "OK! " << endl;
    else{
          // se flag erro
        cout << " não OK! " << endl;
         sb(address,constante,dado);   
    }    
	}
