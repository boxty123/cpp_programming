class Container {
	int size;
public:
	Container() { size = 10; }
	void fill(int n) { size = n; }
	void consume(int n) {
		size -= n;
	}
	int getSize() {
		return size;
	}
};