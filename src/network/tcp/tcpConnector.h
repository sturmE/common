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
   
#pragma once

#include <netinet/in.h>
#include "tcpStream.h"
#include <stdio.h>
#include <string.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
 
class TCPConnector {
  public:
    TCPStream* connect(const char* server, int port);
    TCPStream* connect(const char* server, int port, int timeout);
  private:
    int resolveHost(const char* host, struct in_addr* addr);
};