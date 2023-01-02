#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stack>
#include <vector>
struct Instruction{
	char instr;
	uint32_t jmpLoc;
};
class Interpreter{
	std::vector<Instruction> instructions;
	std::vector<uint8_t> tape;
	uint32_t ptr,instrptr;

	public:
	
	Interpreter(const std::vector<Instruction> &);
	void run();
};

#endif /* BRAINFUCK_H */
