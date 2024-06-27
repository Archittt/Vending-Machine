#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Product class to represent a product in the vending machine
class Product {
public:
    Product(const string& name, double price, const string& icon)
        : name_(name), price_(price), icon_(icon) {}

    const string& getName() const {
        return name_;
    }

    double getPrice() const {
        return price_;
    }

    const string& getIcon() const {
        return icon_;
    }

private:
    string name_;
    double price_;
    string icon_;
};

// VendingMachine class to represent the vending machine
class VendingMachine {
public:
    VendingMachine(const vector<Product>& products)
        : products_(products) {}

    // Display the products available in the vending machine
    void displayProducts() const {
        cout << "==============================" << endl;
        cout << "|       VENDING MACHINE      |" << endl;
        cout << "==============================" << endl;
        cout << "|       PRODUCTS MENU        |" << endl;
        cout << "==============================" << endl;
        for (int i = 0; i < products_.size(); ++i) {
            cout << "| " << i + 1 << ". " << products_[i].getIcon() << "  " << setw(10) << left << products_[i].getName() << "  $" << setw(4) << right << fixed << setprecision(2) << products_[i].getPrice() << " |" << endl;
        }
        cout << "==============================" << endl;
    }

    // Process the user's choice and return the selected product
    Product selectProduct(int choice) const {
        if (choice < 1 || choice > products_.size()) {
            throw invalid_argument("Invalid choice.");
        }
        return products_[choice - 1];
    }

    // Check if payment is sufficient for the selected product
    bool checkPayment(double payment, const Product& product) const {
        return payment >= product.getPrice();
    }

    // Calculate and return the change due to the user
    double calculateChange(double payment, const Product& product) const {
        return payment - product.getPrice();
    }

private:
    vector<Product> products_;
};

int main() {
    // Define the products available in the vending machine
    vector<Product> products = {
        Product("Cola", 1.25, "  C  "),
        Product("Chips", 0.75, "  @  "),
        Product("Candy", 0.50, "  &  ")
    };

    // Create a vending machine object
    VendingMachine vendingMachine(products);

    // Display the products available in the vending machine
    vendingMachine.displayProducts();

    // Get the user's choice
    int choice;
    cout << "Please enter the number of your choice: ";
    cin >> choice;

    // Process the user's choice
    try {
        Product selectedProduct = vendingMachine.selectProduct(choice);
        cout << "You have selected " << selectedProduct.getName() << ". The price is $" << selectedProduct.getPrice() << "." << endl;

        // Ask the user for payment
        double payment;
        cout << "Please insert payment: $";
        cin >> payment;

        // Check if payment is sufficient
        if (vendingMachine.checkPayment(payment, selectedProduct)) {
            double change = vendingMachine.calculateChange(payment, selectedProduct);
            cout << "Thank you for your purchase. Your change is $" << change << "." << endl;
        } else {
            cout << "Insufficient payment. Please try again." << endl;
        }
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}