//
// Created by sebu9426 on 05.06.2017.
//

#include "SerialLinux.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

namespace{
    int
    set_interface_attribs (int fd, int speed, int parity)
    {
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
            std::cout<<"error %d from tcgetattr"<< errno<<std::endl;
            return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
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
            std::cout<<"error %d from tcsetattr"<< errno<<std::endl;
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
            std::cout<<"error %d from tggetattr"<< errno<<std::endl;
            return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
            std::cout<<"error %d setting term attributes"<< errno<<std::endl;
    }
}

SerialLinux::SerialLinux(const char *portName):
    connected(false),
    fd(open (portName, O_RDWR | O_NOCTTY ))
{
    if (fd < 0)
    {
        connected = false;
        std::cout<<"error %d opening %s: %s"<< errno<<portName<<strerror (errno)<<std::endl;
        return;
    }
    else{
        connected = true;
    }

    set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking
}

int SerialLinux::ReadData(char *buffer, unsigned int nbChar)
{
    return  read (fd, buffer, nbChar);

}


bool SerialLinux::WriteData(const char *buffer, unsigned int nbChar)
{

    //Try to write the buffer on the Serial port
//    if(write (fd, buffer, nbChar))
//    {
//        std::cout<<"call linux"<<std::endl;
//        return true;
//    }
    unsigned char cmd[] = "red\r";
//    int n_written = 0,
//            spot = 0;
//
//    do {
//        n_written = write( fd, &cmd[spot], 1 );
//        spot += n_written;
//    } while (cmd[spot-1] != '\r' && n_written > 0);
    std::string str(buffer);
    std::cout<<"call linux"<< str<<std::endl;
    ssize_t writtenBytes = write( fd, buffer, sizeof(buffer));
    tcdrain(fd);
    std::cout<<"biti scrisi"<<writtenBytes<< str<<std::endl;
    if (writtenBytes != sizeof(buffer))
    {
        std::cout << "[AgentHmiEventsQueue::HmiObserver] WARNING write error: "
                  << strerror(errno) << std::endl;
        return false;
    }

return true;


//    else
//        return false;
}

bool SerialLinux::IsConnected()
{
    //Simply return the connection status
    return this->connected;
}