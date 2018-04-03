#include "List.h"

#include "Log.h"

List::List() {
  head = 0;
  tail = 0;
  length = 0;
}

List::~List() {
	while(head != 0) {
		deleteStart();
	}
}

Node* List::createNode(void* data) {
  Node* node = new Node;
  node->data = data;
  node->next = 0;
  node->prev = 0;
  return node;
}

void List::insertStart(void* data) {
  Node* node = List::createNode(data);
  node->next = head;
  head->prev = node;
  head = node;
  length++;
}

void List::insertEnd(void* data) {
  Node* node = List::createNode(data);
  if(head == 0) {
    head = node;
    tail = node;
  } else {
    tail->next = node;
    node->prev = tail;
    tail = node;
  }
  length++;
}

void List::deleteStart() {
  Node* temp = head;
  head = temp->next;
  head->prev = 0;
  length--;
  if(length == 0) tail = 0;
  delete temp;
}

void List::deleteItem(void *data) {
	Node* curr = head;
	while(curr != 0 && curr->data != data) {
		curr = curr->next;
	}

	if(curr != 0) {
		if(curr->next == 0 && curr->prev == 0) {
			head = tail = 0;
		}
		if(curr->next != 0) {
			curr->next->prev = curr->prev;
		}
		if(curr->prev != 0) {
			curr->prev->next = curr->next;
		}
		delete curr;
	}

	length--;
}

void List::deleteAfter(void* data) {
	while(tail != 0 && tail->data != data) {
		deleteEnd();
	}
}

void List::deleteEnd() {
	Node* temp = tail;
	tail = temp->prev;
	tail->next = 0;
	length--;
	if(length == 0) head = 0;
	delete temp;
}

void List::clear() {
	while(length > 0) {
		deleteEnd();
	}
}

Iterator* List::getIteratorStart() {
	return new Iterator(head);
}

Iterator* List::getIteratorEnd() {
	return new Iterator(tail);
}

Iterator::Iterator(Node* head) {
	curr = head;
	start = 1;
}

void* Iterator::next() {
	if(start) {
		start = 0;
	} else {
		curr = curr->next;
	}

	if(curr != 0) return curr->data;
	else return 0;
}

void* Iterator::prev() {
	if(start) {
		start = 0;
	} else {
		curr = curr->prev;
	}

	if(curr != 0) return curr->data;
	else return 0;
}
