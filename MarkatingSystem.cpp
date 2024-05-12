#include<iostream>
#include<fstream>
#include <vector>

using namespace std;

class shopping{
    private:
        int pcode;
        float price;
        float dis;
        string pname;

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void shopping::menu() {
    int choice;
    string email;
    string password;

    do {
        cout << "\t\t\t\t_______________________________\n";
        cout << "\t\t\t\t                               \n";
        cout << "\t\t\t\t     Supermarket main menu     \n";
        cout << "\t\t\t\t                               \n";
        cout << "\t\t\t\t_______________________________\n";
        cout << "\t\t\t\t|       1)Administrator       |\n";
        cout << "\t\t\t\t|       2)Buyer               |\n";
        cout << "\t\t\t\t|       3)Exit                |\n";
        cout << "\t\t\t\t|_____________________________|\n";
        cout << "\t\t\t\tPlease select\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\t\t\t\tPlease Login\n";
            cout << "\t\t\t\tEnter Email\n";
            cin >> email;
            cout << "\t\t\t\tPassword\n";
            cin >> password;

            if (email == "sanjay@gmail.com" && password == "123") {
                administrator();
            } else {
                cout << "\t\t\t\tInvalid Email or password\n";
            }
            break;
        case 2:
            buyer();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\t\t\t\tPlease select from the given options\n";
            break;
        }
    } while (choice != 3);
}

void shopping::administrator() {
    int choice;
    bool continueMenu = true;

    do {
        cout << "\t\t\t\tAdministrator Menu\n";
        cout << "\t\t\t\t1) Add Product\n";
        cout << "\t\t\t\t2) Modify Product\n";
        cout << "\t\t\t\t3) Delete Product\n";
        cout << "\t\t\t\t4) Back to Main Menu\n";
        cout << "\t\t\t\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add(); // Function to add a product
            break;
        case 2:
            edit(); // Function to modify a product
            break;
        case 3:
            rem(); // Function to remove a product
            break;
        case 4:
            continueMenu = false; // Exit the administrator menu
            break;
        default:
            cout << "\t\t\t\tPlease select from the given options\n";
            break;
        }
    } while (continueMenu);
}

void shopping::buyer() {
    int choice;
    bool continueMenu = true;

    do {
        cout << "\t\t\t\tBuyer Menu\n";
        cout << "\t\t\t\t1) Buy product\n";
        cout << "\t\t\t\t2) Go back\n";
        cout << "\t\t\t\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            receipt(); // Function to handle the receipt and purchase process
            break;
        case 2:
            continueMenu = false; // Exit the buyer menu and return to main menu
            break;
        default:
            cout << "\t\t\t\tInvalid choice, please try again.\n";
            break;
        }
    } while (continueMenu);
}


void shopping::add() {
    fstream data;
    int token = 0;
    float p, d;
    string n;
    int c;

    cout << "\t\t\t\tAdd New Product\n";
    cout << "\t\t\t\tProduct Code: ";
    cin >> pcode;
    cout << "\t\t\t\tName of the Product: ";
    cin.ignore(); // To ignore the newline character left in the buffer
    getline(cin, pname); // Handles spaces in product names
    cout << "\t\t\t\tPrice of the Product: ";
    cin >> price;
    cout << "\t\t\t\tDiscount on the Product (%): ";
    cin >> dis;

    // Open the database file in input mode to check for existing product codes
    data.open("database.txt", ios::in);
    if (data) { // Check if file successfully opened
        while (data >> c >> n >> p >> d) {
            if (c == pcode) {
                token = 1;
                break;
            }
        }
        data.close(); // Close the file after reading
    }

    if (token == 1) {
        cout << "\t\t\t\tProduct Code already exists. Please use a different code.\n";
    } else {
        // Open the database file in append mode to add new product
        data.open("database.txt", ios::app | ios::out);
        if (data) {
            data << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
            cout << "\t\t\t\tProduct successfully added!\n";
        } else {
            cout << "\t\t\t\tError opening file to save data.\n";
        }
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey, token = 0;
    int c;
    float p, d;
    string n;

    cout << "\t\t\t\tModify the Record\n";
    cout << "\t\t\t\tProduct Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\t\t\t\tFile doesn't exist or cannot be opened!\n";
        return;
    }

    // We use a temporary file to write all changes, including the edited one
    data1.open("database1.txt", ios::out);
    if (!data1) {
        cout << "\t\t\t\tCannot open temporary file for writing!\n";
        data.close();
        return;
    }

    while (data >> c >> n >> p >> d) {
        if (c == pkey) {
            cout << "\t\t\t\tCurrent Name: " << n << endl;
            cout << "\t\t\t\tCurrent Price: " << p << endl;
            cout << "\t\t\t\tCurrent Discount: " << d << "%" << endl;

            cout << "\t\t\t\tEnter new name (or '.' to keep): ";
            cin.ignore(); // Clear the input buffer
            getline(cin, n);
            if (n == ".") {
                data.clear(); // Reset the stream state
                data.seekg(0); // Return to the beginning of the file
                while (data >> c >> n >> p >> d && c != pkey); // Read until the product again
            }

            cout << "\t\t\t\tEnter new price (or -1 to keep): ";
            cin >> p;
            if (p == -1) {
                data.clear();
                data.seekg(0);
                while (data >> c >> n >> p >> d && c != pkey);
            }

            cout << "\t\t\t\tEnter new discount (or -1 to keep): ";
            cin >> d;
            if (d == -1) {
                data.clear();
                data.seekg(0);
                while (data >> c >> n >> p >> d && c != pkey);
            }

            // Write the updated details to the temporary file
            data1 << c << " " << n << " " << p << " " << d << "\n";
            token++;
        } else {
            data1 << c << " " << n << " " << p << " " << d << "\n"; // Write other records unchanged
        }
    }

    data.close();
    data1.close();

    // Remove the original file and rename the temporary file to original name
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "\t\t\t\tNo record found with the given product code!\n";
    } else {
        cout << "\t\t\t\tRecord updated successfully.\n";
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey, token = 0;
    int c;
    float p, d;
    string n;

    cout << "\t\t\t\tDelete Product\n";
    cout << "\t\t\t\tEnter Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\t\t\t\tFile does not exist or cannot be opened!\n";
        return;
    }

    data1.open("database1.txt", ios::out);
    if (!data1) {
        cout << "\t\t\t\tCannot open temporary file for writing!\n";
        data.close();
        return;
    }

    while (data >> c >> n >> p >> d) {
        if (c != pkey) {
            // Write all products except the one to delete
            data1 << c << " " << n << " " << p << " " << d << "\n";
        } else {
            token = 1;  // Product found and will be deleted
        }
    }

    data.close();
    data1.close();

    // Replace the original file with the updated file
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "\t\t\t\tNo product found with code " << pkey << ".\n";
    } else {
        cout << "\t\t\t\tProduct deleted successfully.\n";
    }
}
void shopping::list() {
    ifstream data("database.txt");
    int c;
    float p, d;
    string n;

    cout << "\t\t\t\t_____________________________\n";
    cout << "\t\t\t\tProduct Listing\n";
    cout << "\t\t\t\t_____________________________\n";
    cout << "\t\t\t\tCode\tName\t\tPrice\tDiscount\n";
    cout << "\t\t\t\t_____________________________\n";

    if (!data) {
        cout << "\t\t\t\tError: Unable to open the file or the file is empty.\n";
        return;
    }

    while (data >> c >> n >> p >> d) {
        cout << "\t\t\t\t" << c << "\t" << n << "\t\t" << p << "\t" << d << "%\n";
    }

    data.close();
    cout << "\t\t\t\t_____________________________\n";
}

void shopping::receipt() {
    ifstream data;
    int productCode;
    int quantity;
    char choice;
    string n;  // Product name
    float p;   // Product price
    float d;   // Product discount
    vector<int> productCodes;
    vector<int> quantities;
    bool validCode;

    cout << "\n\t\t\t\tReceipt\n";
    cout << "\t\t\t\tAvailable Products:\n";
    list(); // Display list of all products

    do {
        cout << "\n\t\t\t\tEnter the product code: ";
        cin >> productCode;
        validCode = false;

        // Check if the product code exists in the database
        data.open("database.txt");
        if (!data) {
            cout << "\t\t\t\tFailed to open product database.\n";
            return;
        }

        int c;
        string n;
        float p, d;
        while (data >> c >> n >> p >> d) {
            if (c == productCode) {
                validCode = true;
                break;
            }
        }
        data.close();

        if (!validCode) {
            cout << "\t\t\t\tInvalid product code, please try again.\n";
            continue;
        }

        cout << "\n\t\t\t\tEnter quantity: ";
        cin >> quantity;

        productCodes.push_back(productCode);
        quantities.push_back(quantity);

        cout << "\n\t\t\t\tDo you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Generating the receipt
    cout << "\n\t\t\t\t----------Receipt Details----------\n";
    cout << "\t\t\t\tCode\tName\tQuantity\tPrice\tTotal\n";

    float total = 0;
    for (size_t i = 0; i < productCodes.size(); i++) {
        data.open("database.txt");
        while (data >> productCode >> n >> p >> d) {
            if (productCode == productCodes[i]) {
                float discountedPrice = p - (p * d / 100);
                float cost = quantities[i] * discountedPrice;
                total += cost;
                cout << "\t\t\t\t" << productCode << "\t" << n << "\t" << quantities[i] << "\t" << p << "\t" << cost << "\n";
                break;
            }
        }
        data.close();
    }

    cout << "\t\t\t\tTotal Amount: " << total << "\n";
}

int main(){
    shopping s;
    s.menu();
    return 0;
}
