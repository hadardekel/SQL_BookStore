create database book_store;

USE book_store;

create table if not exists ORDER_STATUS (
order_status_id int unsigned auto_increment,
order_status_name varchar(30),
PRIMARY KEY (order_status_id)
); 

create table if not exists book_store.PURCHASE_STATUS (
purchase_status_id int unsigned auto_increment,
purchase_status_name varchar(30),
PRIMARY KEY (purchase_status_id)
); 

create table if not exists book_store.SUPPLIER (
supp_id int unsigned,
supp_name varchar(30),
PRIMARY KEY (supp_id)
); 

create table if not exists book_store.EMPLOYEE (
emp_id int unsigned,
emp_name varchar(30),
PRIMARY KEY (emp_id)
);

create table if not exists book_store.BOOK (
book_id int unsigned,
book_name varchar(70),
author varchar(30),
PRIMARY KEY (book_id)
);

create table if not exists book_store.CUSTOMER (
cust_id int unsigned,
cust_name varchar(30),
cust_creation_date datetime default '1900-01-01 00:00:00', 
cust_phone varchar(15),
had_purchased int,
year_purchased_amount decimal,
PRIMARY KEY (cust_id)
);

create table if not exists book_store.CAN_SUPPLY (
supp_id int unsigned not null,
book_id int unsigned not null,
price decimal,
CONSTRAINT fk_supp_id FOREIGN KEY (supp_id) REFERENCES SUPPLIER (supp_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_book_id FOREIGN KEY (book_id) REFERENCES BOOK (book_id)
ON UPDATE CASCADE
ON DELETE RESTRICT
);


create table if not exists book_store.SUPPLIES (
supp_id int unsigned not null,
book_id int unsigned not null,
supply_date datetime default '1900-01-01 00:00:00', 
quantity int default 0,
CONSTRAINT fk_supp1_id FOREIGN KEY (supp_id) REFERENCES SUPPLIER (supp_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_book1_id FOREIGN KEY (book_id) REFERENCES BOOK (book_id)
ON UPDATE CASCADE
ON DELETE RESTRICT
);

create table if not exists book_store.STOCK (
book_id int unsigned not null,
quantity int default 0,
price decimal not null,
global_discount decimal default 0,
CONSTRAINT fk_book2_id FOREIGN KEY (book_id) REFERENCES BOOK (book_id)
ON UPDATE CASCADE
ON DELETE RESTRICT
);


create table if not exists book_store.ORDERS (
order_id int unsigned not null,
cust_id int unsigned not null,
book_id int unsigned not null,
order_date datetime default '1900-01-01 00:00:00', 
order_status_id int unsigned not null,
order_status_date datetime default '1900-01-01 00:00:00', 
PRIMARY KEY(order_id),
CONSTRAINT fk_order_status_id FOREIGN KEY (order_status_id) REFERENCES ORDER_STATUS(order_status_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_cust_id FOREIGN KEY (cust_id) REFERENCES CUSTOMER(cust_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_book3_id FOREIGN KEY (book_id) REFERENCES BOOK (book_id)
ON UPDATE CASCADE
ON DELETE RESTRICT
);


create table if not exists book_store.PURCHASES (
purchase_id int unsigned not null,
cust_id int unsigned not null,
book_id int unsigned not null,
purchase_date datetime default '1900-01-01 00:00:00', 
emp_id int unsigned not null,
purchase_status_id int unsigned not null,
purchase_amount decimal,
cust_discount decimal default 0, 
PRIMARY KEY(purchase_id),
CONSTRAINT fk_purchase_status_id FOREIGN KEY (purchase_status_id) REFERENCES PURCHASE_STATUS(purchase_status_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_cust4_id FOREIGN KEY (cust_id) REFERENCES CUSTOMER(cust_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_book4_id FOREIGN KEY (book_id) REFERENCES BOOK (book_id)
ON UPDATE CASCADE
ON DELETE RESTRICT,
CONSTRAINT fk_emp4_id FOREIGN KEY (emp_id) REFERENCES EMPLOYEE(emp_id)
ON UPDATE CASCADE
ON DELETE RESTRICT
);