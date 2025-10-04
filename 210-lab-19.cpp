// COMSC-210 | Lab 19 | Dainiz Almazan
// IDE used: CLion

// automate code from lab 18 so that it reads comments from an external file and the movie rating is a random double (1 decimal place) between 1.0 and 5.0
// create a Movie class with these private member variables: movie title, a linked list of structs containing the raiting, a review comment
// main() function will have a container of Movie objects, either array, vector, or linked list
// add nodes to head
// write a driver/demo program that has at least four Movie objects, each with at least 3 reviews
#include <iostream>
#include <limits>
using namespace std;

struct Node {
	double rating;
	string comment;
	Node *next;
};

// addNodeToHead() adds a new Node with the rating and comment values provided to the front of a linked list and sets the head to be the new node
// arguments: the head Node of a linked list, a double rating, a string comment
// returns: nothing
void addNodeToHead(Node *&, double, string);

// addNodeToTail() adds a new Node with the rating and comment values provided to the end of a linked list
// arguments: the head Node of a linked list, a double rating, a string comment
// returns: nothing
void addNodeToTail(Node *&, double, string);

// getListMethod() prompts the user for a choice, validates it, and then returns it.
// arguments: none
// returns: an int value 1 or 2
int getListMethod();

// getUserChoice() prompts the user for a choice, validates it, and then returns it.
// arguments: none
// returns: a char value 'Y' or 'N'
char getUserChoice();

// getValidRating() prompts the user for a rating, validates it, and then returns it.
// arguments: none
// returns: a double value between 0 and 5
double getValidRating();

// getValidComment() prompts the user for a comment, makes sure the input isn't empty, and then returns it.
// arguments: none
// returns: a non-empty string comment
string getValidComment();

int main() {
	// Initializing variables
	int listMethod;
	double tempRating;
	string tempComment;
	char choice = 'Y';
	Node *head = nullptr;

	listMethod = getListMethod();

	// lowercase chars are converted to uppercase in getUserChoice(), so only N is checked for
	while (choice != 'N') {
		tempRating = getValidRating();
		// Clearing stream before getline() is called in getValidComment();
		cin.ignore();
		tempComment = getValidComment();

		if (listMethod == 1)
			addNodeToHead(head, tempRating, tempComment);
		else
			addNodeToTail(head, tempRating, tempComment);

		choice = getUserChoice();
	}

	cout << "Outputting all reviews:" << endl;
	Node *cur = head;
	int count = 0;
	double total = 0;
	while (cur) {
		cout << "\t> Review #" << count + 1 << ": " << cur->rating << ": " << cur->comment << endl;
		count++;
		total += cur->rating;
		cur = cur->next;
	}
	cout << "\t> Average: " << total / count << endl;

	return 0;
}

void addNodeToHead(Node *&head, double rating, string comment) {
	// Creating a new Node with the values provided by the user
	Node *newNode = new Node();
	newNode->comment = comment;
	newNode->rating = rating;
	// Setting newNode->next to head to put newNode in front of head in the linked list
	newNode->next = head;
	// Setting head to newNode so that when we use the head pointer it's pointing to the correct node
	head = newNode;
}

void addNodeToTail(Node *&head, double rating, string comment) {
	// Creating a new Node with the values provided by the user
	Node *newNode = new Node();
	newNode->comment = comment;
	newNode->rating = rating;
	newNode->next = nullptr;

	// If list is empty, just set the new node as head
	if (!head)
		head = newNode;
	else {
		// Otherwise, traverse linked list until we reach the end (i.e. cur->next is nullptr)
		Node *cur = head;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		// Now that cur is the last node in the linked list, the new node is added after it
		cur->next = newNode;
	}
}

int getListMethod() {
	int temp;
	bool isValid = false;

	cout << "Which linked list method should we use?" << endl;
	cout << "\t [1] New nodes are added to the head of the linked list" << endl;
	cout << "\t [2] New nodes are added to the tail of the linked list" << endl;
	cout << "\tChoice: ";

	while (!isValid) {
		if (cin >> temp) {
			// If the user entered a valid value, the while loop ends
			if (temp == 1 || temp == 2)
				isValid = true;
			else // Checks for user input being an int value outside 1 or 2
				cout << "Invalid input. Please enter 1 or 2:";
		} else { // Checks for user input being a non-int value
			cout << "Invalid input. Please enter 1 or 2:";
			cin.clear();
			// Clearing the number of characters inputted by the user
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	return temp;
}

char getUserChoice() {
	char temp;
	bool isValid = false;

	cout << "Enter another review? Y/N: ";
	while (!isValid) {
		if (cin >> temp) {
			// If the user entered a valid value, the while loop ends
			if (temp == 'N' || temp == 'n' || temp == 'Y' || temp == 'y')
				isValid = true;
			else // Checks for user input being a char value outside Y or N
				cout << "Invalid input. Please enter Y or N:" << endl;
		} else { // Checks for user input being a non-char value
			cout << "Invalid input. Please enter Y or N:" << endl;
			cin.clear();
			// Clearing the number of characters inputted by the user
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	return toupper(temp);
}

double getValidRating() {
	double temp;
	bool isValid = false;

	cout << "Enter review rating 0-5: ";
	while (!isValid) {
		if (cin >> temp) {
			// If the user entered a valid value, the while loop ends
			if (temp >= 0 && temp <= 5)
				isValid = true;
			else // Checks for user input being a double value outside the range [0,5]
				cout << "Invalid input. Please enter a review rating 0-5:";
		} else { // Checks for user input being a non-double value
			cout << "Invalid input. Please enter a review rating 0-5:";
			cin.clear();
			// Clearing the number of characters inputted by the user
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	return temp;
}

string getValidComment() {
	string temp;

	cout << "Enter review comments: ";
	getline(cin, temp);
	while (temp.empty()) {
		cout << "Comments cannot be empty. Enter review comments:";
		getline(cin, temp);
	}

	return temp;
}
