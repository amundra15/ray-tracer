#include <iostream>
#include <chrono> 

void a_scene();
void a_bumpmappers();
using namespace std::chrono; 

int main(int argc, char* argv[]) {
    
    auto start = high_resolution_clock::now(); 

    a_scene();

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    std::cout << float(duration.count())/1000.0 << "seconds" << std::endl; 
    
    return 0;
}