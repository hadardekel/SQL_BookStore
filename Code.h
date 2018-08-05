// SQL_Connector.cpp : Defines the entry point for the console application.
//

#include "Database.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	Database &db = Database::getInstance();
	Connection *con = db.getConnection();
	con->setSchema("book_store");
	Statement *stmt = con->createStatement();
	ResultSet *rset = NULL;
	PreparedStatement *pstmt = NULL;
	int check, i1, i2, i3, i4, i5;
	string s1, s2, s3, s4, s5, s6, start_year, start_month, start_day, start_date, end_year, end_month, end_day, end_date;
	char name[256];

	// Q1
	rset = stmt->executeQuery("SELECT STOCK.book_id, BOOK.book_name, BOOK.author, STOCK.quantity FROM STOCK inner join BOOK on(STOCK.book_id = BOOK.book_id)");
	cout << "all the books in stock" << endl;
	cout << "----------------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		i1 = rset->getInt("book_id");
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i2 = rset->getInt("quantity");
		cout << "id: " << i1 << ", name: " << s1 << ", author: " << s2 << ", quantity: " << i2 << endl;
	}
	cout << endl;
	
	// Q2
	rset = stmt->executeQuery("SELECT o.order_date, os.order_status_name, b.book_id, b.book_name, b.author, c.cust_name, c.cust_phone FROM ORDERS o	inner join BOOK b on(o.book_id = b.book_id)	inner join CUSTOMER c on(o.cust_id = c.cust_id) inner join ORDER_STATUS os on(o.order_status_id = os.order_status_id) where os.order_status_id <> 4");
	cout << "all the open orders" << endl;
	cout << "-------------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		s1 = rset->getString("order_date");
		s2 = rset->getString("order_status_name");
		i1 = rset->getInt("book_id");
		s3 = rset->getString("book_name");
		s4 = rset->getString("author");
		s5 = rset->getString("cust_name");
		s6 = rset->getString("cust_phone");
		cout << "order date: " << s1 << ", status: " << s2 << ", book id: " << i1 << ", book name: " << s3 << ", author: " << s4 << ", customer: " << s5 << ", phone: " << s6 << endl;
	}
	cout << endl;

	// Q3
	rset = stmt->executeQuery("SELECT cust_id, cust_name, cust_creation_date, cust_phone FROM CUSTOMER where had_purchased = 1");
	cout << "our customers" << endl;
	cout << "-------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		i1 = rset->getInt("cust_id");
		s1 = rset->getString("cust_name");
		s2 = rset->getString("cust_creation_date");
		s3 = rset->getString("cust_phone");
		cout << "id: " << i1 << ", name: " << s1 << ", phone: " << s3 << ", creation date: " << s2 << endl;
	}
	cout << endl;

	// Q4
	rset = stmt->executeQuery("SELECT supp_id, supp_name FROM SUPPLIER");
	cout << "our suppliers" << endl;
	cout << "-------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		i1 = rset->getInt("supp_id");
		s1 = rset->getString("supp_name");
		cout << "id: " << i1 << ", name: " << s1 << endl;
	}
	cout << endl;

	// Q5	
	cout << "please enter start date in this format: year, month, day" << endl; 
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";

	pstmt = con->prepareStatement("SELECT p.PURCHASE_ID,p.purchase_date, ps.purchase_status_name, p.purchase_amount,b.book_name, c.cust_name, e.emp_name FROM PURCHASES p inner join PURCHASE_STATUS ps	on(p.purchase_status_id = ps.purchase_status_id) inner join book b on(p.book_id = b.book_id) inner join CUSTOMER c on(p.cust_id = c.cust_id) inner join EMPLOYEE e on(p.emp_id = e.emp_id) WHERE p.purchase_date between ? and ?");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	cout << "all purchases between selected dates" << endl;
	cout << "------------------------------------" << endl;
	while (rset->next()) {
		i1 = rset->getInt("purchase_id");
		s1 = rset->getString("purchase_date");
		s2 = rset->getString("purchase_status_name"); 
		i2 = rset->getInt("purchase_amount");
		s3 = rset->getString("book_name");
		s4 = rset->getString("cust_name");
		s5 = rset->getString("emp_name");
		cout << "id: " << i1 << ", date: " << s1 << ", status: " << s2 << ", amount: " << i2 << ", book: " << s3 << ", customer: " << s4 << ", employee: " << s5 << endl;
	}
	cout << endl;
	

	// Q6
	rset = stmt->executeQuery("SELECT b.book_id, b.book_name, b.author, s.global_discount FROM STOCK s inner join book b on(s.book_id = b.book_id)	WHERE s.global_discount > 0");
	cout << "books with discount" << endl;
	cout << "-------------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		i1 = rset->getInt("book_id");
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i2 = rset->getInt("global_discount");
		cout << "id: " << i1 << ", name: " << s1 << ", author: " << s2 << ", discount:" << i2 << endl;
	}
	cout << endl;

	// Q7
	cout << "please enter author or name of book" << endl; 	
	cin.getline(name, 256);
	i2 = 0;
	pstmt = con->prepareStatement("SELECT b.book_id, b.book_name, b.author, s.quantity FROM BOOK b left join STOCK s on (b.book_id = s.book_id) WHERE b.author = ? OR b.book_name = ?");
	pstmt->setString(1, name);
	pstmt->setString(2, name);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	cout << "is book in stock" << endl;
	cout << "----------------" << endl;
	while (rset->next()) {
		i1 = rset->getInt("book_id");
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i2 = rset->getInt("quantity");
		if (i2 == 0)
			cout << s1 << " by " << s2 << ": not in stock" << endl;
		else
			cout << s1 << " by " << s2 << ": in stock" << endl;
	}
	cout << endl;

	// Q8
	cout << "please enter author or name of book" << endl;
	cin.getline(name, 256);
	pstmt = con->prepareStatement("SELECT b.book_name, b.author, s.supp_id, s.supp_name FROM BOOK b left join CAN_SUPPLY cs on(cs.book_id = b.book_id) left join SUPPLIER s on(cs.supp_id = s.supp_id)	WHERE b.author = ? OR b.book_name = ?");
	pstmt->setString(1, name);
	pstmt->setString(2, name);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	cout << "list of suppliers" << endl;
	cout << "-----------------" << endl;
	while (rset->next()) {
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i2 = rset->getInt("supp_id");
		s3 = rset->getString("supp_name");
		cout << s1 << " by " << s2 << ": " << i2 << "-" << s3 << endl;
	}
	cout << endl;

	// Q9
	cout << "please enter author or name of book" << endl;
	cin.getline(name, 256);
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT b.book_name, b.author, count(distinct p.purchase_id) purchases_count FROM BOOK b left join PURCHASES p on(p.book_id = b.book_id and p.purchase_date > ?) WHERE b.book_name = ? or b.author = ?");
	pstmt->setString(1, start_date);
	pstmt->setString(2, name);
	pstmt->setString(3, name);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	cout << "purchases from " << start_date << endl;
	cout << "----------------------------------" << endl;
	while (rset->next()) {
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i1 = rset->getInt("purchases_count");
		cout << i1 << " copies of " << s1 << " by " << s2 << endl;
	}
	cout << endl;

	
	// Q10
	cout << "please enter customer details" << endl;
	cin.getline(name, 256);
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i2 = 0;

	pstmt = con->prepareStatement("SELECT c.cust_id, c.cust_name, c.cust_phone, count(distinct p.purchase_id) purchases_count FROM CUSTOMER c left join PURCHASES p on(c.cust_id = p.cust_id and p.purchase_date > ?) WHERE c.cust_name = ? or c.cust_id = ? or c.cust_phone = ? GROUP BY c.cust_id, c.cust_name, c.cust_phone");
	pstmt->setString(1, start_date);
	pstmt->setString(2, name);
	pstmt->setString(3, name);
	pstmt->setString(4, name);
	rset = pstmt->executeQuery();
	cout << "purchases by customer" << endl;
	cout << "---------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("cust_id");
		s1 = rset->getString("cust_name");
		s2 = rset->getString("cust_phone");
		i2 = rset->getInt("purchases_count");
		cout << s1 << " bought " << i2 << " books" << endl;
	}
	cout << endl;
	
	// Q11
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i2 = 0;

	pstmt = con->prepareStatement("SELECT c.cust_id, c.cust_name, c.cust_phone, count(distinct p.purchase_id) purchases_count FROM CUSTOMER c join PURCHASES p on(c.cust_id = p.cust_id) WHERE p.purchase_date > ? GROUP BY c.cust_id, c.cust_name, c.cust_phone ORDER BY purchases_count DESC LIMIT 1");
	pstmt->setString(1, start_date);
	rset = pstmt->executeQuery();
	cout << "the best customer" << endl;
	cout << "-----------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("cust_id");
		s1 = rset->getString("cust_name");
		s2 = rset->getString("cust_phone");
		i2 = rset->getInt("purchases_count");
		cout << i1 << "-" << s1 << ", phone:" << s2 << " bought " << i2 << " books" << endl;
	}
	cout << endl;
	
	// Q12
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i2 = 0;

	pstmt = con->prepareStatement("SELECT s.supp_id, s.supp_name, sum(sp.quantity) quantity_count FROM SUPPLIER s join SUPPLIES sp on(s.supp_id = sp.supp_id) WHERE	sp.supply_date > ? GROUP BY s.supp_id, s.supp_name ORDER BY quantity DESC LIMIT 1");
	pstmt->setString(1, start_date);
	rset = pstmt->executeQuery();
	cout << "the supplier who supplied the biggest amount of books" << endl;
	cout << "-----------------------------------------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("supp_id");
		s1 = rset->getString("supp_name");
		i2 = rset->getInt("quantity_count");
		cout << i1 << "-" << s1 << " supplied " << i2 << " books" << endl;
	}
	cout << endl;
	
	// Q13
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT count(order_id) order_count FROM ORDERS WHERE	order_date between ? and ?");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	cout << "orders count" << endl;
	cout << "------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("order_count");
		cout << i1 << endl;
	}
	cout << endl;

	
	// Q14
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT count(order_id) order_count FROM ORDERS WHERE	order_status_id = 4 and order_date between ? and ?");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	cout << "orders to purchases count" << endl;
	cout << "-------------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("order_count");
		cout << i1 << endl;
	}
	cout << endl;
	
	// Q15
	cout << "please enter customer details" << endl;
	cin.getline(name, 256);
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT sum(p.purchase_amount*p.cust_discount/100) discount_amount FROM PURCHASES p join CUSTOMER c on(p.cust_id = c.cust_id)	WHERE p.cust_discount > 0 and p.purchase_date >= ? and (c.cust_name = ? or c.cust_id = ? or c.cust_phone = ?)");
	pstmt->setString(1, start_date);
	pstmt->setString(2, name);
	pstmt->setString(3, name);
	pstmt->setString(4, name);
	rset = pstmt->executeQuery();
	cout << "discount amount for customer" << endl;
	cout << "----------------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("discount_amount");
		cout << i1 << " ILS" << endl;
	}
	cout << endl;
	
	// Q16
	rset = stmt->executeQuery("SELECT purchase_quarter, sum(amount_after_dis) amount FROM(SELECT p.purchase_date, year(p.purchase_date) * 100 + quarter(p.purchase_date) purchase_quarter,p.purchase_amount, p.cust_discount, p.purchase_amount*(100 - p.cust_discount) / 100 amount_after_dis FROM	PURCHASES p WHERE p.purchase_status_id = 1) t GROUP BY purchase_quarter ORDER BY 1");
	cout << "sales for each quarter" << endl;
	cout << "----------------------" << endl;
	rset->beforeFirst();
	while (rset->next()) {
		i1 = rset->getInt("purchase_quarter");
		i2 = rset->getInt("amount");
		cout << i1 << ": " << i2 << " ILS" << endl;
	}
	cout << endl;
	
	
	// Q17
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT count(cust_id) cust_count FROM CUSTOMER WHERE cust_creation_date >= ?");
	pstmt->setString(1, start_date);
	rset = pstmt->executeQuery();
	cout << "new customer count" << endl;
	cout << "------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("cust_count");
		cout << i1 << endl;
	}
	cout << endl;

	// Q18
	cout << "please enter supplier id" << endl;
	cin >> s1;

	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT sum(total) amount FROM(SELECT sp.book_id, sp.quantity, cs.price, sp.quantity*cs.price total FROM SUPPLIES sp inner join SUPPLIER s on(sp.supp_id = s.supp_id) left join CAN_SUPPLY cs	on(sp.supp_id = cs.supp_id and sp.book_id = cs.book_id)	WHERE sp.supply_date between ? and ? and s.supp_id = ?) t");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	pstmt->setString(3, s1);
	rset = pstmt->executeQuery();
	cout << "purchases from supplier" << endl;
	cout << "-----------------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("amount");
		cout << i1 << " ILS" << endl;
	}
	cout << endl;

	// Q19
	cout << "please enter employee id or name" << endl;
	cin.getline(name, 256);

	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";
	i1 = 0;

	pstmt = con->prepareStatement("SELECT count(distinct p.purchase_id) purchase_count FROM PURCHASES p	inner join EMPLOYEE e on(p.emp_id = e.emp_id) WHERE	p.purchase_date between ? and ? and (e.emp_id = ? or e.emp_name = ?)");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	pstmt->setString(3, name);
	pstmt->setString(4, name);
	rset = pstmt->executeQuery();
	cout << "employee sales" << endl;
	cout << "--------------" << endl;
	if (rset->rowsCount() == 1) {
		rset->first();
		i1 = rset->getInt("purchase_count");
		cout << i1 << " purchases" << endl;
	}
	else {
		cout << "0 purchases" << endl;
	}
	cout << endl;
	
	// Q20
	cout << "please enter start date in this format: year, month, day" << endl;
	cin >> start_year >> start_month >> start_day;
	if (start_month.length() < 2)
		start_month = "0" + start_month;
	if (start_day.length() < 2)
		start_day = "0" + start_day;
	start_date = start_year + "-" + start_month + "-" + start_day + " 00:00:00";

	cout << "please enter end date in this format: year, month, day" << endl;
	cin >> end_year >> end_month >> end_day;
	if (end_month.length() < 2)
		end_month = "0" + end_month;
	if (end_day.length() < 2)
		end_day = "0" + end_day;
	end_date = end_year + "-" + end_month + "-" + end_day + " 00:00:00";

	pstmt = con->prepareStatement("SELECT b.book_id, b.book_name, b.author, count(distinct p.purchase_id) purchase_count FROM BOOK b join PURCHASES p on (b.book_id = p.book_id) WHERE p.purchase_date between ? and ? GROUP BY b.book_id, b.book_name, b.author ORDER BY 4 DESC LIMIT 10");
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	cout << "top sellers" << endl;
	cout << "-----------" << endl;
	rset->beforeFirst();
	i3 = 1;
	while (rset->next()) {
		i1 = rset->getInt("book_id");
		s1 = rset->getString("book_name");
		s2 = rset->getString("author");
		i2 = rset->getInt("purchase_count");
		cout << i3 << ") " << i1 << "-" << s1 << " by " << s2 << ": " << i2;
		if (i2 > 1)
			cout << " copies" << endl;
		else
			cout << " copy" << endl;
		i3++;
	}
	cout << endl;

	delete con;
	delete rset;
	delete pstmt;
	delete stmt;
    return 0;
}

