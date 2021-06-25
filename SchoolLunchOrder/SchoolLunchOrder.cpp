// schoolLunchOrderSystem_LaraKeith.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//  ===== THIS CODE HOLDS LARA AND KEITH'S CODE FOR OUR SCHOOL LUNCH ORDER SYSTEM =====

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <windows.h> 
using namespace std;

// ===== vv Write stuctures here vv =====
struct ParentAcc {
	string firstName;
	string lastName;
	string pinNum;
	string contactNum;

	string childName;
	string childRoomNum;

	string cardNum;
	string cardExpiry;

	string parentID;
};

struct ParentOrder {
	string orderNumber;
	string orderDate;
	string parentID;
	string childName;
	string paymentStatus; //(1 or 2)
	float total;
};

struct Order {
	vector<string> itemOrderName;
	vector<float> itemPrice;
	vector<char> orderday;
};

struct ParentComplaint {
	string compDate;
	string compItem;
	string comptDesc;
	string compNumber;
	string firstName;
	string contactNum;
	bool actionStatus;
};




struct MenuItems {
	string itemName;
	float itemPrice;
	string menuID;
	int itemVeg;
	int itemGF;
};

/*struct AdminAcc {
	string firstName;
	string lastName;
	string pinNum;
};*/
// ===== ^^ Write stuctures here ^^ =====

void menuPreview();

// -- create underlines only --
void underLine(int x) {
	int i;

	for (i = 0; i < x; i++) {
		cout << "-";
	}
	cout << endl;
}

void changeColour(int desiredColour) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColour);
}

// ===== vv LARA CODE SECTION vv =====
void bulkDiscount() {
	cout << "\n\t\t\tBulk Discount Offers\t\t\t" << endl;
	underLine(80);

	cout << "\nItems can be ordered over different days for the children \n(including different weeks)";
	cout << "\n\n1. 5 Items Ordered = 5% off total order";
	cout << "\n2. 10 Items Ordered = 10% off total order";
	cout << "\n3. 20+ Items Ordered = 15% off total order";
}

void contactDetails() {
	cout << "\n\t\t\tContact Details\t\t\t" << endl;
	underLine(80);
	cout << "\nIf you would like to contact us regarding any queries you \nmay have you can reach us via our phone number and email \nshown below: ";
	cout << "\n\nContact Number: (04) 578 - 2364";
	cout << "\n\nEmail: schoollunchsystem@gmail.com";
	cout << "\n\nOffice Location 45 School St, Thorndon, Wellington, NZ";
	cout << "\n\nOffice Hours: 1pm - 5pm, Monday - Friday";
}

int ParentReg(ParentAcc* ptr) {
	system("cls");
	vector<array<string, 9>>  matrix;
	vector<array<string, 9>>  idcheck;
	int num, a;
	unsigned int id;
	string line, row, iD;

	cout << "\n\t\t\tRegistration\t\t\t" << endl;
	underLine(80);
	cout << "\nFirst name: ";
	cin >> ptr->firstName;
	cout << "\n\nLast name: ";
	cin >> ptr->lastName;
loginpin:
	cout << "\n\nLogin Pin (This will be used as your password to login, must \nbe 4 numbers): ";
	cin >> num;
	if (num > 999 && num < 10000) {
		ptr->pinNum = to_string(num);
	}
	else {
		cout << "\n\nPlease enter a valid 4 digit number";
		goto loginpin;
	}
	cout << "\n\nContact number (no spaces): ";
	cin >> ptr->contactNum;
	cout << "\n\nChild's first name: ";
	cin >> ptr->childName;
	cout << "\n\nChild's room number: ";
	cin >> ptr->childRoomNum;
	cout << "\n\nCard Number (no spaces): ";
	cin >> ptr->cardNum;
	cout << "\n\nCard Expiry Date (format as MM/YY): ";
	cin >> ptr->cardExpiry;

	srand(time(NULL));
	id = rand() % 10000000 + 9999999;
	iD = to_string(id);

	ifstream fileid;
	fileid.open("parentlogin.csv", ios::in);

	while (getline(fileid, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 9> f;
		while (getline(ss, row, ',')) {
			f[i++] = row;
		}
		idcheck.push_back(f);
	}
	idchk:
	for (int i = 0; i < idcheck.size(); ++i) {
		if (iD == idcheck.at(i)[0]) {
			srand(time(NULL));
			id = rand() % 1000000 + 999999;
			iD = to_string(id);
			goto idchk;
		}
	}

	fileid.close();

	ptr->parentID = to_string(id);

	ofstream outfile;
	outfile.open("parentlogin.csv", ios::app);

	outfile << ptr->parentID << ","
		<< ptr->firstName << ","
		<< ptr->lastName << ","
		<< ptr->pinNum << ","
		<< ptr->contactNum << ","
		<< ptr->childName << ","
		<< ptr->childRoomNum << ","
		<< ptr->cardNum << ","
		<< ptr->cardExpiry << endl;

	outfile.close();

	ifstream infile;
	infile.open("parentlogin.csv", ios::in);

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 9> b;
		while (getline(ss, row, ',')) {
			b[i++] = row;
		}
		matrix.push_back(b);
	}
		for (int i = 0; i < matrix.size(); ++i) {
			if (ptr->parentID == matrix.at(i)[0]) {
				a = i;
			}
		}
	
	infile.close();
	return a;
}

int parentLogin() {
	system("cls");
	vector<array<string, 9>>  matrix;
	string firstname, line, row, pin;
	int a = -1;
	int n = 2;
	

	cout << "\n\t\t\tLogin\t\t\t" << endl;
	underLine(80);

	ifstream infile;
	infile.open("parentlogin.csv", ios::in);

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 9> b;
		while (getline(ss, row, ',')) {
			b[i++] = row;
		}
		matrix.push_back(b);
	}

	for (int k = 0; k < 3; k++) {
		cout << "\nFirst name: ";
		cin >> firstname;
		cout << "\nPin: ";
		cin >> pin;
		if (firstname == "admin" && pin == "5555") {
			a = -5;
			break;
		}
		for (int i = 0; i < matrix.size(); ++i) {
			if (firstname == matrix.at(i)[1] && pin == matrix.at(i)[3]) {
				a = i;
				goto exit;
			}
		}
		changeColour(4);
		cout << "\n\nWrong login information try again (you have " << n-- << " more attempts!\n";
		changeColour(7);
	}

	if (a == -1) {
		changeColour(4);
		cout << "\n\nThe number of login attempts has been exceeded, try again another time.";
		changeColour(7);
	}

exit:
	infile.close();
	return a;
}

int MakeOrder(int parent) {
	vector<array<string, 7> > oNcheck;
	vector<array<string, 9> > parentinfo;
	vector<array<string, 4> > Menuorder;
	vector<array<int, 2> > quantityordered;
	vector<int> printitems;
	ParentOrder order;
	ParentOrder* ptrorder;
	unsigned int on;
	int option, discount = 0, day, month, year;
	float total, Total = 0, Newtotal;
	string line, row, oN, line2, row2, line3, row3, date, line4, row4;
	char orderday, paymentproceed, continueorder;
	time_t now = time(0);
	tm* ltm = localtime(&now);

	ptrorder = &order;

	srand(time(NULL));
	on = rand() % 10000000 + 9999999;
	oN = to_string(on);

	day = ltm->tm_mday;
	month = (1 + ltm->tm_mon);
	year = (1900 + ltm->tm_year);

	date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

	ifstream fileid;
	fileid.open("parentorder.csv", ios::in);

	while (getline(fileid, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 7> f;
		while (getline(ss, row, ',')) {
			f[i++] = row;
		}
		oNcheck.push_back(f);
	}
oNchk:
	for (int i = 0; i < oNcheck.size(); ++i) {
		if (oN == oNcheck.at(i)[0]) {
			srand(time(NULL));
			on = rand() % 1000000 + 999999;
			oN = to_string(on);
			goto oNchk;
		}
	}

	fileid.close();

	ifstream parentfile;
	parentfile.open("parentlogin.csv", ios::in);

	while (getline(parentfile, line3)) {
		stringstream ss(line3);
		int i = 0;
		array<string, 9> p;
		while (getline(ss, row3, ',')) {
			p[i++] = row3;
		}
		parentinfo.push_back(p);
	}

	parentfile.close();

	fstream infile2;
	infile2.open("menuItems.csv", ios::in);

	while (getline(infile2, line2)) {
		stringstream ss(line2);
		int i = 0;
		array<string, 4> me;
		while (getline(ss, row2, ',')) {
			me[i] = row2;
			i++;
		}
		Menuorder.push_back(me);
	}

	infile2.close();

	fstream infile4; //Daily order read in to then push back into the file through ios::out
	infile4.open("dailyOrder.csv", ios::in);

	while (getline(infile4, line4)) {
		stringstream ss(line4);
		int i = 0;
		array<int, 2> daily;
		while (getline(ss, row4, ',')) {
			daily[i] = stof(row4);
			i++;
		}
		quantityordered.push_back(daily);
	}

	infile4.close();

	ptrorder->orderNumber = oN;
	ptrorder->parentID = parentinfo.at(parent)[0];
continueordering:
	system("cls");
	cout << "\n\n\t\tOrder Screen (" << ptrorder->orderNumber << ")\n";
	underLine(80);
	cout << endl << endl;
	menuPreview();
	cout << "\n\nEnter the number next to the item you would like to order \n(Enter 100 if you'd like to go back to the main menu)";
	changeColour(11);
	cout << "\n\nEnter option: ";
	changeColour(7);
	cin >> option;
	for (int optionsize = 1; optionsize < Menuorder.size(); optionsize++) {
		if (option == optionsize) {
			goto continuingorder;
		}
	}
	if (option == 100) {
		return 0;
		}
	else {
		cout << "\n\nPlease enter a valid option (1 - " << Menuorder.size() << ")\n\n";
		changeColour(11);
		system("pause");
		changeColour(7);
		goto continueordering;
	}
	
	continuingorder:
	printitems.push_back(option);
redoday:
	cout << "\n\nEnter day you would like the food delivered";
	cout << "\n\n\tm - Monday\n\tt - Tuesday\n\tw - Wednesday\n\tu - Thursday\n\tf - Friday";
	changeColour(11);
	cout << "\n\nEnter option: ";
	changeColour(7);
	cin >> orderday;
	if (orderday == 'm' || orderday == 't' || orderday == 'w' || orderday == 'u' || orderday == 'f') {
		
	}
	else {
		changeColour(4);
		cout << "\n\nPlease enter a valid day (m, t, w, u or f)";
		changeColour(7);
		goto redoday;
	}

contorderredo:
	changeColour(11);
	cout << "\n\nContinue Ordering? (y/n) ";
	changeColour(7);
	cin >> continueorder;

	if (continueorder == 'n') {
	paymentproceedredo:
		changeColour(11);
		cout << "\n\nProceed to payment? (y/n)";
		changeColour(7);
		cin >> paymentproceed;
		if (paymentproceed == 'y') {

			for (int o = 0; o < printitems.size(); o++) {
				for (int s = 0; s < quantityordered.size(); s++) {
					if ((printitems[o] - 1) == quantityordered.at(s)[0]) {
						/* = quantityordered.at(s)[1];*/
					}
				}
			}

			ofstream orderfile;
			orderfile.open(ptrorder->orderNumber + ".csv", ios::app);


			for (int d = 0; d < Menuorder.max_size(); d++) {
				if ((option - 1) == d) {
					orderfile << Menuorder.at(d)[0] << "," << Menuorder.at(d)[1] << "," << orderday << "," << date << endl;
					break;
				}
			}

			orderfile.close();
			system("cls");
			cout << "\n\n\tBill for " << parentinfo.at(parent)[1] << " (" << ptrorder->orderNumber << ") " << endl;
			underLine(65);

			cout << "\nItems ordered on (" << date << "):" << endl;
			for (int i = 0; i < printitems.size(); i++) {
				cout << "\n\t" << Menuorder.at(printitems[i] - 1)[0] << "     $" << Menuorder.at(printitems[i] - 1)[1];

				total = stof(Menuorder.at(printitems[i]- 1)[1]);
				Total = total + Total;
				discount++;
			}

			if (discount >= 5 && discount < 10) {
				Newtotal = Total * 0.95;
				cout << "\n\n\nDiscount applied: 5%\t\tTotal:\t\t$" << Newtotal;
			}
			else if (discount >= 10 && discount < 20) {
				Newtotal = Total * 0.9;
				cout << "\n\n\nDiscount applied: 10%\t\tTotal:\t\t$" << Newtotal;
			}
			else if (discount >= 20) {
				Newtotal = Total * 0.85;
				cout << "\n\n\nDiscount applied: 15%\t\tTotal:\t\t$" << Newtotal;
			}
			else {
				Newtotal = Total;
				cout << "\n\n\nTotal:  $" << Newtotal;
			}

			cout << "\nStudent: " << parentinfo.at(parent)[5] << "\t\t\t\tClass: " << parentinfo.at(parent)[6] << endl << endl;

			ofstream parentorderfile;
			parentorderfile.open("parentOrder.csv", ios::app);

			parentorderfile << ptrorder->orderNumber << "," << date << "," << discount << "," << Newtotal << "," << "paid" << "," << parentinfo.at(parent)[5] << "," << parentinfo.at(parent)[6] << endl;

			parentorderfile.close();

			changeColour(11);
			system("pause");
			changeColour(7);
			return 0;
		}
		else if (paymentproceed == 'n') {
			return 0;
		}
		else {
			changeColour(4);
			cout << "\n\nPlease enter a valid option (y/n)";
			changeColour(7);
			goto paymentproceedredo;
		}
	}
	else if (continueorder == 'y') {
			ofstream orderfile;
			orderfile.open(ptrorder->orderNumber + ".csv", ios::app);


			for (int d = 0; d < Menuorder.max_size(); d++) {
				if ((option - 1) == d) {
					orderfile << Menuorder.at(d)[0] << "," << Menuorder.at(d)[1] << "," << orderday << "," << date << endl;
					break;
				}
			}

			orderfile.close();
			goto continueordering;
		
	}
	else {
		changeColour(4);
		cout << "\n\nPlease enter a valid option (y or n)";
		changeColour(7);
		goto contorderredo;
	}

}

void filterPrice() {
	system("cls");
	vector<array<string, 4> > fp;
	vector<array<float, 2> > priceFilter;
	array<float, 2> Item_Price;

	ifstream infile;
	infile.open("menuItems.csv", ios::in);

	string line, row, item;

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 4> b;
		while (getline(ss, row, ',')) {
			b[i++] = row;
		}
		fp.push_back(b);
	}
	infile.close();

	for (float j = 0; j < fp.size(); j++) {
			Item_Price[0] = stof(fp.at(j)[1]);
			Item_Price[1] = j;
		priceFilter.push_back(Item_Price);
	}

	sort(priceFilter.begin(), priceFilter.end());

	cout << "\n\t\t\tPrice from low to high\n";
	underLine(72);

	for (int i = 0; i < fp.size(); i++) {
		cout << "\n\t\t" << fp.at(priceFilter.at(i)[1])[0] << " -  $" << priceFilter.at(i)[0] << endl;
	}

	cout << "\n\n\n\t\t";
	changeColour(11);
	system("pause");
	changeColour(7);
}

void filterVeg() {
	system("cls");
	vector<array<string, 4> > vegmenu;
	vector<int> vegetarian;

	float vege;

	ifstream infile;
	infile.open("menuItems.csv", ios::in);

	string line, row, item, stringprice;

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 4> v;
		while (getline(ss, row, ',')) {
			v[i] = row;
			i++;
		}
		vegmenu.push_back(v);
	}

	int a;
	array<string, 4> ve;

	for (int i = 0; i < vegmenu.size(); i++) {
		vege = stof(vegmenu.at(i)[3]);

		if (vege == 1) {
			vegetarian.push_back(i);
		}

	}

	cout << "\n\t\t\tVegetarian Menu\n";
	underLine(72);

	for (int i = 0; i < vegetarian.size(); i++) {
		a = vegetarian.at(i);
		cout << "\n\t\t" << vegmenu.at(a)[0] << " - " << vegmenu.at(a)[1] << endl;
	}

	infile.close();

	cout << "\n\n\n\t\t";
	changeColour(11);
	system("pause");
	changeColour(7);
}

void filterGF() {
	system("cls");
	vector<array<string, 4> > gfmenu;//
	vector<int> GF;

	float gf;

	ifstream infile;
	infile.open("menuItems.csv", ios::in);

	string line, row, item, stringprice;

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 4> v;
		while (getline(ss, row, ',')) {
			v[i] = row;
			i++;
		}
		gfmenu.push_back(v);
	}

	int a;
	array<string, 4> ve;

	for (int i = 0; i < gfmenu.size(); i++) {
		gf = stof(gfmenu.at(i)[2]);

		if (gf == 1) {
			GF.push_back(i);
		}

	}

	cout << "\n\t\t\tGluten Free Menu\n";
	underLine(72);

	for (int i = 0; i < GF.size(); i++) {
		a = GF.at(i);
		cout << "\n\n\t\t" << gfmenu.at(a)[0] << " - " << gfmenu.at(a)[1] << endl;
	}

	infile.close();

	cout << "\n\n\n\t\t";
	changeColour(11);
	system("pause");
	changeColour(7);
}

void Parentcomplaint(int parent) {
	system("cls");
	struct ParentComplaint ParentComp;
	struct ParentComplaint* ptrParentComp;
	string complaintdate, complaintitem, complaintdescription;
	ptrParentComp = &ParentComp;

	srand(time(NULL));
	int pc = rand() % 100000 + 99999;

	ptrParentComp->compNumber = to_string(pc);

	cout << "\n\t\t\tComplaint Form (" << ptrParentComp->compNumber << ")" << endl;
	underLine(80);
	cout << "\n\nPlease enter the order date for the complaint (formatted as dd/mm/yyyy): ";
	cin >> complaintdate;
	cin.ignore();
	cout << "\n\nPlease enter the item ordered: ";
	getline(cin, complaintitem);
	cout << "\n\nPlease enter the complaint description: ";
	getline(cin, complaintdescription);
	cout << endl << endl;

	ofstream complaintfile;
	complaintfile.open("parentComplaint.csv", ios::app);

	complaintfile << ptrParentComp->compNumber << "," << complaintdate << "," << complaintitem << "," << complaintdescription << endl;

	complaintfile.close();

}

int parentOrder(int person){
	int option;
	int returnordervalue;
menu:
	system("cls");
	cout << "\n\n\t\tMenu";
	cout << "\n----------------------------------------------\n\n";
	vector<array<string, 4>>  vectorMenu;
	int i;

	fstream infile; // reading the file 
	infile.open("menuItems.csv", ios::in);

	string line, row;
	while (getline(infile, line)) { // this loop gets the data from the csv and push_backs into a vector
		stringstream ss(line);
		int i = 0;
		array<string, 4> m;
		while (getline(ss, row, ',')) {//while inside that row. 
			m[i] = row;
			i++;
		}
		vectorMenu.push_back(m);
	}
	// only for printing out data from vector
	for (int i = 0; i < vectorMenu.size(); i++) {
		cout << "\t" << vectorMenu.at(i)[0] << "  -  $" << vectorMenu.at(i)[1] << endl;
	}
	
	cout << "\n\n\nMake a selection from the options below:";
	cout << "\n\n\t1. Filter by price (low to high)";
	cout << "\n\t2. Filter only vegetarian options";
	cout << "\n\t3. Filter only GF options";
	cout << "\n\t4. Order Food";
	cout << "\n\t5. Go back to main menu";
	changeColour(11);
	cout << "\n\n\nEnter Option: ";
	changeColour(7);
	cin >> option;

	switch (option) {
	case 1:
		filterPrice();
		goto menu;
		break;
	case 2:
		filterVeg();
		goto menu;
		break;
	case 3:
		filterGF();
		goto menu;
		break;
	case 4:
		returnordervalue = MakeOrder(person);
		break;
	case 5:
		return 0;
		break;
	default:
		cout << "\n\nPlease enter a valid option (1 - 5)";
		goto menu;
		break;
	}
	return 0;
}
// ===== ^^ LARA CODE SECTION ^^ =====

// ===== vv KEITH CODE SECTION vv =====

// -- writes menu into csv  --
void writeMenuPreview() {
	array<string, 9> menuID;
	unsigned int id;
	string iD;

	string assignID[9];
	
	for (int i = 0; i < 9; i++) {
	redoID:
		srand(time(NULL));
		id = (rand() % (10000000 - 9999999) + 9999999);
		iD = to_string(id);
		for (int j = 0; j < 9; j++) {
			if (assignID[j] == iD) {
				cout << iD;
			}
		}
		iD = assignID[i];
	}

	fstream outfile; // writes into the csv file with menu item data

	outfile.open("menuItems.csv", ios::out);
	outfile << "Ham Sandwich" << ","
		<< "4.50" << "," << "2" << "," << "2" << endl
		<< assignID[1] << "Vegetarian Sandwich" << ","
		<< "5.00" "," << "2" << "," << "1" << endl
		<< assignID[2] << "Chicken and Avocado Sandwich (GF)" << ","
		<< "6.50" "," << "1" << "," << "2" << endl
		<< assignID[3] << "Steak and Cheese Pie" << ","
		<< "4.50" "," << "2" << "," << "2" << endl
		<< assignID[4] << "Butter Chicken Pie" << ","
		<< "5.50" "," << "2" << "," << "2" << endl
		<< assignID[5] << "Mushroom and Cheese Pie (GF)" << ","
		<< "6.50" "," << "1" << "," << "1" << endl
		<< assignID[6] << "Cheese Pizza" << ","
		<< "4.50" "," << "2" << "," << "2" << endl
		<< assignID[7] << "Pepperoni Pizza" << ","
		<< "5.50" "," << "2" << "," << "2" << endl
		<< assignID[8] << "Vegetarian Pizza (GF)" << ","
		<< "6.50" "," << "1" << "," << "1" << endl;
	outfile.close();
}

// --- reads menu csv file 
void  menuPreview() {
	system("cls");
	vector<array<string, 4>>  vectorMenu;
	int i;

	fstream infile; // reading the file 
	infile.open("menuItems.csv", ios::in);

	string line, row;
	while (getline(infile, line)) { // this loop gets the data from the csv and push_backs into a vector
		stringstream ss(line);
		int i = 0;
		array<string, 4> m;
		while (getline(ss, row, ',')) {//while inside that row. 
			m[i] = row;
			i++;
		}
		vectorMenu.push_back(m);
	}
	cout << "\n\n\t\tMenu";
	cout << "\n----------------------------------------------\n\n";
	// only for printing out data from vector
	for (int i = 0; i < vectorMenu.size(); i++) {
		cout << "\n" << (i + 1) << ". " <<  vectorMenu.at(i)[0] << "  -  $" << vectorMenu.at(i)[1] << endl;
	}
}

//admin update menu function 
void adminUpdateMenu() {
	system("cls");
	vector<array<string, 4>>  vectorMenu;
	int i;

	fstream infile; // reading the file 
	infile.open("menuItems.csv", ios::in);

	string line, row;
	while (getline(infile, line)) { // this loop gets the data from the csv and push_backs into a vector
		stringstream ss(line);
		int i = 0;
		array<string, 4> m;
		while (getline(ss, row, ',')) {//while inside that row. 
			m[i] = row;
			i++;
		}
		vectorMenu.push_back(m);
	}

	int choice;
	//Asking admin if they would like to make changes
	cout << "What changes would you like to make?\n\n";
	cout << "1. Change a Menu Item Name\n";
	cout << "2. Change a Menu Item Price\n\n";
	cout << "Please make a selection: (1 or 2) ";
	cin >> choice;

	if (choice == 1) {
		string itemNameChoice;
		string newItemName;
		cin.ignore();
		cout << "\n\nMenu Name Change\n\n";
		menuPreview();

		cout << "\n\nwhat item would you like to change?(Please type the Name of item)\n";
		getline(cin,itemNameChoice);
		// checks if the user selected item matches with the item in that vector cell
		if (itemNameChoice == vectorMenu[0][0]) {
			cout << "\nYou would like to change " << vectorMenu[0][0]; //if it matches, it will then ask the user what they want to
			cout << "\nPlease Enter new item Name: ";
			getline(cin,newItemName);

			vectorMenu[0][0] = newItemName;
			cout << vectorMenu[0][0];
		}
	}

	else if (choice == 2) {
		int itemPriceChoice;
		cout << "\n\nMenu Price Change\n\n";
		menuPreview();
	}

}

//View weekly sales
void weeklySalesFunc() {

}

//check complaints functions

// ===== ^^ KEITH CODE SECTION ^^ =====

int main()
{
	vector<array<string, 9>>  matrix;
	int index, a = 0, b;
	int flag = 0;
	string ID;

	struct ParentAcc Parent;
	struct ParentAcc* ptrParent;

	ptrParent = &Parent;
	writeMenuPreview();
MenuSelect:
	system("cls");
	// --- added intro screen below V --- //
	cout << "\n\t\t\tSchool Lunch Order System\t\t\t" << endl;
	underLine(80);

	cout << "\n\tPlease make a selection from the options below:" << endl;

	cout << "\n\t1.  Preview of Menu" << endl;
	cout << "\t2.  Bulk Discount Offers" << endl;
	cout << "\t3.  School Contact Details & Location" << endl;
	cout << "\t4.  Login to your account" << endl;
	cout << "\t5.  Register a new account" << endl;

	cout << "\n\n";
	changeColour(11);
	cout << "\n  Selection: ";
	changeColour(7);
	cin >> index;
	switch (index) {
	case 1:
		system("cls");
		menuPreview();
		changeColour(11);
		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		changeColour(7);
		cin >> flag;

		if (flag != 1) {   //find a way to make this loop if condition is not met (IN PROGRESS)
			changeColour(4);
			cout << "invalid input! Try again: ";
			changeColour(7);
		}
		else {
			goto MenuSelect;
		}

		break;
	case 2:
		system("cls");
		bulkDiscount();
		changeColour(11);
		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		changeColour(7);
		cin >> flag;
	redo1:
		if (flag != 1) {
			changeColour(4);
			cout << "invalid input! Try again: ";
			changeColour(7);
			cin >> flag;
			goto redo1;
		}
		else {
			goto MenuSelect;
		}
		break;
	case 3:
		system("cls");
		contactDetails();
		changeColour(11);
		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		changeColour(7);
		cin >> flag;
	redo2:
		if (flag != 1) {
			changeColour(4);
			cout << "invalid input! Try again: ";
			changeColour(7);
			cin >> flag;
			goto redo2;
		}
		else {
			goto MenuSelect;
		}
		break;
	case 4:
		b = parentLogin();
		if (b == -1) {
			a = 0;
		}
		else if (b == -5) {
			a = 2;
		}
		else {
			a = 1;
		}
		break;
	case 5:
		b = ParentReg(ptrParent);
		a = 1;
		//Have them go to parents log in menu screen once registered as they are technically logged in
		break;
	default:
		cout << "It seems your selection was invalid, please select one of the given options: " << endl;
		goto MenuSelect;
	}

	if (a == 0) {
		//Too many attempts to log in
	}
	else if (a == 1) {
		string line, row;
		int c, option;
		ifstream infile;
		infile.open("parentlogin.csv", ios::in);

		while (getline(infile, line)) {
			stringstream ss(line);
			int i = 0;
			array<string, 9> d;
			while (getline(ss, row, ',')) {
				d[i++] = row;
			}
			matrix.push_back(d);
		}


		infile.close();
	MenuParentSelect:
		system("cls");
		cout << "\n\t\t\tParent School Lunch System " << matrix.at(b)[1] << endl;
		underLine(80);

		cout << "\n\tPlease make a selection from the options below:" << endl;
		cout << "\n\t1.  Make an order" << endl;
		cout << "\t2.  Bulk Discount Offers" << endl;
		cout << "\t3.  School Contact Details & Location" << endl;
		cout << "\t4.  Make a Complaint" << endl;
		cout << "\t5.  Log Out" << endl;
		cout << "\n\n";

		changeColour(11);
		cout << "\n  Enter Option: ";
		changeColour(7);
		cin >> option;
		cout << endl << endl;

		switch (option) {
		case 1:
			int OrderReturn;

			OrderReturn = parentOrder(b); 

			if (OrderReturn == 0) {
				goto MenuParentSelect;
			}
		redoparentorder:
			changeColour(11);
			cout << "\n\n\n Enter 1 to return back to Parent Menu: ";
			changeColour(7);
			cin >> flag;
		
			if (flag != 1) {
				cout << "invalid input! Try again: ";
				cin >> flag;
				goto redoparentorder;
			}
			else {
				goto MenuParentSelect;
			}
			break;

		case 2:
			system("cls");
			bulkDiscount();
		redoparentbulk:
			changeColour(11);
			cout << "\n\n\n Enter 1 to return back to Parent Menu: ";
			changeColour(7);
			cin >> flag;
		
			if (flag != 1) {
				cout << "invalid input! Try again: ";
				cin >> flag;
				goto redoparentbulk;
			}
			else {
				goto MenuParentSelect;
			}
			break;

		case 3:
			system("cls");
			contactDetails();
		redoparentcontact:
			changeColour(11);
			cout << "\n\n\n Enter 1 to return back to Main Menu: ";
			changeColour(7);
			cin >> flag;

			if (flag != 1) {
				cout << "invalid input! Try again: ";
				cin >> flag;
				goto redoparentcontact;
			}
			else {
				goto MenuParentSelect;
			}
			break;

		case 4:
			Parentcomplaint(b);
		redoparentcomplaint:
			changeColour(11);
			cout << "\n\n\n Enter 1 to return back to Main Menu: ";
			changeColour(7);
			cin >> flag;

			if (flag != 1) {
				cout << "invalid input! Try again: ";
				cin >> flag;
				goto redoparentcomplaint;
			}
			else {
				goto MenuParentSelect;
			}
			
			break;
		case 5:
			goto MenuSelect;
			break;
		default:
			changeColour(4);
			cout << "\n\nPlease enter a valid option";
			changeColour(7);
			goto MenuParentSelect;
			break;
		}


	}

	else if (a == 2) {
		adminUpdateMenu();
	}

}