#include "LibraryCatalogSystem.h"
using namespace std;


int main() {
    LibraryCatalogSystem catalogSystem;
    AuthorRecord author{};
    string authorId;
    const char* ID;
    BookRecord book{};
    string bookISBN;
    const char* ISBN;
    catalogSystem.buildAuthorsPrimaryIndex();
    catalogSystem.buildAuthorsSecondaryIndex();
    catalogSystem.buildBooksPrimaryIndex();
    catalogSystem.buildBooksSecondaryIndex();
    while (true) {
        LibraryCatalogSystem::displayWelcomeScreen();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add New Author logic
                break;
            case 2:
                // Add New Book logic
                break;
            case 3:
                // Update Author Name (Author ID) logic
                break;
            case 4:
                // Update Book Title (ISBN) logic
                break;
            case 5:
                // Delete Book (ISBN) logic
                break;
            case 6:
                // Delete Author (Author ID) logic
                break;
            case 7:
                cout << "Enter Author ID: ";
                cin >> authorId;
                ID = authorId.c_str();
                author = catalogSystem.searchAuthorByID(ID);
                if (strlen(author.authorID) == 0){
                    cout << "<-------------------------------------->\n";
                    cout << " Author ID not found or Invalid ID\n";
                    cout << " <-------------------------------------->\n";
                }else{
                    cout << "<-------------------------------------->\n";
                    cout << " Author ID: " << author.authorID
                         << "\n Author Name: " << author.authorName
                         << "\n Author Address: " << author.address<< endl;
                    cout << " <-------------------------------------->\n";
                }
                break;
            case 8:
                cout << "Enter Book ISBN: ";
                cin >> bookISBN;
                ISBN = bookISBN.c_str();
                book = catalogSystem.searchBookByISBN(ISBN);
                if (strlen(book.ISBN) == 0){
                    cout << "<-------------------------------------->\n";
                    cout << " Book ISBN not found or Invalid ISBN\n";
                    cout << " <-------------------------------------->\n";
                }else{
                    cout << "<-------------------------------------->\n";
                    cout << " Book ISBN: " << book.ISBN
                         << "\n Book Title: " << book.bookTitle
                         << "\n Book Author: " << book.authorID<< endl;
                    cout << " <-------------------------------------->\n";
                }
                break;
            case 9:
                // Write Query logic
                break;
            case 10:
                cout << "Exiting the Library Catalog System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
