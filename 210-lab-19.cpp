// COMSC-210 | Lab 19 | Dainiz Almazan
// IDE used: CLion

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
using namespace std;

// The text file has three reviews per movie
const int NUM_REVIEWS = 3;

// Used to get a random double between 1 and 5 for the rating field in review Node
uniform_real_distribution<double> distribution(1,5);
default_random_engine generator;

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
		Node *newNode = new Node();
		newNode->comment = comment;
		newNode->rating = distribution(generator);
		// Setting newNode->next to reviewsHead to put newNode at the front of the linked list
		newNode->next = reviewsHead;
		// Setting reviewsHead to newNode so that the head pointer is pointing to the correct node
		reviewsHead = newNode;
	}
	void displayMovieInfo() {
		cout << "Movie title: " << title << endl;
		cout << "Movie reviews: " << endl;
		Node *cur = reviewsHead;
		int count = 0;
		while (cur) {
			cout << "\t> Review #" << count + 1 << ": " << cur->rating << ": " << cur->comment << endl;
			count++;
			cur = cur->next;
		}
	}
};


int main() {
	// automate code from lab 18 so that it reads comments from an external file and
	// write a driver/demo program that has at least four Movie objects, each with at least 3 reviews

	// Initializing variables
	vector<Movie> movies;
	string tempTitle, tempComment;

	ifstream infile;
	infile.open("movieReviews.txt");
	if (infile.good()) {
		while (getline(infile, tempTitle)) {
			Movie tempMovie;
			tempMovie.setTitle(tempTitle);
			for (int i = 0; i < NUM_REVIEWS; i++) {
				getline(infile, tempComment);
				tempMovie.addReview(tempComment);
			}
			movies.push_back(tempMovie);
		}




	}else { // If the file can't be opened, the rest of the code can't execute.
		cout << "Error opening file.";
		return 1;
	}

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


	return 0;
}
