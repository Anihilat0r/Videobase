# Videobase

Videobase is a database manager for a virtual video club. It uses two categories of entities, **movies** and **users**. 
The users are further divided into two sub categories **employees** and **customers**.

The data are stored in 3 individual .txt files that are created after the initial run. These files are named "movie_data"
, "customer_data" and "employee_data" with their values being updated before exiting the main menu. Each file is used to 
store the attributes of the objects belonging to the respective class.

## Available actions

Users can create a customer or employee account and login with their username and password in order to perform the available
actions.

### Employees :
1) Add a new movie and all its attributes to the list
2) Add/Remove copies of an existing movie
3) View all the attributes of the available movies

### Customers :
1) Rent a movie (only one per customer at a time)
2) Return the rented movie 
