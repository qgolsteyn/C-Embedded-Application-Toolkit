#include "Log.h"

int log_state = 1;

void __Log_Enable() {
	log_state = 1;
}

void __Log_Disable() {
	log_state = 0;
}

void __Log_Message(string header, string msg, int level) {
	if(!log_state) return;
	switch (level) {
    	case ERROR:
    		std::cerr << "ERROR - "<< header <<": " << msg << "\n";
    		break;
    	case WARN:
    		std::cout << "WARN - "<< header <<": " << msg << "\n";
    		break;
    	case INFO:
    		std::cout << "INFO - "<< header <<": " << msg << "\n";
    	break;
    	case LOW:
    		std::cout << "LOW - "<< header <<": " << msg << "\n";
    		break;
	}
}
