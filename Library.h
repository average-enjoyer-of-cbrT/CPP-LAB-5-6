#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <cstring>

const int MAX_BOOKS = 100;
const int MAX_USERS = 50;

class Book 
{
private:
    char title[50];
    char author[50];
    char isbn[13];
    bool available;

public:
    Book(const char* title = "", const char* author = "", const char* isbn = "") 
    {
        strncpy(this->title, title, 50);
        strncpy(this->author, author, 50);
        strncpy(this->isbn, isbn, 13);
        this->available = true;
    }

    const char* getTitle() const { return title; }
    const char* getAuthor() const { return author; }
    const char* getISBN() const { return isbn; }
    bool isAvailable() const { return available; }

    void borrow() { available = false; }
    void returnBack() { available = true; }
};

class User 
{
protected:
    char name[50];
    int userID;

public:
    User(const char* name, int userID) 
    {
        strncpy(this->name, name, 50);
        this->userID = userID;
    }

    const char* getName() const { return name; }
    int getUserID() const { return userID; }

    virtual void borrowBook(Book& book) = 0;
    virtual void returnBook(Book& book) = 0;
    virtual ~User() {}
};

class Member : public User 
{
public:
    Member(const char* name, int userID) : User(name, userID) {}

    void borrowBook(Book& book) override;
    void returnBook(Book& book) override;
};

class Librarian : public User 
{
public:
    Librarian(const char* name, int userID) : User(name, userID) {}

    void borrowBook(Book& book) override;
    void returnBook(Book& book) override;

    void addBook(Book* books, int& bookCount, const char* title, const char* author, const char* isbn);
    void addUser(User* users[], int& userCount, User* user);
};

class Library 
{
private:
    Book books[MAX_BOOKS];
    User* users[MAX_USERS];
    int bookCount;
    int userCount;

public:
    Library();
    ~Library();

    void displayBooks() const;
    void addBook(const char* title, const char* author, const char* isbn);
    void addUser(User* user);
    void removeBook(const char* title);
    void updateBook(const char* title, const char* newTitle, const char* newAuthor, const char* newISBN);
    void listUsers() const;
    void removeUser(int userID);


    int getUserCount() const;
    User* getUserByID(int userID) const;
    Book* findBook(const char* title);

    void borrowBook(int userID, const char* title); // Новые методы
    void returnBook(int userID, const char* title);
};

#endif
