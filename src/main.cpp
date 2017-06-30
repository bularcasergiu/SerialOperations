#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <memory>
#include <string.h>

#if defined _WIN32 || defined __CYGWIN__
#include "SerialClass.h"
#endif
#ifdef __linux__
#include "SerialLinux.h"
#endif
namespace{
#if defined _WIN32 || defined __CYGWIN__
    int readSerialArguments(int argc, const char** argv, Serial* SP){
        std::string argument = argv[1];
        if(argument=="readSerial"){
            char incomingData[256] = "";			// don't forget to pre-allocate memory
            int dataLength = 255;
            int readResult = 0;

            std::string choice;
            while (SP->IsConnected())
            {
                readResult = SP->ReadData(incomingData,dataLength);
                incomingData[readResult] = 0;
                std::cout<<incomingData<<std::endl;

                Sleep(20);
            }
        }
        else if(argument=="writeSerial"){
            std::string data = argv[2];
            if(SP->IsConnected()){
                const char* incomingData = const_cast<char*>(data.c_str());

//                int dataLength = 255;
                bool writeResult = SP->WriteData(incomingData, (unsigned)strlen(incomingData));
                std::cout<<writeResult<<std::endl;
            }
        }
        return 0;
    }
#endif
#ifdef __linux__
    int readSerialArguments(int argc, const char** argv, SerialLinux* SP){
        std::string argument = argv[1];

        if(argument=="readSerial"){
            char incomingData[256] = "";			// don't forget to pre-allocate memory
            int dataLength = 255;
            int readResult = 0;

            while(SP->IsConnected())
            {
                readResult = SP->ReadData(incomingData,dataLength);
                // std::cout<<"Bytes read: (0 means no data available) %i\n",readResult<<std::endl;
                incomingData[readResult] = 0;

                std::cout<<incomingData<<std::endl;

                usleep(15*1000);
            }
        }
        else if(argument=="writeSerial"){
            std::string data = argv[2];
            if(SP->IsConnected()){
                const char* incomingData = const_cast<char*>(data.c_str());

//                int dataLength = 255;
                std::cout<<"data "<< data<<std::endl;
                bool writeResult = SP->WriteData(incomingData, strlen(incomingData));
                std::cout<<writeResult<<std::endl;
            }
        }
    }
#endif
}

int main(int argc, const char** argv) {

    #if defined _WIN32 || defined __CYGWIN__
    Serial* SP = new Serial("\\\\.\\COM3");    // adjust as needed
    #endif
    #ifdef __linux__
    SerialLinux* SP = new SerialLinux("/dev/ttyACM0");    // adjust as needed
    #endif


    readSerialArguments(argc, argv, SP);
    return 0;
}