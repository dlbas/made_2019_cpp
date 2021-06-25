#include <iostream>
#include <string>

#include "calc/calc.hpp"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "missing arguments" << std::endl;
        return -1;
    }

    std::string arg = argv[1];

    parse_return ret = eval_expr(arg);

    if (ret.err) {
        std::cerr << "error occured" << std::endl;
        return -1;
    }

    std::cout << ret.val;

    return 0;
}