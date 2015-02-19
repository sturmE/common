#pragma once 

#include "address.h"
  

#define MAX_PACKET_SIZE 1024


#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

 #if PLATFORM == PLATFORM_WINDOWS

    #include <winsock2.h>
    #pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>

#endif


class Socket {
private:
    int _handle;
    bool _isBlocking;
public:
    Socket();
    ~Socket();

    ///    Port == 0 if dont care
    bool open(unsigned short port);
    void close();
    bool setTimeout(int ms);
    bool setBlocking(bool blocking);
    bool setBroadcast(bool broadcast);
    bool isBlocking() const;
    bool isOpen() const;
    bool send(const Address& dest, const void* buffer, int size);
    int receive(Address & sender, void * data, int size);
};