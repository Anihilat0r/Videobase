#include "decls.h"

/*----------------------- Data structure instantiation for handling movies, employees and customers ----------------------*/
std::vector<movie> movie_list;
std::unordered_map<int, employee> employee_list;
std::unordered_map<int, customer> customer_list;
/*------------------------------------------------------------------------------------------------------------------------*/

int main() {

	load_movies(movie_list);
	load_customers(customer_list);
	load_employees(employee_list);
	
	string user_choice;
	bool exit_menu = false;

	do {

		cout << "Enter the number corresponding to the action of your choice\n";
		cout << "0 ---- Exit the application.\n";
		cout << "1 ---- Sign up.\n";
		cout << "2 ---- Log in.\n";
		cout << "3 ---- Admin menu.\n";
		std::getline(cin, user_choice);

		if (user_choice.size() != 1) {
			cout << "Please enter a valid answer.\n";
		}
		else if (user_choice[0] == '0') {
			exit_menu = true;
		}
		else if (user_choice[0] == '1') {
			signup_menu(employee_list, customer_list);
		}
		else if (user_choice[0] == '2') {
			login(employee_list, customer_list, movie_list);
		}
		else if (user_choice[0] == '3') {
			admin_menu(employee_list, customer_list);
		}
		else {
			cout << "Please enter a valid answer.\n";
		}
	} while (!exit_menu);

	//Save data to files before exiting
	save_movies(movie_list);
	save_customers(customer_list);
	save_employee(employee_list);

	return 0;
}


