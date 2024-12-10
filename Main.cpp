#include "Library.h"
#include <iostream>
#include <cstring>
using namespace std;

void showMenu(const char* role) 
{
    cout << "\n--- Меню - " << role << " ---\n";
    if (strcmp(role, "Библиотекаря") == 0) 
    {
        cout << "1. Добавить книгу\n";
        cout << "2. Добавить пользователя\n";
        cout << "3. Показать все книги\n";
        cout << "4. Удалить книгу\n";
        cout << "5. Обновить информацию о книге\n";
        cout << "6. Показать всех пользователей\n";
        cout << "7. Удалить пользователя\n";
        cout << "8. Сменить пользователя\n";
        cout << "9. Выход\n";
    } 
    else if (strcmp(role, "читателя библиотеки") == 0) 
    {
        cout << "1. Взять книгу\n";
        cout << "2. Вернуть книгу\n";
        cout << "3. Показать все книги\n";
        cout << "4. Добавить пользователя\n";
        cout << "5. Сменить пользователя\n";
        cout << "6. Выход\n";
    }
    cout << "Выберите действие: ";
}

int main() 
{
    Library library;

    char role[50];
    int currentUserID = -1;

    auto switchUser = [&]() -> bool 
    {
        cout << "\nВведите ID пользователя для смены: ";
        int newUserID;
        cin >> newUserID;
        cin.ignore(); 

        User* user = library.getUserByID(newUserID);
        if (user) 
        {
            currentUserID = newUserID;
            if (dynamic_cast<Member*>(user)) 
            {
                strncpy(role, "читатель библиотеки", sizeof(role) - 1);
            } 
            else if (dynamic_cast<Librarian*>(user)) 
            {
                strncpy(role, "Библиотекарь", sizeof(role) - 1);
            }
            role[sizeof(role) - 1] = '\0';
            cout << "Вы вошли как " << role << " (ID: " << currentUserID << ").\n";
            return true;
        }
        cout << "Пользователь с таким ID не найден.\n";
        return false;
    };

    cout << "Создайте первого пользователя!\n";
    char name[50];
    int userType, userID;
    cout << "Введите имя: ";
    cin.ignore(); 
    cin.getline(name, 50); 
    cout << "Выберите роль (1 - Читатель, 2 - Библиотекарь): ";
    cin >> userType;
    cin.ignore(); 
    cout << "Введите ID: ";
    cin >> userID;
    cin.ignore(); 

    if (userType == 1) 
    {
        library.addUser(new Member(name, userID));
        strncpy(role, "читателя библиотеки", sizeof(role) - 1);
        role[sizeof(role) - 1] = '\0';
    } 
    else if (userType == 2) 
    {
        library.addUser(new Librarian(name, userID));
        strncpy(role, "Библиотекарь", sizeof(role) - 1);
        role[sizeof(role) - 1] = '\0';
    } 
    else 
    {
        cout << "Неверный выбор роли. Завершение программы.\n";
        return 1;
    }
    currentUserID = userID;

    cout << "Пользователь " << name << " (ID: " << userID << ") добавлен как " << role << ".\n";

    while (true) 
    {
        bool switchToMainMenu = false;

        while (!switchToMainMenu) 
        {
            showMenu(role);
            int choice;
            cin >> choice;
            cin.ignore();

            if (strcmp(role, "Библиотекарь") == 0) 
            {
                if (choice == 1) 
                {
                    char title[50], author[50], isbn[13];
                    cout << "Введите название книги: ";
                    cin.getline(title, 50);
                    cout << "Введите автора книги: ";
                    cin.getline(author, 50);
                    cout << "Введите ISBN книги: ";
                    cin.getline(isbn, 13);
                    library.addBook(title, author, isbn);
                } 
                else if (choice == 2) 
                {
                    char userName[50];
                    int userType, userID;
                    cout << "Введите имя пользователя: ";
                    cin.getline(userName, 50);
                    cout << "Выберите роль (1 - Читатель, 2 - Библиотекарь): ";
                    cin >> userType;
                    cin.ignore(); 
                    cout << "Введите ID пользователя: ";
                    cin >> userID;
                    cin.ignore(); 

                    if (userType == 1) 
                    {
                        library.addUser(new Member(userName, userID));
                    } 
                    else if (userType == 2) 
                    {
                        library.addUser(new Librarian(userName, userID));
                    } 
                    else 
                    {
                        cout << "Неверный выбор роли.\n";
                        continue;
                    }

                    cout << "Пользователь " << userName << " (ID: " << userID << ") добавлен.\n";
                } 
                else if (choice == 3) 
                {
                    library.displayBooks();
                } 
                else if (choice == 4) 
                {
                    char title[50];
                    cout << "Введите название книги для удаления: ";
                    cin.getline(title, 50);
                    library.removeBook(title);
                } 
                else if (choice == 5) 
                {
                    char title[50], newTitle[50], newAuthor[50], newISBN[13];
                    cout << "Введите название книги для обновления: ";
                    cin.getline(title, 50);
                    cout << "Введите новое название книги: ";
                    cin.getline(newTitle, 50);
                    cout << "Введите нового автора книги: ";
                    cin.getline(newAuthor, 50);
                    cout << "Введите новый ISBN книги: ";
                    cin.getline(newISBN, 13);
                    library.updateBook(title, newTitle, newAuthor, newISBN);
                } 
                else if (choice == 6) 
                {
                    library.listUsers();
                } 
                else if (choice == 7) 
                {
                    int userID;
                    cout << "Введите ID пользователя для удаления: ";
                    cin >> userID;
                    cin.ignore(); 
                    library.removeUser(userID);
                } 
                else if (choice == 8) 
                {
                    if (switchUser()) 
                    {
                        switchToMainMenu = true;
                    }
                } 
                else if (choice == 9) 
                {
                    cout << "Выход из программы.\n";
                    return 0;
                } 
                else 
                {
                    cout << "Неверный выбор! Попробуйте снова.\n";
                }
            } 
            else if (strcmp(role, "читателя библиотеки") == 0) 
            {
                if (choice == 1) 
                {
                    char title[50];
                    cout << "Введите название книги: ";
                    cin.getline(title, 50);
                    library.borrowBook(currentUserID, title);
                } 
                else if (choice == 2) 
                {
                    char title[50];
                    cout << "Введите название книги: ";
                    cin.getline(title, 50);
                    library.returnBook(currentUserID, title);
                } 
                else if (choice == 3) 
                {
                    library.displayBooks();
                } 
                else if (choice == 4) 
                {
                    char userName[50];
                    int userType, userID;
                    cout << "Введите имя пользователя: ";
                    cin.getline(userName, 50);
                    cout << "Выберите роль (1 - Читатель, 2 - Библиотекарь): ";
                    cin >> userType;
                    cin.ignore(); 
                    cout << "Введите ID пользователя: ";
                    cin >> userID;
                    cin.ignore(); 

                    if (userType == 1) 
                    {
                        library.addUser(new Member(userName, userID));
                    } 
                    else if (userType == 2) 
                    {
                        library.addUser(new Librarian(userName, userID));
                    } 
                    else 
                    {
                        cout << "Неверный выбор роли.\n";
                        continue;
                    }

                    cout << "Пользователь " << userName << " (ID: " << userID << ") добавлен.\n";
                } 
                else if (choice == 5) 
                {
                    if (switchUser()) 
                    {
                        switchToMainMenu = true;
                    }
                } 
                else if (choice == 6) 
                {
                    cout << "Выход из программы.\n";
                    return 0;
                } 
                else 
                {
                    cout << "Неверный выбор! Попробуйте снова.\n";
                }
            }
        }
    }

    return 0;
}
