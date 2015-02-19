/*
   Copyright © 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "tcpStream.h"
using namespace std;


TCPStream::TCPStream(int sd, struct sockaddr_in* address) : sd_(sd) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
    peerIP_ = ip;
    peerPort_ = ntohs(address->sin_port);
}

TCPStream::~TCPStream() {
    close(sd_);
}

int TCPStream::send(const char* buffer, size_t len)  {
    return write(sd_, buffer, len);
}

int TCPStream::receive(char* buffer, size_t len, int bytesToReceive, int timeout)  {
    int bytesRead = 0;
    while(bytesRead < bytesToReceive) {
        int ret = receive(buffer + bytesRead, bytesToReceive - bytesRead, timeout);
        if(ret <= 0) return ret;        
        bytesRead += ret;
    }
    return bytesRead;
}


int TCPStream::receive(char* buffer, size_t len, int timeout)  {
    if (timeout <= 0) return read(sd_, buffer, len);

    if (waitForReadEvent(timeout)) {
        return read(sd_, buffer, len);
    }

    return connectionTimedOut;

}

string TCPStream::getPeerIP() {
    return peerIP_;
}

int TCPStream::getPeerPort() {
    return peerPort_;
}

bool TCPStream::waitForReadEvent(int timeout) {
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(sd_, &sdset);
    if (select(sd_+1, &sdset, NULL, NULL, &tv) > 0) {
        return true;
    }
    return false;
}