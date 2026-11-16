#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class WaterUsage {
protected:
    string activity;
    double litres;
public:
    WaterUsage(const string& a, double l) : activity(a), litres(l) {}
    virtual ~WaterUsage() = default;
    virtual string type() const = 0;
    virtual string tip() const = 0;

    string getActivity() const { return activity; }
    double getLitres() const { return litres; }

    virtual void display() const {
        cout << left << setw(14) << type()
             << setw(18) << activity
             << right << fixed << setprecision(2) << litres << " L\n";
    }

    virtual string toFile() const {
        return type() + "|" + activity + "|" + to_string(litres);
    }
};

class IndoorUsage : public WaterUsage {
public:
    IndoorUsage(const string& a, double l) : WaterUsage(a, l) {}
    string type() const override { return "Indoor"; }
    string tip() const override {
        return "Turn off taps while brushing and use water carefully indoors.";
    }
};

class OutdoorUsage : public WaterUsage {
public:
    OutdoorUsage(const string& a, double l) : WaterUsage(a, l) {}
    string type() const override { return "Outdoor"; }
    string tip() const override {
        return "Use a bucket or watering can and avoid unnecessary hose use.";
    }
};

class WaterTracker {
private:
    vector<unique_ptr<WaterUsage>> records;
    const string fileName = "water_records.txt";

    void loadRecords() {
        ifstream in(fileName);
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string kind, activity, amountText;
            if (getline(ss, kind, '|') &&
                getline(ss, activity, '|') &&
                getline(ss, amountText)) {
                try {
                    double amount = stod(amountText);
                    if (amount < 0) continue;
                    if (kind == "Indoor")
                        records.push_back(make_unique<IndoorUsage>(activity, amount));
                    else if (kind == "Outdoor")
                        records.push_back(make_unique<OutdoorUsage>(activity, amount));
                } catch (...) {
                    continue;
                }
            }
        }
    }

public:
    WaterTracker() { loadRecords(); }

    void addRecord() {
        int choice;
        string activity;
        double amount;

        cout << "Type (1 Indoor, 2 Outdoor): ";
        if (!(cin >> choice) || (choice != 1 && choice != 2)) {
            cout << "Invalid type.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Activity: ";
        getline(cin, activity);
        if (activity.empty() || activity.find('|') != string::npos) {
            cout << "Activity name cannot be empty or contain '|'.\n";
            return;
        }

        cout << "Water used (litres): ";
        if (!(cin >> amount) || amount < 0) {
            cout << "Enter a valid non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (choice == 1)
            records.push_back(make_unique<IndoorUsage>(activity, amount));
        else
            records.push_back(make_unique<OutdoorUsage>(activity, amount));

        cout << "Water usage record added.\n";
    }

    void listRecords() const {
        if (records.empty()) {
            cout << "No records found.\n";
            return;
        }
        cout << "\nNo.  " << left << setw(14) << "Type"
             << setw(18) << "Activity" << "Quantity\n";
        cout << "------------------------------------------------\n";
        for (size_t i = 0; i < records.size(); ++i) {
            cout << left << setw(5) << i + 1;
            records[i]->display();
        }
    }

    void showSummary() const {
        if (records.empty()) {
            cout << "No records available for summary.\n";
            return;
        }
        double total = 0, indoor = 0, outdoor = 0;
        for (const auto& record : records) {
            total += record->getLitres();
            if (record->type() == "Indoor") indoor += record->getLitres();
            else outdoor += record->getLitres();
        }

        cout << fixed << setprecision(2);
        cout << "\nTotal water used : " << total << " L\n";
        cout << "Indoor usage     : " << indoor << " L\n";
        cout << "Outdoor usage    : " << outdoor << " L\n";
        cout << "\nWater-saving tips:\n";
        for (const auto& record : records)
            cout << "- " << record->tip() << "\n";
    }

    void saveRecords() const {
        ofstream out(fileName);
        if (!out) {
            cout << "Error: could not save records.\n";
            return;
        }
        for (const auto& record : records)
            out << record->toFile() << '\n';
        cout << "Records saved. Goodbye!\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n=== WATER CONSERVATION MANAGEMENT SYSTEM ===\n"
                 << "1 Add water usage record\n"
                 << "2 View all records\n"
                 << "3 View consumption summary\n"
                 << "4 Save and exit\n"
                 << "Choice: ";
            if (!(cin >> choice)) {
                cout << "Please enter a number from 1 to 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
                case 1: addRecord(); break;
                case 2: listRecords(); break;
                case 3: showSummary(); break;
                case 4: saveRecords(); break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    WaterTracker tracker;
    tracker.run();
    return 0;
}