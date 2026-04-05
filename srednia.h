#ifndef srednia_h
#define srednia_h

#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>


typedef std::vector<double>::const_iterator iter;

class Srednia{
    public:
        Srednia(const iter &pocz, const iter &end);
        double suma() const{return suma_;};
        void operator() ();
    private:
        double suma_;
        iter pocz_;
        iter end_;
};


class StdLicz{
    public:
        StdLicz(const iter &pocz, const iter &end,const double avg);
        double suma() const{return suma_;};
        void operator() ();
    private:
        double suma_;
        const double avg_;
        iter pocz_;
        iter end_;
};


#endif