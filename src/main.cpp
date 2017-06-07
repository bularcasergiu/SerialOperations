#include <stdio.h>
#include <iostream>
#include <unistd.h>
//#include "SerialClass.h"	// Library described above
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
            //std::cout<<"%s\n",incomingData<<std::endl;
            int dataLength = 255;
            int readResult = 0;

            while(SP->IsConnected())
            {
                readResult = SP->ReadData(incomingData,dataLength);
                // std::cout<<"Bytes read: (0 means no data available) %i\n",readResult<<std::endl;
                incomingData[readResult] = 0;

                std::cout<<incomingData<<std::endl;

                Sleep(20);
            }
        }
        else if(argument=="writeSerial"){
            while(SP->IsConnected())
            {
                char incomingData[256] = "tessssst";			// don't forget to pre-allocate memory
                //std::cout<<"%s\n",incomingData);
                int dataLength = 255;
                bool writeResult = SP->WriteData(incomingData,dataLength);
                // std::cout<<"Bytes read: (0 means no data available) %i\n",readResult<<std::endl;

                std::cout<<writeResult<<std::endl;

//                Sleep(5);
            }
        }
    }
#endif
#ifdef __linux__
    int readSerialArguments(int argc, const char** argv, SerialLinux* SP){
        std::string argument = argv[1];
        if(argument=="readSerial"){
            char incomingData[256] = "";			// don't forget to pre-allocate memory
            //std::cout<<"%s\n",incomingData<<std::endl;
            int dataLength = 255;
            int readResult = 0;

            while(SP->IsConnected())
            {
                readResult = SP->ReadData(incomingData,dataLength);
                // std::cout<<"Bytes read: (0 means no data available) %i\n",readResult<<std::endl;
                incomingData[readResult] = 0;

                std::cout<<incomingData<<std::endl;

                usleep(25);
            }
        }
        else if(argument=="writeSerial"){
            while(SP->IsConnected())
            {
                char incomingData[256] = "tessssst";			// don't forget to pre-allocate memory
                //std::cout<<"%s\n",incomingData);
                int dataLength = 255;
                bool writeResult = SP->WriteData(incomingData,dataLength);
                // std::cout<<"Bytes read: (0 means no data available) %i\n",readResult<<std::endl;

                std::cout<<writeResult<<std::endl;

//                usleep(5);
            }
        }
    }
#endif
}

int main(int argc, const char** argv) {
//    std::cout<<"Welcome to the serial test app!\n\n"<<std::endl;

    #if defined _WIN32 || defined __CYGWIN__
    Serial* SP = new Serial("\\\\.\\COM3");    // adjust as needed
    #endif
    #ifdef __linux__
    SerialLinux* SP = new SerialLinux("\\\\.\\COM3");    // adjust as needed
    #endif


    if (SP->IsConnected())
//        std::cout<<"We're connected"<<std::endl;

    readSerialArguments(argc, argv, SP);

    return 0;
}