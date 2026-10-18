#include "MarkerManager.hpp"


bool MarkerManager::contains(const int id) const {
    if (id <= MarkerManager::markers.size()&&id > 0) {
        return true;
    }
    return false;
}
bool MarkerManager::add(const Marker& marker) {
    if (!contains(marker.id) && marker.id > 0 && marker.priority > 0 && marker.priority < 100) {
        MarkerManager::markers.push_back(marker);
        return true;
    }
    return false;

}

void MarkerManager::showAll(void) const {
    for (int i = 0; i < markers.size(); i++) {
        std::cout << "Id:" << markers[i].id \
        << "\tPosition:(" << markers[i].x_mm << "," << markers[i].y_mm << ")" \
        << "\tPriority:" << markers[i].priority << std::endl;
    }
}

int MarkerManager::calculate(int threshold) const {
    int sum = 0;

    for (int i = 0; i < markers.size(); i++) {
        if (markers[i].priority >= threshold) {
            sum++;
        }
    }
    return sum;
}

 void MarkerManager::sorts(void) { 
    std::sort(markers.begin(), markers.end(), [](const Marker& a, const Marker& b) {
        if (a.priority != b.priority) return a.priority > b.priority;
        else return a.id < b.id;
    });
}

void MarkerManager::modify(int id,int newpriority) {
    if (contains(id) && newpriority >= 0 && newpriority <= 100) {
        markers[id-1].priority = newpriority;
    }
}

void MarkerManager::clearAll(void) { 
    markers.clear();
}