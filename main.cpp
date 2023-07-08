#include <iostream>

#include "modbus.h"

int main()
{
    std::cout << "It works" << std::endl;
    modbus_t *_device = modbus_new_rtu("/dev/serial0", 57600, 'N', 8, 1);

    modbus_rtu_set_serial_mode(_device, MODBUS_RTU_RS485);
    modbus_set_debug(_device, FALSE);
    modbus_rtu_set_rts(_device, MODBUS_RTU_RTS_UP);

    modbus_set_slave(_device, 2);
    modbus_write_register(_device, 2, 0x00);

    modbus_close(_device);

    return 0;
}