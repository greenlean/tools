/*
 * ttyStream.h
 *
 *  Created on: 5 nov. 2016
 *      Author: greenlean
 */

#ifndef TTYSTREAM_H_
#define TTYSTREAM_H_

#include <iostream>
#include <cstring>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <termios.h>

namespace std {

class ttyStream {
private:
	int dev;
	struct termios cfg;
	char deviceName[64];
	char buffer[64];
	bool ready;
public:
	ttyStream();
	virtual ~ttyStream();
	bool openStream(char * device);
	bool def_configuration();
	bool set_configuration(struct termios &cfg);
	bool configure();

	bool closeStream();

	bool writeStream(char *buffer, int length);
	bool readStream(char *buffer, int length);

};

} /* namespace std */

#endif /* TTYSTREAM_H_ */


/*
 *
 class ttyStream{
private:
	int dev;
	struct termios cfg;
	char deviceName[64];
	char buffer[64];
	bool ready;
public:
	ttyStream();
	bool openStream(char * device);
	bool def_configuration();
	bool set_configuration(struct termios &cfg);
	bool configure();

	bool closeStream();

	bool writeStream(char *buffer, int length);
	bool readStream(char *buffer, int length);
};

 *
 */
