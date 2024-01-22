#include "Menu.h"
#include <iostream>
#include <format>

Menu::Menu(const std::string& scenario, const std::string& prompt, const std::string& currentRoom, const std::map<std::string, std::string>& choicesAndOutput)
	:m_scenario{ scenario }, m_prompt{ prompt }, m_choicesAndOutput{ choicesAndOutput }, m_currentRoom{ currentRoom }
{

}

std::string Menu::FireEvent()
{
	std::string choice;
	std::vector<std::string> choices;

	std::cout << std::format("SCENARIO: {}\n\n", m_scenario);
	std::cout << std::format("PROMPT: {}\n\n", m_prompt);
	
	int options = 1;
	for (const auto& pair : m_choicesAndOutput)
	{
		std::cout << std::format("CHOICES: {}.) {}\n", options++, pair.second);
		choices.push_back(pair.first);
	}

	std::cout << std::format("\n>");
	std::getline(std::cin, choice);
	int valChoice = std::stoi(choice);

	const std::pair<std::string, std::string> pair = *m_choicesAndOutput.find(choices[valChoice - 1]);

	return pair.first;
}
