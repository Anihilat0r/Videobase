#include "decls.h"

/*
	This file contains the definitions for the members of the "user" class and its child classes "employee" and "customer".
*/

user::user() {
	id = 0;
	name = "";
	username = "";
	password = "";
}
void user::SetId(int identity) {
	this->id = identity;
}
void user::SetUsername(string un) {
	this->username = un;
}
void user::SetName(string nm) {
	this->name = nm;
}
void user::SetPassword(string ps) {
	this->password = ps;
}
int user::GetId() {
	return id;
}
string user::GetName() {
	return name;
}
string user::GetUsername() {
	return username;
}
string user::GetPassword() {
	return password;
}

//salary 850 is a random value, currently there isn't a way implemented to update this value.
employee::employee() {
	salary = 850;
}
void employee::SetSalary(int salary) {
	this->salary = salary;
}
int employee::GetSalary() {
	return salary;
}
employee::~employee() {
	//cout << "employee member : " << id << " deleted.\n";
}

customer::customer() {
	current_movie = "<none>";
	movie_year = 0;
	rent_date = 0;
	current_cost = 0;
}
void customer::SetCost(float cost) {
	this->current_cost = cost;
}
void customer::SetRentDate(int date) {
	this->rent_date = date;
}
void customer::SetCurrentMovie(string curr_movie) {
	this->current_movie = curr_movie;
}
void customer::SetMovieYear(int year) {
	this->movie_year = year;
}
string customer::GetCurrentMovie() {
	return current_movie;
}
time_t customer::GetRentDate() {
	return rent_date;
}
float customer::GetCost() {
	return current_cost;
}
int customer::GetMovieYear() {
	return movie_year;
}
customer::~customer() {
	//cout << "Customer : " << id << " deleted.\n";
}

void customer::rent_movie(std::vector<movie> movie_list) {
	
	print_list(movie_list, "customer");
	
	if (movie_list.empty()) return;
	
	string title;
	int year = 0;
	bool found = false;

	//The following variables exist in order to get the current year to check for user input year validity
	tm current_time;
	time_t now = time(0);
	
	localtime_r(&now, &current_time);

	cout << "Enter the title of the movie you would like to rent : ";
	std::getline(cin, title);

	cout << "Enter the year it was released (format:YYYY) : ";
	year = stoi(user_input_log());

	//The earliest motion picture known was made in 1888
	while (year < 1888 || year > current_time.tm_year + 1900) {

		cout << "The year entered is invalid, please enter the correct one.\n";
		year = stoi(user_input_log());
	}

	for (movie& i : movie_list) {

		//find movie in vector using title and date
		if (i.GetTitle() == title && i.GetYear() == year) {

			if (i.GetStock() > 0) {

				i.SetStock(i.GetStock() - 1);
				this->current_movie = i.GetTitle();
				this->movie_year = i.GetYear();
				this->current_cost = i.GetCostperday();
				//save the time the movie was rented
				this->rent_date = time(0);
			}
			else cout << "There are no copies of " << title << " available right now.\n";
			found = true;
			break;
		}
	}
	if (found == false) cout << title << " is not available at our stores.\n";
}

void customer::return_movie(std::vector<movie> movie_list) {

	double days, cost;
	tm return_time, rent_time;
	time_t now = time(0);

	localtime_r(&now, &return_time);
	localtime_r(&this->rent_date, &rent_time);

	//Find the number of days to charge for rent
	days = (now - this->rent_date) / 86400;

	if (int(days) == 0) {
		cout << "The minimum charge for renting " << this->GetCurrentMovie() << " is " << this->GetCost() << '\n';
	}
	//If return time is earlier than rent time means it is the next day of int(days)
	else if (return_time.tm_hour < rent_time.tm_hour + int(days)) {
		cost = int(days + 1) * this->GetCost();
		cout << "That will be " << cost << " for the " << int(days) + 1 << " days of rent.\n";
	}
	else {
		cost = int(days) * this->GetCost();
		cout << "That will be " << int(days) << " for the " << int(days) << " days of rent.\n";
	}

	//Find the movie returned and +1 its stock
	for (movie& i : movie_list) {

		//find movie in vector using title and date
		if (i.GetTitle() == this->current_movie && i.GetYear() == this->movie_year) {

			i.SetStock(i.GetStock() + 1);
			break;
		}
	}

	//Update the current customer's data in the map
	this->current_movie = "<none>";
	this->current_cost = 0;
	this->rent_date = 0;
	this->movie_year = 0;
}
