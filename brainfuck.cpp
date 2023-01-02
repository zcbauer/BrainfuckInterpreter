#include <iostream>
#include "brainfuck.h"
#define TapeLen 3000

Interpreter::Interpreter(const std::vector<Instruction> &input):
instructions(input),ptr(0),instrptr(0){
    tape.resize(TapeLen);
}



void Interpreter::run(){
    uint32_t nestcount = 0;
    while(instrptr < instructions.size()){
        bool loopBack = false;
        switch(instructions[instrptr].instr){
            case '>':
                
                ptr += instructions[instrptr].jmpLoc;
                break;
            case '<':
                ptr -= instructions[instrptr].jmpLoc;
                break;
            case '+':
                tape[ptr]+= instructions[instrptr].jmpLoc;
                break;
            case '-':
                tape[ptr]-= instructions[instrptr].jmpLoc;
                break;
            case '.':
                for(uint32_t i =0; i<instructions[instrptr].jmpLoc; ++i)
                    std::cout<<(char)tape[ptr];
                break;
            case ',':
                for(uint32_t i =0; i<instructions[instrptr].jmpLoc; ++i){
                    char input;
                    std::cin>>input;
                    tape[ptr] = (uint8_t)input;
                }
                break;
            case '[':
                if(!tape[ptr])
                    instrptr = instructions[instrptr].jmpLoc;
                break;
            case ']':
                if(tape[ptr])
                    instrptr = instructions[instrptr].jmpLoc;
                break;
        }
        ++instrptr;
    }
}