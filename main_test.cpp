#include"sortable_list_contiguous.h"
#include"sortable_list_contiguous.cpp"
void print(int& entry)
{
	cout << entry;
}

int main()
{
	Sortable_list<int> s(10);
	s.insert(0, 2); s.insert(0, 1); s.insert(0, 7);
	s.insert(0, 4); s.insert(0, 9); s.insert(0, -2);
	s.insert(0, 0); s.insert(0, 4);
	cout << "原始表：";
	s.traverse(print);
	cout << endl;
	s.build_heap();
	cout << "创建堆：";
	s.traverse(print);
	int x = 2;
	s.heap_insert_new(x);
	cout << "插入：" << x << endl << "插入后：";
	s.traverse(print);
}