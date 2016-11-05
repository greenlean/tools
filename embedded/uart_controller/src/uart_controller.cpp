//============================================================================
// Name        : uart_controller.cpp
// Author      : Juanma Gomez
// Version     :
// Copyright   : Free
// Description : Hello World in C++, Ansi-style
//
// Test		   : Use socat to build two TTY interfaces linked,
//				$ socat -d -d  pty,raw,echo=0,b115200 pty,raw,echo=0,b115200
//				Open the first one with the software.
//				$ ./uart_controller
//				Open the second one with cat, to receive the commands.
//				$cat /dev/pts/2

//============================================================================

#include <iostream>

#include "ttyStream.h"

using namespace std;


int main() {
	ttyStream tty_test;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	char deviceName[64] = "/dev/pst/1";

	tty_test.openStream(deviceName);
	tty_test.def_configuration();

	tty_test.configure();

	char buffer[64] = "Hola q tal";
	tty_test.writeStream(buffer, 10);

	tty_test.closeStream();
	return 0;
}
