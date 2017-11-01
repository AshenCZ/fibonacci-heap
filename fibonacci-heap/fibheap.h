template <typename T>
class CyclicList {
public:
	struct Node {
		Node *next;
		Node *prev;
		T value;
	};

private:
	Node *start;

	size_t count;

	Node* end() const {
		if (start)
			return start->prev;
		else
			return nullptr;
	}

public:
	const Node* head() {
		return start;
	}

	const Node* tail() {
		return end();
	}

	size_t size() const { return count; }

	void pushBack(const T value) {
		if (start) {
			Node *newItem = new Node(value);
			newItem->prev = end();
			newItem->next = start();
			end()->next = newItem;
			start->prev = newItem;
		}
		else {
			start = new Node(value);
			start->next = start;
			start->prev = start;
		}
		count++;
	}

	void merge(CyclicList& from) {
		if (start && from) {
			this.count += from.count;
			this.start->prev = from.end();
			from.end()->next = this.start;
			this.end()->next = from.start;
			from.start->prev = this.end();
		}
		else if (start && !from) {
			return;
		}
		else {
			this.start = from.start;
			this.count = from.count;
		}

		from.start = nullptr;
		from.count = 0;		
	}
};

template <typename Key, typename Value>
class FibonacciHeap {

};