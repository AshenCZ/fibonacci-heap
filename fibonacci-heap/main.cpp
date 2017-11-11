#include <gtest/gtest.h>
#include <iostream>
#include "fibheap.h"

void executeLine(const std::string& line, FibonacciHeap& heap) {
    if (line[0] == 'I') {
        int first = atoi(line.c_str() + 4);
        size_t secondSpace = line.find_last_of(" ");
        int second = atoi(line.substr(secondSpace).c_str());
        std::cout << "INS " << first << " " << second << "\n";
        heap.insert({first, second});
    } else if (line[0] == 'D' && line[2] == 'L') {
        std::cout << "DEL\n";
        std::cout << "Extr: " << heap.extractMin() << "\n";
    } else if (line[0] == 'D' && line[2] == 'C') {
        int first = atoi(line.c_str() + 4);
        size_t secondSpace = line.find_last_of(" ");
        int second = atoi(line.substr(secondSpace).c_str());
        std::cout << "DEC " << first << " " << second << "\n";
        heap.decrease(first, second);
    } else if (line[0] == '#') {
        int first = atoi(line.c_str() + 2);
        std::cout << "N;" << first << ";AVG;" << heap.log.getAverage() << ";\n";
        heap.reset();
    } else {
        assert(false);
    }
}

void run() {
    std::string line;
    FibonacciHeap heap;
    while (std::getline(std::cin, line)) {
        executeLine(line, heap);
    }
}

int main(int argc, wchar_t** argv) {
    /// Google test
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    run();

    return 0;
    argc, argv;
}