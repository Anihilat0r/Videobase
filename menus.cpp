#include "decls.h"

/*
	This file contains the menus that present the user with options and call the corresponding functions.
*/

void try_renting(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id);
void try_returning(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id);

void signup_menu(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list) {

	string user_choice;
	bool valid_input = true;

	do {

		valid_input = true;

		cout << "Select the account you want to create : \n";
		cout << "0 ---- Exit account creation.\n";
		cout << "1 ---- Customer account.\n";
		cout << "2 ---- Employee account.\n";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) {
			cout << "Please enter a valid answer.\n";
			valid_input = false;
		}
		else if (user_choice[0] == '0') {
			break;
		}
		else if (user_choice[0] == '1') {
			customer c1;
			signup(employee_list, customer_list, c1);
			
		}
		else if (user_choice[0] == '2') {
			employee s1;
			signup(employee_list, customer_list, s1);
		}
		else {
			cout << "Please enter a valid answer.\n";
			valid_input = false;
		}
	} while (!valid_input);
}

void customer_menu(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id) {

	string user_choice;

	do {

		cout << "Enter the number corresponding to the action of your choice\n";
		cout << "0 ---- Exit menu.\n";
		cout << "1 ---- Rent a movie.\n";
		cout << "2 ---- Return movie.\n";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) {
			cout << "Please enter a valid answer.\n";
		}
		else if (user_choice[0] == '0') {
			break;
		}
		else if (user_choice[0] == '1') {

			try_renting(movie_list, customer_list, id);
		}
		else if (user_choice[0] == '2') {

			try_returning(movie_list, customer_list, id);
		}
		else {
			cout << "Please enter a valid answer.\n";
		}
	} while (1);
}

void employee_menu(std::vector<movie>& movie_list) {

	string user_choice;

	do {

		cout << "Enter the number corresponding to the action of your choice\n";
		cout << "0 ---- Exit menu.\n";
		cout << "1 ---- Add/remove movies to/from the catalogue.\n";
		cout << "2 ---- Print the movie catalogue.\n";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) {
			cout << "Please enter a valid answer.\n";
		}
		else if (user_choice[0] == '0') {
			break;
		}
		else if (user_choice[0] == '1') {
			movie_catalogue_modification(movie_list);
		}
		else if (user_choice[0] == '2') {
			print_list(movie_list, "admin");
		}
		else {
			cout << "Please enter a valid answer.\n";
		}
	} while (1);
}

void admin_menu(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list) {

	string user_choice;

	do {

		cout << "Enter the number corresponding to the action of your choice\n";
		cout << "0 ---- Exit menu.\n";
		cout << "1 ---- Print customer data.\n";
		cout << "2 ---- Print employee data.\n";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) {
			cout << "Please enter a valid answer.\n";
		}
		else if (user_choice[0] == '0') {
			break;
		}
		else if (user_choice[0] == '1') {
			print_list(customer_list);
		}
		else if (user_choice[0] == '2') {
			print_list(employee_list);
		}
		else {
			cout << "Please enter a valid answer.\n";
		}
	} while (1);
}

void try_renting(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id) {

	if (customer_list.find(id)->second.GetCost() == 0) {

		try {
			customer_list.find(id)->second.rent_movie(movie_list);
		}
		catch (const std::invalid_argument& ia) {
			std::cerr << "The value entered is not appropriate : " << ia.what() << '\n';
		}
	}
	else cout << "You have already rented a movie, please return it before renting a different one.\n";
}

void try_returning(std::vector<movie>& movie_list, std::unordered_map<int, customer>& customer_list, int id) {

	if (customer_list.find(id)->second.GetCost() != 0) {
		customer_list.find(id)->second.return_movie(movie_list);
	}
	else cout << "Can't return a movie before renting one.\n";
}
