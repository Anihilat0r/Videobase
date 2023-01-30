#include "decls.h"

/*
	In this file we have the functions that allow the user to perform certain actions
	presented in the menus. The functions presented here are not members of any class.
*/

/*---------------------------------------------------------- Employee signup ----------------------------------------------------------*/
void signup(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, employee& current) {

	int duplicate;

	do {

		int adder = 0;
		
		cout << "Create username : ";
		current.SetUsername(user_input_log());

		//Unique id keys bcs usernames are unique as explained below.
		for (char& i : current.GetUsername()) {
			adder += int(i);
		};

		//Check if the username entered already exists in the employee or client data.
		//If it does, it is not accepted and the user is asked to input a different value.
		duplicate = employee_list.count(adder) + customer_list.count(adder);

		if (duplicate) cout << "The username chosen already exists, please enter a different one.\n";
		else current.SetId(adder);

	} while (duplicate);

	cout << "Enter your full name : ";
	current.SetName(user_input_other());

	cout << "Create password : ";
	current.SetPassword(user_input_log());

	employee_list[current.GetId()] = current;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------- Customer signup -----------------------------------------------------------*/

void signup(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, customer& current) {

	int duplicate;

	do {

		int adder = 0;

		cout << "Create username : ";
		current.SetUsername(user_input_log());

		//Unique id keys because usernames are unique as explained below.
		for (char& i : current.GetUsername()) {
			adder += int(i);
		};

		//Check if the username entered already exists in the employee or client data.
		//If it does, it is not accepted and the user is asked to input a different value.
		duplicate = employee_list.count(adder) + customer_list.count(adder);

		if (duplicate) cout << "The username chosen already exists, please enter a different one.\n";
		else current.SetId(adder);

	} while (duplicate);

	cout << "Enter your full name : ";
	current.SetName(user_input_other());

	cout << "Create password : ";
	current.SetPassword(user_input_log());

	customer_list[current.GetId()] = current;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------- Customer or employee login --------------------------------------------------------*/

void login(std::unordered_map<int, employee>& employee_list, std::unordered_map<int, customer>& customer_list, std::vector<movie>& movie_list) {
	
	int adder = 0;
	string un, ps;


	cout << "Please enter your username : ";
	un = user_input_log();

	cout << "Please enter your password : ";
	ps = user_input_log();

	for (char& i : un) {
		adder += int(i);
	};

	if (employee_list.count(adder) != 0) {

		if (employee_list.find(adder)->second.GetPassword() == ps) {

			//Present the available actions for employees.
			employee_menu(movie_list);
		}
		else cout << "Wrong username or password!!!\n";
	}
	else if (customer_list.count(adder) != 0) {

		if (customer_list.find(adder)->second.GetPassword() == ps) {

			//Present the available actions for customers.
			customer_menu(movie_list, customer_list, adder);
		}
		else cout << "Wrong username or password!!!\n";
	}
	else
	{
		cout << "Wrong username or password!!!\n";
	}
};

/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------- Display the movie listings --------------------------------------------------------*/

void print_list(std::vector<movie>& list, string mode) {

	if (list.empty()) {
		cout << "There are no movies available right now.\n";
		return;
	}

	if (mode == "admin") {
		cout << "The current movie catalogue is : \n";
		for (movie& i : list) {
			cout << "Title : " << i.GetTitle() << " | Year released : " << i.GetYear()
				<< " | Stock : " << i.GetStock() << " | Number of copies available : " << i.GetCopies()
				<< " | Score : " << i.GetScore() << " | Cost per day : " << i.GetCostperday() << '\n';
		};
	}
	else {
		bool no_copies = true;

		cout << "The current movie catalogue is : \n";
		for (movie& i : list) {
			if (i.GetCopies() > 0) {
				cout << "Title : " << i.GetTitle() << " | Year released : " << i.GetYear()
					<< " | Score : " << i.GetScore() << " | Cost per day : " << i.GetCostperday() << '\n';
				no_copies = false;
			}
		};
		if (no_copies == true) cout << "Empty.\n";
	}
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------- Display employee data ----------------------------------------------------------*/

void print_list(std::unordered_map<int, employee> employee_list) {

	if (employee_list.empty()) {
		cout << "There is no employee yet.\n";
		return;
	}
	
	cout << "The current employees are : \n";
	for (auto& [i, member] : employee_list) {
		cout << "Username : " << member.GetUsername() << " | Password : " << member.GetPassword() << " | Full name : " << member.GetName()
			<< " | Employee's salary : " << member.GetSalary() << '\n';
	};
};

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------- Display customer data ----------------------------------------------------------*/

void print_list(std::unordered_map<int, customer> customer_list) {

	if (customer_list.empty()) {
		cout << "There are no customers yet.\n";
		return;
	}
	
	cout << "The current customers are : \n";
	for (auto& [i, member] : customer_list) {
		cout << "Username : " << member.GetUsername() << " | Password : " << member.GetPassword() << " | Full name : " << member.GetName()
			<< " | Current movie's rent date : " << member.GetRentDate()
			<< " | Current movie's cost/day : " << member.GetCost() << '\n';
	};
};

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------- Check user input for certain illegal characters ---------------------------------------------*/

string user_input_log() {

	bool valid_input = true;
	string user_input;
	const int none = string::npos;

	do {

		valid_input = true;

		std::getline(cin, user_input);
		
		if (user_input.find('|') != none || user_input.find(' ') != none || user_input.find("\\") != none) {
			cout << "The characters : '|', empty space, '\\' are not accepted.\n"
				<< "Please try again.\n";
			valid_input = false;
		}
	} while (!valid_input);

	return user_input;
}

string user_input_other() {

	bool valid_input = true;
	string user_input;
	const int none = string::npos;

	do {

		valid_input = true;

		std::getline(cin, user_input);

		if (user_input.find('|') != none || user_input.find("\\") != none) {
			cout << "The characters : '|' and '\\' are not accepted.\n" << "Please try again.\n";
			valid_input = false;
		}
	} while (!valid_input);

	return user_input;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------- Functions for managing the files that keep data about customers, employees and movies --------------------------*/

bool is_empty(std::fstream& pFile)
{
	return pFile.peek() == std::fstream::traits_type::eof();
}

void load_movies(std::vector<movie>& movie_list) {

	movie m1;
	string temp;
	std::fstream file_handler;
	file_handler.open("movie_data.txt", std::fstream::in);

	//Check if all objects got extracted
	while (!is_empty(file_handler)) {

		//Get read values of the object to import to vector
		std::getline(file_handler, temp, '|');
		m1.SetTitle(temp);
		std::getline(file_handler, temp, '|');
		m1.SetYear(stoi(temp));
		std::getline(file_handler, temp, '|');
		m1.SetStock(stoi(temp));
		std::getline(file_handler, temp, '|');
		m1.SetCopies(stoi(temp));
		std::getline(file_handler, temp, '|');
		m1.SetScore(stof(temp));
		std::getline(file_handler, temp, '\n');
		m1.SetCostperday(stof(temp));

		//After all the values are set transfer the object in the vector
		movie_list.push_back(m1);
	}
	file_handler.close();
};

void load_customers(std::unordered_map<int, customer>& customer_list) {

	customer c1;
	string temp;
	std::fstream file_handler;
	file_handler.open("customer_data.txt", std::fstream::in);

	//Check if all objects got extracted
	while (!is_empty(file_handler)) {

		//Get read values of the object to import to vector
		std::getline(file_handler, temp, '|');
		c1.SetId(stoi(temp));
		std::getline(file_handler, temp, '|');
		c1.SetName(temp);
		std::getline(file_handler, temp, '|');
		c1.SetUsername(temp);
		std::getline(file_handler, temp, '|');
		c1.SetPassword(temp);
		std::getline(file_handler, temp, '|');
		c1.SetCurrentMovie(temp);
		std::getline(file_handler, temp, '|');
		c1.SetRentDate(stoi(temp));
		std::getline(file_handler, temp, '|');
		c1.SetCost(stof(temp));
		std::getline(file_handler, temp, '\n');
		c1.SetMovieYear(stoi(temp));

		//After all the values are set transfer the object in the map
		customer_list[c1.GetId()] = c1;
	};
	file_handler.close();
};

void load_employees(std::unordered_map<int, employee>& employee_list) {

	employee s1;
	string temp;
	std::fstream file_handler;
	file_handler.open("employee_data.txt", std::fstream::in);
	
	//Check if all objects got extracted
	while (!is_empty(file_handler)) {

		//Get read values of the object to import to vector
		std::getline(file_handler, temp, '|');
		s1.SetId(stoi(temp));
		std::getline(file_handler, temp, '|');
		s1.SetName(temp);
		std::getline(file_handler, temp, '|');
		s1.SetUsername(temp);
		std::getline(file_handler, temp, '|');
		s1.SetPassword(temp);
		std::getline(file_handler, temp, '\n');
		s1.SetSalary(stoi(temp));

		//After all the values are set transfer the object in the map
		employee_list[s1.GetId()] = s1;
	}
	file_handler.close();
}

void save_movies(std::vector<movie>& movie_list) {

	std::fstream file_handler;
	file_handler.open("movie_data.txt", std::fstream::out | std::fstream::trunc);

	//Pass every value of movie "i" separated by | one object per line, in order for files to be readable
	for (auto& i : movie_list) {
		file_handler << i.GetTitle() << "|" << i.GetYear() << "|" << i.GetStock()
			<< "|" << i.GetCopies() << "|" << i.GetScore() << "|" << i.GetCostperday() << '\n';
	}
	file_handler.close();
};

void save_customers(std::unordered_map<int, customer>& customer_list) {

	std::fstream file_handler;
	file_handler.open("customer_data.txt", std::fstream::out | std::fstream::trunc);

	//Pass every value of customer "i" separated by | one object per line, in order for files to be readable
	for (auto& [i, member] : customer_list) {
		file_handler << member.GetId() << "|" << member.GetName() << "|" << member.GetUsername() << "|" << member.GetPassword() 
			<< "|" << member.GetCurrentMovie() << "|" << member.GetRentDate() << "|" << member.GetCost() << "|" << member.GetMovieYear() << '\n';
	}
	file_handler.close();
};

void save_employee(std::unordered_map<int, employee>& employee_list) {

	std::fstream file_handler;
	file_handler.open("employee_data.txt", std::fstream::out | std::fstream::trunc);

	//Pass every value of employee "i" separated by | one object per line, in order for files to be readable
	for (auto& [i, member] : employee_list) {
		file_handler << member.GetId() << "|" << member.GetName() << "|" << member.GetUsername() << "|" << member.GetPassword()
			<< "|" << member.GetSalary() << '\n';
	}
	file_handler.close();
};

/*-------------------------------------------------------------------------------------------------------------------------------------------*/

