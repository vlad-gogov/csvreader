#include <iostream>
#include <stdexcept>

#include <table/table.hpp>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }
    std::string_view filename = argv[1];
    try {
        auto table = Table::fromFile(filename);
        table.calculate();
        table.print(std::cout);
    } catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
