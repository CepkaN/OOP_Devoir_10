#include<iostream>



template<typename T>
class Node {
private:
	T _data;
public:
	Node(T data):_data(data){}
	~Node() {
		std::cout << "Звено удалено.\n";
	}
	Node* next;
	Node* prev;

	T GetData(){ return _data; }
};
template <typename U>
class List {
private:
	Node<U>* _head;
	Node<U>* _tail;
	int _size;

	bool AddMain(Node<U>* node) {
		if (_head != nullptr)return false;

		_head = node;
		_tail = node;
		_size++;

		return true;
	}
public:
	List() :_head(nullptr), _tail(nullptr), _size(0) {}

	void AddTail(U data) {
		Node<U>* node{ new Node<U>(data) };
		if (AddMain(node))return;

		_size++;

		node->next = _tail;
		_tail->prev = node;
		_tail = node;
	}

	void AddHead(U data) {
		Node<U>* newHead{ new Node<U>(data) };
		if (AddMain(newHead))return;

		_size++;

		_head->next = newHead;
		newHead->prev = _head;
		_head = newHead;
	}

	void ShowListFromHead() {
		if (_size == 0) {
			std::cout << "Нет элементов.\n";
			return;
		}
		for (Node<U>* node = _head; node != _tail->prev; node = node->prev)
			std::cout << node->GetData() << '\n';
	}

	void ShowListFromTail() {
		if (_size == 0) {
			std::cout << "Нет элементов.\n";
			return;
		}
		for (Node<U>* node = _tail; node != _head->next; node = node->next)
			std::cout << node->GetData() << '\n';
	}

	void DeleteAll() {
		for (Node<U>* node = _tail; node != nullptr; ) {
			Node<U>* temp = node;
			node = node->next;
			delete(temp);
			_size--;
		}
	}

	void DeleteElement(int index) {
		if (index > _size || index <= 0)return;

		if (index == _size) {
			Node<U>* temp = _tail;
			_tail = _tail->next;
			delete(temp);
			_size--;

			return;
		}
		else if (index == 1) {
			Node<U>* temp = _head;
			_head = _head->prev;
			delete(temp);
			_size--;

			return;
		}
		Node<U>* nextNode = FindElement(index + 1);
		Node<U>* prevNode = FindElement(index - 1);
		Node<U>* deleteNode = FindElement(index);
		prevNode->prev = nextNode;
		nextNode->next = prevNode;
		delete(deleteNode);
		_size--;

	}

	Node<U>* FindElement(int index) {
		Node<U>* node = _head;
		index--;
		while (index != 0) {
			node = node->prev;
			index--;
		}
		return node;
	}
};


int main() {
	setlocale(LC_ALL, "Russian");

	List<int> list;
	list.AddHead(111);
	list.AddHead(222);
	list.AddHead(333);

	list.AddTail(444);
	list.AddTail(555);
	list.AddTail(666);

	list.ShowListFromHead();
	std::cout << "\n\n";


	std::cout << list.FindElement(2)->GetData();
	std::cout << "\n\n";

	//list.ShowListFromHead();

	list.DeleteElement(2);
	//list.DeleteAll();
	std::cout << "\n\n";

	list.ShowListFromTail();
	std::cout << "\n";
	list.ShowListFromHead();
   
	List<std::string>list1;
	list1.AddHead("aaaaa");
	list1.AddHead("bbbbb");
	list1.AddHead("vvvvv");
	list1.ShowListFromHead();
	std::cout << "\n\n";

	return 0;
}