#pragma once

#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <sstream>

class Address {
private:
    uint32_t _address;
    uint16_t _port;
    std::string _addressString;
public:
    Address();
    Address(std::string address, uint16_t port);
    Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port );
    Address(uint32_t address, uint16_t port );
    uint32_t getAddress() const;    
    uint8_t getA() const;
    uint8_t getB() const;
    uint8_t getC() const;
    uint8_t getD() const;
    uint16_t getPort() const;
    bool operator == ( const Address & other ) const;
    bool operator != ( const Address & other ) const;
    std::string toString() const;
};