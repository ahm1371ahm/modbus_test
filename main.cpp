#include <iostream>
#include <chrono>
#include <thread>

#include "modbus.h"

int main()
{
    std::cout << "It works" << std::endl;
    modbus_t *_device = modbus_new_rtu("/dev/serial0", 57600, 'N', 8, 1);

    modbus_rtu_set_serial_mode(_device, MODBUS_RTU_RS485);
    modbus_set_debug(_device, FALSE);
    modbus_rtu_set_rts(_device, MODBUS_RTU_RTS_UP);

    if (modbus_connect(_device ) == -1) {
        std::cout << "Cannot open the modbus" << std::endl;
        // return 0;
    }

    std::cout << "modbus opened successfully" << std::endl;

    modbus_set_slave(_device, 3);

    uint16_t counter = 0;
    while(true) {
        using namespace std::chrono_literals;
        std::cout << "writing: " << std::dec << counter << "\t" << std::hex << counter << std::endl;
        // std::cout << std::hex << counter << std::endl;
        modbus_write_register(_device, 2, counter);
        counter++;
        std::this_thread::sleep_for(1s);
    }

    modbus_close(_device);
    std::cout << "end of the appliation" << std::endl;
    return 0;
}