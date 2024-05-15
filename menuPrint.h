#ifndef MENUPRINT_H_INCLUDED
#define MENUPRINT_H_INCLUDED

using namespace std;
class MenuPrint{

public:

    void printMainMenu(){
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
        cout << "*           Please enter a command:                *" << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 1 ) Multiple Route Generation             *" << " * * * " << endl;
        cout << "*--------------------------------------------------*" << " M * A " << endl;
        cout << "*      ( 2 ) Single Route Generation               *" << "   *   " << endl;
        cout << "*--------------------------------------------------*" << " R * Z " << endl;
        cout << "*      ( 3 ) Print Map                             *" << " * * * " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 9 ) Exit                                  *" << endl;
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
    }
    void printMultipleRouteMenu(){
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
        cout << "*           Please enter a command:                *" << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 1 ) Floyd-Warshall Rotue                  *" << " M   A " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 2 ) Djikstra Route                        *" << "   *   " << endl;
        cout << "*--------------------------------------------------*" << " R   Z " << endl;
        cout << "*      ( 9 ) Return to Main Menu                   *" << " *   * " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
    }
    void printSingleRouteMenu(){
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
        cout << "*           Please enter a command:                *" << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 1 ) A* Route                              *" << " M   A " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 2 ) Basic Route                          *" << " *   * " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 9 ) Return to Main Menu                   *" << " R   Z " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
    }
    bool printReturn() {
        char option;
        cout << "*      ( Y ) Return to Main Menu                   *" << endl;
        cout << "*--------------------------------------------------*" << endl;
        cout << "*      ( N ) Exit                                  *" << endl;
        cin >> option;
        system("cls");
        if (toupper(option) == 'Y') {
            return true;
        }

        return false; // Will return false on any input other than 'Y'
    }

};

#endif // MENUPRINT_H_INCLUDED
