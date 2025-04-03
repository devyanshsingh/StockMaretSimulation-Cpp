#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct Node {
    int stockId;
    string stockName;
    float price;
    int quantity;
    Node* next;
    Node* prev;
};

struct OrderNode {
    int stockId;
    string stockName;
    int quantity;
    OrderNode* next;
};

class Queue {
    OrderNode* front;
    OrderNode* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void insert(int id, string name, int quantity) {
        OrderNode* newNode = new OrderNode{ id, name, quantity, nullptr };
        if (!newNode) {
            cerr << "Memory allocation failed in Queue::insert()\n";
            return;
        }
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }
        OrderNode* temp = front;
        cout << "Element to be deleted is: " << front->stockId << " "
            << front->stockName << " " << front->quantity << endl;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void peek() {
        if (front != nullptr) {
            cout << front->stockId << " " << front->stockName << " " << front->quantity << endl;
        }
        else {
            cout << "Queue is empty." << endl;
        }
    }

    void display() {
        OrderNode* temp = front;
        while (temp != nullptr) {
            cout << temp->stockId << " " << temp->stockName << " " << temp->quantity << endl;
            temp = temp->next;
        }
    }

    int getId() {
        if (front != nullptr) {
            return front->stockId;
        }
        else {
            cout << "Queue is empty." << endl;
            return -1;
        }
    }

    int getQty() {
        if (front != nullptr) {
            return front->quantity;
        }
        else {
            cout << "Queue is empty." << endl;
            return -1;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    bool isStockIdUnique(int stockId) {
        Node* temp = head;
        while (temp) {
            if (temp->stockId == stockId) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void insertBeg(int stockId, string stockName, float price, int quantity) {
        if (!isStockIdUnique(stockId)) {
            cout << "Stock ID must be unique, Try again.\n";
            return;
        }
        Node* newNode = new Node{ stockId, stockName, price, quantity, nullptr, nullptr };
        if (!newNode) {
            cerr << "Memory allocation failed\n";
            return;
        }
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << "Stock added at the beginning.\n";
    }

    void insertEnd(int stockId, string stockName, float price, int quantity) {
        if (!isStockIdUnique(stockId)) {
            cout << "Stock ID must be unique, Try again.\n";
            return;
        }
        Node* newNode = new Node{ stockId, stockName, price, quantity, nullptr, nullptr };
        if (!newNode) {
            cerr << "Memory allocation failed in DoublyLinkedList::insertEnd()\n";
            return;
        }
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Stock added at the end.\n";
    }

    void insertPos(int stockId, string stockName, float price, int quantity, int position) {
        if (!isStockIdUnique(stockId)) {
            cout << "Stock ID must be unique, Try again.\n";
            return;
        }
        if (position <= 1 || !head) {
            insertBeg(stockId, stockName, price, quantity);
            return;
        }
        Node* newNode = new Node{ stockId, stockName, price, quantity, nullptr, nullptr };
        if (!newNode) {
            cerr << "Memory allocation failed in DoublyLinkedList::insertPos()\n";
            return;
        }
        Node* temp = head;
        for (int i = 1; temp && i < position - 1; i++) {
            temp = temp->next;
        }
        if (!temp || !temp->next) {
            insertEnd(stockId, stockName, price, quantity);
        }
        else {
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            cout << "Stock added at position " << position << ".\n";
        }
    }

    void deleteBeg() {
        if (!head) {
            cout << "List is Empty.\n";
            return;
        }
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        delete temp;
        cout << "Stock deleted from the beginning.\n";
    }

    void deleteEnd() {
        if (!head) {
            cout << "List is Empty.\n";
            return;
        }
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        cout << "Stock deleted from the end.\n";
    }

    void deletePos(int position) {
        if (!head) {
            cout << "List is Empty.\n";
            return;
        }
        if (position <= 1) {
            deleteBeg();
            return;
        }

        Node* temp = head;
        for (int i = 1; temp && i < position; i++) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position out of bounds.\n";
            return;
        }

        if (!temp->next) {
            deleteEnd();
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            cout << "Stock deleted from pos " << position << ".\n";
        }
    }

    Node* searchById(int stockId) {
        Node* temp = head;
        while (temp) {
            if (temp->stockId == stockId) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    Node* searchByPosition(int position) {
        if (position < 1) {
            cout << "Invalid position. Position must be >= 1.\n";
            return nullptr;
        }
        Node* temp = head;
        for (int i = 1; temp && i < position; i++) {
            temp = temp->next;
        }
        return temp;
    }

    int countNodes() {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void displayStocks() {
        if (!head) {
            cout << RED << "\nEmpty\n" << RESET;
            return;
        }

        cout << BLUE << "\nAvailable Stocks:\n" << RESET;
        cout << CYAN;
        cout << setw(10) << "Stock ID" << setw(20) << "Stock Name"
            << setw(10) << "Price" << setw(15) << "Quantity\n";
        cout << string(55, '-') << RESET << "\n";

        Node* temp = head;
        while (temp) {
            if (temp->stockId % 2 == 0)
                cout << GREEN;
            else
                cout << YELLOW;

            cout << setw(10) << temp->stockId << setw(20) << temp->stockName
                << setw(10) << fixed << setprecision(2) << temp->price
                << setw(15) << temp->quantity << RESET << "\n";

            temp = temp->next;
        }
    }

    void placeOrder(int stockId, int quantity, Queue& portfolio) {
        if (quantity <= 0) {
            cout << "Quantity must be positive to place an order.\n";
            return;
        }
        Node* stock = searchById(stockId);
        if (!stock) {
            cout << "Stock ID not found.\n";
            return;
        }
        if (quantity > stock->quantity) {
            cout << "Not enough stock available.\n";
            return;
        }
        portfolio.insert(stockId, stock->stockName, quantity);
        stock->quantity -= quantity;
        cout << "Order placed successfully.\n";
    }

    void executeOrder(Queue& portfolio) {
        if (portfolio.isEmpty()) {
            cout << "No orders to execute" << endl;
            return;
        }

        int id, qty;
        id = portfolio.getId();
        qty = portfolio.getQty();
        Node* stock = searchById(id);
        if (stock == nullptr) {
            cout << "Stock not found" << endl;
            portfolio.pop();
            return;
        }

        portfolio.pop();
        cout << "Order executed successfully.  Stock " << stock->stockName << " quantity adjusted.\n";
    }

    Node* binarySearch(int stockId) {
        int left = 1;
        int right = countNodes();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            Node* midNode = searchByPosition(mid);

            if (midNode == nullptr) {
                return nullptr;
            }

            if (midNode->stockId == stockId) {
                return midNode;
            }
            else if (midNode->stockId < stockId) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return nullptr;
    }

    Node* binarySearchRecursive(int stockId) {
        return binarySearchRecursiveHelper(stockId, 1, countNodes());
    }


    void selectionSortByPrice() {
        if (!head || head == tail) {
            return;
        }

        Node* current = head;
        while (current) {
            Node* minNode = current;
            Node* temp = current->next;

            while (temp) {
                if (temp->price < minNode->price) {
                    minNode = temp;
                }
                temp = temp->next;
            }

            if (minNode != current) {
                swap(current->stockId, minNode->stockId);
                swap(current->stockName, minNode->stockName);
                swap(current->price, minNode->price);
                swap(current->quantity, minNode->quantity);
            }
            current = current->next;
        }
        cout << "Stocks sorted by price.\n";
    }

    void quickSortByStockId() {
        quickSortHelper(head, tail);
        cout << "Stocks sorted by Stock ID using Quick Sort.\n";
    }

private:
    Node* binarySearchRecursiveHelper(int stockId, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int mid = left + (right - left) / 2;
        Node* midNode = searchByPosition(mid);

        if (midNode == nullptr) {
            return nullptr;
        }

        if (midNode->stockId == stockId) {
            return midNode;
        }
        else if (midNode->stockId < stockId) {
            return binarySearchRecursiveHelper(stockId, mid + 1, right);
        }
        else {
            return binarySearchRecursiveHelper(stockId, left, mid - 1);
        }
    }

    Node* partition(Node* low, Node* high) {
        int pivot = high->stockId;
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if (j->stockId < pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i->stockId, j->stockId);
                swap(i->stockName, j->stockName);
                swap(i->price, j->price);
                swap(i->quantity, j->quantity);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i->stockId, high->stockId);
        swap(i->stockName, high->stockName);
        swap(i->price, high->price);
        swap(i->quantity, high->quantity);
        return i;
    }

    void quickSortHelper(Node* low, Node* high) {
        if (high != nullptr && low != high && low != high->next) {
            Node* p = partition(low, high);
            quickSortHelper(low, p->prev);
            quickSortHelper(p->next, high);
        }
    }
};

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

float getFloatInput(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    DoublyLinkedList stocks;
    Queue portfolio;
    int choice;

    do {
        cout << "\n=== Stock Management System ===\n";
        cout << "1. Add Stock\n";
        cout << "2. Delete Stock\n";
        cout << "3. Search Stock by ID\n";
        cout << "4. Search Stock by Position\n";
        cout << "5. Count Stocks\n";
        cout << "6. Display Stocks\n";
        cout << "7. Place Order\n";
        cout << "8. Portfolio\n";
        cout << "9. Execute Order\n";
        cout << "10. Binary Search Stock by ID (Iterative)\n";
        cout << "11. Binary Search Stock by ID (Recursive)\n";
        cout << "12. Sort Stocks by Price\n";
        cout << "13. Quick Sort Stocks by ID\n";
        cout << "14. Exit\n";
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
        case 1: {
            int stockId, quantity, position;
            string stockName;
            float price;

            stockId = getIntInput("\nEnter Stock ID: ");

            cout << "Enter Stock Name: ";
            getline(cin, stockName);

            price = getFloatInput("Enter Stock Price: ");

            quantity = getIntInput("Enter Stock Quantity: ");
            if (quantity <= 0) {
                cout << "Quantity must be positive.\n";
                break;
            }

            cout << "Choose insertion position:\n";
            cout << "1. Beginning\n";
            cout << "2. End\n";
            cout << "3. Specific Position\n";
            int insertChoice = getIntInput("Enter your choice: ");

            if (insertChoice == 1) {
                stocks.insertBeg(stockId, stockName, price, quantity);
            }
            else if (insertChoice == 2) {
                stocks.insertEnd(stockId, stockName, price, quantity);
            }
            else if (insertChoice == 3) {
                position = getIntInput("Enter position: ");
                if (position <= 0) {
                    cout << "Position must be positive.\n";
                    break;
                }
                stocks.insertPos(stockId, stockName, price, quantity, position);
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 2: {
            cout << "Choose deletion position:\n";
            cout << "1. Beginning\n";
            cout << "2. End\n";
            cout << "3. Specific Position\n";
            int deleteChoice = getIntInput("Enter your choice: ");
            if (deleteChoice == 1) {
                stocks.deleteBeg();
            }
            else if (deleteChoice == 2) {
                stocks.deleteEnd();
            }
            else if (deleteChoice == 3) {
                int position = getIntInput("Enter position: ");
                if (position <= 0) {
                    cout << "Position must be positive.\n";
                    break;
                }
                stocks.deletePos(position);
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 3: {
            int stockId = getIntInput("Enter Stock ID to search: ");
            Node* stock = stocks.searchById(stockId);
            if (stock) {
                cout << GREEN << "Stock found: " << RESET
                    << CYAN << setw(10) << stock->stockId << setw(20) << stock->stockName
                    << setw(10) << fixed << setprecision(2) << stock->price
                    << setw(15) << stock->quantity << RESET << "\n";
            }
            else {
                cout << RED << "Stock ID not found.\n" << RESET;
            }
            break;
        }
        case 4: {
            int position = getIntInput("Enter position to search: ");
            Node* stock = stocks.searchByPosition(position);
            if (stock) {
                cout << GREEN << "Stock found at position " << position << ": " << RESET
                    << CYAN << setw(10) << stock->stockId << setw(20) << stock->stockName
                    << setw(10) << fixed << setprecision(2) << stock->price
                    << setw(15) << stock->quantity << RESET << "\n";
            }
            else {
                cout << RED << "No stock found at that position.\n" << RESET;
            }
            break;
        }
        case 5: {
            int count = stocks.countNodes();
            cout << GREEN << "Total number of stocks: " << count << RESET << "\n";
            break;
        }
        case 6:
            stocks.displayStocks();
            break;
        case 7: {
            int stockId = getIntInput("Enter Stock ID to place order: ");
            int quantity = getIntInput("Enter quantity to order: ");
            stocks.placeOrder(stockId, quantity, portfolio);
            break;
        }
        case 8:
            cout << "\nPortfolio:\n";
            portfolio.display();
            break;
        case 9:
            stocks.executeOrder(portfolio);
            break;
        case 10: {
            int stockId = getIntInput("Enter Stock ID to search (Binary Search - Iterative): ");
            Node* stock = stocks.binarySearch(stockId);
            if (stock) {
                cout << GREEN << "Stock found (Binary Search - Iterative): " << RESET
                    << CYAN << setw(10) << stock->stockId << setw(20) << stock->stockName
                    << setw(10) << fixed << setprecision(2) << stock->price
                    << setw(15) << stock->quantity << RESET << "\n";
            }
            else {
                cout << RED << "Stock ID not found (Binary Search - Iterative).\n" << RESET;
            }
            break;
        }
        case 11: {
            int stockId = getIntInput("Enter Stock ID to search (Binary Search - Recursive): ");
            Node* stock = stocks.binarySearchRecursive(stockId);
            if (stock) {
                cout << GREEN << "Stock found (Binary Search - Recursive): " << RESET
                    << CYAN << setw(10) << stock->stockId << setw(20) << stock->stockName
                    << setw(10) << fixed << setprecision(2) << stock->price
                    << setw(15) << stock->quantity << RESET << "\n";
            }
            else {
                cout << RED << "Stock ID not found (Binary Search - Recursive).\n" << RESET;
            }
            break;
        }
        case 12:
            stocks.selectionSortByPrice();
            break;
        case 13:
            stocks.quickSortByStockId();
            break;
        case 14:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 14);

    return 0;
}
