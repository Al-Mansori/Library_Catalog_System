#include "LibraryCatalogSystem.h"
using namespace std;


int main() {
    LibraryCatalogSystem catalogSystem;
    catalogSystem.buildAuthorsPrimaryIndex();
    catalogSystem.buildAuthorsSecondaryIndex();
    catalogSystem.buildBooksPrimaryIndex();
    catalogSystem.buildBooksSecondaryIndex();
    while (true) {
        catalogSystem.displayWelcomeScreen();

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
                // Print Author (Author ID) logic
                break;
            case 8:
                // Print Book (ISBN) logic
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
