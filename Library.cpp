#include "Library.h"
#include <iostream>
#include <cstring>
using namespace std;

Library::Library() : bookCount(0), userCount(0) {}

Library::~Library() 
{
    for (int i = 0; i < userCount; i++) 
    {
        delete users[i];
    }
}

void Library::displayBooks() const 
{
    if (bookCount == 0) 
    {
        cout << "Библиотека пуста.\n";
        return;
    }
    cout << "\nСписок книг:\n";
    for (int i = 0; i < bookCount; i++) 
    {
        cout << i + 1 << ". " << books[i].getTitle() << " - " << books[i].getAuthor()
             << " (ISBN: " << books[i].getISBN() << "). "
             << (books[i].isAvailable() ? "Доступна" : "Выдана") << ".\n";
    }
}

void Library::addBook(const char* title, const char* author, const char* isbn) 
{
    if (bookCount < MAX_BOOKS) 
    {
        books[bookCount++] = Book(title, author, isbn);
        cout << "Книга '" << title << "' добавлена в библиотеку.\n";
    } 
    else 
    {
        cout << "Невозможно добавить больше книг.\n";
    }
}

void Library::addUser(User* user) 
{
    if (userCount < MAX_USERS) 
    {
        users[userCount++] = user;
        cout << "Пользователь " << user->getName() << " добавлен.\n";
    } 
    else 
    {
        cout << "Невозможно добавить больше пользователей.\n";
    }
}

int Library::getUserCount() const 
{
    return userCount;
}

Book* Library::findBook(const char* title) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (strcmp(books[i].getTitle(), title) == 0) 
        {
            return &books[i];
        }
    }
    return nullptr;
}

User* Library::getUserByID(int userID) const 
{
    for (int i = 0; i < userCount; i++) 
    {
        if (users[i]->getUserID() == userID) 
        {
            return users[i];
        }
    }
    return nullptr;
}

void Library::borrowBook(int userID, const char* title) 
{
    for (int i = 0; i < userCount; i++) 
    {
        if (users[i]->getUserID() == userID) 
        {
            for (int j = 0; j < bookCount; j++) 
            {
                if (strcmp(books[j].getTitle(), title) == 0) 
                {
                    if (books[j].isAvailable())
                    {
                        books[j].borrow();
                        users[i]->borrowBook(books[j]);
                        cout << "Книга '" << title << "' успешно выдана пользователю " << users[i]->getName() << ".\n";
                        return;
                    } 
                    else 
                    {
                        cout << "Книга '" << title << "' недоступна.\n";
                        return;
                    }
                }
            }
            cout << "Книга '" << title << "' не найдена.\n";
            return;
        }
    }
    cout << "Пользователь с ID " << userID << " не найден.\n";
}

void Library::returnBook(int userID, const char* title) 
{
    for (int i = 0; i < userCount; i++) 
    {
        if (users[i]->getUserID() == userID) 
        {
            for (int j = 0; j < bookCount; j++) 
            {
                if (strcmp(books[j].getTitle(), title) == 0) 
                {
                    books[j].returnBack();
                    users[i]->returnBook(books[j]);
                    cout << "Книга '" << title << "' успешно возвращена пользователем " << users[i]->getName() << ".\n";
                    return;
                }
            }
            cout << "Книга '" << title << "' не найдена.\n";
            return;
        }
    }
    cout << "Пользователь с ID " << userID << " не найден.\n";
}

void Member::borrowBook(Book& book) 
{
    if (book.isAvailable()) 
    {
        book.borrow();
        cout << "Читатель " << name << " взял книгу \"" << book.getTitle() << "\".\n";
    } 
    else 
    {
        cout << "Книга '" << book.getTitle() << "' недоступна.\n";
    }
}

void Member::returnBook(Book& book) 
{
    book.returnBack();
    cout << "Читатель " << name << " вернул книгу \"" << book.getTitle() << "\".\n";
}

void Librarian::borrowBook(Book& book) 
{
    cout << "Библиотекарь " << name << " не может взять книгу в личное пользование.\n";
}

void Librarian::returnBook(Book& book) 
{
    cout << "Библиотекарь " << name << " не может вернуть книгу.\n";
}

void Librarian::addBook(Book* books, int& bookCount, const char* title, const char* author, const char* isbn) 
{
    if (bookCount < MAX_BOOKS) 
    {
        books[bookCount++] = Book(title, author, isbn);
        cout << "Библиотекарь " << name << " добавил книгу \"" << title << "\".\n";
    } 
    else 
    {
        cout << "Невозможно добавить больше книг.\n";
    }
}

void Library::removeBook(const char* title) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].getTitle(), title) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            cout << "Книга '" << title << "' удалена из библиотеки.\n";
            return;
        }
    }
    cout << "Книга '" << title << "' не найдена.\n";
}

void Library::updateBook(const char* title, const char* newTitle, const char* newAuthor, const char* newISBN) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].getTitle(), title) == 0) {
            books[i] = Book(newTitle, newAuthor, newISBN);
            cout << "Книга '" << title << "' обновлена.\n";
            return;
        }
    }
    cout << "Книга '" << title << "' не найдена.\n";
}

void Library::listUsers() const {
    if (userCount == 0) {
        cout << "В библиотеке нет пользователей.\n";
        return;
    }
    cout << "\nСписок пользователей:\n";
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i]->getName() << " (ID: " << users[i]->getUserID() << ").\n";
    }
}

void Library::removeUser(int userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUserID() == userID) {
            delete users[i];
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            cout << "Пользователь с ID " << userID << " удален.\n";
            return;
        }
    }
    cout << "Пользователь с ID " << userID << " не найден.\n";
}

void Librarian::addUser(User* users[], int& userCount, User* user) 
{
    if (userCount < MAX_USERS) 
    {
        users[userCount++] = user;
        cout << "Библиотекарь " << name << " добавил пользователя " << user->getName() << ".\n";
    } 
    else 
    {
        cout << "Невозможно добавить больше пользователей.\n";
    }
}
