#ifndef kolorki_h
#define kolorki_h

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// ==========================================
// FORMATOWANIE TEKSTU
// ==========================================

//PODSTAWOWE
inline const string RESET     = "\033[0m";
inline const string BOLD      = "\033[1m"; 
inline const string NO_BOLD   = "\033[22m"; 
inline const string UNDERLINE = "\033[4m";

// KOLORY
inline const string BLACK   = "\033[30m";
inline const string RED     = "\033[31m";
inline const string GREEN   = "\033[32m";
inline const string YELLOW  = "\033[33m";
inline const string BLUE    = "\033[34m"; 
inline const string MAGENTA = "\033[35m"; 
inline const string CYAN    = "\033[36m"; 
inline const string WHITE   = "\033[37m"; 

// TŁA  
inline const string BG_BLACK   = "\033[40m";
inline const string BG_RED     = "\033[41m";
inline const string BG_GREEN   = "\033[42m";
inline const string BG_YELLOW  = "\033[43m";
inline const string BG_BLUE    = "\033[44m";
inline const string BG_MAGENTA = "\033[45m";
inline const string BG_CYAN    = "\033[46m";
inline const string BG_WHITE   = "\033[47m";

// ==========================================
// FUNKCJE POMOCNICZE - UNIWERSALNE
// ==========================================

//WYSWIETLANIE NAGLOWKA
inline void prntHeader(string text, string col = MAGENTA, int n = 70) {
    int len = text.length();
    
    if (len >= n - 2) { 
        cout << YELLOW << BOLD << text << RESET << endl;
        return;
    }
    
    int miejsce = n - len - 2;
    int left = miejsce / 2;
    int right = miejsce - left; 

    cout << endl;
    cout << YELLOW << string(left, '-') << " " << BOLD << col << text << YELLOW << NO_BOLD << " " << string(right, '-') << RESET << endl;
}

//TEMPLATE do czyszczenia liczb - do wyswietlania bo normlanie zamienianie na string nie dzialalo dla double

inline string cleanNum(double liczba) {
    stringstream ss;
    ss << liczba;
    return ss.str();
}

// WYSWIETLANIE TABLIC - 2 WIERSZE
inline void prntTablica(string n, string s11, string s12, string s13, string s14, string s21, string s22, string s23, string s24) {
    prntHeader(n);
    const int col = 33;
    const string sep = " | ";
    
    cout << YELLOW << BOLD;
    
    string col1 = s11 + s12;
    cout << left << setw(col) << col1 << NO_BOLD << sep << BOLD << s13 << s14 << endl;
    
    string col2 = s21 + s22;
    cout << left << setw(col) << col2 << NO_BOLD << sep << BOLD << s23 << s24 << RESET << endl << endl;
}

// WYSWIETLANIE TABLIC - 1 WIERSZ
inline void prntTablica(string n, string s11, string s12, string s13, string s14) {
    prntHeader(n);
    const int col = 33;
    const string sep = " | ";
    
    cout << YELLOW << BOLD;
    
    string col1 = s11 + s12;
    cout << left << setw(col) << col1 << NO_BOLD << sep << BOLD << s13 << s14 << RESET << endl << endl;
}

// WYSWIETLANIE TABLIC - 3 WIERSZE
inline void prntTablica(string n, string s11, string s12, string s13, string s14, string s21, string s22, string s23, string s24, string s31, string s32, string s33, string s34) {
    prntHeader(n);
    const int col = 33;
    const string sep = " | ";
    
    cout << YELLOW << BOLD;
    
    string col1 = s11 + s12;
    cout << left << setw(col) << col1 << NO_BOLD << sep << BOLD << s13 << s14 << endl;
    
    string col2 = s21 + s22;
    cout << left << setw(col) << col2 << NO_BOLD << sep << BOLD << s23 << s24 << endl;

    string col3 = s31 + s32;
    cout << left << setw(col) << col3 << NO_BOLD << sep << BOLD << s33 << s34 << RESET << endl << endl;
}

#endif