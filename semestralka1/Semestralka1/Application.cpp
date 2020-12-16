#include "Application.hpp"

/**
* @brief Function for finding rooms by date/price/capacity
*/
void Application::FindRoom()
{
	ConsoleMenu reservemenu("Find a room");
	reservemenu.Add("By date", [this]() { 
		std::string date;
		std::cout << "Enter date in format YYYY-MM-DD: ";
		std::cin >> date;
		std::cout << "Empty rooms on " << date << std::endl;
		
		Table * t = GenerateReservationData();
		for (unsigned int i = 0; i < rooms.Size(); i++) {
			bool found = false;

			for (unsigned int j = 0; j < t->Size(); j++)
				if ((t->At("id", j) == rooms.At("id", i)) && (t->At("date", j) == date)) {
					found = true;
					if((t->At("occupied", j) != t->At("capacity", j)))
						std::cout << "Room " << t->At("id", j) << " (" << t->At("occupied", j) << "/" << t->At("capacity", j) << ")" << std::endl;
				}

			if(!found)
				std::cout << "Room " << rooms.At("id", i) << " (0/" << rooms.At("capacity", i) << ")" << std::endl;
		}
		delete t;
	});
	reservemenu.Add("By price", [this]() { 
		unsigned int minprice, maxprice;
		std::cout << "Enter minimum price: ";
		std::cin >> minprice;
		std::cout << "Enter maximum price: ";
		std::cin >> maxprice;

		std::cout << "Rooms with prices between " << minprice << " and " << maxprice << std::endl;
		for (unsigned int i = 0; i < rooms.Size(); i++) {
			unsigned int price = std::stoi(rooms.At("price", i));

			if (price <= maxprice && price >= minprice)
				std::cout << "Room " << rooms.At("id", i) << ", price: " << price << std::endl;
		}
	});
	reservemenu.Add("By capacity", [this]() {
		unsigned int mincapacity, maxcapacity;
		std::cout << "Enter minimum capacity: ";
		std::cin >> mincapacity;
		std::cout << "Enter maximum capacity: ";
		std::cin >> maxcapacity;

		std::cout << "Rooms with capacity between " << mincapacity << " and " << maxcapacity << " people" << std::endl;
		for (unsigned int i = 0; i < rooms.Size(); i++) {
			unsigned int capacity = std::stoi(rooms.At("capacity", i));

			if (capacity <= maxcapacity && capacity >= mincapacity)
				std::cout << "Room " << rooms.At("id", i) << ", capacity: " << capacity << std::endl;
		}
	 });
	reservemenu.Show();
}

/**
* @brief Function for generating reservation data
* Joins room table and reservations table by id and merges mulriple reservations into one
* @return Pointer to a new table with reservation data
*/
Table * Application::GenerateReservationData()
{
	//join the table and then truncate it when we find the same date and id
	Table * joined = Table::Join(reservations, rooms, "id");
	joined->AddColumn("occupied", "1");
	joined->Sort("id");

	for (unsigned int i = 0; i < joined->Size(); i++) {
		for (unsigned int j = i + 1; j < joined->Size(); j++) {
			if (joined->At("id", i) == joined->At("id", j) && joined->At("date", i) == joined->At("date", j)) {
				joined->At("occupied", i) = std::to_string(std::stoi(joined->At("occupied", i)) + 1);
				joined->Remove(j);
				j--;
			}
		}
	}

	return joined;
}

/**
* @brief Application entry point
* Loads the room and reservation data and displays the main menu
* @param room_data_file Room data CSV filename
* @param reservation_data_file Reservation data CSV filename
*/
void Application::Run(const char* room_data_file, const char* reservation_data_file)
{
	if (!rooms.Load(room_data_file))
		std::cout << "ERROR: Unable to load file: " << room_data_file << std::endl;

	if (!reservations.Load(reservation_data_file))
		std::cout << "ERROR: Unable to load file: " << reservation_data_file << std::endl;

	std::cout << "Loaded data:" << std::endl
		<< "Rooms: " << room_data_file << std::endl
		<< "Reservations: " << reservation_data_file << std::endl;

	ConsoleMenu reservationsmenu("Reservations");
	reservationsmenu.Add("Print current reservations", [this]() {
		auto d = GenerateReservationData();  d->Print(); 
		delete d; 
	});
	reservationsmenu.Add("Export current reservations to HTML", [this]() {
		auto d = GenerateReservationData();
		d->ExportHtml("reservations.html", "Reservations");
		delete d; 
		std::cout << "Reservations exported to 'reservations.html'" << std::endl;
	});

	ConsoleMenu mainmenu("Reservation system");
	mainmenu.Add("Reserve a room", [this, reservation_data_file]() {
		unsigned int occupied;
		std::string date, id;
		std::cout << "Please enter date in format YYYY-MM-DD: ";
		std::cin >> date;
		std::cout << "Please enter number of reservations: ";
		std::cin >> occupied;
		std::cout << "Please enter room id: ";
		std::cin >> id;

		Table * t = GenerateReservationData();

		int rid = rooms.Find("id", id.c_str());
		if (rid != -1) {
			for (unsigned int i = 0; i < t->Size(); i++) {
				std::vector<std::string*> * r = (*t)[i];
				if (*r->at(t->GetColumnPosition("date")) == date && *r->at(t->GetColumnPosition("id")) == id &&
					(std::stoi(*r->at(t->GetColumnPosition("occupied"))) + occupied) > (unsigned int)std::stoi(*r->at(t->GetColumnPosition("capacity")))) {
					std::cout << "Room with id " << id << " can't accomodate " << occupied << " more people." << std::endl;
					return;
				}
			}
			unsigned int max_capacity = std::stoi(*rooms[rid]->at(rooms.GetColumnPosition("capacity")));
			if (occupied <= max_capacity) {
				for (unsigned int i = 0; i < occupied; i++) {
					std::vector<std::string*> * row = new std::vector<std::string*>();
					row->push_back(new std::string(id));
					row->push_back(new std::string(date));
					reservations.Add(row);
				}
				reservations.Save(reservation_data_file);
				std::cout << "Reservation/s saved!" << std::endl;
			}
			else
				std::cout << "Room with id " << id << " can accomodate maximum of " << max_capacity << " people." << std::endl;
		}
		else {
			std::cout << "Room with id " << id << " does not exist." << std::endl;
		}

		delete t;
	});
	mainmenu.Add("Current reservations", [&reservationsmenu]() { 
		reservationsmenu.Show(); 
	});
	mainmenu.Add("Find room", [this]() {
		FindRoom();
	});

	while (!mainmenu.Exit())
		mainmenu.Show();

}
