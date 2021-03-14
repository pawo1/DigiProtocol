#include <iostream>
#include <string>

#include "../DigiProtocol.h"


int main(int argc, char *argv[]) {

	std::string ID = "", message = "";
	int r=0; // r - for return values

	if(argc > 2 ) {
		std::cout << "Too many arguments were passed to the program." << "\n";
		std::cout << "\"send [ID]\" - specifying the ID is optional, otherwise connecting to the default device" << "\n";
		return 1;
	} else  if(argc == 2) {
		ID = argv[1];
	}

	DigiProtocol digiSpark(ID);
	

	if(digiSpark.isOpen() != true) {
		std::cout << "Couldn't find the device";
		if(ID != "") std::cout << " with ID: " << ID;
		std::cout << "\n";
		return 1;
	}
	
	r = digiSpark.readID(ID); 
	
	if(r < DP_NO_ERROR) {
		std::cout << "Error during reading ID!" << "\n";
		return 1;
	} else { 
		std::cout << "Connected with: " << ID << "\n";
	}
	
	std::cout << "Type Ctrl+C or Ctrl+Z to exit the program" << "\n";

    while(1) {
		message="";
        r = digiSpark.readMessage(message, 1000);
        if(r > 0) std::cout << "Incoming: " << message << "\n";
        else if(r < 0) std::cout << "ERROR NO: " << r << "\n";
    }

    return 0;
}


