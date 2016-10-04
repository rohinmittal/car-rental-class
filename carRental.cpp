#include<iostream>
#include<string>
#include<map>
#include<list>
#include "engine.h"

using namespace std;

int main() {
    CarRental cr;
    // create an instance of SUV with third row as false 
    Car* c1 = cr.addCar("SUV", "NY1000", "BMW");
    cout<<c1->getLicenseNumber()<<" "<<c1->getBrand()<<" "<<c1->getCapacity()<<endl;

    // set it's thirdRow as true
    (dynamic_cast<SUV*>(c1))->setThirdRow(true);
    cout<<c1->getLicenseNumber()<<" "<<c1->getBrand()<<" "<<c1->getCapacity()<<endl;

    // create an instance of SUV with third row as true 
    Car* c2 = cr.addCar("SUV", "NY1234", "Audi", true);
    cout<<c2->getLicenseNumber()<<" "<<c2->getBrand()<<" "<<c2->getCapacity()<<endl;

    // create an instance of Sedan
    Car* c3 = cr.addCar("Sedan", "MA1290", "Ford");
    // print the details
    cout<<c3->getLicenseNumber()<<" "<<c3->getBrand()<<" "<<c3->getCapacity()<<endl;
    return 0;
}
