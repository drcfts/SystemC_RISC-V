include "systemc.h"

#ifndef CACHE_H
#define CACHE_H

SC_MODULE(cache){
	
	sc_in<sc_uint<32>> address;
	sc_out<sc_uint<32>> data;
	sc_out<sc_bool> hit;

	SC_CTOR(Cache){
		SC_METHOD(get_data)
		sensitive << address;
	}

	void get_data();

	private:

	bool cached_v[512];
	unsigned int cached_tag[512];
	int cached_data[512][16];

	unsigned int address_tag;
	unsigned int address_index;
	unsigned int address_offset;

	void address_handler();

}


#endif // CACHE_H
