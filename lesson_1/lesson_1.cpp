#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sys/sysinfo.h>

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        return result;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void getStackMemorySize() {
    std::string stack_memory = exec("ulimit -s");   //Linux
    std::cout << "Stack memory size = " << stack_memory << std::endl;
    // Stack memory size = 8192
}

void getHeapMemorySize() {
    unsigned char* heap_memory;
    size_t memorySize = 1;
    size_t memoryChange = (512*1024*1024); // + 512 Mb

    while (true) {
        try {
            std::cout << "Trying to allocate: " << memorySize/1024/1024 <<"Mb"<< std::endl;
            heap_memory = new unsigned char[memorySize]();
        } catch (std::bad_alloc& ba)
        {
            std::cout << "Max heap size = " << memorySize - memoryChange << std::endl;
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            break;
        }
        delete heap_memory;

        memorySize += memoryChange;
    }
    // Limit is the free virtual memory
    // The total amount of virtual memory space available on a linux system is (roughly) RAM + swap space - kernel overhead

    //The C++ standard absolutely guarantees that allocated memory will be contiguous
}

void getSystemMemory() {
    struct sysinfo sys_info;

    unsigned long total_ram = 0;
    unsigned long total_swap = 0;

    if (sysinfo(&sys_info) != -1) {
        total_ram = ((unsigned long)sys_info.totalram * sys_info.mem_unit)/1024;
        total_swap = ((unsigned long)sys_info.totalswap * sys_info.mem_unit)/1024;
    }

    std::cout << "RAM size: " << (double)total_ram/1024/1024 << "Gb" << std::endl;
    std::cout << "Swap size: " << (double)total_swap/1024/1024 << "Gb" <<std::endl;
    // RAM size: 15.5251Gb
    // Swap size: 15.3057Gb
}

int main() {

    getStackMemorySize();
    getSystemMemory();
    getHeapMemorySize();

    return 0;
}