#include <stack>
#include <cstdlib>
#include "input.h"
#include "brainfuck.h"

int main(int argc, char *argv[]){
    Inputer input(argc,argv);
    auto instructions = input.readIN();
    Interpreter inter(instructions);
    inter.run();
}
