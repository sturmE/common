#include "address.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


Address::Address() {
    _address = 0;
    _port = 0;
}

Address::Address(std::string ip, uint16_t port) {
    _port = port;
    std::vector<std::string> elements  = split(ip, '.');

    assert(elements.size() == 4);

    uint8_t a = atoi(elements[0].c_str());
    uint8_t b = atoi(elements[1].c_str());
    uint8_t c = atoi(elements[2].c_str());
    uint8_t d = atoi(elements[3].c_str());

    _address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;

    std::ostringstream ss;     
    ss << (uint32_t)getA() << "." << (uint32_t)getB() << "." << (uint32_t)getC() << "." << (uint32_t)getD() << ":" << getPort();
    _addressString = ss.str();
}

Address::Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port) {
    _address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
    _port = port;

    std::ostringstream ss;     
    ss << (uint32_t)getA() << "." << (uint32_t)getB() << "." << (uint32_t)getC() << "." << (uint32_t)getD() << ":" << getPort();
    _addressString = ss.str();
}

Address::Address(uint32_t address, uint16_t port ) {
    _address = address;
    _port = port;

    std::ostringstream ss;     
    ss << (uint32_t)getA() << "." << (uint32_t)getB() << "." << (uint32_t)getC() << "." << (uint32_t)getD() << ":" << getPort();
    _addressString = ss.str();
}

uint32_t Address::getAddress() const {
    return _address;
}

uint16_t Address::getPort() const {
    return _port;
}

uint8_t Address::getA() const {
    return ( _address >> 24) & 0x000000FF;
}

uint8_t Address::getB() const {
    return ( _address >> 16) & 0x000000FF;
}

uint8_t Address::getC() const {
    return ( _address >> 8) & 0x000000FF;
}

uint8_t Address::getD() const {
    return ( _address ) & 0x000000FF;
}

bool Address::operator == (const Address& other) const {
    return _address == other.getAddress();
}

bool Address::operator != (const Address& other) const {
    return _address != other.getAddress();
}

std::string Address::toString() const {    
     return _addressString;
}

