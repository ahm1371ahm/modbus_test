#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "modbus.h"

modbus_t *_device = nullptr;

void resetAll(int registerNumber)
{
    modbus_set_slave(_device, registerNumber);
    modbus_write_register(_device, 2, 0x0000);
}

void setAll(int registerNumber)
{
    modbus_set_slave(_device, registerNumber);
    modbus_write_register(_device, 2, 0xFFFF);
}

void setPin(int registerNumber, int pinNumber, bool on = true)
{
    if (pinNumber <= 0)
    {
        std::cout << "Pin Number Must start from 1";
        return;
    }

    modbus_set_slave(_device, registerNumber);
    if (on)
    {
        uint16_t modbusLastState = 0x0000;
        modbus_read_registers(_device, 2, 1, &modbusLastState);

        std::cout << "Last State: " << std::hex << modbusLastState << std::endl;

        // const uint16_t singleOne = 1 << (pinNumber - 1);
        // const uint16_t value = singleOne | 0x0000;
        // std::cout << std::dec << "turning on pinNumber: " << pinNumber << std::hex << "\tvalue to be written: " << value << std::endl;
        // modbus_write_register(_device, 2, value);
    }
}

int main()
{
    std::cout << "It works" << std::endl;
    _device = modbus_new_rtu("/dev/serial0", 57600, 'N', 8, 1);

    modbus_rtu_set_serial_mode(_device, MODBUS_RTU_RS485);
    modbus_set_debug(_device, FALSE);
    modbus_rtu_set_rts(_device, MODBUS_RTU_RTS_UP);

    if (modbus_connect(_device) == -1)
    {
        std::cout << "Cannot open the modbus" << std::endl;
        return 0;
    }
    std::cout << "modbus opened successfully" << std::endl;

    // resetAll(3);
    using namespace std::chrono;
    std::this_thread::sleep_for(5s);
    setPin(3, 1);
    std::this_thread::sleep_for(5s);
    setPin(3, 5);

    // uint16_t counter = 0;
    // while (true)
    // {
    //     std::cout << "writing: " << std::dec << counter << "\t" << std::hex << counter << std::endl;
    //     // std::cout << std::hex << counter << std::endl;
    //     modbus_write_register(_device, 2, counter);
    //     counter++;
    //     std::this_thread::sleep_for(50ms);
    // }

    modbus_close(_device);
    free(_device);
    std::cout << "end of the appliation" << std::endl;
    return 0;
}

// mbpoll -a 3 -b 57600 -t 3 -r 1 -c 2 /dev/serial0