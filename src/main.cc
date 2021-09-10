#include <iostream>
#include "globalDefinitions.hh"
#include "arena.hh"
#include "init.hh"

int main() {
    vm_init_globals();
    juint ju = 10;
    std::cout << ju << std::endl;
    std::cout << "hello world" << std::endl;
    Arena a;
    return 0;
}