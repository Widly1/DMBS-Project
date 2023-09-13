#include <stdlib.h>
#include <iostream>
/*
 Include directly the different
 headers from cppconn/ and mysql_driver.h + mysql_util.h
 (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

// This program retrieves all of the musicians

// Compile:
// g++ -I/usr/include GameBox_menu.cpp -o GameBox_menu -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./GameBox_menu
// 
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 sql::PreparedStatement  *prep_stmt;

void findall();
void findbyid();
void findcompatibility();
void addgame();

int main(void)
{

try {

   
 /* Create a connection */
 driver = get_driver_instance();

  
con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL GameBox database */
    
 con->setSchema("GameBox");
 //stmt = con->createStatement();
    
 int option = 6;
 
 while (option != 5) {
     
     cout << endl;
     cout << "1. Add a game" << endl;
     cout << "2. Find a game by id" << endl;
     cout << "3. Find if a game is compatible with console" << endl;
     cout << "4. Show all game" << endl;
     cout << "5. Exit" << endl << endl;
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
        
        case 1: addgame();
                break;  

        case 2: findbyid();
                 break;

        case 3: findcompatibility();
                 break;
             
        case 4: findall();
                 break;
        
        case 5:
        cout << "Exiting Program..." << endl;
                break;
                default:
                cout << "Invalid choice, please choose one of the options above.";
       
     }
 }
 

 delete res;
 delete stmt;
 delete con;
} catch (sql::SQLException &e) {
 cout << "# ERR: SQLException in " << __FILE__;
 cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
 cout << "# ERR: " << e.what();
 cout << " (MySQL error code: " << e.getErrorCode();
 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
cout << endl;
return EXIT_SUCCESS;

}
  /*Case 4        findall()*/
 void findall() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from Product");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     

     cout << res->getString("product_name") << " ";
     cout << res->getString("product_genre") << " ";
     cout << res->getString("product_star_rating") << " ";
     cout << res->getString("product_publisher") << " ";
     cout << res->getDouble("product_price") << " ";
     cout << res->getString("product_release_date") << " " << endl;
 
 }
     
 }


            /*Case 3     findcompaitbility();*/
void findcompatibility() {
    int product_id, console_id;
    string product_name, console_type;

    cout << "Enter the game ID: ";
    cin >> product_id;

    cout << "Enter the console ID: ";
    cin >> console_id;

    prep_stmt = con->prepareStatement("SELECT Console.console_type, Product.product_name, Compatibility.compatibility FROM Console, Product, Compatibility WHERE Console.console_id = ? AND Product.product_id = ? AND Compatibility.product_id = Product.product_id AND Compatibility.console_id = Console.console_id");

    prep_stmt->setInt(1, console_id);
    prep_stmt->setInt(2, product_id);

    res = prep_stmt->executeQuery();

    if (res->next()) {
        console_type = res->getString("console_type");
        product_name = res->getString("product_name");
        string compatibility = res->getString("compatibility");

        cout << "Product Name: " << product_name << endl;
        cout << "Console Type: " << console_type << endl;
        cout << "Compatibility: " << compatibility << endl;
        
    } else {
        cout << "There are no compatible products for the selected console and game." << endl;
    }
}



            /*Case 2 findbyid() */
void findbyid() {
     
 
int product_id;
string product_name, product_genre, product_star_rating, product_publisher, product_release_date;
double product_price;
      

    
 cout << "Enter the game ID : ";
 cin >> product_id;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM Product WHERE product_id = ?");
prep_stmt->setInt(1, product_id);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("product_name") << "   ";
      cout  << endl;

     cout << res->getString("product_genre") << "   ";

      cout  << endl;

     cout << res->getString("product_star_rating") << "   ";
     cout  << endl;

     cout << res->getString("product_publisher") << "   ";
     cout  << endl;

     cout << res->getDouble("product_price") << "   ";
     cout  << endl;

      cout << res->getString("product_release_date");
     cout  << endl;

cout << product_name;
cout << product_genre;
cout << product_star_rating;
cout << product_publisher;
cout << product_price;
cout << product_release_date; 
cout << endl;
 }

 }
     
 


 /*Case 1           addgame();*/

 void addgame() {
    int product_id;
    string product_star_rating;
    double product_price;
    string product_name, product_genre, product_publisher, product_release_date;

    cout << "Enter variables for Product Table" << endl;

    cin.ignore(); // ignore the newline character left in the buffer

    cout << "product_name : ";
    std::getline(std::cin, product_name);

    cout << "product_genre : ";
    std::getline(std::cin, product_genre);

    cout << "product_star_rating : ";
    cin >> product_star_rating;

    cin.ignore(); // ignore the newline character left in the buffer

    cout << "product_publisher: ";
   std::getline(std::cin >> std::ws, product_publisher);

    cout << "product_price : ";
    cin >> product_price;

    cin.ignore(); // ignore the newline character left in the buffer

    cout << "product_release_date: ";
    std::getline(std::cin, product_release_date);

    con->setSchema("GameBox");
    prep_stmt = con->prepareStatement("insert into Product (product_name, product_genre, product_star_rating, product_publisher, product_price, product_release_date) VALUES (?,?,?,?,?,?)");

    prep_stmt->setString(1, product_name);
    prep_stmt->setString(2, product_genre);
    prep_stmt->setString(3, product_star_rating);
    prep_stmt->setString(4, product_publisher);
    prep_stmt->setDouble(5, product_price);
    prep_stmt->setString(6, product_release_date);

    prep_stmt->execute();

    cout << endl << "Game added successfully!" << endl;
}



