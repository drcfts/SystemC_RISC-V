#include "nocdebug.h"
#include "shell_Memoria.h"

MemoriaShell::MemoriaShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MemoriaShell::_threadRun()
{
	std::vector<uint32_t> rec;
	std::vector<uint32_t> send;
    for (;;) {
        // Reading
        std::vector<uint32_t> payload;
        int payloadSrc;
        NoCDebug::printDebug("Shell Memoria <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        for (unsigned i=0; i<payload.size(); i++){
        	rec.push_back(payload.at(i));
        }
        NoCDebug::printDebug("Shell Memoria -> Memoria", NoCDebug::NI);
        shellOut.write(rec);

        // Writing
        NoCDebug::printDebug("Shell Memoria <- Memoria", NoCDebug::NI);
        send = shellIn.read();
        payload.clear();
        for (unsigned i=0; i<send.size(); i++){
        	payload.push_back(send.at(i));
        }
        int payloadDst = 0;
        NoCDebug::printDebug("Shell Memoria -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();
    }
}

