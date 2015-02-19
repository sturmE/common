#include "socket.h"

Socket::Socket() {
    _handle = -1;
    _isBlocking = true;    
}

Socket::~Socket() {
    close();
}

bool Socket::setBlocking(bool blocking) {
 #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int opts;

    opts = fcntl(_handle,F_GETFL);
    if (opts < 0) {        
        return false;
    }

    blocking ? opts = opts & (~O_NONBLOCK) : opts = (opts | O_NONBLOCK);
    if (fcntl(_handle,F_SETFL,opts) < 0) {    
        return false;
    }
    
    return true;

#elif PLATFORM == PLATFORM_WINDOWS

    DWORD setting = blocking ? 1 : 0;
    if (ioctlsocket( _handle, FIONBIO, &setting ) != 0 ) {
       // printf( "failed to set non-blocking socket\n" );
        return false;
    }

#endif

    _isBlocking = blocking;
    return true;
}

bool Socket::isBlocking() const {
    return _isBlocking;
}

bool Socket::setBroadcast(bool bcast) {
    int broadcast = bcast ? 1 : 0;
    if(setsockopt(_handle, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(int))) {
        perror("Error: setsockopt call failed");
        return false;
    }

    return true;   
}

bool Socket::open(unsigned short port) {
     _handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if ( _handle <= 0 ) {
        return false;
    }    

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (unsigned short) port );

    if (bind( _handle, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0) {
        //printf( "failed to bind socket\n" );
        return false;
    }

    if(!setBlocking(true) ) {
        return false;
    }

    

    return true;
}

bool Socket::setTimeout(int ms) {
    
    long total_us = (ms * 1000);
    long microseconds = total_us % 1000000;
    total_us -= microseconds;
    int seconds = total_us / 1000000;
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = microseconds; 
    if (setsockopt(_handle, SOL_SOCKET, SO_RCVTIMEO, &tv,sizeof(tv)) < 0) {
        return false;
    }
    return true;
}

void Socket::close() {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    shutdown(_handle, SHUT_RDWR);
#elif PLATFORM == PLATFORM_WINDOWS
    closesocket( _handle );
#endif
    _handle = -1;
}

bool Socket::isOpen() const {
    return _handle != -1;
}

bool Socket::send( const Address & destination, const void * data, int size ) {
    sockaddr_in address;
    address.sin_family = AF_INET;    
    address.sin_addr.s_addr = htonl( destination.getAddress() );
    address.sin_port = htons( destination.getPort() );

   int sentBytes = sendto(_handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

    if ( sentBytes != size ) {
        //printf( "failed to send packet: return value = %d\n", sent_bytes );
        return false;
    }
    return true;
}

int Socket::receive(Address& sender, void * data, int size) {
#if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
#endif

    //unsigned char recvBuffer[MAX_PACKET_SIZE];
    sockaddr_in from;
    socklen_t fromLength = sizeof( from );
    /*while ( true ) {
        int received_bytes = recvfrom( _handle, (char*)recvBuffer, MAX_PACKET_SIZE, 0, (sockaddr*)&from, &fromLength );

        if ( received_bytes <= 0 )
            break;

        unsigned int from_address = ntohl( from.sin_addr.s_addr );
        unsigned int from_port = ntohs( from.sin_port );
        sender = Address(from_address, from_port);        
    }*/

    int receivedBytes = recvfrom( _handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength );
    if ( receivedBytes > 0 ) {
        unsigned int from_address = ntohl( from.sin_addr.s_addr );
        unsigned int from_port = ntohs( from.sin_port );
        sender = Address(from_address, from_port);    
    }
    return receivedBytes;
}