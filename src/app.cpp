#define		_CRT_SECURE_NO_WARNINGS

#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<string>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
bool Redundant(BST*, Student);
bool Redundant2(BTNode*, Student);
int menu();
int choice;
bool ctrl = true;

int main() {
	BST* t1 = new BST;
	BST t2;
	int order, source;
	Student stu;

	do {
		choice = menu();
		switch (choice) {
		case(1)://read file
			if (!readFile("student.txt", t1))
				cout << "Error: Student.txt does not exist.\n";
			system("pause");
			system("cls");
			break;

		case(2)://Print Deepest Node
			if (!t1->deepestNodes())
				cout << "The tree is empty.\n";
			cout << endl;

			system("pause");
			system("cls");
			break;

		case(3)://Display student info
			cout << "Please choose an order you want data be printed (1 - Ascending, 2 - Descending): ";
			cin >> order;
			if (order != 1 && order != 2)
			{
				cout << "Invalid choice! Please choose again: ";
				cin >> order;
			}

			cout << "Please choose the data you might print in (1 - Screen, 2 - student-info.txt): ";
			cin >> source;
			if (source != 1 && source != 2)
			{
				cout << "Invalid choice! Please choose again: ";
				cin >> source;
			}

			if (t1->display(order, source))
			{
				cout << "Successfully display output\n\n";
				system("pause");
				system("cls");
			}
			else {
				cout << "The tree is empty\n";
				system("pause");
				system("cls");
			}


			break;

		case(4): //Clone Subtree Function
		{
			cout << "\nCloning subtree\n";
			cout << "================\n\n";
			cout << "Please enter the student ID that you wish to clone their subtree : ";
			cin >> stu.id;
				if (!t2.CloneSubtree(*t1, stu))
					cout << "\nFailed To Clone SubTree.\n" << endl;

				else {
					cout << "\n";
					cout << "===========================================================================" << endl;
					cout << "This is the pre-order print for t1:\n";
					cout << "===========================================================================\n" << endl;
					t1->preOrderPrint();
					cout << "\n\n";
					cout << "===========================================================================" << endl;
					cout << "This is the pre-order print for t2:\n";
					cout << "===========================================================================" << endl;
					t2.preOrderPrint();
					cout << "===========================================================================\n" << endl;
				}

			system("pause");
			system("cls");
			break;
		}

		case(5)://Print Level Node
			if (!t1->printLevelNodes())
				cout << "The tree is empty.\n";
			system("pause");
			system("cls");
			break;

		case(6)://Print Path
			if (!t1->printPaths())
				cout << "The tree is empty.\n";
			system("pause");
			system("cls");
			break;

		case(7)://Exit
			cout << "\nThe program will now exit." << endl;
			ctrl = false;
			break;

		default:
			//When choice input is out of range < 1 || > 7
			cout << "Invalid input. Please try again." << endl << endl;
			system("pause");
			system("cls");
			break;

		}
	} while (ctrl);
}

// member 1
bool Redundant(BST* tree, Student record)
{
	if (tree->empty()) return false;
	return Redundant2(tree->root, record);
}

bool Redundant2(BTNode* cur, Student record)
{
	if (cur == NULL) return false;
	if (cur->item.compare3(record.id)) return true; //Return true when there are duplicate record
	if (cur->item.id > record.id) //if the record ID is smaller than current node ID move to left node
	{
		return Redundant2(cur->left, record);
	}
	else return Redundant2(cur->right, record);
}

bool readFile(const char* filename, BST* tree) {
	Student student;
	ifstream infile;
	string line, skip = "= ", studentID;
	int count = 0;
	infile.open(filename); //open file and read

	if (!infile) return false;

	while (!infile.eof()) { //copy the student information until end of file
		getline(infile, line);
		student.id = stoi(line.substr(line.find(skip) + skip.length()));
		getline(infile, line);
		strcpy(student.name, line.substr(line.find(skip) + skip.length()).c_str());
		getline(infile, line);
		strcpy(student.address, line.substr(line.find(skip) + skip.length()).c_str());
		getline(infile, line);
		strcpy(student.DOB, line.substr(line.find(skip) + skip.length()).c_str());
		getline(infile, line);
		strcpy(student.phone_no, line.substr(line.find(skip) + skip.length()).c_str());
		getline(infile, line);
		strcpy(student.course, line.substr(line.find(skip) + skip.length()).c_str());
		getline(infile, line);
		student.cgpa = stod(line.substr(line.find(skip) + skip.length()));
		infile.ignore();

		if (!Redundant(tree, student)) { // check duplicate record
			tree->insert(student); // if not duplicate insert into tree
			count++;
		}
	}
	if (count == 0)
		cout << "There are no record inserted into the tree\n";
	else
		cout << count << " students have been successfully inserted.\n";
	infile.close();
	return true;

}

int menu() {
	int choice;
	cout << "\nMenu:\n";
	cout << "1. Read file\n";
	cout << "2. Print Deepest node\n";
	cout << "3. Display student\n";
	cout << "4. Clone Subtree\n";
	cout << "5. Print Level Node\n";
	cout << "6. Print Path\n";
	cout << "7. Exit\n";
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}
