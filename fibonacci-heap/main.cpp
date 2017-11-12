//#include <gtest/gtest.h>
#include <iostream>
#include "fibheap.h"
#include <string>

//#define VERBAL

void executeLine(const std::string& line, FibonacciHeap& heap) {
    if (line[0] == 'I') {
        int first = atoi(line.c_str() + 4);
        size_t secondSpace = line.find_last_of(" ");
        int second = atoi(line.substr(secondSpace).c_str());

#ifdef VERBAL
        std::cout << "INS " << first << " " << second << "\n";
#endif

        heap.insert({first, second});
    } else if (line[0] == 'D' && line[2] == 'L') {
        int ret = heap.extractMin();
        ret;
#ifdef VERBAL
        std::cout << "DEL == " << ret << "\n";
#endif
    } else if (line[0] == 'D' && line[2] == 'C') {
        int first = atoi(line.c_str() + 4);
        size_t secondSpace = line.find_last_of(" ");
        int second = atoi(line.substr(secondSpace).c_str());

#ifdef VERBAL
        std::cout << "DEC " << first << " " << second << "\n";
#endif

        heap.decrease(first, second);
    } else if (line[0] == '#') {
        if (heap.log.init()) {
            std::cout << "N;" << heap.log.N << ";AVG;" << heap.log.getAverage() << ";\n";
        }
        int first = atoi(line.c_str() + 2);
        heap.log.rememberN(first);
        heap.reset();
    } else {
        std::cout << "EXIT\n";
        assert(false);
    }
}

void run() {
    std::string line;
    FibonacciHeap heap;
    while (std::getline(std::cin, line)) {
        executeLine(line, heap);
    }
    std::cout << "N;" << heap.log.N << ";AVG;" << heap.log.getAverage() << ";\n";
}

int main(int argc, char** argv) {
    /// Google test
    //::testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();

    run();
    argc, argv;
    return 0;
}