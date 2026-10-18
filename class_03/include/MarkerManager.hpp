#pragma once

# include <iostream>
# include <vector>
#include <algorithm>

struct Marker{
    int id;
    int x_mm;
    int y_mm;
    int priority;
};
class MarkerManager{
    public:
        bool add(const Marker& marker);
        bool contains(int id) const;
        void showAll(void) const;
        int  calculate(int threshold) const;
        void sorts(void);
        void modify(int id,int newpriority);
        void clearAll(void);
    private:
        std::vector<Marker> markers;
};