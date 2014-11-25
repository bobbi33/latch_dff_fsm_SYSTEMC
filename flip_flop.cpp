#include <systemc.h>

//this is the head file
SC_MODULE(d_ff){
	sc_in<bool> d,clk,s,r;
	sc_out<bool> q,q_b;
	
	void dff_func();
	
	SC_CTOR(d_ff){
		SC_THREAD(dff_func);
		sensitive << clk.posedge_event();
	}
};

//this is the cpp file
void d_ff::dff_func(){
	while(1){
		if(s.read()){
			wait(4,SC_NS);
			q = true;
			wait(4,SC_NS);
			q_b = false;		
		}
		else if(r.read()){
			wait(4,SC_NS);
			q = false;
			wait(4,SC_NS);
			q_b = true;
		}
		else{
			wait(4,SC_NS);
			q = d.read();
			wait(4,SC_NS);
			q_b = !d.read();
		}
	wait();
	}
}
