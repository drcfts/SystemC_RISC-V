#ifndef SLAVESHELL_H
#define SLAVESHELL_H

#include <systemc.h>
#include "networkinterfacefrontendbase.h"

class MemoriaShell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(MemoriaShell);

    void _threadRun();

public:
    // IO
    sc_fifo_in< std::vector<uint32_t> > shellIn;
    sc_fifo_out< std::vector<uint32_t> > shellOut;

    MemoriaShell(sc_module_name name);
};

#endif // SLAVESHELL_H
