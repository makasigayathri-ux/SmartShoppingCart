
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class CartItem {
public:
    string name;
    double price;
    int quantity;

    CartItem(string n, double p, int q) {
        name = n;
        price = p;
        quantity = q;
    }

    double getTotal() const {
        return price * quantity;
    }
};

class Cart {
private:
    vector<CartItem> items;
    double budget;

public:
    Cart(double b) {
        budget = b;
    }

    double calculateSubtotal() const {
        double total = 0;

        for (size_t i = 0; i < items.size(); i++) {
            total += items[i].getTotal();
        }

        return total;
    }

    void addProduct() {
        string name;
        double price;
        int quantity;

        cout << "Enter product name: ";
        getline(cin >> ws, name);

        cout << "Enter price: Rs. ";
        if (!(cin >> price) || price < 0) {
            cout << "Invalid price!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter quantity: ";
        if (!(cin >> quantity) || quantity <= 0) {
            cout << "Invalid quantity!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        double total = calculateSubtotal() + price * quantity;

        if (total > budget) {
            cout << "Warning: Budget exceeded! Product not added.\n";
            cout << "Your budget: Rs. " << budget << '\n';
            cout << "Expected total: Rs. " << total << '\n';
            return;
        }

        items.push_back(CartItem(name, price, quantity));
        cout << "Product added successfully!\n";
    }

    void viewCart() const {
        if (items.empty()) {
            cout << "\nYour cart is empty.\n";
            return;
        }

        cout << fixed << setprecision(2);
        cout << "\n-------- SHOPPING CART --------\n";

        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].name
                 << " | Price: Rs. " << items[i].price
                 << " | Quantity: " << items[i].quantity
                 << " | Total: Rs. " << items[i].getTotal()
                 << '\n';
        }

        cout << "Subtotal: Rs. " << calculateSubtotal() << '\n';
        cout << "Budget: Rs. " << budget << '\n';
        cout << "Remaining: Rs. "
             << budget - calculateSubtotal() << '\n';
    }

    void removeProduct() {
        int position;

        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        viewCart();
        cout << "Enter product number to remove: ";

        if (!(cin >> position)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (position < 1 ||
            position > static_cast<int>(items.size())) {
            cout << "Invalid product number!\n";
            return;
        }

        items.erase(items.begin() + position - 1);
        cout << "Product removed successfully!\n";
    }

    void changeQuantity() {
        int position, quantity;

        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        viewCart();
        cout << "Enter product number: ";

        if (!(cin >> position)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (position < 1 ||
            position > static_cast<int>(items.size())) {
            cout << "Invalid product number!\n";
            return;
        }

        cout << "Enter new quantity: ";

        if (!(cin >> quantity) || quantity <= 0) {
            cout << "Quantity must be greater than zero!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        CartItem& item = items[position - 1];

        double newTotal = calculateSubtotal()
                        - item.getTotal()
                        + item.price * quantity;

        if (newTotal > budget) {
            cout << "Warning: Budget exceeded! Quantity unchanged.\n";
            return;
        }

        item.quantity = quantity;
        cout << "Quantity updated successfully!\n";
    }
};

int main() {
    double budget;

    cout << "===== SMART SHOPPING CART =====\n";
    cout << "Enter your budget (Rs.): ";

    if (!(cin >> budget) || budget < 0) {
        cout << "Invalid budget!\n";
        return 1;
    }

    Cart cart(budget);
    int choice = 0;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Add Product\n";
        cout << "2. View Cart\n";
        cout << "3. Remove Product\n";
        cout << "4. Change Quantity\n";
        cout << "5. View Subtotal\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cart.addProduct();
                break;

            case 2:
                cart.viewCart();
                break;

            case 3:
                cart.removeProduct();
                break;

            case 4:
                cart.changeQuantity();
                break;

            case 5:
                cout << fixed << setprecision(2);
                cout << "Subtotal: Rs. "
                     << cart.calculateSubtotal() << '\n';
                break;

            case 6:
                cout << "Thank you for shopping!\n";
                break;

            default:
                cout << "Invalid choice! Select 1 to 6.\n";
        }

    } while (choice != 6);

    return 0;
}
