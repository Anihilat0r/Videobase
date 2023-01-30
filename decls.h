#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <fstream>

using std::cin, std::cout, std::string;

//Used to check user inputs for illegal characters
string user_input_log();
string user_input_other();

/*------------------------------------ Movie class and functions handling movie objects ------------------------------------*/

class movie {
	string title;
	float score, cost_per_day;
	int year_released, copies_available, stock;

public:
	movie();

	string GetTitle();
	int GetYear();
	float GetCostperday();
	float GetScore();
	int GetCopies();
	int GetStock();

	void SetTitle(string title);
	void SetYear(int year);
	void SetCostperday(float cost);
	void SetScore(float score);
	void SetCopies(int copies);
	void SetStock(int stock);

	void modify_copies(std::vector<movie>& movie_list);
	void modify_existing_listing(std::vector<movie>& movie_list, movie& current_movie);

	~movie();
};

void movie_catalogue_modification(std::vector<movie>& list);
void print_list(std::vector<movie>& list, string mode);

void load_movies(std::vector<movie>& movie_list);
void save_movies(std::vector<movie>& movie_list);

/*------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------ user class and subclasses for handling users ------------------------------------*/

class user {
protected:
	string name, username, password;
	int id;
public:
	user();

	void SetId(int id);
	void SetUsername(string un);
	void SetName(string nm);
	void SetPassword(string ps);
	int GetId();
	string GetName();
	string GetUsername();
	string GetPassword();
};

class employee : public user {
	int salary;

public:
	employee();

	int GetSalary();
	void SetSalary(int salary);
	void modify_employee() {}

	~employee();
};

void print_list(std::unordered_map<int, employee> employee_list);

class customer : public user {

	float current_cost;
	time_t rent_date;
	string current_movie;
	int movie_year;

public:
	customer();

	float GetCost();
	time_t GetRentDate();
	string GetCurrentMovie();
	int GetMovieYear();

	void SetCost(float cost);
	void SetRentDate(int rent_date);
	void SetCurrentMovie(string current_movie);
	void SetMovieYear(int movie_year);

	void rent_movie(std::vector<movie> movie_list);
	void return_movie(std::vector<movie> movie_list);

	~customer();
};

void print_list(std::unordered_map<int, customer> customer_list);

//Functions to create a user account or log into an existing one
void signup(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, employee& employee_obj);
void signup(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, customer& cust_obj);
void login(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, std::vector<movie>& movie_list);

//Functions to present to the user the available actions
void signup_menu(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list);
void admin_menu(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list);
void customer_menu(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id);
void employee_menu(std::vector<movie>& movie_list);

//Functions to load data from the .txt files into the corresponding data structure or store data to said files
void save_customers(std::unordered_map<int, customer>& customer_list);
void load_customers(std::unordered_map<int, customer>& customer_list);
void save_employee(std::unordered_map<int, employee>& employee_list);
void load_employees(std::unordered_map<int, employee>& employee_list);
