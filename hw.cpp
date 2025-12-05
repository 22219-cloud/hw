#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* ============================
AUTHOR
============================ */
class Author {
private:
    string name;
    int birthYear;

public:
    Author(string n = "Unknown", int y = 1900)
        : name(n), birthYear(y) {}

    string getName() const { return name; }

    string toString() const {
        return name + " (" + std::to_string(birthYear) + ")";
    }
};


/* ============================
BOOK
============================ */
class Book {
private:
    string title;
    Author author;
    string isbn;
    int year;
    double price;

public:
    Book(string t = "Untitled",
         Author a = Author(),
         int y = 1900,
         double p = 0.0,
         string isbn = "NONE")
        : title(t), author(a), isbn(isbn), year(y), price(p) {}

    string getISBN() const { return isbn; }
    Author getAuthor() const { return author; }

    string toString() const {
        return title + " | " + author.toString() +
               " | year: " + to_string(year) +
               " | price: " + to_string(price) +
               " | ISBN: " + isbn;
    }
};


/* ============================
MEMBER
============================ */
class Member {
private:
    string name;
    string memberId;

public:
    Member(string n = "Unknown", string id = "NONE")
        : name(n), memberId(id) {}

    string getId() const { return memberId; }

    string toString() const {
        return name + " (" + memberId + ")";
    }
};


/* ============================
LOAN
============================ */
class Loan {
private:
    string isbn;
    string memberId;
    bool returned;

public:
    Loan(string i, string m)
        : isbn(i), memberId(m), returned(false) {}

    string getISBN() const { return isbn; }
    string getMemberId() const { return memberId; }
    bool isReturned() const { return returned; }

    void markReturned() { returned = true; }
};


/* ============================
LIBRARY
============================ */
class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;

public:
    void addBook(const Book& b) { books.push_back(b); }
    void addMember(const Member& m) { members.push_back(m); }

    bool hasBook(const string& isbn) const {
        for (auto& b : books)
            if (b.getISBN() == isbn) return true;
        return false;
    }

    bool isBookAvailable(const string& isbn) const {
        for (auto& l : loans)
            if (l.getISBN() == isbn && !l.isReturned())
                return false;
        return true;
    }

    bool loanBook(const string& isbn, const string& memberId) {
        if (!hasBook(isbn)) return false;
        if (!isBookAvailable(isbn)) return false;

        loans.emplace_back(isbn, memberId);
        return true;
    }

    bool returnBook(const string& isbn, const string& memberId) {
        for (auto& l : loans) {
            if (l.getISBN() == isbn &&
                l.getMemberId() == memberId &&
                !l.isReturned()) {
                l.markReturned();
                return true;
            }
        }
        return false;
    }

    vector<Book> findByAuthor(const string& name) const {
        vector<Book> result;
        for (auto& b : books)
            if (b.getAuthor().getName().find(name) != string::npos)
                result.push_back(b);
        return result;
    }

    string toString() const {
        int active = 0;
        for (auto& l : loans)
            if (!l.isReturned()) active++;

        return "Library: " + to_string(books.size()) +
               " books, " + to_string(members.size()) +
               " members, " + to_string(active) + " active loans.";
    }
};


/* ============================
MAIN
============================ */
int main() {
    Library lib;

    Author a("Ivan Vazov", 1850);
    Book b1("Pod Igoto", a, 1894, 25.50, "ISBN-001");
    Book b2("Nema Zemya", a, 1900, 18.90, "ISBN-002");

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addMember(Member("Petar Petrov", "M001"));

    cout << lib.toString() << "\n";

    if (lib.loanBook("ISBN-001", "M001"))
        cout << "Loan created.\n";

    cout << "Available ISBN-001? "
         << boolalpha << lib.isBookAvailable("ISBN-001") << "\n";

    lib.returnBook("ISBN-001", "M001");

    cout << "Available ISBN-001? "
         << boolalpha << lib.isBookAvailable("ISBN-001") << "\n";

    for (auto& bk : lib.findByAuthor("Vazov"))
        cout << bk.toString() << "\n";
}
