#include <bits/stdc++.h>

using namespace std;

class User {
	string id, password, name;
public:
	User(string id, string password) {}

	User(string id, string password, string name) {}

	vector<string> details() const { return { getid(), getpassword(), getname() }; }

	string getid() const { return id; }
	
	string getpassword() const { return password; }
	
	string getname() const { return name; }
};


class Users {
	unordered_map<string, User> Hash;
public:
	Users() {}

	Users(string file) {}

	Users(ifstream in) {}

	vector<string> details(sting id) {
		unorderd_map<string, User>::iterator it = Hash.find(id);
		if(it == Hash.end())
			return "not found";
		return it->second.details();
	}

	bool login(string id, string password) {
		unorderd_map<string, User>::iterator it = Hash.find(id);
		if(it == Hash.end())
			return false;
		return it->second.getpassword() == password;
	}
};

class Library {

public:
	Library() {}

	Library(string file) {}

	Library(ifstream in) {}

	void Search(string book) {

	}

	void borrow(string id, string book) {

	}

	void back(string book) {

	}
};


int main() {
	Users* users = new Users("people.data");
	Library* lib = new Library("books.data");
	while(true) {
		int choice;
		string id, s, password;
		cout << "1. Search" << endl << "2. Query" << "3. Borrow" << endl << "4. Return" << endl << "5.Exit" << endl;
		cin >> choice;
		switch(choice) {
			case 1:
				cout << "Search by Book name, Barcode No, or Author : ";
				cin >> s;
				lib.search(s);
				break;
			case 2:
				cout << "Enter your ID : ";
				cin >> id;
				for(auto& e : users.details(s))
				       cout << e << endl;
				break;
			case 3:
				cout << "Login" << endl << "ID : ";
				cin >> id;
				cout << "Password : ";
				cin >> password;
				cout << "Enter the book Barcode No : ";
				cin >> s;
				if(users.login(id,password))
					lib.borrow(id,s);
				else
					cout << "Not registered" << endl;
				break;
			case 4:
				cout << "Enter book Barcode No : ";
				cin >> s;
				lib.back(s);
				break;
			case 5:
				return 0;
			default:
				break;
		}
	}
	return 0;
}
