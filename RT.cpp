#include <iostream>
#include <vector>
#include <set>
#include <ctime>

#define vs vector<string>
#define pb push_back
using namespace std;

class LibraryBook{
    
public:
    
    LibraryBook(string title, string Author, int PubYear, int TotalCopies){
        this->title = title;
        this->Author = Author;
        this->PubYear = PubYear;
        this->TotalCopies = TotalCopies;
    }
    int AvailableCopies = TotalCopies;
    int reserved = 0;
    bool check_out()
    {
        if(AvailableCopies){
            AvailableCopies--;
            return true;
        }
        else{
            return false;
        }
    }
    bool check_in(){
        if(AvailableCopies < TotalCopies){
            AvailableCopies++;
            return true;
        }
        else{
            return false;
        }
    }
    void reserve(){
        reserved++;
    }
    void remove_reserve(){
        reserved--;
    }

private:
    string title;
    string Author;
    int PubYear;
    int TotalCopies;
    
};

class LibraryPatron{
public:
    LibraryPatron(int id, string name){
        id = id;
        name = name;
        
    }
    
    bool checkout(LibraryBook& book){
        if(book.check_out()){
            checkedbooks.pb(&book);
            return true;
        }
        else{
            return false;
        }
    }
    bool returnbook(LibraryBook& book){
        auto it = checkedbooks.begin();
        while(it != checkedbooks.end()){
            if(*it == &book){
                break;
            }
            it++;
        }
        if(it == checkedbooks.end()){
            return false;
        }
        else{
            checkedbooks.erase(it);
            book.check_in();
            return true;
        }
    }
    bool reserve_book(LibraryBook& book){
        book.reserve();
        reservedbooks.pb(&book);
        return true;
    }
    bool remove_reservation(LibraryBook& book){
        book.remove_reserve();
        auto it = reservedbooks.begin();
        while (it != reservedbooks.end())
        {
            if (*it == &book)
            {
                break;
            }
            it++;
        } 
        if(it!=reservedbooks.end()){
            reservedbooks.erase(it);
            return true;
        }
        else{
            return false;
        }
    }

private:
    int id;
    string name;
    vector<LibraryBook*> checkedbooks;
    vector<LibraryBook*> reservedbooks;
};

class LibraryTransaction{
public:
    LibraryTransaction(LibraryPatron &patron, LibraryBook &book)
        : Patron(patron), book(book), Ttime(std::time(0)) {}

private:
    LibraryBook& book;
    LibraryPatron& Patron;
    time_t Ttime;
};

class LibraryBranch{

public:
    LibraryBranch(string foo)
    {
        branchname = foo;
    }
    
    void add_book(LibraryBook& book){
        books.pb(&book);
    }
    
    void add_patron(LibraryPatron& patron){
        patrons.pb(&patron);
    }

private:
    string branchname;
    vector<LibraryBook *> books;
    vector<LibraryPatron *> patrons;
};

int main(){
    LibraryBook b1 = LibraryBook("book1", "Author1", 2004, 10);
    LibraryBook b2 = LibraryBook("book2", "Author2", 2004, 10);
    LibraryBook b3 = LibraryBook("book3", "Author3", 2004, 10);

    LibraryPatron p1 = LibraryPatron(343, "Jay");
    LibraryPatron p2 = LibraryPatron(344, "ant");
    LibraryPatron p3 = LibraryPatron(345, "Jha");

    LibraryBranch B1 = LibraryBranch("Kanpur");

    B1.add_book(b1);
    B1.add_patron(p1);

    p1.checkout(b1);
    p1.checkout(b2);
    p1.returnbook(b1);
    LibraryTransaction T1 = LibraryTransaction(p1, b1);

    p1.reserve_book(b3);
    p1.remove_reservation(b3);
    p1.checkout(b3);
    p1.returnbook(b3);
    LibraryTransaction T2 = LibraryTransaction(p1, b3);
    
    
    
    return 0;
}
