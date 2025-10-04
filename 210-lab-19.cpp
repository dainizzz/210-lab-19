// COMSC-210 | Lab 19 | Dainiz Almazan
// IDE used: CLion

// automate code from lab 18 so that it reads comments from an external file and
// the movie rating is a random double (1 decimal place) between 1.0 and 5.0
// write a driver/demo program that has at least four Movie objects, each with at least 3 reviews
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	double rating;
	string comment;
	Node *next;
};

class Movie {
	string title;
	Node* reviews;
public:
	// TODO: add getters and setters
};

// addNodeToHead() adds a new Node with the rating and comment values provided to the front of a linked list and sets the head to be the new node
// arguments: the head Node of a linked list, a double rating, a string comment
// returns: nothing
void addNodeToHead(Node *&, double, string);


int main() {
	// Initializing variables
	vector<Movie> movies;

	//TODO: Implement reading from file

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
