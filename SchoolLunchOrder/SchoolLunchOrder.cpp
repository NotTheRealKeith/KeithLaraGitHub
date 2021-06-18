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
	ParentAcc parentID;
	ParentAcc childName;
	string itemOrderName;
	float itemOrderPrice;
	int quantity;
	bool paymentStatus;
};

struct ParentComplaint {
	string compDate;
	string compItem;
	string comptDesc;
	string compNumber;
	ParentAcc firstName;
	ParentAcc contactNum;
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

// -- create underlines only --
void underLine(int x) {
	int i;

	for (i = 0; i < x; i++) {
		cout << "-";
	}
	cout << endl;
}

// ===== vv LARA CODE SECTION vv =====
void bulkDiscount() {
	cout << "\n\t\t\tBulk Discount Offers\t\t\t" << endl;
	underLine(80);

	cout << "\nItems can be ordered over different days for the children \n(including different weeks)";
	cout << "\n\n1. 15 Items Ordered = 5% off total order";
	cout << "\n2. 25 Items Ordered = 10% off total order";
	cout << "\n1. 40+ Items Ordered = 15% off total order";
}

void contactDetails() {
	cout << "\n\t\t\tContact Details\t\t\t" << endl;
	underLine(80);
	cout << "\nIf you would like to contact us regarding any queries you \nmay have you may reach us via our phone number and email \nshown below: ";
	cout << "\n\nContact Number: (04) 578 - 2364";
	cout << "\n\nEmail: schoollunchsystem@gmail.com";
	cout << "\n\nOffice Location 45 School St, Thorndon, Wellington, NZ";
	cout << "\n\nOffice Hours: 1pm - 5pm, Monday - Friday";
}

int ParentReg(ParentAcc* ptr) {
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
	outfile.open("parentlogin.csv", ios::out);

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
		cout << "\n\nWrong login information try again (you have " << n-- << " more attempts!\n";
	}

	if (a == -1) {
		cout << "\n\nThe number of login attempts has been exceeded, try again another time.";
	}

exit:
	infile.close();
	return a;
}

void filterPrice() {

	/*vector<array<string, 2> > fp;
	vector<array<string, 2> > food;
	array<string, 2> fo;

	ifstream infile;
	infile.open("menuItems.csv", ios::in);

	string line, row, item, stringprice;
	float fpImp;

	while (getline(infile, line)) {
		stringstream ss(line);
		int i = 0;
		array<string, 2> b;
		while (getline(ss, row, ',')) {
			b[i++] = row;
		}
		fp.push_back(b);
	}

	infile.close();

	sort(fp.begin(), fp.end());

	for (auto item : fp) {
		cout << item << "\t\t" << item;
	}

	*/



	//Create minimum and maxixmum for vector
}

void filterVeg() {
	//vector<vector<string> > vegmenu;//
	//
	//vector<array< string, 4> > veg;

	//ifstream infile;
	//infile.open("menuItems.csv", ios::in);

	//string line, row, item, stringprice;

	//while (getline(infile, line)) {
	//	stringstream ss(line);
	//	int i = 0;
	//	vector<string> b;
	//	while (getline(ss, row, ',')) {
	//		b[i] = row;
	//		i++;
	//		
	//	}
	//	vegmenu.push_back(b);
	//}
	//for (auto i : vegmenu) {
	//	if ()

	//}

	//vector<array<string, 2> > matrix;
	//vector<array<string, 2> > food;

	//ifstream infile;
	//infile.open("menuItems.csv", ios::in);

	//string line, row, item;
	//float matrixImp;

	//while (getline(infile, line)) {
	//	stringstream ss(line);
	//	int i = 0;
	//	array<string, 2> b;
	//	while (getline(ss, row, ',')) {
	//		b[i++] = row;
	//	}
	//	matrix.push_back(b);
	//}

	//for (int i = 0; i < matrix.size(); ++i) {
	//	float a = stof(matrix.at(i)[1]);
	//	if (matrixImp < a) {
	//		item = matrix.at(i)[0];
	//		string stringprice = to_string(a);
	//		food.push_back(item);
	//		food.push_back(stringprice);
	//	}
	//}
	//

	//infile.close();

}

int parentOrder(int person){
	int option;
	menu:
	ifstream infile;
	infile.open("menuItems.csv", ios::in);

	string readData;
	int itemPrice;

	cout << "Menu Items: \n\n";
	while (getline(infile, readData)) {
		cout << readData << endl;
	}

	infile.close();
	
	cout << "\n\n\nMake a selection from the options below:";
	cout << "\n\n1. Filter by price (low to high)";
	cout << "\n2. Filter only vegetarian options";
	cout << "\n3. Filter only GF options";
	cout << "\n4. Order Food";
	cout << "\n5. Go back to main menu";
	cout << "\n\n\nEnter Option: ";
	cin >> option;

	switch (option) {
	case 1:
		filterPrice();
		break;
	case 2:
		filterVeg();
		break;
	case 3:
		//Filter gf opt
		break;
	case 4:
		//Order
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
		id = rand() % 10000000 + 9999999;
		iD = to_string(id);
		for (int j = 0; j < 9; j++) {
			if (assignID[j] == iD) {
				goto redoID;
			}
		}
		iD = assignID[i];
	}

	fstream outfile; // writes into the csv file with menu item data

	outfile.open("menuItems.csv", ios::out);
	outfile << assignID[0] << "Ham Sandwich" << ","
		<< "4.50" << "," << "2" << "," << "2" << endl
		<< assignID[1] << "Vegetarian Sandwich" << ","
		<< "5.00" "," << "2" << "," << "1" << endl
		<< assignID[2] << "Chicken and Avo\t\t" << ","
		<< "6.50" "," << "1" << "," << "2" << endl
		<< "Steak and Cheese" << ","
		<< "4.50" "," << "2" << "," << "2" << endl
		<< "Butter Chicken" << ","
		<< "5.50" "," << "2" << "," << "2" << endl
		<< "Mushroom and Cheese" << ","
		<< "6.50" "," << "1" << "," << "1" << endl
		<< "Cheese" << ","
		<< "4.50" "," << "2" << "," << "2" << endl
		<< "Pepperoni" << ","
		<< "5.50" "," << "2" << "," << "2" << endl
		<< "Veg (GF)" << ","
		<< "6.50" "," << "1" << "," << "1" << endl;
	outfile.close();
}

// --- reads menu csv file 
void  menuPreview() {
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
		cout << vectorMenu.at(i)[0] << " - " << vectorMenu.at(i)[1] << endl;
	}
}

//admin update menu function 
void adminUpdateMenu() {
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
		int itemNameChoice;
		cout << "\n\nMenu Name Change\n\n";
		menuPreview();

		cout << "what item would you like to change?(choose from 1 -6)\n";
		cin >> itemNameChoice;
		if (itemNameChoice == 1) {
			for (int i = 0; i < vectorMenu.size(); i++) {
				cout << vectorMenu.at(i)[0] << endl;
			}
		}


	}

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
	// --- added intro screen below V --- //
	cout << "\n\t\t\tSchool Lunch Order System\t\t\t" << endl;
	underLine(80);

	cout << "\n\tPlease make a selection from the options below:" << endl;
MenuSelect:
	cout << "\n\t1.  Preview of Menu" << endl;
	cout << "\t2.  Bulk Discount Offers" << endl;
	cout << "\t3.  School Contact Details & Location" << endl;
	cout << "\t4.  Login to your account" << endl;
	cout << "\t5.  Register a new account" << endl;

	cout << "\n\n";

	cout << "\n  Selection: ";
	cin >> index;

	switch (index) {
	case 1:
		menuPreview();

		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		cin >> flag;

		if (flag != 1) {   //find a way to make this loop if condition is not met (IN PROGRESS)
			cout << "invalid input! Try again: ";
		}
		else {
			goto MenuSelect;
		}

		break;
	case 2:
		bulkDiscount();

		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		cin >> flag;
	redo1:
		if (flag != 1) {
			cout << "invalid input! Try again: ";
			cin >> flag;
			goto redo1;
		}
		else {
			goto MenuSelect;
		}
		break;
	case 3:
		contactDetails();

		cout << "\n\n\n Enter 1 to return back to Main Menu: ";
		cin >> flag;
	redo2:
		if (flag != 1) {
			cout << "invalid input! Try again: ";
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
		cout << "\n\t\t\tParent School Lunch System " << matrix.at(b)[1] << endl;
		underLine(80);

		cout << "\n\tPlease make a selection from the options below:" << endl;
		cout << "\n\t1.  Make an order" << endl;
		cout << "\t2.  Bulk Discount Offers" << endl;
		cout << "\t3.  School Contact Details & Location" << endl;
		cout << "\t4.  Make a Complaint" << endl;
		cout << "\n\n";

		cout << "\n  Enter Option: ";
		cin >> option;

		switch (option) {
		case 1:
			int OrderReturn;

			OrderReturn = parentOrder(b); 

			if (OrderReturn == 0) {
				goto MenuParentSelect;
			}

			cout << "\n\n\n Enter 1 to return back to Parent Menu: ";
			cin >> flag;
		redoparentorder:
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
			bulkDiscount();

			cout << "\n\n\n Enter 1 to return back to Parent Menu: ";
			cin >> flag;
		redoparentbulk:
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
			contactDetails();

			cout << "\n\n\n Enter 1 to return back to Main Menu: ";
			cin >> flag;
		redoparentcontact:
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
			struct ParentComplaint ParentComp;
			struct ParentComplaint* ptrParentComp;

			ptrParentComp = &ParentComp;

			srand(time(NULL));
			int pc = rand() % 100000 + 99999;

			ptrParentComp->compNumber = to_string(pc);

			cout << "\n\t\t\tComplaint Form (" << ptrParentComp->compNumber << ")" << endl;
			underLine(80);
			break;
		}


	}

	else if (a == 2) {
		adminUpdateMenu();
	}

}