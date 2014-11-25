//this is the head file
SC_MODULE(mealy_detector){
	sc_in <sc_logic> x;
	sc_in <bool> en, clk, rst;
	sc_out <sc_logic> z;
	
	enum states{reset, got1, got10, got11};
	sc_signal<states> p_state, n_state;
	
	void trans_func();
	void outp_func();
	void seq_func();
	
	SC_CTOR(mealy_detector){
	
		SC_METHOD(trans_func);
		sensitive << p_state << x;
		
		SC_METHOD(outp_func);
		sensitive << p_state << x;
		
		SC_THREAD(seq_func);
		sensitive << clk.posedge_event();	
	}
};

//this is the cpp file
void mealy_detector::trans_func(){
	n_state = reset;
	switch(p_state){
		case(reset): 
			if(x.read() == '1')
				n_state = got1;
			else
				n_state = reset;
		break;
		case(got1):
			if(x.read() == '0')
				n_state = got10;
			else
				n_state = got11;
		break;
		case(got10):
			if(x.read() == '1')
				n_state = got1;
			else
				n_state = reset;
		break;
		case(got11):
			if(x.read() == '1')
				n_state = got11;
			else
				n_state = got10;
		break;	
	}
}

void mealy_detector::outp_func(){
	z = '0';
	switch(p_state){
		case(reset):
			z = '0';
		break;
		case(got1):
			z = '0';
		break;
		case(got10):
			if(x.read() == '1')
				z = '1';
			else
				z = '0';
		break;
		case(got11):
			if(x.read() == '1')
				z = '0';
			else
				z = '1';
		break;	
	}
}
