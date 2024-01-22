#pragma once

#include <string>
#include <map>
#include <vector>

class Menu
{
public:
	Menu(const std::string& scenario, const std::string& prompt, const std::string& currentRoom, const std::map<std::string, std::string>& choicesAndOutput);

	std::string FireEvent();


	inline const std::string& GetCurrentRoom() const { return m_currentRoom; }
private:
	std::string m_currentRoom;
	std::string m_scenario;
	std::string m_prompt;
	std::map<std::string, std::string> m_choicesAndOutput;
};

