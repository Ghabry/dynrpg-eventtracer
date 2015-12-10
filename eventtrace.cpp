#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <fstream>
#include <ctime>
#include <sstream>

std::ofstream ofs;

void onMoveCommand() {
	RPG::Character* character;
	char* _edx;
	char* _eax;
	unsigned int address = 0x478E80;

	// Load registers to C variables
	// Character is obtained by reading the stack frame of the caller...
	asm("movl 48(%%ebp), %0\n\t"
		"movl %%edx, %1\n\t"
		"movl %%eax, %2\n\t"
		: "=r" (character), "=r" (_edx), "=r" (_eax));

	// Invoke the overwritten function call
	// return in eax, arguments in eax and edx
	__asm volatile(
		"call *%1\n\t"
		: "=a" (_eax)
		: "b" (address), [_eax] "a" (_eax), [_edx] "d" (_edx)
		: "memory");
	
	// Save all registers and run own code
	asm("pusha":);
	ofs << "M\t" << character->id << "\t" << character->_unknown_44 << std::endl;
	asm("popa":);
}

bool onStartup(char *pluginName) {
	DWORD old_protect;

	// Patch call at 0x4C51A5 to call onMoveCommand
	VirtualProtect((DWORD*)0x4C51A5, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	*(DWORD*)(0x4C51A5) = (DWORD)onMoveCommand - 0x4C51A4 - 5;
	VirtualProtect((DWORD*)0x4C51A5, 4, PAGE_EXECUTE, &old_protect);
	
	std::time_t t = std::time(NULL);
	char timestr[100];
	strftime(timestr, 100, "%Y-%m-%d-%H-%M-%S", std::localtime(&t));
	
	std::stringstream ss;
	ss << "eventtrace_" << timestr << ".txt";
	ofs.open(ss.str().c_str());
	
	strftime(timestr, 100, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
	ofs << "# Session start at " << timestr << std::endl;
	ofs << "# E\tevt_id\tpage_id\tline_id" << std::endl;
	ofs << "# M\tevt_id\tline_id" << std::endl;
	
	return true;
}

bool onEventCommand(
	RPG::EventScriptLine*, RPG::EventScriptData*,
	int eventId, int pageId, int lineId, int*) {
	ofs << "E\t" << eventId << "\t" << pageId << "\t" << lineId << std::endl;
}

bool onComment(const char*  text,  
	const RPG::ParsedCommentData*,  
	RPG::EventScriptLine*,  
	RPG::EventScriptData*,  
	int, int, int, int*) {
	ofs << "# " << text << std::endl;
}

void onExit() {
	std::time_t t = std::time(NULL);
	char timestr[100];
	strftime(timestr, 100, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
	
	ofs << "# Session end at " << timestr << std::endl;
	ofs.close();
}
