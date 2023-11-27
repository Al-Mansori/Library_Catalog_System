#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <limits>
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

class LibraryCatalogSystem {
private:
    const string authorsFileName = "authors.txt";
    const string booksFileName = "books.txt";
    string authorsPrimaryIndexFileName = "authors_primary_index.txt";
    string authorsSecondaryIndexFileName = "authors_secondary_index.txt";
    string booksPrimaryIndexFileName = "books_primary_index.txt";
    string booksSecondaryIndexFileName = "books_secondary_index.txt";
    const int lengthIndicatorSize = 2;
    string RRN;

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
    vector<BookRecord> searchBooksByAuthorID(const char* authorID);
    string searchAuthorNameByID(const char* authorID);

    // Function declarations for index-related operations
    void buildAuthorsPrimaryIndex();
    void buildBooksPrimaryIndex();
    void buildBooksSecondaryIndex();
    void buildAuthorsSecondaryIndex();

    // Additional functions for handling indexes, AVAIL LIST, and file operations

    // Function to parse and execute user queries
    void executeQuery(const string& query);

    // Function for user interface
    static void displayWelcomeScreen();

    // to save the index
    void saveAuthorsPrimaryIndex();
    void saveBooksPrimaryIndex();
    void saveAuthorsSecondaryIndex();
    void saveBooksSecondaryIndex();

};
