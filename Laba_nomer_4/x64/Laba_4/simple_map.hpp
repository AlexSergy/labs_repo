// ����������� ��������� MAP
#pragma once



template<typename K, typename V>
class simple_map {
public:

	struct Nodemap {
		K key;
		V value;
		Nodemap* next;

		Nodemap(const K& key, const V& value, Nodemap* next) : key(key), value(value), next(next) {}
	};

	Nodemap* head;

	simple_map() : head(nullptr) {}
	~simple_map() { clear(); }

	void insert(K key, V value) {
		if (!head) {
			head = new Nodemap(key, value, nullptr);
			return;
		}
		Nodemap** node = &head;
		while (*node && (*node)->key != key) { node = &(*node)->next; }
		if (*node) { (*node)->value += value; }
		else { *node = new Nodemap{ key, value, nullptr }; }
	}

	void remove(const K& key) {
		Nodemap** node = &head;
		while (*node && (*node)->key != key) { node = &(*node)->next; }
		if (*node) {
			Nodemap* del = *node;
			*node = (*node)->next;
			delete del;
		}
	}

	// ������� ���� ����������� ��������
	// ���������� ������ � ������� �������� ��������
	Nodemap* split(Nodemap* start) {
		Nodemap* fast = start;
		Nodemap* slow = start;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		Nodemap* middle = slow->next;
		slow->next = nullptr;
		return middle;
	}

	// ������� ���� ��������������� �������
	Nodemap* merge(Nodemap* first, Nodemap* second) {
		// ���� ���� �� ������� ����, ���������� ������
		if (!first) return second;
		if (!second) return first;

		if (first->value > second->value) { // sort � ������� ��������
			first->next = merge(first->next, second);
			return first;
		}
		else {
			second->next = merge(first, second->next);
			return second;
		}
	}

	// ���� ����������
	Nodemap* mergeSort(Nodemap* start) {
		if (!start || !start->next) return start;

		Nodemap* middle = split(start);
		Nodemap* left = mergeSort(start);
		Nodemap* right = mergeSort(middle);

		return merge(left, right);
	}

	// �������� �������
	void sort() { head = mergeSort(head); }

	// �������� ���������� ��������
	void removeRegion(const K& name) {
		Nodemap** node = &head;
		while (*node) {
			Nodemap* del = *node;
			if (del->key == name) {
				*node = del->next;
				delete del;
				break;
			}
			node = &(del->next);
		}
	}

	// ��� ��������� ����. ���������� ��������� ���������� �������.
	void remove_population(const K& region, const V& population) {
		Nodemap** node = &head;
		while (*node) {
			if ((*node)->key == region) {
				if ((*node)->value >= population) { (*node)->value -= population; }
				else { remove(region); }
				// if ��������� ������ ������ ��� �����, ��� �������, ������� ������
				// �� ������ ������, ����� � map �� ���� ���. ��������
				return;
			}
			node = &(*node)->next;
		}
	}

	V getValue(const K& key) { // ���������� �������� �� �����
		Nodemap* cur = head;
		while (cur != nullptr) {
			if (cur->key == key) { return cur->value; }
			cur = cur->next;
		}
		throw out_of_range("Key not found!");
	}

	void clear() {
		while (head) {
			Nodemap* temp = head;
			head = head->next;
			delete temp;
		}
	}
};