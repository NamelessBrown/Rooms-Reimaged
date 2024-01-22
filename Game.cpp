#include "Game.h"
#include <tinyxml2.h>
#include <iostream>
#include <format>
#include <numeric>

// The main contents of Game is to:
/* handles input */
/* update values */
/* print text */
/* Close game is to save progress */

Game::Game()
	:m_running{ true }
{
	LoadData();
	m_start = m_menus.front().FireEvent();
}

void Game::Run()
{
	while (m_running) 
	{
		HandleInput();
		Update();
		PrintText();
	}
}

void Game::HandleInput()
{
	auto pair = m_decisionAndNextRoom.find(m_start);
	std::cout << std::format("\nOUTPUT: {}\n", pair->second.second);

	auto iter = std::find_if(m_menus.begin(), m_menus.end(), [&](const Menu& menu) { return menu.GetCurrentRoom() == pair->second.first; });
	m_start = iter->FireEvent();
}

void Game::Update()
{

}

void Game::PrintText()
{
	std::cout << "Press [Enter] to continue...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	system(CLEAR);
}

void Game::CloseGame()
{

}

void Game::LoadData()
{
	tinyxml2::XMLDocument files;
	files.LoadFile("Events\\MasterEvents.xml");

	for (tinyxml2::XMLElement* element = files.RootElement(); element != nullptr; element = element->NextSiblingElement())
	{
		std::string filename = element->GetText();
		m_filenames.push_back(filename);
	}

	for (const auto& file : m_filenames)
	{
		tinyxml2::XMLDocument document;
		document.LoadFile(file.c_str());

		std::string scenario;
		std::string prompt;
		std::map<std::string, std::string> choicesAndOutput;
		std::string currentRoom;
		
		for (tinyxml2::XMLElement* element = document.RootElement(); element != nullptr; element = element->NextSiblingElement())
		{
			std::string elementValue = element->Value();
			if (elementValue == "scenario")
			{
				const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
				scenario = element->GetText();
				currentRoom = attribute->Value();

			}
			else if (elementValue == "prompt")
				prompt = element->GetText();
			else
			{
				if (elementValue == "choice")
				{
					const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
					choicesAndOutput[attribute->Value()] = element->GetText();
				}

				if (elementValue == "outcome")
				{
					const tinyxml2::XMLAttribute* decisionAttribute = element->FindAttribute("decision");
					const tinyxml2::XMLAttribute* roomAttribute = element->FindAttribute("room");

					m_decisionAndNextRoom[decisionAttribute->Value()] = { roomAttribute->Value(), element->GetText() };

				}
			}
		}

		m_menus.emplace_back(scenario, prompt, currentRoom, choicesAndOutput);
	}
}
