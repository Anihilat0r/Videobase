#include "decls.h"
#include <float.h>

/*
	This file contains the definitions for the members of the "movies" class.
*/

movie::movie() {
	title = "";
	score = 0;
	cost_per_day = 0;
	year_released = 0;
	copies_available = 0;
	stock = 0;
}

string movie::GetTitle() {
	return title;
}
int movie::GetYear() {
	return year_released;
}
float movie::GetCostperday() {
	return cost_per_day;
}
float movie::GetScore() {
	return score;
}
int movie::GetCopies() {
	return copies_available;
}
int movie::GetStock() {
	return stock;
}

void movie::SetTitle(string title) {
	this->title = title;
}
void movie::SetYear(int year) {
	this->year_released = year;
}
void movie::SetCostperday(float cost) {
	this->cost_per_day = cost;
}
void movie::SetScore(float score) {
	this->score = score;
}
void movie::SetCopies(int copies) {
	this->copies_available = copies;
}
void movie::SetStock(int stock) {
	this->stock = stock;
}

movie::~movie() {
	//cout << "Movie : " << id << " deleted.\n";
}

void movie::modify_copies(std::vector<movie>& movie_list) {
	bool found = false;
	string temp_data;
	int int_data;
	float float_data;

	//Get the current date in order to check movie release year validity
	tm current_time;
	time_t now = time(0);
	
	localtime_r(&now, &current_time);

	cout << "Enter movie title : ";
	this->title = user_input_other();

	cout << "Enter the year it was released (format:YYYY) : ";
	std::getline(cin, temp_data);

	int_data = stoi(temp_data);
	//The earliest motion picture known was made in 1888
	//Check if the lengths of the string input and its integer conversion are equal bcs 
	//stoi() accepts inputs along the lines of "1999abcd" and extracts the integer, which is not desired
	while (temp_data.length() != std::to_string(int_data).length() || int_data < 1888 || int_data > current_time.tm_year + 1900) {

		cout << "The year entered is invalid, please enter the correct one.\n";
		std::getline(cin, temp_data);
		int_data = stoi(temp_data);
	}
	this->year_released = int_data;

	for (movie& i : movie_list) {

		//find movie in vector using title and date
		if (i.title == this->title && i.year_released == this->year_released) {

			modify_existing_listing(movie_list, i);

			found = true;
			break;
		}
	}

	//If the movie soesn't exist in the catalogue enter the rest of its information
	if (found == false) {

		cout << "Enter movie's review score (between 0 - 10) : ";
		std::getline(cin, temp_data);
		float_data = stof(temp_data);

		while (float_data <= 0 || float_data >= 10) {

			cout << "The movie's score entered is invalid, please enter the correct one.\n";
			std::getline(cin, temp_data);
			float_data = stof(temp_data);
		}
		this->score = float_data;

		cout << "Enter the cost of rent per day : ";
		std::getline(cin, temp_data);
		float_data = stof(temp_data);

		while (float_data <= 0 || float_data >= 100) {

			cout << "The movie's cost entered is invalid, please enter the correct one.\n";
			std::getline(cin, temp_data);
			float_data = stof(temp_data);
		}
		this->cost_per_day = float_data;

		cout << "Enter the stock of copies available for this movie : ";
		std::getline(cin, temp_data);
		int_data = stoi(temp_data);

		while (int_data <= 0 || int_data != stof(temp_data)) {

			cout << "The movie's stock number is invalid, please enter the correct one.\n";
			std::getline(cin, temp_data);
			int_data = stof(temp_data);
		}
		this->stock = int_data;
		this->copies_available = this->stock;

		movie_list.push_back(*this);
	}
}

void movie::modify_existing_listing(std::vector<movie>& movie_list, movie& current_movie) {
	int extra_copies, movie_position;
	string temp_data;

	cout << "Enter the number to modify copies : ";
	std::getline(cin, temp_data);

	while (stoi(temp_data) != stof(temp_data)) {

		cout << "The number of copies has to be an integer, please enter the correct one.\n";
		std::getline(cin, temp_data);
	}
	extra_copies = stoi(temp_data);

	//The following conditions work because stock >= copies_available always.
	if (current_movie.copies_available + extra_copies < 0) {
		cout << "Can't remove more copies than the ones we have.";
	}
	else if (current_movie.stock + extra_copies == 0) {
		//Find index of object "i" in vector in order to remove it
		movie_position = &current_movie - &movie_list[0];
		movie_list.erase(movie_list.begin() + movie_position);
	}
	else {
		//Add the extra_copies to the existing stock
		current_movie.stock += extra_copies;
		current_movie.copies_available += extra_copies;
	}
}

void movie_catalogue_modification(std::vector<movie>& movie_list)
{
	string user_choice;
	movie m1;

	cout << "Welcome to the movie catalogue modification!\n";
	do {
		try {
			m1.modify_copies(movie_list);
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "The value entered is not appropriate : " << ia.what() << '\n';
		}

		cout << "Continue modifying the movie catalogue? (Y/N) : ";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) break;

	} while (user_choice[0] == 'Y');

}
