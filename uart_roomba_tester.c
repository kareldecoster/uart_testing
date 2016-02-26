#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int fd; /* port file descriptor */
char port[20] = "/dev/ttyO1"; /* port to connect to */
speed_t baud = B115200; /* baud rate */

void roomba_start(int fd){
	char msg[2]={0x80, '\n'};
	write(fd,msg,2);
	return;
}

void roomba_full_mode(int fd){
	char msg[2]={0x84,'\n'};
	write(fd, msg,2);
	return;
}

void roomba_demo(int fd, char demo){
	char msg[3] = {136, 0x09, '\n'};
	write(fd, msg, 3);
	return;
}

void roomba_clean(int fd){
	char msg[2] = {0x87,'\n'};
	write(fd,msg,2);
	return;
}

void roomba_control(int fd){
	char msg[2] = {0x82, '\n'};
	write(fd,msg,2);
	return;

}

int main(){
	fd = open(port, O_RDWR); /* connect to port */

	/* set the other settings (in this case, 115200 8N1) */
	struct termios settings;
	tcgetattr(fd, &settings);

	cfsetospeed(&settings, baud); /* baud rate */
	settings.c_cflag &= ~PARENB; /* no parity */
	settings.c_cflag &= ~CSTOPB; /* 1 stop bit */
	settings.c_cflag &= ~CSIZE;
	settings.c_cflag |= CS8 | CLOCAL; /* 8 bits */
	settings.c_lflag = ICANON; /* canonical mode */
	settings.c_oflag &= ~OPOST; /* raw output */

	tcsetattr(fd, TCSANOW, &settings); /* apply the settings */
	tcflush(fd, TCOFLUSH);

	/* — code to use the port here — */
	char buff[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	char msg[6];
	/*roomba_start(fd);
	sleep(1);	
	read(fd,&buff,6);
	printf("message : %x %x %x %x %x %x \n", buff[0], buff[1], buff[2],buff[3], buff[4], buff[5]);
	roomba_start(fd);
	sleep(1);	
	read(fd,&buff,6);
	printf("message : %x %x %x %x %x %x \n", buff[0], buff[1], buff[2],buff[3], buff[4], buff[5]);
	roomba_start(fd);
	sleep(1);	
	read(fd,&buff,6);
	printf("message : %x %x %x %x %x %x \n", buff[0], buff[1], buff[2],buff[3], buff[4], buff[5]);
	roomba_control(fd);
	sleep(1);
	read(fd,&buff,6);
	printf("message : %x %x %x %x %x %x \n", buff[0], buff[1], buff[2],buff[3], buff[4], buff[5]);
	roomba_full_mode(fd);*/
	msg[0]=0x80;
	msg[1]=0x84;
	msg[3]='\n';
	write(fd,msg,3);
	//read(fd,&buff,2);
	//printf("message : %x %x\n", buff[0], buff[1]);
	/*roomba_clean(fd);*/
	msg[0]=0x8c;
	msg[1]=0x00;
	msg[2]=0x01;
	msg[3]=0x3e;
	msg[4]=0x20;
	msg[5]='\n';
	write(fd,msg,6);
	//read(fd,&buff,5);
	//printf("message : %x %x %x %x %x \n", buff[0], buff[1], buff[2],buff[3], buff[4]);
	msg[0]=0x8d;
	msg[1]=0x00;
	msg[2]='\n';
	write(fd,msg,3);
	//read(fd,&buff,2);
	//printf("message : %x %x\n", buff[0], buff[1]);

	close(fd); /* cleanup */
	return 0;
}
