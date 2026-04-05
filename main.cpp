#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>  
#include <sstream>
#include <random>
#include <tuple>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <execution>

#include "kolorki.h"
#include "srednia.h"

using namespace std;

void prntHelp(){//Help - inormacje o komendach
    const int w = 30; 
    const string sep = " | ";

    prntHeader("LISTA DOSTEPNYCH KOMEND");

    cout << YELLOW << BOLD << left << setw(w) << "KOMENDA" << sep << "OPIS" << RESET << endl;
    cout << YELLOW << string(w, '-') << "-+-" << string(40, '-') << RESET << endl; 

    cout << BG_BLACK << left << setw(w) << "test" << RESET << YELLOW << sep << " Plus nr: 1 Liniowe liczenie avg i std 2 Wielowatkowe 3 Najlepszy" << RESET << endl;
    cout << BG_BLACK << left << setw(w) << "x" << RESET << YELLOW << sep << "Wyjscie z programu." << RESET << endl;
    cout << BG_BLACK << left << setw(w) << "help" << RESET << YELLOW << sep << "Wyswietlenie dostepnych komend" << RESET << endl;

    cout << endl;
}

void resett(vector <double> &dane,const int n){
    std::uniform_real_distribution<double> rozklad(0.0, 1.0);
    std::mt19937 gen{std::random_device{}()};

    for(int i = 0; i < n; i++){
        dane[i] = rozklad(gen); 
    }

}

tuple <double, double> srednia_i_std_klasycznie(const vector <double> &dane,const int n){
    //Średnia
    double sum=0;
    for(const auto &d:dane ){
        sum+=d;
    }

    double srednia=sum/n;
    //std
    double s1=0;

    for(const auto &d:dane ){
        s1+=(d-srednia)*(d-srednia);
    }

    double std=sqrt(s1/(n-1));
    return {srednia, std};
}

tuple <double, double> srednia_i_std_watki(const vector <double> &dane,const int n, const int p){
    //Średnia
    vector <Srednia*> srednie;
    vector<thread> watki;

    for (int i = 0; i < p; ++i){ // przydziela zakresy poszczególnym obiektom
        Srednia *s = new Srednia(dane.begin() + n*i/p, dane.begin() + n*(i+1)/p);
        srednie.push_back(s);

        watki.push_back(thread(ref(*s)));
    }

    for (auto& t : watki) {
        if (t.joinable()) t.join();
    }

    double sum=0;
    for(const auto &s:srednie ){
        sum+=s->suma();
    }
    double srednia=sum/n;

    for (auto s : srednie) delete s;

    //std

    vector <StdLicz*> stda;
    vector<thread> watkistd;

    for (int i = 0; i < p; ++i){ // przydziela zakresy poszczególnym obiektom
        StdLicz *s = new StdLicz(dane.begin() + n*i/p, dane.begin() + n*(i+1)/p,srednia);
        stda.push_back(s);

        watkistd.push_back(thread(ref(*s)));
    }

    for (auto& t : watkistd) {
        if (t.joinable()) t.join();
    }

    double s1=0;
    for(const auto &s:stda ){
        s1+=s->suma();
    }

    for (auto s : stda) delete s;


    
    double std=sqrt(s1/(n-1));
    return {srednia, std};
}

tuple <double, double> srednia_i_std_stl(const vector <double> &dane, const int n) {
    // Średnia - zrównoleglone sumowanie
    double sum = reduce(std::execution::par_unseq, dane.begin(), dane.end(), 0.0);
    double srednia = sum / n;

    // Odchylenie - zrównoleglone odejmowanie od średniej, potęgowanie i sumowanie w jednym
    double s1 = transform_reduce(
        std::execution::par_unseq, 
        dane.begin(), dane.end(), 
        0.0, 
        std::plus<>(), 
        [srednia](double x) { return (x - srednia) * (x - srednia); }
    );
    
    double std = sqrt(s1 / (n - 1));
    return {srednia, std};
}

void test(vector <double> & dane, const int n,int id){
    double time=0;
    if(id==1){
        for(int i=0;i<105;i++){
    
            auto start = chrono::high_resolution_clock::now();
            auto [avg,std]=srednia_i_std_klasycznie(dane,n);
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> czas_ms = stop - start;
            time=czas_ms.count();
            prntTablica("Klasyczne","Avg: ",cleanNum(avg),"Std: ",cleanNum(std),"Time (ms): ",cleanNum(time),"Ilosc: ",cleanNum(dane.size()));

            ofstream plik("klasycznie.txt", ios::app);
            if (plik.is_open()) {
            plik << time <<endl;
            plik.close(); 
            time=0;
    }
            resett(dane,n);
        }

    }else if(id==2){
        for (int p =1;p<17;p++){
            ofstream plik("wielo_watkowo.txt", ios::app);
                if (plik.is_open()) {
                    plik <<p<<endl;
                    plik.close(); 
                }
            for(int i=0;i<105;i++){
                auto start = chrono::high_resolution_clock::now();
                auto [avg,std]=srednia_i_std_watki(dane,n,p);
                auto stop = chrono::high_resolution_clock::now();
                chrono::duration<double, std::milli> czas_ms = stop - start;
                time=czas_ms.count();
                prntTablica("Watki","Avg: ",cleanNum(avg),"Std: ",cleanNum(std),"Time (ms): ",cleanNum(time),"Ilosc: ",cleanNum(dane.size()));
    
                ofstream plik("wielo_watkowo.txt", ios::app);
                if (plik.is_open()) {
                    plik << time <<endl;
                    plik.close(); 
                }
                time=0;
                resett(dane,n);
            
            }
        }
    }else if(id==3){
        for (int i = 0; i < 105; i++) {
            auto start = chrono::high_resolution_clock::now();
            auto [avg, std] = srednia_i_std_stl(dane, n);
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> czas_ms = stop - start;
            time = czas_ms.count();
            
            prntTablica("STL Par", "Avg: ", cleanNum(avg), "Std: ", cleanNum(std), "Time (ms): ", cleanNum(time), "Ilosc: ", cleanNum(dane.size()));

            // Zapis do pliku
            ofstream plik("op.txt", ios::app);
            if (plik.is_open()) {
                plik << time << endl;
                plik.close(); 
            }
            
            time = 0;
            resett(dane, n);
        }
    }else{
        cout<<RED<<BOLD<<"Blad!!!!"<<RESET<<endl;
    }

}
void commands(vector <double> &dane,int n){

    bool running=true;
    while(running){

        cout<<BOLD<<CYAN<<"~~  "<<YELLOW<<"Co chcesz zrobic?"<<RESET<<endl;
        cout<<CYAN<<">>"<<RESET;
        string linia;
        getline(cin,linia);
        if(linia.empty()){return;}
        stringstream ss(linia);
        string command;
        ss>>command;

        if (command=="x"){
            cout<<RED<<BOLD<<"Zamykanie..."<<RESET<<endl;   
            running=false;
        } else if(command=="help"){
        prntHelp();
        }else if(command=="test"){
            int t;
            if(ss>>t){
                test(dane,n,t);
            }else{
                cout<<RED<<BOLD<<"Zly nr komendy!!\n\n"<<RESET;
            }
        }
        else{
            cout<<RED<<BOLD<<"Nieznana komenda!!\n\n"<<RESET;
        }
    
        cout<<endl;
    }
}



int main () 
{
    //Początek
    int n = 10000000;
    vector <double> dane;

    std::uniform_real_distribution<double> rozklad(0.0, 1.0);
    std::mt19937 gen{std::random_device{}()};
    for(int i=0; i<n;i++){
        dane.push_back(rozklad(gen));
    }

    //Petla z komendami
    commands(dane,n);

}
