//
// Created by sebu9426 on 05.06.2017.
//

#ifndef COMREAD_SERIALLINUX_H
#define COMREAD_SERIALLINUX_H


class SerialLinux {
public:
    SerialLinux(const char *portName);
    //Close the connection
    ~SerialLinux();
    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int ReadData(char *buffer, unsigned int nbChar);
    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool WriteData(const char *buffer, unsigned int nbChar);
    //Check if we are actually connected
    bool IsConnected();

private:
    bool connected;
    int fd;

};


#endif //COMREAD_SERIALLINUX_H
