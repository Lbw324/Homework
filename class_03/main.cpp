#include "MarkerManager.hpp"
int main(void){
    std::vector<Marker> init_markers;
    init_markers.push_back(Marker{1,100,200,80});
    init_markers.push_back({2,200,-50,95});
    init_markers.push_back({3,0,0,60});
    
    for(auto marker:init_markers){
        std::cout << "Id:" << marker.id \
        << "\tPosition:(" << marker.x_mm << "," << marker.y_mm << ")" \
        << "\tPriority:" << marker.priority << std::endl;
    }

    Marker* Ptr = &init_markers[0];
    Marker& Ref = init_markers[0];
    std::cout << "Id_Ptr:" << Ptr -> id << "\tId_Ref:" << Ref.id << std::endl;
    std::cout<<std::endl;

    MarkerManager Manager;
    Manager.add(init_markers[0]);
    Manager.add(init_markers[1]);
    Manager.add(init_markers[2]);
    Manager.add({2, 100, 100, 50});
    Manager.add({4, 200, 100, 101});

    Manager.showAll();

    std::cout << "Marker Count when threshold = 80: " << Manager.calculate(80) << std::endl;
    std::cout << "Marker Count when threshold = 90: " << Manager.calculate(90) << std::endl;
    
    std::cout<<std::endl;
    Manager.modify(1,95);
    Manager.sorts();
    Manager.modify(1,101);
    Manager.showAll();

    std::cout << "----------------------------------------------------------------------"<< std::endl;

    Manager.clearAll();

    while(1){
        std::cout << "1.showAll\n2.add new id\n3.check using id\n4.calculate\n0.exit\n";
        std::cout << "select: ";
        int select;
        int id;
        int priority;
        int x_mm;
        int y_mm;
        int threshold;
        std::cin >> select;

        if(select == 0) break;

        switch(select){
            case 1: Manager.showAll(); break;
            case 2: std::cout << "id: "; std::cin >> id;
                    std::cout << "x_mm: "; std::cin >> x_mm;
                    std::cout << "y_mm: "; std::cin >> y_mm;
                    std::cout << "priority: "; std::cin >> priority;
                    Manager.add(Marker{id,x_mm,y_mm,priority});
                    break;
            case 3: std::cout << "id: "; std::cin >> id;
                    if (Manager.contains(id)) std::cout << "contains\n";
                    else std::cout << "not contains\n";
                    break;
            case 4: std::cout << "threshold: "; std::cin >> threshold;
                    std::cout << "calculate: " << Manager.calculate(threshold) << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}