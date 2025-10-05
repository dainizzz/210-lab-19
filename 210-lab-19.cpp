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

// Used to get a random double between 1 and 5 for the rating field in review Node
uniform_real_distribution<double> distribution(1, 5);
default_random_engine generator;

struct Node {
	double rating;
	string comment;
	Node *next;
};

class Movie {
	string title;
	Node *reviewsHead;

public:
	// The default constructor sets the head node of the reviews linked list to nullptr
	Movie() { reviewsHead = nullptr; }
	string getTitle() const { return title; }
	Node *getReviews() const { return reviewsHead; }
	void setTitle(string title) { this->title = title; }

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
		static int movieNum = 1;
		cout << "MOVIE #" << movieNum++ << ":" << endl;
		cout << "Title: " << title << endl;
		cout << "Movie reviews: " << endl;
		Node *cur = reviewsHead;
		int reviewNum = 1;
		while (cur) {
			cout << "\t> Review #" << reviewNum++ << ": " << setprecision(2) << cur->rating << ": " << cur->comment <<
					endl;
			cur = cur->next;
		}
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
		while (getline(infile, tempTitle)) {
			Movie tempMovie;
			tempMovie.setTitle(tempTitle);
			for (int i = 0; i < NUM_REVIEWS; i++) {
				getline(infile, tempComment);
				tempMovie.addReview(tempComment);
			}
			movies.push_back(tempMovie);
		}
	} else {
		// If the file can't be opened, the rest of the code can't execute.
		cout << "Error opening file.";
		return 1;
	}

	cout << "Movie data added successfully! Outputting movie data..." << endl;
	for (Movie movie: movies) {
		movie.displayMovieInfo();
	}


	return 0;
}
