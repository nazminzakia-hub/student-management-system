
#include <iostream>
#include <list>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

// Book Structure
struct Book {
    int id;
    string name;
    string author;
};

// Linked List for storing books
list<Book> bookList;

// Hash Table for fast search
unordered_map<int, Book> bookMap;

// Stack for undo
stack<pair<string, Book>> undoStack;

// Queue for borrow requests
queue<int> borrowQueue;

// Add Book
void addBook() {
    Book b;
    cout << "Enter ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, b.name);
    cout << "Enter Author: ";
    getline(cin, b.author);

    bookList.push_back(b);
    bookMap[b.id] = b;

    undoStack.push({"add", b});

    cout << "Book Added!\n";
}

// Remove Book
void removeBook() {
    int id;
    cout << "Enter ID to remove: ";
    cin >> id;

    for (auto it = bookList.begin(); it != bookList.end(); it++) {
        if (it->id == id) {
            undoStack.push({"remove", *it});
            bookMap.erase(id);
            bookList.erase(it);
            cout << "Book Removed!\n";
            return;
        }
    }
    cout << "Book Not Found!\n";
}

// Search Book
void searchBook() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    if (bookMap.find(id) != bookMap.end()) {
        Book b = bookMap[id];
        cout << "Found: " << b.name << " by " << b.author << endl;
    } else {
        cout << "Not Found!\n";
    }
}

// Display Books
void displayBooks() {
    for (auto b : bookList) {
        cout << b.id << " | " << b.name << " | " << b.author << endl;
    }
}

// Borrow Book
void borrowBook() {
    int id;
    cout << "Enter Book ID to borrow: ";
    cin >> id;

    borrowQueue.push(id);
    cout << "Added to borrow queue!\n";
}

// Process Borrow
void processBorrow() {
    if (borrowQueue.empty()) {
        cout << "No requests!\n";
        return;
    }

    int id = borrowQueue.front();
    borrowQueue.pop();

    cout << "Processing borrow for Book ID: " << id << endl;
}

// Undo
void undo() {
    if (undoStack.empty()) {
        cout << "Nothing to undo!\n";
        return;
    }

    auto action = undoStack.top();
    undoStack.pop();

    if (action.first == "add") {
        bookList.remove_if([&](Book b) { return b.id == action.second.id; });
        bookMap.erase(action.second.id);
        cout << "Undo Add!\n";
    } else if (action.first == "remove") {
        bookList.push_back(action.second);
        bookMap[action.second.id] = action.second;
        cout << "Undo Remove!\n";
    }
}

// Menu
int main() {
    int choice;

    do {
        cout << "\n===== Library System =====\n";
        cout << "1. Add Book\n2. Remove Book\n3. Search Book\n4. Display Books\n";
        cout << "5. Borrow Book\n6. Process Borrow\n7. Undo\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: removeBook(); break;
            case 3: searchBook(); break;
            case 4: displayBooks(); break;
            case 5: borrowBook(); break;
            case 6: processBorrow(); break;
            case 7: undo(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
