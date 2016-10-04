class Car {
    protected:
        std::string licenseNumber_;
        std::string brand_;
        int capacity_;
        bool isAvailable_;
        // protected constructor to not allow any instance of this class from main or other routine
        // but only through the derived classes. 
        Car(std::string licenseNumber, std::string brand, int capacity = 5, int isAvailable = true):licenseNumber_(licenseNumber), brand_(brand), capacity_(capacity), isAvailable_(isAvailable) {}
        
    public:
        virtual int getCapacity() {
            return capacity_;
        }
        inline std::string getLicenseNumber() { return licenseNumber_; }
        inline std::string getBrand() { return brand_; }
        inline bool getAvailability() { return isAvailable_; }
        inline void setAvailability(bool val) {isAvailable_ = val; }
};

// SUV class derived from Car class
class SUV:public Car {
    private:
        bool hasThirdRow_;
    public:
        SUV(std::string licenseNumber, std::string brand, bool thirdRow = false):Car(licenseNumber, brand), hasThirdRow_(thirdRow) {
            // add 3 whenever, thirdRow is set to true
            if(thirdRow == true) {
                capacity_ += 3;
            }
        } // end-constructor

        inline void setThirdRow(bool val) { 
            if(hasThirdRow_ == true) 
                return;
            hasThirdRow_ = val; 
            capacity_ += 3;
        }
        inline bool getThirdRow() { return hasThirdRow_; }
};

// Sedan class derived from Car class
class Sedan:public Car {
    private:
        bool hasSportPackage_;
    public:
        Sedan(std::string licenseNumber, std::string brand, bool sportPackage= false):Car(licenseNumber, brand), hasSportPackage_(sportPackage) {
        }

        inline void setSportPackage(bool val) { hasSportPackage_ = val; }
        inline bool getSportPackage() { return hasSportPackage_; }
};

// CarRental class
class CarRental {
    private:
        std::map<std::string, Car*> licenseToCar; // std::map for license number of Car*
        std::map<int, std::list<Car*> > capacityMap;
    public:
        Car* addCar(std::string, std::string, std::string, bool = false);
        bool bookCar(std::string);
        bool dropCar(std::string);
        bool updateCarAvailability(std::string, bool);
        std::list<Car*> getCarsWithCapacity(int);
};

/************************************************************************
name    : addCar 
purpose : creates a car instance and adds it to teh car rental availability std::map; 
@inputs : type -> car type {SUV, Sedan}
          licenseNumber -> license number of the car
          brand -> brand of the car
          val -> boolean variable which denotes 
                hasThirdRow when type == SUV
                hasSportPackage when type == Sedan 
@return : Instance of car
************************************************************************/
Car* CarRental::addCar(std::string type, std::string licenseNumber, std::string brand, bool val) {
    Car* c = NULL;
    if(type == "SUV") {
        c = new SUV(licenseNumber, brand, val);
    }
    else if(type == "Sedan") {
        c = new Sedan(licenseNumber, brand, val);
    }
    else {
        // error
        return NULL;
    }
    capacityMap[c->getCapacity()].push_back(c);
    licenseToCar[licenseNumber] = c;
    return c;
}       

/************************************************************************
name    : addCarsWithCapacity
purpose : gets a std::list of all the available cars with given capacity 
@inputs : capacity -> capacity of the car 
@return : std::list of available cars with capacity as 'capacity'
************************************************************************/
std::list<Car*> CarRental::getCarsWithCapacity(int capacity) { 
    std::list<Car*> retVal;

    std::list<Car*> temp = capacityMap[capacity];
    for(std::list<Car*>::iterator it = temp.begin(); it != temp.end(); ++it) {
        // if car is not available, continue
        if((*it)->getAvailability() == false) {
            continue;
        }
        retVal.push_back(*it);
    }
    return retVal;
}

/************************************************************************
name    : updateCarAvailability 
purpose : either books a car or drops a car
@inputs : licenseNumber -> license number of the car  
          book -> true whenever car needs to be booked else false
@return : true if the car can be booked / dropped else false 
************************************************************************/
bool CarRental::updateCarAvailability(std::string licenseNumber, bool book) {
    std::map<std::string, Car*>::iterator iter = licenseToCar.find(licenseNumber);
    if(iter == licenseToCar.end()) {
        // no such car exists;
        return false;
    }
    
    if((iter->second)->getAvailability() == book) {
        // car not available(booking) || car already available(dropping)
        return false;
    }
    (iter->second)->setAvailability(book);
    return true;
} 

/************************************************************************
name    : dropCar 
purpose : drops the car 
@inputs : licenseNumber -> license number of the car  
@return : true if the car can be dropped else false 
************************************************************************/
bool CarRental::dropCar(std::string licenseNumber) {
    return updateCarAvailability(licenseNumber, true);
}

/************************************************************************
name    : bookCar 
purpose : books the car 
@inputs : licenseNumber -> license number of the car  
@return : true if the car can be booked else false 
************************************************************************/
bool CarRental::bookCar(std::string licenseNumber) {
    return updateCarAvailability(licenseNumber, false);
}
