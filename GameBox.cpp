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
using namespace sql;
using namespace std;

// This program retrieves all of the musicians

// Compile:
// g++ -I/usr/include GameBox.cpp -o GameBox -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./GameBox
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
void updatecus();
void showorders();
void deleteorder();
void deletegame();
void countzip();

int main(void)
{

try {

   
 /* Create a connection */
 driver = get_driver_instance();

  
con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL GameBox database */
    
 con->setSchema("GameBox");
 //stmt = con->createStatement();
    
 int option = 11;
 
 while (option != 10) {
     cout << endl;
     cout << " Program Menu ";
     cout << endl;
     cout << "1. Add a game" << endl;
     cout << "2. Find a game by id" << endl;
     cout << "3. Find if a game is compatible with console" << endl;
     cout << "4. Show all game" << endl;
     cout << "5. Delete a game " << endl;
     cout << "6. Update a customer info" << endl;
     cout << "7. Show Orders" << endl;   
     cout << "8. Delete a Order" << endl;
     cout << "9. Count Customer Zip Code" << endl;

     cout << "10.Exit" << endl << endl;
     
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
        

         case 5: deletegame();
                  break;

        case 6: updatecus();
                  break;

        case 7: showorders();
                  break;

        case 8: deleteorder();
                  break;

        case 9: countzip();
                    break;

        case 10:
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

/*      Case 9 countzip();*/

void countzip(){

int cus_zip_code;
cout << "Enter zip code: ";
    cin >> cus_zip_code;

 
   prep_stmt = con->prepareStatement("SELECT COUNT(*) FROM Customers WHERE cus_zip_code = ?");
    prep_stmt->setInt(1, cus_zip_code);

    ResultSet *res = prep_stmt->executeQuery();
    if (res->next()) {
        int count = res->getInt(1);
        cout << endl;
        cout << "Area code " << cus_zip_code << ": " << count << endl;
    }
    delete res;
    delete prep_stmt;
}


/*    Case 8   deleteorder()*/


void deleteorder() {
    int cus_id;
    cout << "Enter the customer ID: ";
    cin >> cus_id;

    

    prep_stmt = con->prepareStatement("DELETE FROM Orders WHERE Orders.cus_id = ? ");
    prep_stmt->setInt(1, cus_id);
    

    int result = prep_stmt->executeUpdate();
    if (result > 0) {
        cout << "Customer order deleted successfully." << endl;
    } else {
        cout << "Customer Order not found for the given id " << endl;
    }
}







/* Case 7    showorders();*/

void showorders() {
   
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from Orders");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
        cout << "     Order Details" << endl << endl;
      
     cout << " Order Number: " << res->getString("order_num") << " ";
     cout << endl;
 
     cout << " Customer Id: " << res->getString("cus_id") << " ";
     cout << endl;

     cout << " Delivery Date: "  << res->getString("delivery_date") << " ";
     cout << endl;
     cout <<  " Order Type: " <<res->getString("order_type") << " ";
     cout << endl <<endl;
 }
     
 }

    
/*      CASE 6 updatecus(); */
 void updatecus(){
     int cus_id;
     string cus_phone_num, cus_email;

cout << "Enter customer ID: " ;
cin >> cus_id; 
cout << endl;


cout << "Enter customer phone number: " ;
cin >> cus_phone_num; 
cout << endl;


cout << "Enter customer email address: " ;
cin >> cus_email; 
cout << endl;


      prep_stmt = con->prepareStatement("UPDATE Customers SET cus_phone_num=?, cus_email=? WHERE cus_id=?");
    prep_stmt->setString(1, cus_phone_num);
    prep_stmt->setString(2, cus_email);
    prep_stmt->setInt(3, cus_id);

int rowsUpdated = prep_stmt->executeUpdate();

if (rowsUpdated > 0) {
        cout << "Customer info updated successfully." << endl;
    } else {
        cout << "Customer info update failed! " << endl;
    }


    cout << "Customer ID: " << cus_id << endl;
    cout << "Updated Customer Phone Number: " << cus_phone_num <<endl;
    cout << "Updated Customer Email: " << cus_email << endl;
}




 









      /* Case 5  deletegame()*/


void deletegame() {
    int product_id;
    cout << "Enter the game ID: ";
    cin >> product_id;

    

    prep_stmt = con->prepareStatement("DELETE FROM Product WHERE product_id = ? ");
    prep_stmt->setInt(1, product_id);
    

    int result = prep_stmt->executeUpdate();
    if (result > 0) {
        cout << "Game deleted successfully." << endl;
    } else {
        cout << "No video game found for the given id " << endl;
    }
}




  /*Case 4        findall()*/
 void findall() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from Product");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
    cout << "Game ID: " << res->getInt("product_id") << " ";
     cout <<endl;

     cout << "Name of Game: " << res->getString("product_name") << " ";
     cout <<endl;

     cout << "Genre of Game: "  << res->getString("product_genre") << " ";
     cout <<endl;

     cout << "Game Rating: " << res->getString("product_star_rating") << " ";
     cout <<endl;

     cout << "Game Publisher: " << res->getString("product_publisher") << " ";
     cout <<endl;

     cout << "Price for Game: " << res->getDouble("product_price") << " ";
     cout <<endl;

     cout << "Game Release Date:" << res->getString("product_release_date") << " " << endl;
     cout <<endl;
 
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
     
     cout  << "Game Name: " << res->getString("product_name") << "   ";
      cout  << endl;

     cout << "Game Genre: " << res->getString("product_genre") << "   ";

      cout  << endl;

     cout << "Game Rating: "<< res->getString("product_star_rating") << "   ";
     cout  << endl;

     cout << "Publisher: "<< res->getString("product_publisher") << "   ";
     cout  << endl;

     cout << "Price : "<< res->getDouble("product_price") << "   ";
     cout  << endl;

     cout << "Release Date: "<< res->getString("product_release_date") << "   ";
     cout  << endl;

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



