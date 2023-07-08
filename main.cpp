#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

#include "ModbusHardware.hpp"

ModbusHardware hw("/dev/serial0");

int main()
{
    std::cout << "It works" << std::endl;

    hw.connect();
    hw.setAll(3);
    using namespace std::chrono;
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 1, false);
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 5, false);
    std::this_thread::sleep_for(5s);
    hw.setPin(3, 8, false);
    std::this_thread::sleep_for(5s);

    while (true)
    {
        hw.setPin(3, 6, false);
        std::this_thread::sleep_for(1s);
        hw.setPin(3, 6, true);
        std::this_thread::sleep_for(1s);
    }

    std::cout << "end of the appliation" << std::endl;
    return 0;
}

// mbpoll -a 3 -b 57600 -t 3 -r 1 -c 2 /dev/serial0