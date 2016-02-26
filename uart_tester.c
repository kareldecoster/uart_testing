#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


int fd; /* port file descriptor */
char port[20] = "/dev/ttyO1"; /* port to connect to */
speed_t baud = B9600; /* baud rate */

int main(){
	fd = open(port, O_RDWR); /* connect to port */

	/* set the other settings (in this case, 9600 8N1) */
	struct termios settings;
	tcgetattr(fd, &settings);

	cfsetospeed(&settings, baud); /* baud rate */
	cfsetispeed(&settings, baud);
	settings.c_cflag &= ~PARENB; /* no parity */
	settings.c_cflag &= ~CSTOPB; /* 1 stop bit */
	settings.c_cflag &= ~CSIZE;
	settings.c_cflag |= CS8 | CLOCAL; /* 8 bits */
	settings.c_lflag = ICANON; /* canonical mode */
	settings.c_oflag &= ~OPOST; /* raw output */

	tcsetattr(fd, TCSANOW, &settings); /* apply the settings */
	tcflush(fd, TCOFLUSH);

	/* — code to use the port here — */
	int i = 0;
	char buff[3]={0x00, 0x00, '\n'};
	while(i< 10){
		write(fd,"KD\n",3);
		read(fd,&buff,sizeof(buff));
		printf("message : %s \n", &buff);
		i++;
	}

	close(fd); /* cleanup */
}
