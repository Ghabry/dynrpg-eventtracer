#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <fstream>
#include <ctime>
#include <sstream>

std::ofstream ofs;

bool onStartup(char *pluginName) {
	std::time_t t = std::time(NULL);
	char timestr[100];
	strftime(timestr, 100, "%Y-%m-%d-%H-%M-%S", std::localtime(&t));
	
	std::stringstream ss;
	ss << "eventtrace_" << timestr << ".txt";
	ofs.open(ss.str().c_str());
	
	strftime(timestr, 100, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
	ofs << "# Session start at " << timestr << std::endl;
	ofs << "# evt_id\tpage_id\tline_id" << std::endl;
	
	return true;
}

bool onEventCommand(
	RPG::EventScriptLine*, RPG::EventScriptData*,
	int eventId, int pageId, int lineId, int*) {
	ofs << eventId << "\t" << pageId << "\t" << lineId << std::endl;
}

void onExit() {
	std::time_t t = std::time(NULL);
	char timestr[100];
	strftime(timestr, 100, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
	
	ofs << "# Session end at " << timestr << std::endl;
	ofs.close();
}
