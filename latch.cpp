#include <systemc.h>

//this is the head file 
SC_MODULE(latch){
	sc_in<bool> d,c;
	sc_out<bool> q,q_b;
	
	void latch_func;
	
	SC_CTOR(latch){
		SC_THREAD(latch_func);
		sensitive << c << d;
	}
};

//this is the cpp file

void latch::latch_func(){
	while(1){
		if(c.read()){
			wait(4,SC_NS);
			q = d.read();
			wait(3,SC_NS);
			q_b = !d.read();		
		}
		wait();	
	}
}
