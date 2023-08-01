#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to validate the username and password
bool isValidLogin(const string& username, const string& password) {
    // Replace the following hardcoded credentials with your desired username and password
    const string validUsername = "admin";
    const string validPassword = "admin";
    return (username == validUsername && password == validPassword);
}

// Book class definition
class Book {
public:
    // Public member variables to store book information
    string bookId;      // The unique identifier for the book
    string title;       // The title of the book
    string author;      // The author of the book
    string publisher;   // The publisher of the book
    bool available;     // A flag to indicate whether the book is available for borrowing

    // Constructor: Initializes the Book object with the provided information
    Book(string id, string t, string a, string p, bool avail)
            : bookId(move(id)), title(move(t)), author(move(a)),
              publisher(move(p)), available(avail) {}
};

// Patron class definition
class Patron {
public:
    // Public member variables to store patron information
    string patronId;    // The unique identifier for the patron
    string name;        // The name of the patron
    string contact;     // The contact information for the patron (e.g., phone number or email)

    // Constructor: Initializes the Patron object with the provided information
    Patron(string id, string n, string c)
            : patronId(move(id)), name(move(n)), contact(move(c)) {}
};

// Library class definition
class Library {
private:
    vector<Book> books;       // A vector to store the collection of books in the library
    vector<Patron> patrons;   // A vector to store the list of patrons or library members

public:

    // Function to add a new book to the library's collection
    void addBook();

    // Function to search for a book by its Book ID, Title, or Author
    void searchBook();

    // Function to update the details of an existing book in the library
    void updateBook();

    // Function to delete a book from the library's collection
    void deleteBook();

    // Function to display all the books in the library
    void displayAllBooks();

    // Member functions to interact with the library's patrons or members

    // Function to add a new patron or library member
    void addPatron();

    // Function to search for a patron by their Patron ID or Name
    void searchPatron();

    // Function to update the details of an existing patron
    void updatePatron();

    // Function to delete a patron from the library's records
    void deletePatron();

    // Function to display all the patrons or library members
    void displayAllPatrons();

    // Member functions to handle book checkouts and returns

    // Function to check out a book to a patron
    void checkOutBook();

    // Function to return a book from a patron
    void returnBook();

    // Function to display all the currently checked-out books with their respective patrons
    void displayAllCheckouts();

    // Member functions to save and load library data from a file

    // Function to save the library's data (books, patrons, checkouts) to a file
    void saveDataToFile();

    // Function to load the library's data (books, patrons, checkouts) from a file
    void loadDataFromFile();
};


void Library::addBook() {
    // Declare variables to store book information
    string bookId, title, author, publisher;
    bool available = true;

    cout << "-------------------------------------------------" << endl;
    cout << "                     ADD BOOK                    " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the book ID
    cout << "Enter Book ID: ";
    cin >> bookId;

    // Check if the book ID already exists in the library using a traditional for loop
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].bookId == bookId) {
            cout << "A book with this ID already exists." << endl;
            return; // Exit the function if the book ID is already present
        }
    }
    // Clear any leftover newline character from the previous input
    cin.ignore();

    // Ask the user to enter the book title
    cout << "Enter Title: ";
    getline(cin, title);

    // Ask the user to enter the book author
    cout << "Enter Author: ";
    getline(cin, author);

    // Ask the user to enter the book publisher
    cout << "Enter Publisher: ";
    getline(cin, publisher);

    // Create a new Book object using the entered information and add it to the library's collection of books
    books.emplace_back(bookId, title, author, publisher, available);

    // Print a success message with a design or visual feedback
    cout << "-------------------------------------------------" << endl;
    cout << " Book added successfully! Here are the details:  " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Book ID: " << bookId << endl;
    cout << " Title: " << title << endl;
    cout << " Author: " << author << endl;
    cout << " Publisher: " << publisher << endl;
    cout << "-------------------------------------------------" << endl;
}

void Library::searchBook() {
    // Declare a variable to store the search term entered by the user
    string searchTerm;

    cout << "-------------------------------------------------" << endl;
    cout << "                    SEARCH BOOK                  " << endl;
    cout << "-------------------------------------------------" << endl;

    cout << "Enter Book ID, Title, or Author to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    // Create a vector to store the search results
    vector<Book> searchResults;

    // Search for the book by ID, title, or author using a traditional for loop
    for (size_t i = 0; i < books.size(); i++) {
        const Book& book = books[i];
        if (book.bookId == searchTerm || book.title == searchTerm || book.author == searchTerm) {
            // If the book matches the search term, add it to the searchResults vector
            searchResults.push_back(book);
        }
    }

    // Check if there are any search results
    if (searchResults.empty()) {
        cout << "-------------------------------------------------" << endl;
        cout << "Book not found." << endl;
    } else {
        // If there are search results, display them to the user
        cout << "-------------------------------------------------" << endl;
        cout << "Search Results:" << endl;
        int resultNumber = 1;
        for (const auto& book : searchResults) {
            cout << "Result " << resultNumber << ":" << endl;
            cout << "Book ID: " << book.bookId << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Publisher: " << book.publisher << endl;
            cout << "Availability: " << (book.available ? "Available" : "Not Available") << endl;
            cout << "-------------------------------------------------" << endl;
            resultNumber++;
        }

        // Ask if the user wants more details about a specific book
        cout << "Do you want more details about a specific book? (Y/N): ";
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            cout << "Enter the Result number for the book you want more details about: ";
            int bookIndex;
            cin >> bookIndex;
            bookIndex--; // Convert to 0-based index

            if (bookIndex >= 0 && bookIndex < searchResults.size()) {
                const auto& book = searchResults[bookIndex];
                // Display detailed information about the selected book
                cout << "Detailed Information:" << endl;
                cout << "Book ID: " << book.bookId << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Publisher: " << book.publisher << endl;
                cout << "Availability: " << (book.available ? "Available" : "Not Available") << endl;
                // Add more details about the book here if needed
            } else {
                cout << "Invalid Result number. No detailed information available." << endl;
            }
        }
    }
}

void Library::updateBook() {
    // Declare variables to store book information
    string bookId, title, author, publisher;

    cout << "-------------------------------------------------" << endl;
    cout << "                    UPDATE BOOK                  " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the book ID to update
    cout << "Enter Book ID to update: ";
    cin.ignore();
    getline(cin, bookId);

    // Find the book with the given ID using a traditional for loop
    vector<Book>::iterator bookToUpdate = books.end(); // Initialize with the end iterator
    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        if (it->bookId == bookId) {
            // If the book with the given ID is found, assign the iterator to bookToUpdate
            bookToUpdate = it;
            break;
        }
    }

    // Check if the book with the given ID is found
    if (bookToUpdate != books.end()) {
        // If the book with the given ID is found, ask the user to enter the new details
        // Ask the user to enter the new title of the book
        cout << "Enter New Title: ";
        getline(cin, title);

        // Ask the user to enter the new author of the book
        cout << "Enter New Author: ";
        getline(cin, author);

        // Ask the user to enter the new publisher of the book
        cout << "Enter New Publisher: ";
        getline(cin, publisher);

        // Update the book's details with the new information
        bookToUpdate->title = title;
        bookToUpdate->author = author;
        bookToUpdate->publisher = publisher;

        // Notify the user that the book has been successfully updated
        cout << "-------------------------------------------------" << endl;
        cout << "Book updated successfully." << endl;
    } else {
        // If the book with the given ID is not found, inform the user
        cout << "-------------------------------------------------" << endl;
        cout << "Book with the specified ID not found." << endl;
    }
}

void Library::deleteBook() {
    // Declare a variable to store the book ID to delete
    string bookId;

    cout << "-------------------------------------------------" << endl;
    cout << "                    DELETE BOOK                  " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter Book ID to delete: ";
    cin >> bookId;

    // Find the book with the given ID using a traditional for loop
    vector<Book>::iterator bookToDelete = books.end(); // Initialize with the end iterator
    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        if (it->bookId == bookId) {
            // If the book with the given ID is found, assign the iterator to bookToDelete
            bookToDelete = it;
            break;
        }
    }

    // Check if the book with the given ID is found
    if (bookToDelete != books.end()) {
        // If the book with the given ID is found, erase it from the vector
        books.erase(bookToDelete);

        // Notify the user that the book has been successfully deleted
        cout << "-------------------------------------------------" << endl;
        cout << "Book deleted successfully." << endl;
    } else {
        // If the book with the given ID is not found, inform the user
        cout << "-------------------------------------------------" << endl;
        cout << "Book with the specified ID not found." << endl;
    }
}


void Library::displayAllBooks() {

    cout << "-------------------------------------------------" << endl;
    cout << "                  DISPLAY ALL BOOKS              " << endl;
    cout << "-------------------------------------------------" << endl;
    // Check if the vector of books is empty
    if (books.empty()) {
        // If there are no books in the library, inform the user
        cout << "-------------------------------------------------" << endl;
        cout << "No books found in the library." << endl;
    } else {
        // Ask the user whether they want to display only available books or show all books
        cout << "-------------------------------------------------" << endl;
        cout << "Do you want to display all available books or show all books? (Enter 'A' for available books, 'S' for all books): ";
        char choice;
        cin >> choice;

        // Convert the choice to uppercase for case-insensitive comparison
        choice = toupper(choice);

        if (choice == 'A') {
            // Display available books only
            cout << "Available Books:" << endl;
            bool foundAvailableBook = false;
            for (const auto& book : books) {
                if (book.available) {
                    cout << "-------------------------------------------------" << endl;
                    cout << "Book ID: " << book.bookId << endl; // Display the book's ID
                    cout << "Title: " << book.title << endl;   // Display the book's title
                    cout << "Author: " << book.author << endl; // Display the book's author
                    cout << "Publisher: " << book.publisher << endl; // Display the book's publisher
                    cout << "Availability: " << "Available" << endl; // Display the book's availability
                    foundAvailableBook = true;
                }
            }

            if (!foundAvailableBook) {
                cout << "-------------------------------------------------" << endl;
                cout << "No available books found." << endl;
            }
        } else {
            // Display all books with pagination (e.g., 10 books per page)
            const int booksPerPage = 10;
            int totalPages = (books.size() + booksPerPage - 1) / booksPerPage; // Calculate total pages required

            int currentPage = 1;
            while (true) {
                cout << "Page " << currentPage << "/" << totalPages << ":" << endl;
                int startIndex = (currentPage - 1) * booksPerPage;
                int endIndex = min(startIndex + booksPerPage, static_cast<int>(books.size()));

                for (int i = startIndex; i < endIndex; ++i) {
                    cout << "-------------------------------------------------" << endl;
                    cout << "Book ID: " << books[i].bookId << endl; // Display the book's ID
                    cout << "Title: " << books[i].title << endl;   // Display the book's title
                    cout << "Author: " << books[i].author << endl; // Display the book's author
                    cout << "Publisher: " << books[i].publisher << endl; // Display the book's publisher
                    cout << "Availability: " << (books[i].available ? "Available" : "Not Available") << endl; // Display the book's availability
                }

                cout << "-------------------------------------------------" << endl; // Separate the books from the message below

                // Ask if the user wants to see the next page
                if (currentPage < totalPages) {
                    cout << "-------------------------------------------------" << endl;
                    cout << "Do you want to see the next page? (Y/N): ";
                    cin >> choice;

                    if (choice != 'Y' && choice != 'y') {
                        break; // Exit the pagination loop if the user doesn't want to see the next page
                    }
                } else {
                    // End of the catalog
                    cout << "-------------------------------------------------" << endl;
                    cout << "End of library catalog." << endl;
                    break;
                }

                currentPage++;
            }
        }
    }
}
void Library::addPatron() {
    // Declare variables to store patron information
    string patronId, name, contact;
    cout << "-------------------------------------------------" << endl;
    cout << "                    ADD PATRON                   " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the patron ID
    cout << "Enter Patron ID: ";
    cin >> patronId;

    for (size_t i = 0; i < patrons.size(); ++i) {
        const Patron& patron = patrons[i];
        // Compare the entered patron ID with each existing patron's ID in the 'patrons' vector
        if (patron.patronId == patronId) {
            // If a patron with the same ID is found, inform the user and return from the function
            cout << "-------------------------------------------------" << endl;
            cout << "A patron with this ID already exists." << endl;
            return;
        }
    }

    // If the patron ID is unique, proceed to ask for the patron's name and contact details

    // Ask the user to enter the patron's name
    cout << "Enter Name: ";
    cin.ignore(); // Clear any leftover newline character from the previous input
    getline(cin, name); // Read the entire line of input, including spaces, into the 'name' variable

    // Ask the user to enter the patron's contact details
    cout << "Enter Contact Details: ";
    getline(cin, contact); // Read the entire line of input, including spaces, into the 'contact' variable

    // Check if the user provided non-empty name and contact information
    if (name.empty() || contact.empty()) {
        cout << "Name and contact details must not be empty. Patron not added." << endl;
        return;
    }

    // Create a new Patron object with the provided information and add it to the 'patrons' vector
    patrons.emplace_back(patronId, name, contact);

    // Notify the user that the patron has been successfully added
    cout << "-------------------------------------------------" << endl;
    cout << "Patron added successfully." << endl;
}

void Library::searchPatron() {
    // Declare a variable to store the search term (patron ID or name)
    string searchTerm;
    cout << "-------------------------------------------------" << endl;
    cout << "                    ADD PATRON                   " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter Patron ID or Name to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    // Check if the user provided a non-empty search term
    if (searchTerm.empty()) {
        cout << "-------------------------------------------------" << endl;
        cout << "Search term must not be empty. Please try again." << endl;
        return;
    }

    // Create a vector to store search results (matched patrons)
    vector<Patron> searchResults;

// Search for the patron by ID or name using a traditional for loop
    for (size_t i = 0; i < patrons.size(); ++i) {
        const Patron& patron = patrons[i];
        // Check if the patron's ID or name matches the entered search term
        if (patron.patronId == searchTerm || patron.name == searchTerm) {
            // If the patron is found, add it to the searchResults vector
            searchResults.push_back(patron);
        }
    }

    // Check if any patrons were found based on the search results
    if (searchResults.empty()) {
        // If no patrons were found, inform the user
        cout << "-------------------------------------------------" << endl;
        cout << "Patron not found." << endl;
    } else {
        // If patrons were found, display the search results
        cout << "-------------------------------------------------" << endl;
        cout << "Search Results:" << endl;
        for (const auto& patron : searchResults) {
            // Display the details of each matched patron
            cout << "Patron ID: " << patron.patronId << endl; // Display the patron's ID
            cout << "Name: " << patron.name << endl; // Display the patron's name
            cout << "Contact Details: " << patron.contact << endl; // Display the patron's contact details
            cout << "-------------------------------------------------" << endl; // Separate each patron's details with a line
        }
    }
}

void Library::updatePatron() {
    // Declare variables to store patron information
    string patronId, name, contact;
    cout << "-------------------------------------------------" << endl;
    cout << "                   UPDATE PATRON                 " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the patron ID to update
    cout << "Enter Patron ID to update: ";
    cin >> patronId;

    // Check if the entered patron ID is not empty
    if (patronId.empty()) {
        cout << "-------------------------------------------------" << endl;
        cout << "Patron ID must not be empty. Patron not updated." << endl;
        return;
    }

    // Create a flag to keep track if the patron with the given ID is found
    bool patronFound = false;

    // Search for the patron by ID and update their details using a for loop
    for (size_t i = 0; i < patrons.size(); ++i) {
        Patron& patron = patrons[i];
        // Check if the patron's ID matches the entered patronId
        if (patron.patronId == patronId) {

            // Ask the user to enter the new name of the patron
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, name);

            // Check if the entered name is not empty
            if (name.empty()) {
                cout << "-------------------------------------------------" << endl;
                cout << "Name must not be empty. Patron not updated." << endl;
                return;
            }

            // Ask the user to enter the new contact details of the patron
            cout << "Enter New Contact Details: ";
            getline(cin, contact);

            // Check if the entered contact details are not empty
            if (contact.empty()) {
                cout << "-------------------------------------------------" << endl;
                cout << "Contact details must not be empty. Patron not updated." << endl;
                return;
            }

            // Update the patron's details with the new information
            patron.name = name;
            patron.contact = contact;

            // Notify the user that the patron has been successfully updated
            cout << "-------------------------------------------------" << endl;
            cout << "Patron updated successfully." << endl;

            // Set the flag to true, indicating that the patron has been found and updated
            patronFound = true;

            // Exit the loop since we have already found and updated the patron
            break;
        }
    }
    // If the patron with the given ID is not found, inform the user
    if (!patronFound) {
        cout << "-------------------------------------------------" << endl;
        cout << "Patron not found." << endl;
    }
}

void Library::deletePatron() {
    // Declare a variable to store the patron ID to be deleted
    string patronId;
    cout << "-------------------------------------------------" << endl;
    cout << "                   DELETE PATRON                 " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter Patron ID to delete: ";
    cin >> patronId;

    // Check if the entered patron ID is not empty
    if (patronId.empty()) {
        cout << "-------------------------------------------------" << endl;
        cout << "Patron ID must not be empty. Patron not deleted." << endl;
        return;
    }

    // Create a boolean flag to keep track if the patron with the given ID is found
    bool patronFound = false;

    // Search for the patron by ID and delete them
    for (std::vector<Patron>::iterator it = patrons.begin(); it != patrons.end(); ++it) {
        // Check if the patron's ID matches the entered patronId
        if (it->patronId == patronId) {
            // If the patron with the given ID is found, remove them from the 'patrons' vector
            patrons.erase(it);
            // Notify the user that the patron has been successfully deleted
            cout << "-------------------------------------------------" << endl;
            cout << "Patron deleted successfully." << endl;
            // Set the flag to true, indicating that the patron has been found and deleted
            patronFound = true;
            // Exit the loop since we have already found and deleted the patron
            break;
        }
    }

    // If the patron with the given ID is not found, inform the user
    if (!patronFound) {
        cout << "-------------------------------------------------" << endl;
        cout << "Patron not found." << endl;
    }
}


void Library::displayAllPatrons() {
    cout << "-------------------------------------------------" << endl;
    cout << "                DISPLAY ALL PATRON               " << endl;
    cout << "-------------------------------------------------" << endl;
    // Check if the 'patrons' vector is empty
    if (patrons.empty()) {
        // If there are no patrons in the library, inform the user
        cout << "No patrons found." << endl;
        cout << "-------------------------------------------------" << endl;
    } else {
        // If there are patrons in the library, display their details

        // Print a heading to indicate that we are displaying all patrons
        cout << "All Patrons:" << endl;
        cout << "-------------------------------------------------" << endl;

        for (size_t i = 0; i < patrons.size(); ++i) {
            const Patron& patron = patrons[i];
            // Display the details of each patron

            // Print the patron's ID using 'patron.patronId'
            cout << "Patron ID: " << patron.patronId << endl;

            // Print the patron's name using 'patron.name'
            cout << "Name: " << patron.name << endl;

            // Print the patron's contact details using 'patron.contact'
            cout << "Contact Details: " << patron.contact << endl;

            // Separate each patron's details with a line of dashes for better readability
            cout << "-------------------------------------------------" << endl;
        }
    }
}

void Library::checkOutBook() {
    // Declare variables to store patron and book IDs
    string patronId, bookId;
    cout << "-------------------------------------------------" << endl;
    cout << "                  CHECKOUT BOOK                  " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the patron ID
    cout << "Enter Patron ID: ";
    cin >> patronId;

    // Ask the user to enter the book ID
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "-------------------------------------------------" << endl;

    // Create boolean flags to keep track if the patron and book with the given IDs are found
    bool patronFound = false;
    bool bookFound = false;

    // Search for the patron by their ID
    for (size_t i = 0; i < patrons.size(); ++i) {
        Patron& patron = patrons[i];
        // Check if the patron's ID matches the entered patronId
        if (patron.patronId == patronId) {
            // If the patron with the given ID is found, set the patronFound flag to true
            patronFound = true;
            // Exit the loop since we have already found the patron
            break;
        }
    }

    // If the patron with the given ID is not found, inform the user and return from the function
    if (!patronFound) {
        cout << "Invalid patron ID." << endl;
        return;
    }

    // Search for the book by its ID
    for (auto& book : books) {
        // Check if the book's ID matches the entered bookId
        if (book.bookId == bookId) {
            // If the book with the given ID is found, set the bookFound flag to true
            bookFound = true;
            // Check if the book is currently not available for checkout (i.e., book.available is false)
            if (!book.available) {
                // If the book is not available, notify the user and return from the function
                cout << "The book is currently not available." << endl;
                return;
            }
            // Set the book's availability status to false, indicating it has been checked out
            book.available = false;
            // Notify the user that the book has been successfully checked out
            cout << "Book checked out successfully." << endl;
            // Set the bookFound flag to true since we found and updated the book
            bookFound = true;
            // Exit the loop since we have already found and updated the book
            break;
        }
    }
    // If the book with the given ID is not found, inform the user
    if (!bookFound) {
        cout << "Invalid book ID." << endl;
    }
}

void Library::returnBook() {
    // Declare variables to store patron and book IDs
    string patronId, bookId;
    cout << "-------------------------------------------------" << endl;
    cout << "                   RETURN BOOK                   " << endl;
    cout << "-------------------------------------------------" << endl;
    // Ask the user to enter the patron ID
    cout << "Enter Patron ID: ";
    cin >> patronId;

    // Ask the user to enter the book ID
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "-------------------------------------------------" << endl;

    // Create boolean flags to keep track if the patron and book with the given IDs are found
    bool patronFound = false;
    bool bookFound = false;

    // Search for the patron and book by their IDs
    for (size_t i = 0; i < patrons.size(); ++i) {
        Patron& patron = patrons[i];
        // Check if the patron's ID matches the entered patronId
        if (patron.patronId == patronId) {
            // If the patron with the given ID is found, set the patronFound flag to true
            patronFound = true;
            // Exit the loop since we have already found the patron
            break;
        }
    }

    for (size_t i = 0; i < books.size(); ++i) {
        Book& book = books[i];
        // Check if the book's ID matches the entered bookId
        if (book.bookId == bookId) {
            // If the book with the given ID is found, set the bookFound flag to true
            bookFound = true;
            // Check if the book is already returned (i.e., book.available is true)
            if (book.available) {
                // If the book is already returned, notify the user and return from the function
                cout << "The book is already returned." << endl;
                return;
            }

            // Set the book's availability status to true, indicating it has been returned
            book.available = true;
            cout << "Book returned successfully." << endl;

            // Calculate and display fine for late return (assuming a fixed fine amount)
            // You can modify this logic according to your requirements
            // For simplicity, let's assume the due date is 7 days from the checkout date
            // and the fine amount is $1 per day
            // You may need to include date/time handling libraries to implement this accurately
            const int finePerDay = 1;
            const int daysDue = 7;
            int fine = 0; // Calculate the fine based on actual due date and return date

            // Display the fine amount if it's greater than zero
            if (fine > 0) {
                cout << "Fine for late return: $" << fine << endl;
            }

            // Exit the loop since we have already found and updated the book
            break;
        }
    }

    // If the patron with the given ID is not found, inform the user
    if (!patronFound) {
        cout << "Invalid patron ID." << endl;
    }

    // If the book with the given ID is not found, inform the user
    if (!bookFound) {
        cout << "Invalid book ID." << endl;
    }
}

void Library::displayAllCheckouts() {

    cout << "-------------------------------------------------" << endl;
    cout << "              DISPLAY ALL CHECKOUTS             " << endl;
    cout << "-------------------------------------------------" << endl;
    // Create a vector to store checked-out books
    vector<Book> checkedOutBooks;

    for (size_t i = 0; i < books.size(); ++i) {
        const Book& book = books[i];
        // Check if the book is not available (i.e., checked out)
        if (!book.available) {
            // If the book is checked out, add it to the 'checkedOutBooks' vector
            checkedOutBooks.push_back(book);
        }
    }

    // Check if there are no checked-out books
    if (checkedOutBooks.empty()) {
        // If there are no checked-out books, inform the user
        cout << "No books are currently checked out." << endl;
    } else {
        // If there are checked-out books, display them
        cout << "Checked-out Books:" << endl;
        for (size_t i = 0; i < checkedOutBooks.size(); ++i) {
            const Book& book = checkedOutBooks[i];
            // Display information for each checked-out book
            cout << "Book ID: " << book.bookId << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Publisher: " << book.publisher << endl;
            cout << "-------------------------------------------------" << endl;
        }
    }
}

void Library::saveDataToFile() {
    cout << "-------------------------------------------------" << endl;
    cout << "                 SAVE DATA TO FILE               " << endl;
    cout << "-------------------------------------------------" << endl;
    // Create an output file stream and open the file "library_data.txt" for writing
    ofstream file("library_data.txt");

    // Check if the file is successfully opened
    if (file.is_open()) {
        // Save books data to the file
        for (const auto& book : books) {
            // Write each book's data in a comma-separated format to the file
            // The format is: "Book,bookId,title,author,publisher,available"
            // Each piece of data is separated by a comma, and a new line is added after each book's data
            file << "Book," << book.bookId << "," << book.title << "," << book.author
                 << "," << book.publisher << "," << book.available << endl;
        }

        // Save patrons data to the file
        for (size_t i = 0; i < patrons.size(); ++i) {
            const Patron& patron = patrons[i];
            // Write each patron's data in a comma-separated format to the file
            // The format is: "Patron,patronId,name,contact"
            // Each piece of data is separated by a comma, and a new line is added after each patron's data
            file << "Patron," << patron.patronId << "," << patron.name << ","
                 << patron.contact << endl;
        }

        // Notify the user that the data has been successfully saved to the file
        cout << "Data saved successfully." << endl;

        // Close the file after writing
        file.close();
    }
}

void Library::loadDataFromFile() {
    // Create an input file stream and open the file "library_data.txt" for reading
    ifstream file("library_data.txt");

    // Check if the file is successfully opened
    if (file.is_open()) {
        // Clear the existing data in 'books' and 'patrons' vectors to avoid duplication
        books.clear();
        patrons.clear();

        // Declare a string variable 'line' to read each line from the file
        string line;

        // Read data line by line from the file until the end of file (EOF) is reached
        while (getline(file, line)) {
            // Extract the first part of the line until the first comma to determine the data type (Book or Patron)
            string type = line.substr(0, line.find(','));
            line = line.substr(line.find(',') + 1);

            if (type == "Book") {
                // If the data type is "Book", extract book information from the line

                // Extract each piece of book data (bookId, title, author, publisher, available)
                string bookId = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string title = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string author = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string publisher = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                bool available = (line == "1\n"); // Convert the string representation of 'available' to a boolean value

                // Create a new book object with the extracted data and add it to the 'books' vector
                books.emplace_back(bookId, title, author, publisher, available);
            } else if (type == "Patron") {
                // If the data type is "Patron", extract patron information from the line

                // Extract each piece of patron data (patronId, name, contact)
                string patronId = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string name = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string contact = line;

                // Create a new patron object with the extracted data and add it to the 'patrons' vector
                patrons.emplace_back(patronId, name, contact);
            }
        }

        // Notify the user that the data has been successfully loaded from the file
        cout << "Data loaded successfully." << endl;

        // Close the file after reading
        file.close();
    }
}

int main() {

    string username, password;
    cout << " -------------------------------------------------" << endl;
    cout << "|          Library Management System Login       |"<< endl;
    cout << " -------------------------------------------------" << endl;
   do { // Ask for the username and password
       cout << "                  Username: ";
       cin >> username;
       cout << "                  Password: ";
       cin >> password;
       if (!isValidLogin(username, password)) {
           cout << "Invalid login credentials." << endl;
       }
   }while(username != "admin" && password!="admin");

//    if (!isValidLogin(username, password)) {
//        cout << "Invalid login credentials. Exiting Library Management System." << endl;
//        return 0;
//    }

    Library library;
    library.loadDataFromFile();
    int choice;
    cout << "          __...--~~~~~-._   _.-~~~~~--...__           "<< endl;
    cout << "        //               `V'               \\\\       "<< endl;
    cout << "       //      JAWO       |      NATH       \\\\      "<< endl;
    cout << "      //__...--~~~~~~-._  |  _.-~~~~~~--...__\\\\     "<< endl;
    cout << "     //__.....----~~~~._\\ | /_.~~~~----.....__\\\\   "<< endl;
    cout << "    ====================\\\\|//====================   "<< endl;
    cout << "                        `---`                         " << endl;

    do {


        cout << " -------------------------------------------------" << endl;
        cout << "|           Library Management System             |"<< endl;
        cout << " -------------------------------------------------" << endl;

        cout << "  [1]. Add Book         " << "       [9].  Delete Patron" << endl;
        cout << "  [2]. Search Book      " << "       [10]. Display All Patrons" << endl;
        cout << "  [3]. Update Book      " << "       [11]. Check-out Book" << endl;
        cout << "  [4]. Delete Book      " << "       [12]. Return Book" << endl;
        cout << "  [5]. Display All Books" << "       [13]. Display All Check-outs" << endl;
        cout << "  [6]. Add Patron       " << "       [14]. Save Data to File" << endl;
        cout << "  [7]. Search Patron    " << "       [0].  Exit" << endl;
        cout << "  [8]. Update Patron    " << endl;


        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        // Use a switch statement to handle the user's choice and call the corresponding Library functions
        switch (choice) {
            case 1:
                // If the user chooses option 1, call the addBook() function from the Library class
                library.addBook();
                break;
            case 2:
                // If the user chooses option 2, call the searchBook() function from the Library class
                library.searchBook();
                break;
            case 3:
                // If the user chooses option 3, call the updateBook() function from the Library class
                library.updateBook();
                break;
            case 4:
                // If the user chooses option 4, call the deleteBook() function from the Library class
                library.deleteBook();
                break;
            case 5:
                // If the user chooses option 5, call the displayAllBooks() function from the Library class
                library.displayAllBooks();
                break;
            case 6:
                // If the user chooses option 6, call the addPatron() function from the Library class
                library.addPatron();
                break;
            case 7:
                // If the user chooses option 7, call the searchPatron() function from the Library class
                library.searchPatron();
                break;
            case 8:
                // If the user chooses option 8, call the updatePatron() function from the Library class
                library.updatePatron();
                break;
            case 9:
                // If the user chooses option 9, call the deletePatron() function from the Library class
                library.deletePatron();
                break;
            case 10:
                // If the user chooses option 10, call the displayAllPatrons() function from the Library class
                library.displayAllPatrons();
                break;
            case 11:
                // If the user chooses option 11, call the checkOutBook() function from the Library class
                library.checkOutBook();
                break;
            case 12:
                // If the user chooses option 12, call the returnBook() function from the Library class
                library.returnBook();
                break;
            case 13:
                // If the user chooses option 13, call the displayAllCheckouts() function from the Library class
                library.displayAllCheckouts();
                break;
            case 14:
                // If the user chooses option 14, call the saveDataToFile() function from the Library class
                library.saveDataToFile();
                break;
            case 0:
                // If the user chooses option 0, print a goodbye message and exit the loop
                cout << "Exiting Library Management System. Goodbye!" << endl;
                break;
            default:
                // If the user enters an invalid choice, display an error message and continue to the next iteration of the loop
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        // Continue the loop until the user enters 0 (Exit)
    } while (choice != 0);

    return 0;
}
