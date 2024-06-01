#pragma once
#include "MiaoMiaoSense.hpp"
#include "Driver.hpp"


class Memory {
public:
    template <typename T>
    inline void Read(uint64_t address, T& out) {
        out = driver::read_memory<T>(driverhandle, address);
    };

    template <typename T>
    inline T Read_DOut(uint64_t address) {
        return driver::read_memory<T>(driverhandle, address);
    };

    template <typename T>
    inline void Write(uint64_t address, const T& value) {
        driver::write_memory<T>(driverhandle, address, value);
    };
};