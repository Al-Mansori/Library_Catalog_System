#include "LibraryCatalogSystem.h"
using namespace std;

void LibraryCatalogSystem::addAuthor(const AuthorRecord& author) {
    // Implementation
}

void LibraryCatalogSystem::deleteAuthor(const char* authorID) {
    // Implementation
}

void LibraryCatalogSystem::updateAuthor(const AuthorRecord& updatedAuthor) {
    // Implementation
}

void LibraryCatalogSystem::addBook(const BookRecord& book) {
    // Implementation
}

void LibraryCatalogSystem::deleteBook(const char* ISBN) {
    // Implementation
}

void LibraryCatalogSystem::updateBook(const BookRecord& updatedBook) {
    // Implementation
}

AuthorRecord LibraryCatalogSystem::searchAuthorByID(const char* authorID) {
    // Implementation
    return AuthorRecord(); // Placeholder
}

std::vector<BookRecord> LibraryCatalogSystem::searchBooksByAuthorID(const char* authorID) {
    // Implementation
    return std::vector<BookRecord>(); // Placeholder
}

std::string LibraryCatalogSystem::searchAuthorNameByID(const char* authorID) {
    // Implementation
    return ""; // Placeholder
}

void LibraryCatalogSystem::buildAuthorsPrimaryIndex() {
    std::ifstream authorsFile(authorsFileName, std::ios::in);

    if (!authorsFile.is_open()) {
        std::cerr << "Error opening authors.txt\n";
        return;
    }
    // Clear existing index
    authorsPrimaryIndex.clear();

    // Read the Relative Record Number (RRN)
    authorsFile >> RRN;

    while (!authorsFile.eof()) {
        std::streampos position = authorsFile.tellg(); // Get the position before reading the record

        char delimiter;
        authorsFile >> delimiter; // Read the delimiter ('$')

        // Check if the record should be processed
        if (delimiter == '*') {
            // Ignore the record and move to the next
            authorsFile.ignore(std::numeric_limits<std::streamsize>::max(), '$');
            continue;
        }

        char length_arr[lengthIndicatorSize];
        authorsFile.read(length_arr, lengthIndicatorSize);
        length_arr[lengthIndicatorSize] = '\0';

        // Check if the record has a newline character after the length indicator
        if (length_arr[0] == '\n') {
            length_arr[0] = length_arr[1];
            authorsFile >> length_arr[1];
        }

        int length = atoi(length_arr);

        // Read the actual record data
        char max_authors[length];
        authorsFile.read(max_authors, length);
        max_authors[length] = '\0';

        char id[16] = {0}; // 15 characters for ID plus null terminator
        char name[31] = {0}; // 30 characters for Name plus null terminator
        char address[31] = {0}; // 30 characters for Address plus null terminator

        int count = 0;
        int i = 0;

        if (authorsFile.eof()){
            break;
        }

        // Read ID
        while (max_authors[i] != '|') {
            id[count] = max_authors[i];
            count++;
            i++;
        }
        id[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Name
        while (max_authors[i] != '|') {
            name[count] = max_authors[i];
            count++;
            i++;
        }
        name[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Address
        while (max_authors[i] != max_authors[length]) {
            address[count] = max_authors[i];
            count++;
            i++;
        }
        address[count] = '\0';

        authorsFile >> delimiter;

        // Build the primary index
        PrimaryIndex index;
        strcpy(index.key, id);
        index.position = position;

        authorsPrimaryIndex.push_back(index);
    }

    authorsFile.close();
// Sort the primary index based on the key before saving
    std::sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
              [](const PrimaryIndex& a, const PrimaryIndex& b) {
                  return std::strcmp(a.key, b.key) < 0;
              });

    // Save the primary index to authors_primary_index.dat
    saveAuthorsPrimaryIndex();

    // Print the built primary index for testing
//    std::cout << "Built Authors Primary Index:\n";
//    for (const auto &index : authorsPrimaryIndex) {
//        std::cout << "Key: " << index.key << ", Position: " << index.position << "\n";
//    }
}

void LibraryCatalogSystem::buildBooksPrimaryIndex() {
    std::ifstream booksFile(booksFileName , std::ios::in);

    if (!booksFile.is_open()) {
        std::cerr << "Error opening books.txt\n";
        return;
    }
    // Read the Relative Record Number (RRN)
    booksFile >> RRN;
    booksPrimaryIndexFileName.clear(); // Clear existing index

    while (!booksFile.eof()) {
        std::streampos position = booksFile.tellg(); // Get the position before reading the record

        char delimiter;
        booksFile >> delimiter; // Read the delimiter ('$')

        // Check if the record should be processed
        if (delimiter == '*') {
            // Ignore the record and move to the next
            booksFile.ignore(std::numeric_limits<std::streamsize>::max(), '$');
            continue;
        }

        char length_arr[lengthIndicatorSize];
        booksFile.read(length_arr, lengthIndicatorSize);
        length_arr[lengthIndicatorSize] = '\0';

        // Check if the record has a newline character after the length indicator
        if (length_arr[0] == '\n') {
            length_arr[0] = length_arr[1];
            booksFile >> length_arr[1];
        }

        int length = atoi(length_arr);

        // Read the actual record data
        char max_books[length];
        booksFile.read(max_books, length);
        max_books[length] = '\0';

        char isbn[16] = {0}; // 15 characters for ISBN plus null terminator
        char title[31] = {0}; // 30 characters for Title plus null terminator
        char aID[16] = {0}; // 15 characters for Author ID plus null terminator

        int count = 0;
        int i = 0;

        if (booksFile.eof()){
            break;
        }

        // Read ISBN
        while (max_books[i] != '|') {
            isbn[count] = max_books[i];
            count++;
            i++;
        }
        isbn[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Title
        while (max_books[i] != '|') {
            title[count] = max_books[i];
            count++;
            i++;
        }
        title[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Authors ID
        while (max_books[i] != '\0') {
            aID[count] = max_books[i];
            count++;
            i++;
        }
        aID[count] = '\0';

        booksFile >> delimiter;


        // Build the primary index
        PrimaryIndex index;
        strcpy(index.key, isbn);
        index.position = position;

        booksPrimaryIndex.push_back(index);



    }

    booksFile.close();
// Sort the primary index based on the key before saving
    std::sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
              [](const PrimaryIndex& a, const PrimaryIndex& b) {
                  return std::strcmp(a.key, b.key) < 0;
              });

//     Save the primary index to authors_primary_index.dat
        saveBooksPrimaryIndex();

    // Print the built primary index for testing
//    std::cout << "Built Books Primary Index:\n";
//    for (const auto &index : booksPrimaryIndex) {
//        std::cout << "Key: " << index.key << ", Position: " << index.position << "\n";
//    }
}

void LibraryCatalogSystem::buildBooksSecondaryIndex() {
    booksSecondaryIndexFileName.clear(); // Clear existing secondary index

    for (const auto &index : booksPrimaryIndex){
        // Read the book record using the position from the primary index
        std::ifstream booksFile(booksFileName, std::ios::in | std::ios::binary);
        booksFile.seekg(index.position);

        char delimiter;
        booksFile >> delimiter; // Read the delimiter ('$')

        char length_arr[lengthIndicatorSize];
        booksFile.read(length_arr, lengthIndicatorSize);
        length_arr[lengthIndicatorSize] = '\0';
        if (length_arr[0]== '\n'){
            length_arr[0] = length_arr[1];
            booksFile >> length_arr[1];
        }
        int length = atoi(length_arr);

        // Read the actual record data
        char max_books[length];
        booksFile.read(max_books, length);
        max_books[length] = '\0';

        char isbn[16] = {0}; // 15 characters for ISBN plus null terminator
        char title[31] = {0}; // 30 characters for Title plus null terminator
        char aID[16] = {0}; // 15 characters for Author ID plus null terminator

        int count = 0;
        int i = 0;


        // Read ISBN
        while (max_books[i] != '|') {
            isbn[count] = max_books[i];
            count++;
            i++;
        }
        isbn[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Title
        while (max_books[i] != '|') {
            title[count] = max_books[i];
            count++;
            i++;
        }
        title[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Authors ID
        while (max_books[i] != '\0') {
            aID[count] = max_books[i];
            count++;
            i++;
        }
        aID[count] = '\0';


        // Build the secondary index
        SecondaryIndex secondaryIndex;
        strcpy(secondaryIndex.key, aID);
        secondaryIndex.positions.emplace_back(isbn);

        // Check if the key already exists in the secondary index
        auto it = std::find_if(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                               [&secondaryIndex](const SecondaryIndex& s) {
                                   return std::strcmp(s.key, secondaryIndex.key) == 0;
                               });

        if (it != booksSecondaryIndex.end()) {
            // Key exists, append position to existing entry
            it->positions.emplace_back(isbn);
        } else {
            // Key does not exist, add a new entry
            booksSecondaryIndex.push_back(secondaryIndex);
        }

        booksFile.close();

    }

    // Sort the secondary index based on the key (Author ID)
    std::sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
              [](const SecondaryIndex& a, const SecondaryIndex& b) {
                  return std::strcmp(a.key, b.key) < 0;
              });

    // Save the secondary index to books_secondary_index.txt
    saveBooksSecondaryIndex();
}

void LibraryCatalogSystem::buildAuthorsSecondaryIndex(){
    authorsSecondaryIndexFileName.clear(); // Clear existing secondary index

    for (const auto &index : authorsPrimaryIndex) {
        // Read the author record using the position from the primary index
        std::ifstream authorsFile(authorsFileName, std::ios::in | std::ios::binary);
        authorsFile.seekg(index.position);

        char delimiter;
        authorsFile >> delimiter; // Read the delimiter ('$')

        char length_arr[lengthIndicatorSize];
        authorsFile.read(length_arr, lengthIndicatorSize);
        length_arr[lengthIndicatorSize] = '\0';
        if (length_arr[0]== '\n'){
            length_arr[0] = length_arr[1];
            authorsFile >> length_arr[1];
        }
        int length = atoi(length_arr);

        // Read the actual record data
        char max_authors[length];
        authorsFile.read(max_authors, length);
        max_authors[length] = '\0';

        char id[16] = {0}; // 15 characters for ID plus null terminator
        char name[31] = {0}; // 30 characters for Name plus null terminator
        char address[31] = {0}; // 30 characters for Address plus null terminator

        int count = 0;
        int i = 0;

        // Read ID
        while (max_authors[i] != '|') {
            id[count] = max_authors[i];
            count++;
            i++;
        }
        id[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Name
        while (max_authors[i] != '|') {
            name[count] = max_authors[i];
            count++;
            i++;
        }
        name[count] = '\0';
        count = 0;
        i++; // Skip the '|'

        // Read Address
        while (max_authors[i] != '\0') {
            address[count] = max_authors[i];
            count++;
            i++;
        }
        address[count] = '\0';



        // Build the secondary index
        SecondaryIndex secondaryIndex;
        strcpy(secondaryIndex.key, name);
        secondaryIndex.positions.emplace_back(id);

        // Check if the key already exists in the secondary index
        auto it = std::find_if(authorsSecondaryIndex.begin(), authorsSecondaryIndex.end(),
                               [&secondaryIndex](const SecondaryIndex& s) {
                                   return std::strcmp(s.key, secondaryIndex.key) == 0;
                               });

        if (it != authorsSecondaryIndex.end()) {
            // Key exists, append position to existing entry
            it->positions.emplace_back(id);
        } else {
            // Key does not exist, add a new entry
            authorsSecondaryIndex.push_back(secondaryIndex);
        }

        authorsFile.close();
    }

    // Sort the secondary index based on the key (Author Name)
    std::sort(authorsSecondaryIndex.begin(), authorsSecondaryIndex.end(),
              [](const SecondaryIndex& a, const SecondaryIndex& b) {
                  return std::strcmp(a.key, b.key) < 0;
              });

    // Save the secondary index to authors_secondary_index.dat
    saveAuthorsSecondaryIndex();
}

void LibraryCatalogSystem::displayWelcomeScreen() {
    cout << "Welcome to the Library Catalog System\n";
    cout << "--------------------------------------\n";
    cout << "1. Add New Author\n";
    cout << "2. Add New Book\n";
    cout << "3. Update Author Name (Author ID)\n";
    cout << "4. Update Book Title (ISBN)\n";
    cout << "5. Delete Book (ISBN)\n";
    cout << "6. Delete Author (Author ID)\n";
    cout << "7. Print Author (Author ID)\n";
    cout << "8. Print Book (ISBN)\n";
    cout << "9. Write Query\n";
    cout << "10. Exit\n";
    cout << "--------------------------------------\n";
}

void LibraryCatalogSystem::saveAuthorsPrimaryIndex(){
    std::ofstream indexFile("authors_primary_index.txt", std::ios::out | std::ios::binary);

    if (!indexFile.is_open()) {
        std::cerr << "Error opening authors_primary_index.dat\n";
        return;
    }

    for (const auto &index : authorsPrimaryIndex) {
        // Write the key and position to the index file
        indexFile.write(index.key, strlen(index.key));
        indexFile << " " << index.position;
        indexFile << "\n";
    }

    indexFile.close();

}

void LibraryCatalogSystem::saveAuthorsSecondaryIndex(){
    std::ofstream indexFile("authors_secondary_index.txt", std::ios::out);

    if (!indexFile.is_open()) {
        std::cerr << "Error opening authors_secondary_index.dat\n";
        return;
    }

    for (const auto &index : authorsSecondaryIndex) {
        // Write the key and positions to the index file
        indexFile.write(index.key, strlen(index.key));

        for (const auto &pos : index.positions) {
            indexFile << " " << pos; // Write positions as a string
        }

        indexFile << "\n"; // Add newline for readability
    }

    indexFile.close();
}

void LibraryCatalogSystem::saveBooksPrimaryIndex(){
    std::ofstream indexFile("books_primary_index.txt", std::ios::out | std::ios::binary);

    if (!indexFile.is_open()) {
        std::cerr << "Error opening authors_primary_index.dat\n";
        return;
    }

    for (const auto &index : booksPrimaryIndex) {
        // Write the key and position to the index file
        indexFile.write(index.key, strlen(index.key));
        indexFile << " " << index.position;
        indexFile << "\n";
    }

    indexFile.close();
}

void LibraryCatalogSystem::saveBooksSecondaryIndex(){
    std::ofstream indexFile( "books_secondary_index.txt", std::ios::out);

    if (!indexFile.is_open()) {
        std::cerr << "Error opening books_secondary_index.dat\n";
        return;
    }

    for (const auto &index : booksSecondaryIndex) {
        // Write the key and positions to the index file
        indexFile.write(index.key, strlen(index.key));

        for (const auto &pos : index.positions) {
            indexFile << " " << pos; // Write positions as a string
        }

        indexFile << "\n"; // Add newline for readability
    }

    indexFile.close();
}

void LibraryCatalogSystem::executeQuery(const string& query) {
    // Implementation
}

