#include <iostream>

#include <table/table.hpp>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }
    std::string_view filename = argv[1];
    auto table = Table::fromFile(filename);
    table.calculate();
    table.print(std::cout);
    return 0;
}
