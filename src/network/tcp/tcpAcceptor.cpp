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
   
#include "tcpAcceptor.h"

TCPAcceptor::TCPAcceptor(int port, const char* address) 
    : lsd_(0), port_(port), address_(address), listening_(false) {} 

TCPAcceptor::~TCPAcceptor() {
    if (lsd_ > 0) {
        close(lsd_);
    }
}

bool TCPAcceptor::start() {
    if (listening_ == true) {
        return 0;
    }

    lsd_ = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(port_);
    if (address_.size() > 0) {
        inet_pton(PF_INET, address_.c_str(), &(address.sin_addr));
    }
    else {
        address.sin_addr.s_addr = INADDR_ANY;
    }
    
    int optval = 1;
    setsockopt(lsd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval); 

    int set = 1;
    //setsockopt(lsd_, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
     
    
    int result = bind(lsd_, (struct sockaddr*)&address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return false;
    }
    
    result = listen(lsd_, 5);
    if (result != 0) {
        perror("listen() failed");
        return false;
    }
    listening_ = true;
    return true;
}

TCPStream* TCPAcceptor::accept() {
    if (listening_ == false) {
        return NULL;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = ::accept(lsd_, (struct sockaddr*)&address, &len);
    if (sd < 0) {
        perror("accept() failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
}