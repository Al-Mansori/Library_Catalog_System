#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <limits>
#include <map>
#include <regex>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

// Define Record structures for Authors and Books
struct AuthorRecord {
    char authorID[16]; // Extra byte for null terminator
    char authorName[31]; // Extra byte for null terminator
    char address[31]; // Extra byte for null terminator
};

struct BookRecord {
    char ISBN[16]; // Extra byte for null terminator
    char bookTitle[31]; // Extra byte for null terminator
    char authorID[16]; // Extra byte for null terminator
};

// Define Index structures
struct PrimaryIndex {
    char key[16]; // Extra byte for null terminator
    streampos position;
};

struct SecondaryIndex {
    char key[16]; // Extra byte for null terminator
    vector<string> positions;
};

struct InvertedIndex {
    map<string, int> invertedList; // Map key to next index position, -1 if none
};



class LibraryCatalogSystem {
private:
    const string authorsFileName = "authors.txt";
    const string booksFileName = "books.txt";
    string authorsPrimaryIndexFileName = "authors_primary_index.txt";
    string authorsSecondaryIndexFileName = "authors_secondary_index.txt";
    string authorsInvertedList = "authors_inverted_list.txt";
    string booksPrimaryIndexFileName = "books_primary_index.txt";
    string booksSecondaryIndexFileName = "books_secondary_index.txt";
    string booksInvertedList = "books_inverted_list";
    const int lengthIndicatorSize = 2;
    string RRN;
    InvertedIndex authorsInvertedIndex;
    InvertedIndex booksInvertedIndex;

    // Additional data structures for AVAIL LIST and other necessary components
    vector<streampos> authorsAvailList;
    vector<streampos> booksAvailList;

    // Index structures
    vector<PrimaryIndex> authorsPrimaryIndex;
    vector<PrimaryIndex> booksPrimaryIndex;
    vector<SecondaryIndex> booksSecondaryIndex;
    vector<SecondaryIndex> authorsSecondaryIndex;

public:
    // Function declarations for CRUD operations
    void addAuthor(const AuthorRecord& author);
    void deleteAuthor(const char* authorID);
    void updateAuthor(const AuthorRecord& updatedAuthor);

    void addBook(const BookRecord& book);
    void deleteBook(const char* ISBN);
    void updateBook(const BookRecord& updatedBook);

    // Function declarations for search operations
    AuthorRecord searchAuthorByID(const char* authorID);
    BookRecord searchBookByISBN(const char* ISBN);
    vector<BookRecord> searchBooksByAuthorID(const char* authorID);
    vector<AuthorRecord> searchAuthorIDByName(const char* authorName);

    // Function to return the positions
    int getPositionsAuthorByID(const char* authorID);
    int getPositionBookByISBN(const char* ISBN);

    // Function declarations for index-related operations
    void buildAuthorsPrimaryIndex();
    void buildBooksPrimaryIndex();
    void buildBooksSecondaryIndex();
    void buildAuthorsSecondaryIndex();

    // Additional functions for handling indexes, AVAIL LIST, and file operations

    // Function to parse and execute user queries
    void executeQuery();

    // Function for user interface
    static void displayWelcomeScreen();

    // to save the index
    void saveAuthorsPrimaryIndex();
    void saveBooksPrimaryIndex();
    void saveAuthorsSecondaryIndex();
    void saveBooksSecondaryIndex();
    void saveAuthorsInvertedList ();
    void saveBooksInvertedList();
    void run();

};
