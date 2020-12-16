#include "Application.hpp"
/**
* @mainpage Room Reservation
*
* @section intro_sec Intro
* Program for managing room reservations. It is able to reserve a room, search room by specified date/price/capacity and export
* reservations to HTML or console.
* 
* @section usage_sec Usage
* @subsection step1 1. Run the program with arguments "program.exe room_data.csv reservation_data.csv"
* @subsection step2 2. Choose an option depending on what you want to do
* @subsection step3 3. Press 0 to exit the program
*
* @author lblzr_
*/

/**
* @file Source.cpp
* @brief Main program file
*/

/** @fn int main()
 *  @brief Program entry point
 */
int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Invalid arguments!" << std::endl << "Usage: " << argv[0] << " room_data reservation_data" << std::endl;
	}
	else {
		try {
			Application app;
			app.Run(argv[1], argv[2]);
		}
		catch (const std::exception &e) {
			std::cout << "EXCEPTION: " << e.what();
		}
	}
	return 0;
}