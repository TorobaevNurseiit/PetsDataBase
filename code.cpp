#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Date
{
    int day, month, year;

    void newDate(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
};

struct Pet
{
    string name;
    string breed;
    int age;
    string description;
    bool adopted;
    Date adoptionDate;

    void newPet(const string& n, const string& b, int a, const string& desc)
    {
        name = n;
        breed = b;
        age = a;
        description = desc;
        adopted = false; // Initially not adopted
    }

    void adoptPet(const Date& date)
    {
        adopted = true;
        adoptionDate = date;
    }

    void printPet() const
    {
        cout << "Name: " << name << endl;
        cout << "Breed: " << breed << endl;
        cout << "Age: " << age << " years old" << endl;
        cout << "Description: " << description << endl;
        cout << "Adopted: " << (adopted ? "Yes" : "No") << endl;
        if (adopted)
        {
            cout << "Adoption Date: " << adoptionDate.day << "/" << adoptionDate.month << "/" << adoptionDate.year << endl;
        }
    }

    void saveToFile(ofstream& file) const
    {
        file << name << endl;
        file << breed << endl;
        file << age << endl;
        file << description << endl;
        file << adopted << endl;
        if (adopted)
        {
            file << adoptionDate.day << " " << adoptionDate.month << " " << adoptionDate.year << endl;
        }
    }

    friend ifstream& operator>>(ifstream& file, Pet& pet)
    {
        getline(file, pet.name);
        getline(file, pet.breed);
        file >> pet.age;
        file.ignore();
        getline(file, pet.description);
        file >> pet.adopted;
        if (pet.adopted)
        {
            file >> pet.adoptionDate.day >> pet.adoptionDate.month >> pet.adoptionDate.year;
        }
        file.ignore(); // Ignore newline character after reading
        return file;
    }
};

void printMenu()
{
    cout << "Main Menu:\n";
    cout << "1. Add Pet\n";
    cout << "2. Print Pets\n";
    cout << "3. Adopting Pet\n";
    cout << "4. Save Pets to File\n";
    cout << "5. Load Pets from File\n";
    cout << "6. Delete Pet\n";
    cout << "7. Exit\n";
}

void deletePet(vector<Pet>& pets, int index)
{
    if (index < 0 || index >= pets.size())
    {
        cout << "Invalid index entered." << endl;
    }
    else
    {
        pets.erase(pets.begin() + index);
        cout << "Pet deleted successfully." << endl;
    }
}

void savePetsToFile(const vector<Pet>& pets, const string& filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto& pet : pets)
        {
            pet.saveToFile(file);
        }
        file.close();
        cout << "Pets saved to file successfully." << endl;
    }
    else
    {
        cout << "Unable to open file for saving pets." << endl;
    }
}

void loadPetsFromFile(vector<Pet>& pets, const string& filename)
{
    pets.clear();
    ifstream file(filename);
    if (file.is_open())
    {
        Pet pet;
        while (file >> pet) // Read pets until no more data
        {
            pets.push_back(pet);
        }
        file.close();
        cout << "Pets loaded from file successfully." << endl;
    }
    else
    {
        cout << "Unable to open file for loading pets." << endl;
    }
}

int main()
{
    vector<Pet> pets;

    int choice;
    do
    {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, breed, description;
            int age;
            cout << "Enter pet's name: ";
            cin >> name;
            cout << "Enter pet's breed: ";
            cin >> breed;
            cout << "Enter pet's age: ";
            cin >> age;
            cout << "Enter pet's description: ";
            cin.ignore(); // Ignore newline character
            getline(cin, description);
            Pet pet;
            pet.newPet(name, breed, age, description);
            pets.push_back(pet);
            cout << "Pet added successfully." << endl;
            break;
        }
        case 2:
        {
            cout << "Pets:\n";
            for (size_t i = 0; i < pets.size(); ++i)
            {
                cout << "Index: " << i << endl;
                pets[i].printPet();
                cout << endl;
            }
            break;
        }
        case 3:
        {
            int index;
            cout << "Enter the index of the adopting pet: ";
            cin >> index;

            if (index < 0 || index >= pets.size())
            {
                cout << "Invalid index entered." << endl;
            }
            else
            {
                Pet& pet = pets[index];
                if (pet.adopted)
                {
                    cout << "This pet has already been adopted." << endl;
                }
                else
                {
                    Date adoptionDate;
                    cout << "Enter adoption date (day month year): ";
                    cin >> adoptionDate.day >> adoptionDate.month >> adoptionDate.year;
                    pet.adoptPet(adoptionDate);
                    cout << "Pet adopted successfully." << endl;
                }
            }
            break;
        }
        case 4:
        {
            string filename;
            cout << "Enter filename to save pets to: ";
            cin >> filename;
            savePetsToFile(pets, filename);
            break;
        }
        case 5:
        {
            string filename;
            cout << "Enter filename to load pets from: ";
            cin >> filename;
            loadPetsFromFile(pets, filename);
            break;
        }
        case 6:
        {
            int index;
            cout << "Enter the index of the pet to delete: ";
            cin >> index;
            deletePet(pets, index);
            break;
        }
        case 7:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
            break;
        }
        cout << "Press Enter to continue...";				                            //clearing the screen
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        system("cls");
    } while (choice != 7);

    return 0;
}
