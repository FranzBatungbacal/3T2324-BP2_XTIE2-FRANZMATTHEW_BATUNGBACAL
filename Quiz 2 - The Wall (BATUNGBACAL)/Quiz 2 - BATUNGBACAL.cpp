#include <iostream>
#include <string>
#include <random>

using namespace std;

int randomRange(int _min, int _max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(_min, _max);
    return distrib(gen);
}

struct Node {
    string data;
    Node* next;

    Node(string value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList() : head(nullptr) {}

    void addNode(const string& data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            head->next = head;
        }
        else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void display() const {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    void passCloak(int& memberAmt) {
        if (!head) return;

        int randNumber = randomRange(1, memberAmt);
        Node* current = head;
        Node* prev = nullptr;

        for (int i = 0; i < randNumber - 1; ++i) {
            prev = current;
            current = current->next;
        }

        cout << "Result:" << endl << endl;
        cout << "Member " << current->data << " has been eliminated." << endl << endl;

        if (current == head && current->next == head) {
            delete current;
            head = nullptr;
        }
        else {
            if (current == head) {
                head = head->next;
            }
            if (prev) {
                prev->next = current->next;
            }
            delete current;
        }

        memberAmt--;
    }

    void playGame(int& memberAmt) {
        int round = 1;

        while (memberAmt > 1) {
            cout << "= = = = = = = = = = = = = = =" << endl << endl;
            cout << "Round: " << round << " :" << endl << endl;
            cout << "Team Members:" << endl;
            display();
            passCloak(memberAmt);
            round++;
        }

        if (head) {
            cout << endl << "= = = = = = = = = = = = = = =" << endl << endl;
            cout << "Result: " << endl;
            cout << head->data << " will seek help!" << endl;
            cout << endl << "= = = = = = = = = = = = = = =" << endl;
        }
    }
};

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

int main() {
    int memberAmt;
    string memberName;

    cout << "How many members are in your team? " << endl;
    cin >> memberAmt;

    CircularLinkedList teamList;

    cout << "What are your names?" << endl;
    for (int i = 0; i < memberAmt; ++i) {
        cin >> memberName;
        teamList.addNode(memberName);
    }

    clearScreen();

    teamList.playGame(memberAmt);

    return 0;
}
