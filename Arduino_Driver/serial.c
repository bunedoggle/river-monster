#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#define error_message printf
#define SERIAL_PORT "/dev/ttyAMA0"

int
set_interface_attribs (int fd, int speed, int parity)
{
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0)
    {
      error_message ("error %d from tcgetattr", errno);
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
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
      error_message ("error %d from tcsetattr", errno);
      return -1;
    }
  return 0;
}

void
set_blocking (int fd, int should_block)
{
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0)
    {
      error_message ("error %d from tggetattr", errno);
      return;
    }

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 10;            // .1 second read timeout

  if (tcsetattr (fd, TCSANOW, &tty) != 0)
    error_message ("error %d setting term attributes", errno);
}

int main(int argc, const char *argv[]){

  char *portname = SERIAL_PORT;
  char cmd[265];
  char buf[256];
  int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
  int n,i = 1;
  int forever=1;


  if (fd < 0)
    {
      error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
      return;
    }

  set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
  set_blocking (fd, 0);                // set no blocking

  //write (fd, "@GV#\n", 5);


  if(argc > 1){
    //printf("argc = %i", argc);
    forever = 0;
  }

  do{

    if(!forever){
      //printf("grabbing arg %i which is %s\n", i, argv[i]);
      strcpy(cmd, argv[i++]);
    }
    else{
      printf("cmd> ");
      scanf("%s", cmd);
    }
    //printf("Sending: %s\n", cmd);

    // Not 100% sure why I need this, but I need to wait before sending else I get no response
    write (fd, cmd, strlen(cmd));
    write (fd, "\n", 1);

    // Give the arduino time to respond.  In theory we could be getting 265 bytes at 115200 baud
    // that would take 22222 useconds I believe.
    usleep(22222);
    n = 0;
    n = read (fd, buf, sizeof buf);  // read up to 256 characters if ready to read

    if(n==0){
      printf("@RNo reply#\n");
    }
    else{
      buf[n] = '\0';
      printf("%s", buf);
    }
  }while((argv[i] != '\0') || forever);

}
