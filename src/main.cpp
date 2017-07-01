
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "stdarg.h"
#include "breg.h"
#include "memoria.h"


int sc_main(int argc, char* argv[]){
	fetch Fetch("Fetch");
	decode Decode("Decode");
	execute Execute("Execute");

	mem Memoria("Memoria");
	breg Breg("Breg");

	sc_fifo < contexto* > e_f( 1);
	sc_fifo < contexto* > f_d( 1);
	sc_fifo < contexto* > d_e( 1);


	Fetch.p_mem(Memoria);
	Fetch.p_breg(Breg);
	Fetch.execute_fetch(e_f);
	Fetch.fetch_decode(f_d);

	Execute.p_breg(Breg);
	Execute.p_mem(Memoria);
	Execute.decode_execute(d_e);
	Execute.execute_fetch(e_f);

	Decode.p_breg(Breg);
	Decode.decode_execute(d_e);
	Decode.fetch_decode(f_d);

	contexto *dado_entrada = new contexto();

	// zera pc;
	Breg.write(31, 0);
	e_f.write(dado_entrada);

	sc_start();

	return 0;
}

