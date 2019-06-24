#include <iostream>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

class Person {
public:
    Person(){

    }

    Person(string firstName, string lastName, int yearBorn){
        this->yearBorn = yearBorn;
        firstNamesForYear[yearBorn] = firstName;
        lastNamesForYear[yearBorn] = lastName;
    }

    void ChangeFirstName(int year, const string& first_name) {
        /*if(year < yearBorn){
            return;
        }*/
        firstNamesForYear[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        /*if(year < yearBorn){
            return;
        }*/
        lastNamesForYear[year] = last_name;
    }

    string GetFullName(int year) const {
        /*if(year < yearBorn){
            return "No person";
        }*/
        string firstName = getFirstName(year);
        string lastName = getLastName(year);
        if(firstName.size() == 0 && lastName.size() == 0){
            return "Incognito";
        }else if(firstName.size() == 0){
            return lastName + " with unknown first name";
        }else if(lastName.size() == 0){
            return firstName + " with unknown last name";
        }else{
            return firstName + " " + lastName;
        }
    }

    string GetFullNameWithHistory(int year) const{
        /*if(year < yearBorn){
            return "No person";
        }*/
        string firstName;
        int changeYear;
        for(const auto& name : firstNamesForYear){
            if(year < name.first){
                break;
            }else{
                changeYear = name.first;
                firstName = name.second;
            }
        }
        auto iter = firstNamesForYear.begin();
        for(; iter != firstNamesForYear.end() && (iter->first != changeYear || iter->second != firstName); iter++){
        }
        vector<string> firstNameHistory;
        string name = firstName;
        if(iter != firstNamesForYear.end()){
            for(;iter != firstNamesForYear.begin(); iter--){
                if(iter->second != name){
                    firstNameHistory.push_back(iter->second);
                    name = iter->second;
                }

            }
            if(iter->second != name){
                firstNameHistory.push_back(iter->second);
            }
        }
        string lastName;
        for(const auto& name : lastNamesForYear){
            if(year < name.first){
                break;
            }else{
                changeYear = name.first;
                lastName = name.second;
            }
        }
        iter = lastNamesForYear.begin();
        for(; iter != lastNamesForYear.end() && (iter->first != changeYear || iter->second != lastName); iter++){
        }
        vector<string> lastNameHistory;
        name = lastName;
        if(iter != lastNamesForYear.end()){
            for(;iter != lastNamesForYear.begin(); iter--){
                if(iter->second != name){
                    lastNameHistory.push_back(iter->second);
                    name = iter->second;
                }

            }
            if(iter->second != name){
                lastNameHistory.push_back(iter->second);
            }
        }
        if(!firstNameHistory.empty()){
            firstName += " (";
            for(int i(0); i < firstNameHistory.size(); i++){
                if(i == 0){
                    firstName += firstNameHistory[i];
                }else
                {
                    firstName += ", " + firstNameHistory[i];
                }
            }
            firstName += ")";
        }

        if(!lastNameHistory.empty()){
            lastName += " (";
            for(int i(0); i < lastNameHistory.size(); i++){
                if(i == 0){
                    lastName += lastNameHistory[i];
                }else
                {
                    lastName += ", " + lastNameHistory[i];
                }
            }
            lastName += ")";
        }


        if(firstName.size() == 0 && lastName.size() == 0){
            return "Incognito";
        }else if(firstName.size() == 0){
            return lastName + " with unknown first name";
        }else if(lastName.size() == 0){
            return firstName + " with unknown last name";
        }else{
            return firstName + " " + lastName;
        }
    }

    string getFirstName(int year) const{
        string firstName;
        for(const auto& name : firstNamesForYear){
            if(year < name.first){
                break;
            }else{
                firstName = name.second;
            }
        }
        return firstName;
    }

    string getLastName(int year) const{
        string lastName;
        for(const auto& name : lastNamesForYear){
            if(year < name.first){
                break;
            }else{
                lastName = name.second;
            }
        }
        return lastName;
    }
private:
    int yearBorn;
    map<int, string> firstNamesForYear;
    map<int, string> lastNamesForYear;
};

int main()
{
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
