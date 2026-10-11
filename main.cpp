#include <iostream>
#include <vector>
#include <string>
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

    double total() {
        return price * quantity;
    }
};

class Cart {
public:
    vector<CartItem> items;
    double budget;

    Cart(double b) {
        budget = b;
    }

    double subtotal() {
        double sum = 0;

        for (int i = 0; i < items.size(); i++) {
            sum += items[i].total();
        }

        return sum;
    }

    void addProduct() {
        string name;
        double price;
        int quantity;

        cout << "Enter product name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter price: ";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        if (price < 0 || quantity <= 0) {
            cout << "Invalid details!\n";
            return;
        }

        if (subtotal() + price * quantity > budget) {
            cout << "Budget exceeded! Product not added.\n";
            return;
        }

        items.push_back(CartItem(name, price, quantity));
        cout << "Product added!\n";
    }

    void viewCart() {
        if (items.empty()) {
            cout << "Cart is empty.\n";
            return;
        }

        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].name
                 << " Price: " << items[i].price
                 << " Quantity: " << items[i].quantity
                 << " Total: " << items[i].total() << endl;
        }

        cout << "Subtotal: " << subtotal() << endl;
    }

    void removeProduct() {
        int number;
        viewCart();

        cout << "Enter product number to remove: ";
        cin >> number;

        if (number >= 1 && number <= items.size()) {
            items.erase(items.begin() + number - 1);
            cout << "Product removed!\n";
        } else {
            cout << "Invalid product number!\n";
        }
    }

    void changeQuantity() {
        int number, quantity;
        viewCart();

        cout << "Enter product number: ";
        cin >> number;

        if (number < 1 || number > items.size()) {
            cout << "Invalid product number!\n";
            return;
        }

        cout << "Enter new quantity: ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "Invalid quantity!\n";
            return;
        }

        double newTotal = subtotal()
            - items[number - 1].total()
            + items[number - 1].price * quantity;

        if (newTotal > budget) {
            cout << "Budget exceeded!\n";
            return;
        }

        items[number - 1].quantity = quantity;
        cout << "Quantity updated!\n";
    }
};

int main() {
    double budget;
    int choice;

    cout << "Enter your budget: ";
    cin >> budget;

    if (budget < 0) {
        cout << "Invalid budget!\n";
        return 0;
    }

    Cart cart(budget);

    do {
        cout << "\n--- SHOPPING CART ---\n";
        cout << "1. Add Product\n";
        cout << "2. View Cart\n";
        cout << "3. Remove Product\n";
        cout << "4. Change Quantity\n";
        cout << "5. View Subtotal\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

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
                cout << "Subtotal: " << cart.subtotal() << endl;
                break;

            case 0:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
