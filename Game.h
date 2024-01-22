#pragma once
#include <algorithm>
#include "Menu.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

class Game
{
public:
	Game();
	
	void Run();

private:
	void HandleInput();
	void Update();
	void PrintText();
	void CloseGame();
	void LoadData();
private:
	bool m_running;
	std::vector<std::string> m_filenames;
	std::vector<Menu> m_menus;
	std::map<std::string, std::pair<std::string, std::string>> m_decisionAndNextRoom;
	std::string m_start;
};

