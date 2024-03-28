#include<stdexcept>
using namespace std;

struct Node { // создаем структуру узла
	int data; // элемент, в котором храним значение
	Node* next; // ссылка на след. узел

	Node(int value) : data(value), next(nullptr) {} // Если инициализируется нода с значением, значение присваиваем в data
};



class List {
public:
	Node* head = nullptr;
	Node* flag = nullptr;
	int common_count = 0;
	int num_flag = -1;

	Node* go_to_num(Node* head) {
		Node* cur = head;
		while (cur->next != head) { cur = cur->next; }
		return cur;
	}
	
	Node* go_to_num(Node* head, int num) {
		num--;
		Node* cur = head;
		if (common_count == 0) { num = 0; }
		else if (common_count == num) { return go_to_num(head); } 
		if (num == 0) { return cur; } 
		for (int i = 0; i < num; i++) { cur = cur->next; }
		return cur;
	}


	void add(int value) {
		Node* newNode = new Node(value);
		common_count++;
		if (head == nullptr) { head = newNode; newNode->next = head; }
		else {
			Node* last = go_to_num(head);
			last->next = newNode;
			newNode->next = head;
		}
	}

	void insert(int num, int value) {
		if (num < 0 || (head == nullptr && num > 0)) { return; }
		if (common_count == 0 || num == common_count) { 
			add(value);
			return;
		}
		Node* newNode = new Node(value);
		Node* cur = nullptr;
		if (num == 0) { 
			cur = go_to_num(head);
			head = newNode;
		}
		else { cur = go_to_num(head, num); }
		newNode->next = cur->next;
		cur->next = newNode;
		common_count++;
	}

	void removeAt(int num) {
		if (num < 0 || head == nullptr) { return; }
		Node* beforeDel = nullptr;
		Node* del = nullptr;
		if (num == 0) { 
			beforeDel = go_to_num(head);
		}
		else { beforeDel = go_to_num(head, num); }
		del = beforeDel->next;
		beforeDel->next = del->next;
		if (head == del && common_count > 1) { head = head->next; } // условия если выбрано начало
		if (common_count == 1) { head = nullptr; }
		del->next = nullptr;
		delete del;
		common_count--;
	}

	int elementAt(int num) {
		if (num < 0 || (head == nullptr && num > 0)) { throw out_of_range("Invalid value!"); }
		Node* cur = nullptr;
		if (flag == nullptr || num < num_flag) { cur = go_to_num(head, num + 1); }
		else if (num == num_flag) { cur = flag; }
		else { cur = go_to_num(flag, (num + 1) - num_flag); }
		flag = cur;
		num_flag = num;
		return cur->data;
	}

	int count() { return common_count; }

	void insertBeforeNegative() {
		if (head == nullptr) { return; }
		Node* cur = go_to_num(head);
		do {
			if (cur->next->data < 0) {
				Node* newNode = new Node(1);
				newNode->next = cur->next;
				cur->next = newNode;
				cur = cur->next->next;
				if (head->data < 0) { head = newNode; } 
				/*Сработает только один раз если head->data < 0
				  понятно, что после эта уже бесполезная строка каждый
				  раз будет проверяться,но без нее никак*/
				common_count++;
			}
			else { cur = cur->next; }
		} while (cur->next != head);
	}

	void removeNegative() {
		if (head == nullptr) { return; }
		Node* cur = head;
		do {
			Node* nextNode = cur->next;
			if (nextNode->data < 0) {
				if (nextNode == head) { head = head->next; }
				cur->next = nextNode->next;
				nextNode->next = nullptr;
				delete nextNode;
				common_count--;
			}
			else { cur = nextNode; }
		} while (cur != head);
	} 

	int count(int value) {
		int count = 0;
		Node* cur = head;
		if (head != nullptr) {
			do {
				if (cur->data == value) { count++; }
				cur = cur->next;
			} while (cur != head);
		}
		return count;
	}

	void clear() {
		if (head == nullptr) { return; }// Список уже пуст, ничего не нужно делать
		Node* current = head;
		do {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		} while (current != head);
		head = nullptr;
		common_count = 0;
	}
};