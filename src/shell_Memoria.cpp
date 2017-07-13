#include "nocdebug.h"
#include "shell_Memoria.h"

MemoriaShell::MemoriaShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MemoriaShell::_threadRun()
{
	uint32_t rec;
	uint32_t send;
	int flag_save = 0;

    for (;;) {
    	flag_save = 0;

        // Reading
        std::vector<uint32_t> payload;
        int payloadSrc;
	// payload = ShellIn.read();    
        NoCDebug::printDebug("Shell Memoria <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        NoCDebug::printDebug("Shell Memoria -> Memoria", NoCDebug::NI);
        rec = payload.at(0);
        shellOut.write(rec);
        //Se for save, tem-se endereco e dado
        if(rec == _SB || rec == _SW || rec == _SH){
        	flag_save = 1;
        	//Le addr
        	rec = payload.at(1);
        	//Coloca addr
        	shellOut.write(rec);
        	//Le dado
        	send = payload.at(2);
        	//Coloca dado
        	shellOut.write(send);
        }
        else{
        	//Le addr
        	rec = payload.at(1);
        	//Coloca addr
        	shellOut.write(rec);
        }

        // Writing
        NoCDebug::printDebug("Shell Memoria <- Memoria", NoCDebug::NI);
        send = shellIn.read();
        payload.clear();
        payload.push_back(send);
        //Se for load, tem dado
        if(!flag_save){
        	send = shellIn.read();
        	payload.push_back(send);
        }
        int payloadDst = 0;
        NoCDebug::printDebug("Shell Memoria -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}

