/*
 * shell_RISCV.cpp
 *
 *  Created on: 4 de jul de 2007
 *      Author: drcfts
 */

#include "shell_RISCV.h"
#include "nocdebug.h"

ShellRISCV::ShellRISCV(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void ShellRISCV::_threadRun()
{
	std::vector<uint32_t>   send, rec;
    uint32_t overhead;
    for (;;) {
        // Writing
        NoCDebug::printDebug("ShellRISC <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        //Payload eh um vetor, send tbm
        //Pega elemento a elemento do send e manda pro payload
        for (unsigned i=0; i<send.size(); i++){
            payload.push_back(send.at(i));
        }
        // DESTINO -> MEMÓRIA, qual o valor ?????????//////
        int payloadDst = 1;
        NoCDebug::printDebug("ShellRISC -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc = 0;
        NoCDebug::printDebug("ShellRISC <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        overhead = payload.at(0);

        rec.push_back(overhead);
        //Se deu certo
        if(overhead){

        	NoCDebug::printDebug("ShellRISC -> Master", NoCDebug::NI);
        	//Como os dois sao vetores, copia-se elemento a elemento
        	for (unsigned i=0; i<payload.size(); i++){
        		rec.push_back(payload.at(i));
        	}
        	shellOut.write(rec);
        }
        //Apos fim das operacoes, limpa payload
        payload.clear();

        //Se n deu certo, n escreve de volta para a Cache

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}

    std::vector<uint32_t> monta_send(uint32_t adress,uint32_t commando)
    {
     std::vector<uint32_t> aux,ans;   
        aux = (commando & 0xFF);
        ans = ((adress & 0x3FF) << 8) | aux;
        return ans;
    }

