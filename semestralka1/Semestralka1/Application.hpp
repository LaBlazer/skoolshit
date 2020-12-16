#pragma once
#include "ConsoleMenu.hpp"
#include "Table.hpp"

/**
* @class Application
* @brief Main application class, implements all functionalty
*/
class Application {
	Table rooms{ "id", "floor", "room", "capacity", "price" };
	Table reservations{ "id", "date" };

	void FindRoom();
	Table *GenerateReservationData();
public:
	void Run(const char* room_data_file, const char* reservation_data_file);
};