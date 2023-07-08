#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "ModbusHardware.hpp"


int main()
{
    std::cout << "It works" << std::endl;

    ModbusHardware hw("/dev/serial0");
    hw.connect();
    hw.resetAll(3);
    using namespace std::chrono;
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 1);
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 5);
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 8);

    // uint16_t counter = 0;
    // while (true)
    // {
    //     std::cout << "writing: " << std::dec << counter << "\t" << std::hex << counter << std::endl;
    //     // std::cout << std::hex << counter << std::endl;
    //     modbus_write_register(_device, 2, counter);
    //     counter++;
    //     std::this_thread::sleep_for(50ms);
    // }

    std::cout << "end of the appliation" << std::endl;
    return 0;
}

// mbpoll -a 3 -b 57600 -t 3 -r 1 -c 2 /dev/serial0