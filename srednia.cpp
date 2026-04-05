#include "srednia.h"

Srednia::Srednia(const iter &pocz, const iter &end):pocz_(pocz),end_(end){}


void Srednia::operator() () // wykonuje obliczenia
{
    suma_ = 0.0;
    for (auto it = pocz_; it != end_; ++it) {
    suma_ += *it;
}
}



StdLicz::StdLicz(const iter &pocz, const iter &end,const double avg):pocz_(pocz),end_(end),avg_(avg){}


void StdLicz::operator() () // wykonuje obliczenia
{
    suma_ = 0.0;
    for (auto it = pocz_; it != end_; ++it) {
        suma_+=(*it-avg_)*(*it-avg_);
    }
}