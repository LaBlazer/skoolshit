#pragma once
#include "Table.hpp"

/**
* @brief Joins two tables
* Joins two tables by column specified in the 'join_by' parameter
* @param a Reference to the first table
* @param b Reference to the second table
* @param join_by Name of the column by which we should join the table
* @return Pointer to new joined table
*/
Table * Table::Join(Table &a, Table &b, const char * join_by)
{
	int join_by_pos_a = a.GetColumnPosition(join_by);
	int join_by_pos_b = a.GetColumnPosition(join_by);

	if (join_by_pos_a == -1 || join_by_pos_b == -1) {
		std::cout << "[ERROR]: Failed joining the tables." << std::endl;
		return nullptr;
	}

	std::vector<std::string> res_column_names;
	res_column_names.push_back(join_by);

	for (auto a : *a.column_names)
		if (a != join_by)
			res_column_names.push_back(a);
	
	for (auto b : *b.column_names)
		if (b != join_by)
			res_column_names.push_back(b);

	Table *res_table = new Table(res_column_names);

	// for each row in table a
	for (const std::vector<std::string*> *a_row : *a.data) {
		// we find a pair in table b
		std::vector<std::string*> *b_row = nullptr;
		for (std::vector<std::string*> *row : *b.data)
			// if the join by columns are the same
			if (*a_row->at(join_by_pos_a) == *row->at(join_by_pos_b)) {
				b_row = row;
				break;
			}

		if (b_row == nullptr) {
			std::cout << "[ERROR] Could not find column '" << join_by << "' with data '" << a_row->at(join_by_pos_a) << "' in table b!" << std::endl;
			continue;
		}
		else {
			std::vector<std::string*> * res_row = new std::vector<std::string*>();
			res_row->push_back(new std::string(*a_row->at(join_by_pos_a))); //insert join_by item

			for (int i = 0; i < a.column_names->size(); i++) { //insert items from table a
				if(i != join_by_pos_a)
					res_row->push_back(new std::string(*a_row->at(i)));
			}

			for (int i = 0; i < b.column_names->size(); i++) { //insert items from table b
				if (i != join_by_pos_b)
					res_row->push_back(new std::string(*b_row->at(i)));
			}
			res_table->data->push_back(res_row);
		}
	}

	return res_table;
}

/**
* @brief Loads the table data from a CSV file
* @param filename Name of the CSV file to load from
* @param delimeter Data delimeter in the CSV file (usually ',' or ';'), default: ','
* @return true if the CSV was loaded successfully, otherwise false
*/
bool Table::Load(const char *filename, char delimeter) {
	std::ifstream ifs(filename);
	if (!ifs.good())
		return false;

	std::string line;

	while (std::getline(ifs, line)) {
		std::vector<std::string*> *row = new std::vector<std::string*>();
		
		std::istringstream iss(line);
		std::string cell;
		while (std::getline(iss, cell, delimeter)) {
			std::string *d = new std::string(cell);
			row->push_back(d);
		}

		if (row->size() != 0) {
			data->push_back(row);
		}
	}

	return data;
} 

/**
* @brief Saves the table data to a CSV file
* @param filename Name of the CSV file to save to
* @param delimeter Data delimeter in the CSV file (usually ',' or ';'), default: ','
* @return true if the CSV was saved successfully, otherwise false
*/
bool Table::Save(const char* filename, char delimeter) {
	std::ofstream ofs(filename);
	if (!ofs.good())
		return false;

	std::string del = "";

	for (const std::vector<std::string*> *row : *data) {
		for (const std::string *data : *row) {
			ofs << del << *data;
			del = delimeter;
		}
		del = "";
		ofs << std::endl;
	}

	return true;
}

/**
* @brief Exports the table data to a HTML file/table
* @param filename Name of the HTML file to export to
* @param title Title of the table in the HTML file
* @return true if the HTML was exported successfully, otherwise false
*/
bool Table::ExportHtml(const char * filename, const char * title)
{
	std::ofstream ofs(filename, std::ios::out);
	if (!ofs.good())
		return false;

	ofs << "<!DOCTYPE HTML><html><head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\"/>"
		"<style>html{display:table;margin:auto}body{display:table-cell;vertical-align:middle}thead{background-color:#3f87a6;color:#fff}"
		"caption{padding:10px 0;font-size:1.5em}table{font-family:arial,sans-serif;border-collapse:collapse;width:100%}"
		"td,th{border:1px solid #ddd;text-align:left;padding:8px}tr:nth-child(even){background-color:#ddd}</style>"
		"<title>" << title << "</title></head><body><table><caption>" << title << "</caption><thead><tr>";

	for (const auto &col : *column_names)
		ofs << "<th>" << col << "</th>";

	ofs << "</tr></thead><tbody>";

	for (const std::vector<std::string*> *row : *data) {
		ofs << "<tr>";
		for (const std::string *data : *row) {
			ofs << "<td>" << *data << "</td>";
		}
		ofs << "</tr>";
	}

	ofs << "</tbody></table></center></body></html>";
	ofs.close();
	return true;
}

/**
* @brief Sorts the table by the column specified in the 'sort_by' parameter
* @param sort_by column by which we want to sort the data
* @return true if sorting was successfull, otherwise false
*/
bool Table::Sort(const char * sort_by)
{
	//we find the column by which we are sorting the table
	long col = (long)(std::find(column_names->begin(), column_names->end(), sort_by) - column_names->begin());

	if (col >= column_names->size()) {
		std::cout << "ERROR: Column with name '" << sort_by << "' does not exist!" << std::endl;
		return false;
	}

	std::sort(data->begin(), data->end(), [col](std::vector<std::string*>* ac, std::vector<std::string*>* bc) {
		std::string *a = ac->at(col), *b = bc->at(col);

		//if the first string is smaller return true
		if (a->size() < b->size()) {
			return true;
		}
		else if (a->size() == b->size()) {
			//compare strings by ascii value, we only do this if the strings are the same size
			for (unsigned int i = 0; i < a->size(); i++) {
				//if the first char is smaller, return true, if the second one is smaller, return false, if they are the same continue the for loop
				if (a->at(i) < b->at(i))
					return true;
				else if (a->at(i) == b->at(i))
					continue;
				else
					return false;
			}
		}
		return false;
	});

	return true;
}

/**
* @brief Gets the position of the column in the data
* @param name Name of the column
* @return Column position
*/
int Table::GetColumnPosition(const char * name)
{
	auto it = std::find(column_names->begin(), column_names->end(), name);
	if (it == column_names->end())
	{
		std::cout << "[ERROR]: Column with name '" << name << "'does not exist." << std::endl;
		return -1;
	}
	else
	{
		return (int)std::distance(column_names->begin(), it);
	}
}

/**
* @brief Finds first occurence of data in the column
* @param column Column where we should search for the data
* @param what What should we search for
* @return Row where the data was found if successfull, otherwise -1
*/
int Table::Find(const char * column, const char * what)
{
	int col = GetColumnPosition(column);

	for (int i = 0; i < data->size(); i++)
		if (*data->at(i)->at(col) == what)
			return i;

	return -1;
}

/**
* @brief Gets data at column and row
* @param column Column of the data
* @param row Row of the data
* @return Reference to the string at the position specified by column and data parameters
*/
std::string& Table::At(const char * column, unsigned int row)
{
	return *this->data->at(row)->at(GetColumnPosition(column));
}

/**
* @brief Prints the table to console
*/
void Table::Print() {
	std::cout << std::endl;
	for (const std::vector<std::string*> *row : *data) {
		std::cout << "|";
		for (int i = 0; i < row->size(); i++)
			std::cout << column_names->at(i) << ": " << std::setw(6) << *row->at(i) << "| ";
		std::cout << std::endl;
	}
}

/**
* @brief Gets the total size (rows) of the table
* @return Size of the table
*/
unsigned int Table::Size()
{
	return (unsigned int)data->size();
}

/**
* @brief Adds a row to the table
* @param row Pointer to a vector of pointers to string
*/
void Table::Add(std::vector<std::string*>* row)
{
	data->push_back(row);
}

/**
* @brief Removes row from the table
* @param row Row which we want to remove
*/
void Table::Remove(unsigned int row)
{
	if (row > 0 && row < data->size()) {
		Data::iterator it = data->begin();
		std::advance(it, row);

		for (const std::string * cell : *(*it)) {
			delete cell;
		}
		delete (*it);

		data->erase(it);
	}
	else {
		std::cout << "[ERROR] Could not remove row " << row << " because it does not exist." << std::endl;
	}
}

/**
* @brief Adds a column to the table
* @param name Name of the column
* @param default_value Default value of each cell in this column
*/
void Table::AddColumn(const char * name, const char * default_value)
{
	column_names->push_back(name);
	for (std::vector<std::string*> *row : *data)
		row->push_back(new std::string(default_value));
}