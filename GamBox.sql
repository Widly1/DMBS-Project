drop database if exists GameBox;
drop table if exists Compatibility;

create database GameBox;

use GameBox;


   create table Product (
  product_id int NULL AUTO_INCREMENT, 
  product_name varchar(100) NOT NULL,
  product_genre varchar(50) NOT NULL, 
  product_star_rating varchar(7) NOT NULL,
  product_publisher varchar(50) NOT NULL,
  product_price decimal(10,2) NOT NULL,
  product_release_date varchar(10) NOT NULL,
  primary key (product_id)
   ) AUTO_INCREMENT=100;

 create table Console (
console_id int NOT NULL AUTO_INCREMENT,
console_name varchar(50) NOT NULL,
console_type varchar(50) NOT NULL,
console_hard_drive_size  varchar(6) NOT NULL,
console_color varchar(15) NOT NULL,
console_price decimal(10,2) NOT NULL,
console_condition varchar(15) NOT NULL,
console_release_date date NOT NULL,
console_fps int NOT NULL,
primary key(console_id)
);


   create table Compatibility (
  console_product int AUTO_INCREMENT,
  product_id int NULL,
  console_id int NOT NULL,
  console_name varchar(50) NOT NULL,
console_type varchar(50) NOT NULL,
  compatibility varchar(10) NULL,
  primary key (console_product)
    ) AUTO_INCREMENT=200; 

   
 create table Customers (
  cus_id int NOT NULL AUTO_INCREMENT,
  product_id int NULL,
  console_id int NULL,
  order_num int NUll,
  cus_name varchar(100) NOT NULL,
  cus_address varchar(100) NOT NULL,
  cus_state varchar(3) NOT NULL,
  cus_zip_code int NOT NULL,
  cus_email varchar(100) NOT NULL,
  cus_phone_num varchar(10) NOT NULL,
  primary key( cus_id),
  foreign key(product_id) REFERENCES Product(product_id)
   ) AUTO_INCREMENT=10001;


create table Orders (
  order_num int NOT NULL AUTO_INCREMENT,
  cus_id int NOT NULL,
  delivery_date date NOT NULL,
  order_type varchar(50) NOT NULL,
  primary key (order_num),   
  foreign key (cus_id) REFERENCES Customers(cus_id)
    )AUTO_INCREMENT=66000; 
   