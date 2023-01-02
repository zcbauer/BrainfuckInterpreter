#include "input.h"
#include <stack>
#include <iostream>
#include <getopt.h>
#include <regex>

void Inputer::gethelp(){//TODO: write this
    std::cout<<"This could be a helpful message or something\n";
}
bool Inputer::parseArgs(int argc, char* argv[]){
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    bool verify = true;
    option long_options[] = {
        {"NoCheck", no_argument, nullptr,'n'},
        {"Optimized",no_argument,nullptr,'O'},
        {"help",no_argument,nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    while ((choice = getopt_long(argc, argv, "nOh", long_options, &option_index)) != -1){
        switch (choice){
        case 'n':
            verify = false;
            break;
        case 'h':
            gethelp();
            break; 	
        case 'O':
            OPT = true;
            break;
        default:
            std::cerr << "Error: Invalid command line option\n";
            exit(1);
        } // switch
    } // while
    return verify;
}
inline bool Inputer::valdInstr(char input){
    return (input == '>' || input == '<'|| input == '+' 
            || input == '-' || input == '.'|| input == ','
            || input == '['|| input == ']');
}
inline std::vector<Instruction> Inputer::Optimized(){ // 
    char input, curInstr = '\0';
    uint16_t numRepeat =0;
    uint32_t instructionNum = 0;
    std::vector<Instruction> instructions;
    std::stack<uint32_t> locations;
    while(std::cin>>input){
        if(valdInstr(input)){
           if(input == '['){
                locations.push(instructionNum - numRepeat);
                instructions.push_back({input,0});
                curInstr = '\0';
            }
            else if(input == ']'){
                instructions.push_back({input,locations.top()});
                instructions[locations.top()].jmpLoc = instructionNum-numRepeat;
                locations.pop();
                curInstr = '\0';
            }
            else{
                if(input == curInstr){
                    ++instructions.back().jmpLoc;
                    ++numRepeat;
                }
                else{
                    curInstr = input;
                    instructions.push_back({input,1});
                }
            }
            ++instructionNum;
        }
    } 
    return instructions;
}
inline std::vector<Instruction> Inputer::NOcheck(){
    char input;
    uint32_t instructionNum = 0;
    std::vector<Instruction> instructions;
    std::stack<uint32_t> locations;
    
    while(std::cin>>input){
        if(valdInstr(input)){
            if(input == '['){
                locations.push(instructionNum);
                instructions.push_back({input,0});
            }
            else if(input == ']'){
                instructions.push_back({input,locations.top()});
                instructions[locations.top()].jmpLoc = instructionNum;
                locations.pop();
            }
            else{
                instructions.push_back({input,1}); 
            }
            ++instructionNum;
        }
    }
    return instructions;
}
inline std::vector<Instruction> Inputer::Check(){
   char input;
    uint32_t instructionNum = 0;
    std::vector<Instruction> instructions;
    std::stack<uint32_t> locations; 
    std::stack<char> checker;
    while(std::cin>>input){
        if(valdInstr(input)){
            if(input == '['){
                checker.push(input);
                locations.push(instructionNum);
                instructions.push_back({input,0});
            }
            else if(input == ']'){
                if(checker.empty()||checker.top() != '['){
                    std::cout<<"Missing opening [ to closing ] at char"<<instructionNum<<'\n';
                    exit(1);
                }
                else{
                    checker.pop();
                    instructions.push_back({input,locations.top()});
                    instructions[locations.top()].jmpLoc = instructionNum;
                    locations.pop();
                }
            }
            else{
                instructions.push_back({input,1});  
            }
            ++instructionNum;
        }
    }
    return instructions;
}

Inputer::Inputer(int argc, char* argv[]):
OPT(0)
{Verify = parseArgs(argc,argv);}
std::vector<Instruction> Inputer::readIN(){
    if(OPT)
        return Optimized();
    else if(Verify)
        return Check();
    return NOcheck();
}
