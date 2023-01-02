#ifndef READER
#define READER
#include <stack>
#include <vector>
#include <cstdlib>
#include "brainfuck.h"
class Inputer{
	bool Verify;
	bool OPT;
	inline std::vector<Instruction> NOcheck();
	inline std::vector<Instruction> Check();
	inline std::vector<Instruction> Optimized();
	inline bool valdInstr(char);
	inline void gethelp();
	inline bool parseArgs(int, char *[]);
	public:
	Inputer(int, char*[]);
	std::vector<Instruction>readIN();	
};
#endif
