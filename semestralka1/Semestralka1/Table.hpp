#pragma once
#include "Common.hpp"

typedef std::vector<std::vector<std::string*>*> Data;

/**
* @class Table
* @brief Generic table of strings implementation
*/
class Table {
	Data *data;
	std::vector<std::string> * column_names;

public:
	//constructors and destructors
	Table(Data *data, std::initializer_list<std::string> names) : data(data) { column_names = new std::vector<std::string>(names); };
	Table(std::initializer_list<std::string> names) : data(new Data()) { column_names = new std::vector<std::string>(names); };
	Table(std::vector<std::string> &names) : data(new Data()), column_names(new std::vector<std::string>(names)) { };

	/**
	* @brief Table destructor
	* Deletes all cells and rows
	*/
	~Table() {
		for (const std::vector<std::string*> * row : * data) {
			for (const std::string * cell : * row) {
				delete cell;
			}
			delete row;
		}

		delete data;
		delete column_names;
	}

	//functions
	static Table* Join(Table &a, Table &b, const char * join_by);

	//methods
	bool Load(const char * filename, char delimeter = ',');
	bool Save(const char * filename, char delimeter = ',');
	bool ExportHtml(const char * filename, const char * title);
	bool Sort(const char * sort_by);
	int GetColumnPosition(const char * name);
	int Find(const char * column, const char * what);
	std::string& At(const char * column, unsigned int row);
	void Print();
	unsigned int Size();
	void Add(std::vector<std::string*> * row);
	void Remove(unsigned int row);
	void AddColumn(const char * name, const char * default_value);

	//operators
	/**
	* @brief Overloaded operator []
	* Gets the row of the table
	* @param row Row
	* @return Pointer to the row
	*/
	inline std::vector<std::string*>* operator[] (unsigned int row) {
		return this->data->at(row);
	}
};