#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Order {
    int order_id;
    string item;
    string address;
    int urgency;
    int time;

    // [NEW] Updated constructor to include address
    Order(int id, string item, string addr, int urg, int time)
        : order_id(id), item(item), address(addr), urgency(urg), time(time) {}
};

struct order_comp {
    bool operator()(const Order & o1, const Order & o2) const {
        if (o1.urgency != o2.urgency) {
            return o1.urgency < o2.urgency;
        }
        return o1.time > o2.time;
    }
};

class order_sys {
    private:
    priority_queue<Order, vector<Order>, order_comp> pq;
    int curr_time;

    public:
    order_sys() {
        curr_time = 0;
    }


    void add_order(int id, string item, string address, int urgency) {
        curr_time++;
        Order new_ord(id, item, address, urgency, curr_time);
        pq.push(new_ord);

        string urgencyStr = (urgency == 3) ? "High" : (urgency == 2) ? "Medium" : "Low";
        cout << "> Order Added: #" << id << " - " << item << " (Urgency: " << urgencyStr << ")" << endl;
    }

    void proc_next_ord() {
        if (pq.empty()) {
            cout << "Order List Empty" << endl;
            return;
        }

        Order top_ord = pq.top();
        pq.pop();


        cout << "Preparing & Dispatching: #" << top_ord.order_id<< " - " << top_ord.item << endl;
        cout << "  > Delivering to: " << top_ord.address << endl;
    }

    bool hasOrders() const {
        return !pq.empty();
    }
};

int main() {
    order_sys kitchen;
    int id, urgency;
    string item, address;
    char choice;

    cout << "Kitchen Order Management System" << endl;

    do {
        cout << "\nEnter Order ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a numeric Order ID: ";
        }


        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Food Item: ";
        getline(cin, item);

        cout << "Enter Delivery Address: ";
        getline(cin, address);

        cout << "Enter Urgency (3 = High/VIP, 2 = Medium, 1 = Low): ";
        while (!(cin >> urgency)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1, 2, or 3): ";
        }

        kitchen.add_order(id, item, address, urgency);

        cout << "\nDo you want to add another order? (y/n): ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'y' || choice == 'Y');

    cout << "\n--- Processing Orders ---" << endl;

    if (!kitchen.hasOrders()) {
        cout << "No orders were placed." << endl;
    } else {
        while (kitchen.hasOrders()) {
            kitchen.proc_next_ord();
        }
    }

    cout << "\nAll orders dispatched!" << endl;

    return 0;
}