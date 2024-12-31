#include<iostream>
using namespace std;

class Patient {
public:
    int id;
    string name;
    int age;
    string disease;
    string phone;
    string assignedDoctor;
    int bedNumber;
    Patient* next;

    Patient(int id, string name, int age, string disease, string phone, string doctor, int bed) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->disease = disease;
        this->phone = phone;
        this->assignedDoctor = doctor;
        this->bedNumber = bed;
        this->next = nullptr;
    }
};

class Doctor {
public:
    int id;
    string name;
    int age;
    string phone;

    Doctor(int id = 0, string name = "", int age = 0, string phone = "") {
        this->id = id;
        this->name = name;
        this->age = age;
        this->phone = phone;
    }
};


class Hospital {
private:
    Patient* head;
    Doctor doctors[4];
    int totalBeds;
    bool beds[20];

    int minHeap[100];
    int heapSize;


public:
    Hospital() {
        head = nullptr;
        heapSize = 0;
        totalBeds = 20;
        for (int i = 0; i < 20; i++) beds[i] = false;
        for (int i = 0; i < 4; i++) {
            doctors[i] = Doctor(i + 1, "", 0, "");
        }
    }

    void addPatient(int id, string name, int age, string disease, string phone, string doctor, int bed) {
        Patient* newPatient = new Patient(id, name, age, disease, phone, doctor, bed);
        newPatient->next = head;
        head = newPatient;
    }

    void displayPatients() {
        if (!head) {
            cout << "No patients available.\n";
            return;
        }
        Patient* temp = head;
        while (temp) {

            cout << "\nPatient Details\n";
            cout << "ID: " << temp->id << "\nName: " << temp->name << "\nAge: " << temp->age;
            cout << "\nDisease: " << temp->disease << "\nPhone: " << temp->phone;
            cout << "\nDoctor: " << temp->assignedDoctor << "\nBed: " << temp->bedNumber << "\n";
            temp = temp->next;
        }
    }

    Patient* searchPatientByID(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void searchPatientByName(string name) {
        Patient* temp = head;
        bool found = false;
        while (temp) {
            if (temp->name == name) {
                cout << "\nPatient Found:\n";
                cout << "ID: " << temp->id << ", Name: " << temp->name << ", Age: " << temp->age << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No patient found with name: " << name << "\n";
        }
    }

    void addDoctor(int id, string name, int age, string phone) {
        if (id < 1 || id > 4) {
            cout << "Invalid Doctor ID." << endl;
            return;
        }
        doctors[id - 1] = Doctor(id, name, age, phone);
    }

    void displayDoctors() {
        for (int i = 0; i < 4; i++) {
            if (doctors[i].name != "") {
                cout << "ID: " << doctors[i].id << ", Name: " << doctors[i].name;
                cout << ", Age: " << doctors[i].age << ", Phone: " << doctors[i].phone << endl;
            }
        }
    }

    int assignBed() {
        for (int i = 0; i < totalBeds; i++) {
            if (!beds[i]) {
                beds[i] = true;
                return i + 1;
            }
        }
        return -1;
    }

    void releaseBed(int bedNumber) {
        if (bedNumber > 0 && bedNumber <= totalBeds) {
            beds[bedNumber - 1] = false;
        }
    }

    void displayBedStatus() {
        cout << "\nBed Status:\n";
        for (int i = 0; i < totalBeds; i++) {
            cout << "Bed " << i + 1 << ": " << (beds[i] ? "Occupied" : "Available") << "\n";
        }
    }

    void addEmergencyPatient(int priority) {
        minHeap[heapSize++] = priority;
        int i = heapSize - 1;
        while (i != 0 && minHeap[(i - 1) / 2] > minHeap[i]) {
            swap(minHeap[i], minHeap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void viewEmergencyPatients() {
        if (heapSize == 0) {
            cout << "No emergency patients.\n";
            return;
        }
        cout << "Emergency Patients (Priorities):\n";
        for (int i = 0; i < heapSize; i++) {
            cout << minHeap[i] << " ";
        }
        cout << "\n";
    }

    void ownerMenu() {
        int choice;
        do {
            cout << "\n------------Owner Menu------------\n";
            cout << "1. Add Doctor\n2. Display Doctors\n3. Display All Patients\n4. Display Bed Status\n5. Exit\n";
            cin >> choice;
            switch (choice) {
            case 1: {
                int id, age;
                string name, phone;
                cout << "Enter Doctor ID (1-4): ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Phone: ";
                cin >> phone;
                addDoctor(id, name, age, phone);
                break;
            }
            case 2:
                displayDoctors();
                break;
            case 3:
                displayPatients();
                break;
            case 4:
                displayBedStatus();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 5);
    }

    void doctorMenu() {
        int choice;
        do {
            cout << "\n------------Doctor Menu------------\n";
            cout << "1. View Patients\n2. Search Patient by ID\n3. Search Patient by Name\n4. Exit\n";
            cin >> choice;
            switch (choice) {
            case 1:
                displayPatients();
                break;
            case 2: {
                int id;
                cout << "Enter Patient ID: ";
                cin >> id;
                Patient* patient = searchPatientByID(id);
                if (patient) {
                    cout << "Patient Found: " << patient->name << ", Age: " << patient->age << "\n";
                }
                else {
                    cout << "Patient not found!\n";
                }
                break;
            }
            case 3: {
                string name;
                cout << "Enter Patient Name: ";
                cin >> name;
                searchPatientByName(name);
                break;
            }
            case 4:
                cout << "\nExiting Doctor Menu! Good Bye";
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    void receptionistMenu() {
        int choice;
        do {
            cout << "\n------------Receptionist Menu------------\n";
            cout << "1. Add Patient\n2. Assign Emergency Priority\n3. View Emergency Patients\n4. Exit\n";
            cin >> choice;
            switch (choice) {
            case 1: {
                int id, age;
                string name, disease, phone, doctor;
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Disease: ";
                cin >> disease;
                cout << "Enter Phone: ";
                cin >> phone;
                cout << "Enter Doctor Name: ";
                cin >> doctor;
                int bed = assignBed();
                if (bed == -1) {
                    cout << "No beds available.\n";
                }
                else {
                    addPatient(id, name, age, disease, phone, doctor, bed);
                    cout << "Patient added with Bed Number: " << bed << "\n";
                }
                break;
            }
            case 2: {
                int priority;
                cout << "Enter Patient Emergency Priority: ";
                cin >> priority;
                addEmergencyPatient(priority);
                break;
            }
            case 3:
                viewEmergencyPatients();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    void patientMenu() {
        int choice;
        do {
            cout << "\n------------Patient Menu------------\n";
            cout << "\n1. View Own Details\n2. Exit\n";
            cin >> choice;
            switch (choice) {
            case 1: {
                int id;
                cout << "Enter Your Patient ID: ";
                cin >> id;
                Patient* patient = searchPatientByID(id);
                if (patient) {
                    cout << "Patient Details: Name: " << patient->name << ", Disease: " << patient->disease;
                    cout << ", Assigned Doctor: " << patient->assignedDoctor << ", Bed Number: " << patient->bedNumber << "\n";
                }
                else {
                    cout << "Patient not found!\n";
                }
                break;
            }
            case 2:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        } while (choice != 2);
    }
};

int main() {
    Hospital hospital;
    int userType;

    do {
        cout << "\n ------------Welcome to The Hospital Management System------------\n";
        cout << "Enter your role \n1-Owner \n2-Doctor \n3-Receptionist \n4-Patient \n5-Exit Program\n";
        cin >> userType;

        switch (userType) {
        case 1:
            hospital.ownerMenu();
            break;
        case 2:
            hospital.doctorMenu();
            break;
        case 3:
            hospital.receptionistMenu();
            break;
        case 4:
            hospital.patientMenu();
            break;
        case 5:
            cout << "\nExiting the Program! Goodbye!\n";
            break;
        default:
            cout << "Invalid role. Please try again.\n";
        }
    } while (userType != 5);

    return 0;
}