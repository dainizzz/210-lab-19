// COMSC-210 | Lab 19 | Dainiz Almazan
// IDE used: CLion

#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

// The text file has three reviews per movie
const int NUM_REVIEWS = 3;

// Used to get a random double between 1 and 5 for the rating field in the review Nodes
uniform_real_distribution<double> distribution(1, 5);
default_random_engine generator;

struct Node {
	double rating;
	string comment;
	Node *next;
};

class Movie {
	// The default access specifier for classes is private, so private: isn't necessary here
	string title;
	Node *reviewsHead;

public:
	// The default constructor sets the head node of the reviews linked list to nullptr
	Movie() { reviewsHead = nullptr; }

	// title is the only field that needs to be modified in the driver program
	void setTitle(string title) { this->title = title; }

	// reviewsHead has no setter since it only needs to be modified when more nodes are added to the front of the linked
	// list in addReview()
	void addReview(string comment) {
		Node *newNode = new Node();
		newNode->comment = comment;
		newNode->rating = distribution(generator);
		// Setting newNode->next to reviewsHead to put newNode at the front of the linked list
		newNode->next = reviewsHead;
		// Setting reviewsHead to newNode so that the head pointer is pointing to the correct node
		reviewsHead = newNode;
	}

	// displayMovieInfo() is used instead of providing getters for the Movie class since the driver program doesn't need
	// to do anything with the Movie data except outputting it
	void displayMovieInfo() {
		static int movieNum = 1;
		cout << "Movie #" << movieNum++ << ": " << title << endl;
		cout << "Reviews: " << endl;
		Node *cur = reviewsHead;
		int reviewNum = 1;
		while (cur) {
			cout << "\t> Review #" << reviewNum++ << ": " << setprecision(2) << cur->rating << ": " <<
					cur->comment << endl;
			cur = cur->next;
		}
		cout << endl;
	}
};


int main() {
	// Initializing variables
	vector<Movie> movies;
	string tempTitle, tempComment;

	cout << "Reading movie data from file..." << endl;
	ifstream infile;
	infile.open("movieReviews.txt");
	if (infile.good()) {
		// In movieReviews.txt, the movie title is followed by three reviews so this code first reads the movie title
		// and stores it in tempTitle
		while (getline(infile, tempTitle)) {
			Movie tempMovie;
			tempMovie.setTitle(tempTitle);
			// The 3 (i.e. NUM_REVIEWS) consequent lines in movieReviews.txt are each reviews
			for (int i = 0; i < NUM_REVIEWS; i++) {
				getline(infile, tempComment);
				tempMovie.addReview(tempComment);
			}
			// After all the relevant data has been successfully read and added to the Movie object, the Movie is added
			// to the vector of Movie objects.
			movies.push_back(tempMovie);
		}
	} else {
		// If the file can't be opened, the program should end
		cout << "Error opening file.";
		return 1;
	}

	cout << "Movie data added successfully! Outputting movie data..." << endl << endl;
	for (Movie movie: movies) {
		movie.displayMovieInfo();
	}

	return 0;
}
