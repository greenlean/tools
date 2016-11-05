/*
 * ttyStream.cpp
 *
 *  Created on: 5 nov. 2016
 *      Author: greenlean
 */

#include "ttyStream.h"

namespace std {

ttyStream::ttyStream() {
	// TODO Auto-generated constructor stub
	dev = -1;
	ready = false;

}

ttyStream::~ttyStream() {
	// TODO Auto-generated destructor stub
	close(this->dev);
	this->dev = -1;
	ready = false;
}


bool ttyStream::openStream(char *device){

	dev = open("/dev/pts/1", O_RDWR | O_NOCTTY | O_NDELAY);
	if (dev == -1){
		perror("open_port: Unable to open file. \n");
		return false;
	}
	else{
		fcntl(dev, F_SETFL, 0);
	}

	return true;
};

bool ttyStream::def_configuration(){

	tcgetattr (this->dev, &this->cfg);

	//baudrate 115200
	cfsetispeed(&this->cfg, B115200);
	cfsetospeed(&this->cfg, B115200);

	//Enable Receiver set local mode
	this->cfg.c_cflag |= (CLOCAL | CREAD);

	//More options (8N1)
	//No parity
	this->cfg.c_cflag &= ~PARENB;
	//No stop bit.
	this->cfg.c_cflag &= ~CSTOPB;
	//Character size 8.
	this->cfg.c_cflag &= ~CSIZE;
	this->cfg.c_cflag |= CS8;

	//Local configuration
	this->cfg.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	//Input configuration
	this->cfg.c_iflag |= (IGNPAR | IGNBRK | IGNCR);
	this->cfg.c_iflag &= ~(IXON | IXOFF | IGNCR);

	//Output Configuraiton
	this->cfg.c_oflag &= ~OPOST;

	return true;
}

bool ttyStream::set_configuration(struct termios &cfg){

	//memcpy(static_cast<void *>(&this->cfg),static_cast<void *>cfg, sizeof(struct termios));
	return true;
}
bool ttyStream::configure(){
	/**/
	//Set new options
	// TCSANOW => Make changes inmediatelly
	tcsetattr(this->dev, TCSANOW, &this->cfg);
	return true;
}

bool ttyStream::closeStream(){
	close(this->dev);
	this->dev = -1;
	return true;
};

bool ttyStream::writeStream(char *buffer, int length){
	int cont = 0;
	if (this->dev != -1){
		if ( (cont = write(this->dev, buffer, length)) != 0)
			return true;
	}
	return false;
}

} /* namespace std */

