#include "io.h"

char* progname = "";

void fatal(const char *msg) {
	if (errno != 0) {
		fprintf(stderr, "%s: %s: %s\n", progname, msg, strerror(errno));
	} else {
		fprintf(stderr, "%s: %s\n", progname, msg);
	}
	fflush(stdout);
	fflush(stderr);
	abort();
}

void setProgName(char *name) {
	progname = name;
}


void ewrite(int fd, const void *buf, size_t nbytes) {
	//printf("ewrite fd=%x buf=%p size=%ld \n", fd, buf, nbytes);
	size_t written = write(fd, buf, nbytes);
	if (written < 0) {
		fatal("write");
	}
}


void efgets(char *str, int num, FILE *stream) {
	char* ret = fgets(str, num, stream);
	if (ret == NULL) {
		fatal("read");
	}
}


void checkArgs(int argc, int nArgs, char *msg) {
	if(argc != nArgs+1) {
		fprintf(stderr, "%s: need %d arguments: %s\n", progname, nArgs, msg);
		fflush(stderr);
		abort();
	}
}

static int set_interface_attribs (int fd, int speed, int parity);
static void set_blocking (int fd, int should_block);

int myReadfull( int fd, void *buffer, int nbytes ) {
	memset( buffer, 0, nbytes );
	uint8_t *buffercast = (uint8_t *) buffer;
	int bytesread = 0;
	bytesread = read(fd, buffercast, nbytes);
	while( bytesread < nbytes && bytesread >= 0 ) {
		bytesread += read(fd, &(buffercast[bytesread]), nbytes - bytesread);
	}
	assert(bytesread > 0); // TODO == nbytes?
	return bytesread; // TODO: don't return?
}

int myRead( int fd, void *buffer, int nbytes ) {
	memset( buffer, 0, nbytes );
	uint8_t *buffercast = (uint8_t *) buffer;
	int bytesread = 0;
	bytesread = read(fd, buffercast, nbytes);
	return bytesread;
}



int initSerial(int baudrate, char *devname ) {
	printf("%s: open %s baud%d \n", progname, devname, baudrate);
	int fd = open( devname, O_RDWR | O_NOCTTY | O_SYNC );
	if (fd < 0) {
		fatal("initSerial");
	}
	set_interface_attribs (fd, baudrate, 0);  // set speed to baudrate, 8n1 (no parity)
	set_blocking (fd, 0);                // set non blocking
	return fd;
}

static int set_interface_attribs (int fd, int speed, int parity) {
	struct termios tty;
	memset (&tty, 0, sizeof(struct termios) );
	if (tcgetattr (fd, &tty) != 0) {
		printf("error %d from tcgetattr", errno);
		return -1;
	}

	cfsetospeed (&tty, speed);
	cfsetispeed (&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // ignore break signal
	tty.c_lflag = 0;                // no signaling chars, no echo,
	// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
	// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	//tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0) {
		printf("error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

static void set_blocking (int fd, int should_block) {
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0) {
		printf("error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
		printf("error %d setting term attributes", errno);
}

int myWrite( int fd, const char *format, ...) {
	char buffer[1024];
	memset(buffer, 0, 1024);
	va_list vl;
	va_start( vl, format );
	int ret = vsnprintf( buffer, 1024, format, vl );
	va_end(vl);
	assert( (ret > 0) && (ret < 1024) );
	ewrite( fd, buffer, strlen(buffer) );
	return SUCCESS;
}
