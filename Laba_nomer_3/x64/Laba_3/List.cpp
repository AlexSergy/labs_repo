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
	Node* tail = nullptr;
	int common_count = 0;
	int num_flag = -1;

	Node* go_to(int num) {
		if (!head) { throw out_of_range("Empty list"); }
		if (num == -1) { return tail; }
		if (common_count!=0) num %= common_count;
		Node* start = head;
		int steps = num;
		int distance_flag = flag ? num - num_flag : INT_MAX;

		if (distance_flag >= 0 && distance_flag < steps) {
			start = flag;
			steps = distance_flag;
		}
		while (steps-- > 0) { start = start->next; }
		flag = start;
		num_flag = num;
		return start;
	}

	void flag_check(int num) {
		if (num < num_flag) { num_flag--; } // условия для num_flag
		if (num == num_flag) { 
			flag = flag->next;
			++num_flag %= common_count;
		}
	}

	void add(int value) {
		Node* newNode = new Node(value);
		if (!head) { head = newNode; newNode->next = head; }
		else {
			Node* last = tail;
			last->next = newNode;
			newNode->next = head;
		}
		tail = newNode;
		common_count++;
	}

	void insert(int num, int value) {
		Node* newNode = new Node(value);
		if (!head) { head = newNode; head->next = newNode; }
		num %= common_count + 1;
		Node* cur = nullptr;
		if (num == 0) { 
			cur = tail;
			head = newNode;
		}
		else { cur = go_to(num-1); }
		newNode->next = cur->next;
		cur->next = newNode;
		common_count++;
		if (num <= num_flag) { num_flag++; }
	}

	void removeAt(int num) {
		if (!head) { return; }
		Node* beforeDel = nullptr;
		Node* del = nullptr;
		beforeDel = go_to(num - 1);
		if (num == 0) { head = common_count > 1 ? head->next : nullptr; }
		if (num == common_count - 1) { tail = common_count > 1 ? go_to(common_count - 2) : nullptr; }
		del = beforeDel->next;
		beforeDel->next = del->next;
		delete del;
		common_count--;
	}

	int elementAt(int num) { return go_to(num)->data; }
	
	int count() { return common_count; }

	void insertBeforeNegative() {
		if (!head) { return; }
		Node* prev = tail;
		Node* cur = prev->next;
		int count = common_count;

		for (int i = 0; i < count; i++) {
			if (cur->data < 0) {
				Node* newNode = new Node(1);
				newNode->next = cur;
				prev->next = newNode;
				if (cur == head) { head = newNode; }
				if (i <= num_flag) { num_flag++; } // для случаев, когда elementAt уже был использован
				common_count++;
			}
			prev = cur;
			cur = cur->next;
		}
	}
	

	void removeNegative() {
		if (!head) { return; }
		Node* cur = head;
		Node* prev = tail;
		int count = common_count;
		for (int i = 0; i < count; i++) {
			if (cur->data < 0) {
				prev->next = cur->next;
				if (cur == head) { head = head->next; }
				if (cur == tail) tail = prev;
				flag_check(i);
				delete cur;
				if (common_count != 1) { cur = prev->next; }
				else {
					head = nullptr;
					tail = nullptr;
					flag = nullptr;
					num_flag = -1;
				}
				common_count--;
				
			}
			else {
				prev = cur;
				cur = cur->next;
			}
			if (!head) { return; }
		}
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
		if (!head) { return; }// Список уже пуст, ничего не нужно делать
		Node* current = head;
		do {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		} while (current != head);
		head = nullptr;
		tail = nullptr;
		flag = nullptr;
		common_count = 0;
		num_flag = -1;
	}
};