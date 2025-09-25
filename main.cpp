#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class Agency 
{
protected:
    string agencyName;
public:
    Agency() { agencyName = "Wanderluxe"; }
    void showAgency() {
        cout << "\nAgency Name: " << agencyName << "\n";
    }
};


class Payment
{
protected:
    double amount;
    string paymentMode;
public:
    Payment() { amount = 0; paymentMode = "Not Set"; }
    void setPayment(double amt, string mode) {
        amount = amt;
        paymentMode = mode;
    }
    void showPayment() {
        cout << "Payment Amount: $" << amount << " | Mode: " << paymentMode << "\n";
    }
};


class Travel : public Agency, public Payment 
{
private:
    string destination;
    string season;
    string travelType;
    string selectedPackage;
    string travelerName;
    int age;
    string id;
    static string AgencyName;

public:
    
    Travel operator+(const Travel &other)
    {
        Travel combined;
        combined.travelerName = travelerName + " & " + other.travelerName;
        combined.age = age + other.age;
        combined.selectedPackage = selectedPackage + " + " + other.selectedPackage;
        combined.destination = destination;
        combined.season = season;
        combined.travelType = travelType;
        combined.id = id;
        return combined;
    }

    
    Travel() 
    {
        destination = "Not Set";
        season = "Any";
        travelerName = "Unknown";
        age = 0;
        id = "None";
    }

    
    Travel(string dest, string seas, string tType, string pkg) 
    {
        destination = dest;
        season = seas;
        travelType = tType;
        selectedPackage = pkg;
    }

    
    Travel(const Travel &t)
    {
        destination = t.destination;
        season = t.season;
        travelType = t.travelType;
        selectedPackage = t.selectedPackage;
        travelerName = t.travelerName;
        age = t.age;
        id = t.id;
    }

    
    Travel operator++() { ++age; return *this; }
    Travel operator--() { if (age > 0) --age; return *this; }
    bool operator!() { return age == 0; }

    void CustomerDetails()
    {
        cout << "\nEnter your travel destination: ";
        getline(cin, destination);
        cout << "\nEnter your preferred season: ";
        getline(cin, season);
        cout << "Destination saved successfully.\n";
    }

    void TravelType(string defaultType = "Solo") 
    {
        cout << "\nChoose Type of Travel (Solo / Family / Group)(default: " << defaultType << "): ";
        getline(cin, travelType);
        if (travelType.empty()) {
            travelType = defaultType;
        }
        if (travelType != "Solo" && travelType != "solo" &&
            travelType != "Family" && travelType != "family" &&
            travelType != "Group" && travelType != "group") {
            cout << "Invalid travel type selected. Defaulting to Solo.\n";
            travelType = defaultType;
        } else {
            cout << "Travel type set to " << travelType << ".\n";
        }
    }

    void choosePackage(int packageChoice = 4)
    {
        cout << "\nChoose a travel package:\n";
        cout << "1. goa ($15,000)\n";
        cout << "2. jaipur ($12,000)\n";
        cout << "3. manali ($10,000)\n";
        cout << "4. custom package\n";
        cout << "Enter your package choice (1-4)(default: " << packageChoice << "): ";
        string input;
        getline(cin, input);
        if (!input.empty()) {
            stringstream ss(input);
            ss >> packageChoice;
        }
        switch (packageChoice) {
            case 1: selectedPackage = "goa"; break;
            case 2: selectedPackage = "jaipur"; break;
            case 3: selectedPackage = "manali"; break;
            case 4: selectedPackage = "Custom Package"; break;
            default:
                selectedPackage = "Custom Package";
                cout << "Invalid choice. Setting to Custom Package.\n";
        }
        cout << "Selected Package: " << selectedPackage << "\n";
    }

    void choosePackage(string customPackage)
    {
        selectedPackage = customPackage;
        cout << "Custom package selected: " << selectedPackage << "\n";
    }

    void TravelerDetails()
    {
        cout << "\nEnter your name: ";
        getline(cin, travelerName);
        cout << "Enter your age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter ID proof (e.g. Aadhaar No.): ";
        getline(cin, id);
        cout << "Traveler details saved.\n";
    }

    void TravelerDetails(string name, int Age, string ID) 
    {
        travelerName = name;
        age = Age;
        id = ID;
        cout << "Traveler details set successfully\n";
    }

    void TripSummary() 
    {
        cout << "\n--- Trip Summary ---\n";
        cout << "Traveler: " << travelerName << " | Age: " << age << " | ID: " << id << "\n";
        cout << "Travel Type: " << travelType << "\n";
        cout << "Destination: " << destination << "\n";
        cout << "Package Selected: " << selectedPackage << "\n";
        showAgency();   
        showPayment();  
    }

    static void TravelTips() 
    {
        cout << "\n Travel Tips from " << AgencyName << " \n";
        cout << "Carry valid ID proof\n";
        cout << "Pack according to the season\n";
        cout << "Confirm bookings in advance\n";
    }

    friend void showdetails(Travel t);
};

string Travel::AgencyName = "Wanderluxe";

void showdetails(Travel t) {
    cout << "Traveler Name: " << t.travelerName << "\n";
    cout << "Age: " << t.age << "\n";
    cout << "ID: " << t.id << "\n";
}

int main() 
{
    Travel::TravelTips();

    Travel trip1;
    trip1.CustomerDetails();
    trip1.TravelerDetails();

    trip1.setPayment(15000, "Credit Card");

    Travel trip2("Paris", "winter", "Family", "Luxury Package");
    trip2.setPayment(20000, "UPI");

    Travel combinedTrip = trip1 + trip2;
    cout << "\n Combined Trip Details \n";
    combinedTrip.TripSummary();

    return 0;
}
