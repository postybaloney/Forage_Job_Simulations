#include <vector>
#include <string>
#include<iostream>
#include <utility>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(
            std::string name,
            int quantity,
            float price
    ) :
            name{std::move(name)},
            quantity{quantity},
            price{price} {

    }

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string &other) {
        return name == other;
    }
};

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;
    float total_money = 0;

    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

    auto find_item(const std::string& name) {
        return std::find_if(items.begin(), items.end(), [&](const auto& item) {
            return item->is_match(name)
        });
    }

public:
    Inventory() :
            items{},
            total_money{0} {
    }
    
    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        items.push_back(std::make_unique<Item>(name, quantity, price));
    }

    void sell_item() {
        int quantity_to_sell;
        std::string item_to_check;
        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> item_to_check;
        std::cout << "\nEnter how many you want to sell: ";
        std::cin >> quantity_to_sell;

        auto it = find_item(item_to_check);
        if(it == items.end()){
            std::cout << "\nThis item is not in your Inventory";
        }

        Item& item = **it;
        if (quantity_to_sell > item.get_quantity()) {
            std::cerr << "\nInsufficient quantity to sell.\n";
            return;
        }

        item.set_quantity(item.get_quantity() - quantity_to_sell);
        total_money += quantity_to_sell * item.get_price();
        std::cout << "\nSold " << quantity_to_sell << " of " << item_to_check;

        if(item.get_quantity() == 0) {
            items.erase(it);
            std::cout << "\nItem removed from inventory";
        }
    }

    void list_items() {
        if (items.empty()) {
            std::cout << "\nInventory empty.";
            return;
        }

        std::cout << "\nInventory: ";
        for (const auto& item : items) {
            display_data(*item);
            std::cout << "\n";
        }
    }
};

// no need to modify anything here
int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (1) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                exit(0);

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
