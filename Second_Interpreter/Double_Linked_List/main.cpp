#include <iostream>

// Define the node type
template <typename T>
struct Node {
	Node* next = nullptr;
	Node* previous = nullptr;
	T value;
};

template <typename T>
struct DoubleLinkedList {
	Node<T>* firstNode = nullptr;
	Node<T>* lastNode = nullptr;
};

template <typename T>
Node<T>* find_Node(DoubleLinkedList<T>* list, T value) {
	Node<T>* currentNode = list->firstNode;
	while (currentNode != nullptr) {
		if (currentNode->value == value) return currentNode;
		else currentNode = currentNode->next;
	}
	return nullptr;
}

template <typename T>
void insert_after(DoubleLinkedList<T>* list, T value, T newValue) {
	Node<T>* desiredNode = find_Node(list, value);
	if (desiredNode == nullptr) return;

	if (desiredNode->next == nullptr) {
		desiredNode->next = new Node<T> {
			nullptr,
			desiredNode,
			newValue
		};
		list->lastNode = desiredNode->next;
	} else {
		Node<T>* newNode = new Node<T>{
			desiredNode->next,
			desiredNode,
			newValue,
		};
		desiredNode->next->previous = newNode;
		desiredNode->next = newNode;
	}
}

template <typename T>
void insert_before(DoubleLinkedList<T>* list, T value, T newValue) {
	Node<T>* desiredNode = find_Node(list, value);
	if (desiredNode == nullptr) return;

	if (desiredNode->previous == nullptr) {
		desiredNode->previous = new Node<T> {
			desiredNode,
			nullptr,
			newValue
		};
		list->firstNode = desiredNode->previous;
	} else {
		Node<T>* newNode = new Node<T>{
			desiredNode,
			desiredNode->previous,
			newValue,
		};
		desiredNode->previous->next = newNode;
		desiredNode->previous = newNode;
	}
}

template <typename T>
void insert_start(DoubleLinkedList<T>* list, T value) {
	if (list->firstNode == nullptr) {
		list->firstNode = new Node<T> {
			nullptr,
			nullptr,
			value
		};
		list->lastNode = list->firstNode;
	} else insert_before(list, list->firstNode->value, value);
}

template <typename T>
void insert_end(DoubleLinkedList<T>* list, T value) {
	if (list->lastNode == nullptr) insert_start(list, value);
	else insert_after(list, list->lastNode->value, value);
}

template <typename T>
void remove_item(DoubleLinkedList<T>* list, T value) {
	Node<T>* node = find_Node(list, value);
	if (node == nullptr) return;

	if (node->previous == nullptr) list->firstNode = node->next;
	else node->previous->next = node->next;

	if (node->next == nullptr) list->lastNode = node->previous;
	else node->next->previous = node->previous;
	
	delete node;
}

template <typename T>
void print_list_forwards(DoubleLinkedList<T>* list) {
	Node<T>* currentNode = list->firstNode;
	
	while (currentNode != nullptr) {
		std::cout << currentNode->value << " -> ";
		currentNode = currentNode->next;
	}
	std::cout << std::endl;
}

template <typename T>
void print_list_backwards(DoubleLinkedList<T>* list) {
	Node<T>* currentNode = list->lastNode;
	
	while (currentNode != nullptr) {
		std::cout << currentNode->value << " -> ";
		currentNode = currentNode->previous;
	}
	std::cout << std::endl;
}

int main() {
	DoubleLinkedList<int> list;

	//insert some nodes
	insert_start(&list, 2);
	insert_start(&list, 0);
	insert_end(&list, 8);
	insert_end(&list, 10);
	
	insert_after(&list, 0, 1);
	insert_before(&list, 10, 9);

	// Print list	
	print_list_forwards(&list);
	print_list_backwards(&list);

	// Insert some more nodes
	insert_after(&list, 2, 3);
	insert_after(&list, 3, 4);
	print_list_forwards(&list);	

	// Remove nodes
	remove_item(&list, 0);
	print_list_forwards(&list);
	remove_item(&list, 10);
	print_list_forwards(&list);
	remove_item(&list, 3);
	print_list_forwards(&list);

	// Delete list
	remove_item(&list, 1);
	remove_item(&list, 2);
	remove_item(&list, 3);	
	remove_item(&list, 4);
	remove_item(&list, 8);
	remove_item(&list, 9);
	print_list_backwards(&list);

	return 0;
}