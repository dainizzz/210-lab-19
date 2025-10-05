// COMSC-210 | Lab 19 | Dainiz Almazan
// IDE used: CLion

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
	Node* reviewsHead;
public:
	string getTitle() const { return title;}
	Node* getReviews() const {return reviewsHead;}
	void setTitle(string title) { this->title = title;}
	void addReview(string comment) {
		// Creating a new Node with the values provided by the user
		Node *newNode = new Node();
		newNode->comment = comment;
		newNode->rating; //the movie rating is a random double (1 decimal place) between 1.0 and 5.0
		// Setting newNode->next to reviewsHead to put newNode at the front of the linked list
		newNode->next = reviewsHead;
		// Setting reviewsHead to newNode so that the head pointer is pointing to the correct node
		reviewsHead = newNode;
	}
};


int main() {
	// automate code from lab 18 so that it reads comments from an external file and
	// write a driver/demo program that has at least four Movie objects, each with at least 3 reviews

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

	// TODO: Change this so it goes through the vector of Movie objects and then the reviews
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
