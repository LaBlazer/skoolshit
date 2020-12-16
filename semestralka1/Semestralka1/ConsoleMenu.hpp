#pragma once
#include "Common.hpp"

/**
* @class ConsoleMenu
* @brief Class for creating console menus
*/
class ConsoleMenu {
	const char* text;
	bool exit;
	std::vector<std::pair<const char*, std::function<void()>>> menu;
public:
	/**
	* @brief ConsoleMenu constructor
	* @param text Text to display when the menu is shown
	*/
	ConsoleMenu(const char* text) : text(text) {};
	void Add(const char* text, std::function<void()> callback);
	void Show();
	bool Exit();
};