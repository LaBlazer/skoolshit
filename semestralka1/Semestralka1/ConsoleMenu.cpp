#include "ConsoleMenu.hpp"

/**
* @brief Adds a new menu item to the menu
* @param text Menu item description
* @param callback Function that will be called when user chooses this menu item
*/
void ConsoleMenu::Add(const char * text, std::function<void()> callback)
{
	this->menu.push_back(std::pair<const char*, std::function<void()>>(text, callback));
}

/**
* @brief Shows the menu to the user
*/
void ConsoleMenu::Show()
{
	if (this->exit) {
		return;
	}

	unsigned int choice, menusize = (unsigned int)this->menu.size();

	std::cout << std::endl << this->text << std::endl
		<< "____________________" << std::endl;
	for (unsigned int i = 0; i < menusize; i++) {
		std::cout << i + 1 << ". " << this->menu[i].first << std::endl;
	}
	std::cout << "____________________" << std::endl;

	std::cout << "Please choose option 1 - " << menusize << " or 0 to exit: ";
	std::cin >> choice;

	while (!std::cin.good() || choice < 0 || choice > menusize) {
		std::cout << "Invalid option, please choose option 1 - " << menusize - 1 << " or 0 to exit: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> choice;
	}

	if (choice == 0) {
		this->exit = true;
	}
	else {
		this->menu[choice - 1].second();
	}
}

/**
* @brief Checks whether the user exited the menu
* @return true if menu was dismissed, otherwise false
*/
bool ConsoleMenu::Exit()
{
	return this->exit;
}

