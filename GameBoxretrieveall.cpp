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
using namespace std;



// Compile:
// g++ -I/usr/include GameBoxretrieveall.cpp -o GameBoxretrieveall -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./GameBoxretrieveall
// 

int main(void)
{
cout << endl;
cout << "SELECT * from Product " << endl;
try {

    
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 /* Create a connection */
 driver = get_driver_instance();

    

con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL gamebox database */
    
 con->setSchema("GameBox");
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from Product");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     cout <<"Product Table" <<endl;

cout << res->getString("product_name")<< " ";
cout << res->getString("product_genre")<< " ";
cout << res->getString("product_star_rating")<< " ";
cout << res->getString("product_publisher")<< " ";
cout << res->getDouble("product_price")<< " ";
cout << res->getString("product_release_date")<< " ";

cout << endl;

cout <<"Console Table" <<endl;
cout << res->getString("console_name")<< " ";
cout << res->getString("console_type")<< " ";
cout << res->getString("console_hard_drive_size")<< " ";
cout << res->getString("console_color")<< " ";
cout << res->getDouble("console_price")<< " ";
cout << res->getString("console_condition")<< " ";
cout << res->getString("console_release_date")<< " ";
cout << res->getInt("console_fps")<< " ";

cout << endl;

 
cout <<"Compatibility Table" <<endl;
cout << res->getInt("product_id")<< " ";
cout << res->getInt("console_id")<< " ";
cout << res->getString("console_name")<< " ";
cout << res->getString("console_type")<< " ";
cout << res->getString("compatibility")<< " ";

cout << endl;


cout <<"Customers Table" <<endl;
cout << res->getInt("product_id")<< " ";
cout << res->getInt("console_id")<< " ";
cout << res->getString("cus_name")<< " ";
cout << res->getString("cus_address")<< " ";
cout << res->getDouble("cus_state")<< " ";
cout << res->getInt("cus_zip_code")<< " ";
cout << res->getString("cus_email")<< " ";
cout << res->getString("cus_phone_num")<< " ";

cout << endl;






cout <<"Orders Table" <<endl;

cout << res->getInt("cus_id")<< " ";
cout << res->getString("delivery_date")<< " ";
cout << res->getString("order_type")<< " ";


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
