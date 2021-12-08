#include <iostream>
using namespace std;
int get_integer_value()
{
    int number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n') {};
        cout << "Некорректное значение. Попробуйте снова: ";
    }
    return number;
}
double get_value()
{
    double number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n') {};
        cout << "Некорректное значение. Попробуйте снова: ";
    }
    return number;
}
struct Node {
    double value;
    Node* next;
};

struct List {
    Node* start = nullptr;
    Node* finish = nullptr;
    int number = 0;
};

void add_last(List& list, double newValue) {
    Node* newNode = new Node;
    newNode->value = newValue;
    newNode->next = nullptr;

    if (list.number == 0) {
        list.start = newNode;
        list.finish = newNode;
    }
    else {
        list.finish->next = newNode;
        list.finish = newNode;
    }
    ++list.number;
}

void Print(const List& list) {
    Node* tmp = list.start;
    while (tmp != nullptr) {
        cout << tmp->value << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

void pop_first(List& list) {
    if (list.number > 0) {
        Node* tmp = list.start->next;
        delete list.start;
        list.start = tmp;
        if (list.start == nullptr) {
            list.finish = nullptr;
        }
        --list.number;
    }
}

void pop_index(List& list, int index) {
    if (index > 1 && list.number > 1 && index <= list.number) {
        Node* tmp = list.start;
        int i = 1;
        while (i != index - 1) {
            ++i;
            tmp = tmp->next;
        }
        Node* tmp_del = tmp->next;
        tmp->next = tmp->next->next;
        delete tmp_del;
        --list.number;
    }
    else if (index == 1 && list.number != 0) {
        pop_first(list);
    }
}

void add_first(List& list, double newValue) {
    Node* newNode = new Node;
    newNode->value = newValue;
    newNode->next = list.start;

    if (list.number == 0) {
        list.start = newNode;
        list.finish = newNode;
    }
    else {
        list.start = newNode;
    }
    ++list.number;
}

void add_index(List& list, int index, double newValue) {
    if (index > 1 && list.number > 1 && index <= list.number + 1) {
        Node* tmp = list.start;
        int i = 1;
        while (i != index - 1) {
            ++i;
            tmp = tmp->next;
        }
        Node* newNode = new Node;
        newNode->value = newValue;
        newNode->next = tmp->next;
        tmp->next = newNode;
        if (index == list.number + 1) {
            list.finish = newNode;
        }

        ++list.number;
    }
    else if (index == 1) {
        add_first(list, newValue);
    }
}


void clear(List& list) {
    while (list.number > 0) {
        pop_first(list);
    }
}

void create_node(List& list)
{
    int kol;
    cout << "Введите количество элементов списка: ";
    kol = get_integer_value();
    for (int i = 1; i <= kol; i++)
    {
        cout << "Введите " << i << " элемент списка: ";
        add_last(list, get_value());
    }
}


int main()
{
    int menu = 1;
    do
    {
        setlocale(LC_ALL, "RUS");
        List list1, list2;
        double change;
        int kol = 0, list1_start = 0, number = 1, kol_sov = 0, kol_sov_iskl = 0, first_sov = 0;
        cout << "Создание первого списка: " << endl;
        create_node(list1);
        cout << "Создание второго списка: " << endl;
        create_node(list2);
        cout << "Введите число для замены: " << endl;
        change = get_value();
        Node* tmp1 = list1.start;
        Node* tmp2 = list2.start;
        //Print(list1);
        //Print(list2);
        while (tmp1 != nullptr)
        {
            if (tmp1->value == tmp2->value)
            {
                list1_start = number;
                if (number == 1) first_sov = 1;
                while (tmp1 != nullptr && tmp2 != nullptr && tmp1->value == tmp2->value)
                {
                    //cout << "list1_start = " << list1_start << endl;
                    //Print(list1);
                    kol++;
                    kol_sov++;
                    kol_sov_iskl++;
                    if (kol_sov_iskl == 2 * list2.number && tmp1->next == nullptr && first_sov == 1)
                    {
                        clear(list1);
                        add_first(list1, change);
                        add_first(list1, change);
                        break;
                    }
                    if (kol_sov == list2.number + 1)
                    {
                        list1_start = number;
                        kol_sov = 1;
                        kol = 1;
                    }
                    if (kol == list2.number)
                    {
                        for (int i = 1; i <= list2.number; i++)
                        {
                            pop_index(list1, list1_start);
                        }
                        add_index(list1, list1_start, change);
                        number = list1_start;
                        tmp1 = tmp1->next;
                        number++;
                        if (tmp1 != nullptr) tmp2 = list2.start;
                        kol = 0;
                    }
                    else
                    {
                        tmp1 = tmp1->next;
                        if (tmp1 != nullptr) tmp2 = tmp2->next;
                        number++;
                    }

                }
            }
            else
            {
                tmp1 = tmp1->next;
                number++;
            }
        }
        cout << "Результат работы программы: " << endl;
        Print(list1);
        cout << "Чтобы выйти из программы, нажмите 0. Чтобы продолжить - любое другое целое число: ";
        menu = get_integer_value();
    } while (menu != 0);
}


