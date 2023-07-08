#pragma once

#include "modbus.h"
#include "string"

class ModbusHardware
{
public:
    ModbusHardware(const char *serialPort = "/dev/serial0", int address = 2);
    ~ModbusHardware();

    bool connect() const;
    bool isConnected() { return this->_connected; }

    void resetAll(int registerNumber) const;
    void setAll(int registerNumber) const;

    void setPin(int registerNumber, int pinNumber, bool on = true);

private:
    modbus_t *_device = nullptr;
    int _address;
    mutable bool _connected;
};