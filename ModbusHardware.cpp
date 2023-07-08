#include "ModbusHardware.hpp"

#include "iostream"

ModbusHardware::ModbusHardware(const char *serialPort, int address) : _address(address),
                                                                      _connected(false)
{
    this->_device = modbus_new_rtu(serialPort, 57600, 'N', 8, 1);

    modbus_rtu_set_serial_mode(_device, MODBUS_RTU_RS485);
    modbus_set_debug(_device, FALSE);
    modbus_rtu_set_rts(_device, MODBUS_RTU_RTS_UP);
}

ModbusHardware::~ModbusHardware()
{
    if (this->_connected) 
        modbus_close(this->_device);
    modbus_free(this->_device);
}


bool ModbusHardware::connect() const
{
    if (this->_connected)
        return true;

    if (modbus_connect(_device) == -1) 
        return false;
    this->_connected = true;
    return true;
}

void ModbusHardware::resetAll(int registerNumber) const
{
    if (!this->_connected) {
        this->_showNotConnectedErrorMessage();
        return;
    }
    modbus_set_slave(_device, registerNumber);
    modbus_write_register(_device, this->_address, 0x0000);
}

void ModbusHardware::setAll(int registerNumber) const
{
        if (!this->_connected) {
        this->_showNotConnectedErrorMessage();
        return;
    }
    modbus_set_slave(_device, registerNumber);
    modbus_write_register(_device, this->_address, 0xFFFF);
}

void ModbusHardware::setPin(int registerNumber, int pinNumber, bool on) const
{
        if (!this->_connected) {
        this->_showNotConnectedErrorMessage();
        return;
    }
    if (pinNumber <= 0) {
        std::cerr << "Pin Number Must start from 1" << std::endl;
        return;
    }

    modbus_set_slave(_device, registerNumber);
    if (on)
    {
        uint16_t modbusLastState = 0x0000;
        modbus_read_registers(_device, this->_address, 1, &modbusLastState);

        std::cout << "Last State: " << std::hex << modbusLastState << std::endl;

        const uint16_t singleOne = 1 << (pinNumber - 1);
        const uint16_t value = singleOne | modbusLastState;
        std::cout << std::dec << "turning on pinNumber: " << pinNumber << std::hex << "\tvalue to be written: " << value << std::endl;
        modbus_write_register(_device, this->_address, value);
    }
}

void ModbusHardware::_showNotConnectedErrorMessage() const 
{
    std::cerr << "Serial Port is not connected for the Modbus" << std::endl; 
}