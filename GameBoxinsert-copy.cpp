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



// Compile:
// g++ -I/usr/include GameBoxinsert-copy.cpp -o GameBoxinsert-copy -I /usr/local/lib -lmysqlcppconn
//
// Execute:
// ./GameBoxinsert-copy
//

int main(void)
{
 
try {
 
   
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 sql::PreparedStatement *prep_stmt;
   
string product_name, product_genre, product_publisher, product_release_date ,
        console_name, console_type, console_hard_drive_size, console_color, console_condition, console_release_date,      
         cus_name, cus_address, cus_state,cus_email, cus_phone_num, compatibility,
         delivery_date, order_type,product_star_rating;
int product_id, console_fps, console_id, cus_zip_code;

double product_price, console_price;
    cout << "Enter variables for Product Table" << endl;

   

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





    /*
    cout << "Enter variables for Product Table" <<endl;
 cout << "product_name : ";
 std::getline(std::cin, product_name);
 
 cout << "product_genre : ";
 std::getline(std::cin, product_genre);
 
 cout << "product_star_rating : ";
 cin >> product_star_rating;
 
 cout << "product_publisher: ";
 std::getline(std::cin, product_publisher);

 cout << "product_price : ";
cin >> product_price;

 cout << "product_release_date: ";
 cin >>product_name;
  cout << endl;
/*


  /*
    cout << "Enter variables for Console Table" <<endl;

  cout << "console_name : ";
 cin >> console_name;
 
 cout << "console_type : ";
 cin >> console_type;
 
 cout << "console_hard_drive_size : ";
 cin >> console_hard_drive_size;
 
 cout << "console_color: ";
 cin >> console_color;

 cout << "console_price : ";
 cin >> console_price;

 cout << "console_condition: ";
 cin >> console_condition;

 cout << "console_release_date : ";
 cin >> console_release_date;

 cout << "console_fps: ";
 cin >> console_fps;


  cout << endl;
*/
    cout << endl;
    cout << "Enter variables for Customer Table" <<endl;

 cout << "product_id : ";
 cin >> product_id;
     cin.ignore(); // ignore the newline character left in the buffer

 cout << "console_id : ";
 cin >> console_id;
 cout << endl;
    cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_name : ";
 std::getline(std::cin, cus_name);
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_address: ";
std::getline(std::cin, cus_address);
    cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_state : ";
std::getline(std::cin, cus_state);
    cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_zip_code: ";
 cin >> cus_zip_code;
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_email : ";
 cin >> cus_email;
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "cus_phone_num: ";
 cin >> cus_phone_num;
     cin.ignore(); // ignore the newline character left in the buffer


  cout << endl;

    cout << "Enter variables for Compatibility Table" <<endl;

 cout << "product_id: ";
 cin >> product_id;
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "console_id : ";
 cin >> console_id;
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "console_name: ";
 std::getline(std::cin, console_name);
     cin.ignore(); // ignore the newline character left in the buffer


 cout << "console_type : ";
std::getline(std::cin, console_type);
    cin.ignore(); // ignore the newline character left in the buffer


 cout << "compatibility: ";
std::getline(std::cin, compatibility);
    cin.ignore(); // ignore the newline character left in the buffer


  cout << endl;

    cout << "Enter variables for Orders Table" <<endl;

/*
 cout << "cus_id: ";
 cin >> cus_id;
     cin.ignore(); // ignore the newline character left in the buffer
*/


 cout << "delivery_date : ";
std::getline(std::cin, delivery_date);
    cin.ignore(); // ignore the newline character left in the buffer


 cout << "order_type: ";
std::getline(std::cin, order_type);
    cin.ignore(); // ignore the newline character left in the buffer

   cout << endl;


 
 /* Create a connection */
 driver = get_driver_instance();
 
con = driver->connect("tcp://127.0.0.1:3306", "root", "");


/* Connect to the MySQL music database */


con->setSchema("GameBox");
 
prep_stmt = con->prepareStatement("insert into Product (product_name, product_genre, product_star_rating, product_publisher, product_price, product_release_date )" \
                                   "VALUES(?,?,?,?,?,?) ");
                                                                   
                                   
prep_stmt->setString(1, product_name);
prep_stmt->setString(2, product_genre);
prep_stmt->setString(3, product_star_rating);
prep_stmt->setString(4, product_publisher);
prep_stmt->setDouble(5, product_price);
prep_stmt->setString(6, product_release_date);

prep_stmt->executeUpdate();



                                   
prep_stmt = con->prepareStatement("INSERT INTO Customers(cus_name, cus_address, cus_state, cus_zip_code, cus_email, cus_phone_num) VALUES (?, ?, ?, ?, ?, ?)");

// set the parameters for the customer
prep_stmt->setString(1, cus_name);
prep_stmt->setString(2, cus_address);
prep_stmt->setString(3, cus_state);
prep_stmt->setInt(4, cus_zip_code);
prep_stmt->setString(5, cus_email);
prep_stmt->setString(6, cus_phone_num);

// execute the statement
prep_stmt->executeUpdate();

// get the generated cus_id value
res = stmt->executeQuery("SELECT LAST_INSERT_ID()");
int cus_id = 0;
if (res->next()) {
    cus_id = res->getInt(1);
}



prep_stmt = con->prepareStatement("INSERT INTO Orders(product_id, console_id, cus_id, delivery_date, order_type) VALUES (?, ?, ?, ?, ?)");

// set the parameters for the order
prep_stmt->setInt(1, product_id);
prep_stmt->setInt(2, console_id);
prep_stmt->setInt(3, cus_id);
prep_stmt->setString(4, delivery_date);
prep_stmt->setString(5, order_type);

// execute the statement
prep_stmt->executeUpdate();


prep_stmt = con->prepareStatement("insert into Compatibility(product_id, console_id, console_name, console_type, compatibility )" \
                                   "VALUES(?,?,?,?,?)");
prep_stmt->setInt(1, product_id);
prep_stmt->setInt(2, console_id);
prep_stmt->setString(3, console_name);
prep_stmt->setString(4, console_type);
prep_stmt->setString(5, compatibility);

prep_stmt->executeUpdate();


   
 

 delete res;
 delete prep_stmt;
 delete con;

 
   
} 
catch (sql::SQLException &e) {
 cout << "# ERR: SQLException in " << __FILE__;
 cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
 cout << "# ERR: " << e.what();
 cout << " (MySQL error code: " << e.getErrorCode();
 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
cout << endl;
return EXIT_SUCCESS;
}
}





