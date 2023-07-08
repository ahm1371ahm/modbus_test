#include "ModbusHardware.hpp"

ModbusHardware::ModbusHardware(const char *serialPort, int address) : _address(address),
                                                                      _connected(false)
{
    this->_device = modbus_new_rtu(serialPort, 57600, 'N', 8, 1);

    modbus_rtu_set_serial_mode(_device, MODBUS_RTU_RS485);
    modbus_set_debug(_device, FALSE);
    modbus_rtu_set_rts(_device, MODBUS_RTU_RTS_UP);
}


bool ModbusHardware::ModbusHardware::connect() const
{
    if (this->_connected)
        return true;

    if (modbus_connect(_device) == -1) 
        return false;
    this->_connected = true;
    return true;
}