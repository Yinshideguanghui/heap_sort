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
	cout << "ԭʼ��";
	s.traverse(print);
	cout << endl;
	s.build_heap();
	cout << "�����ѣ�";
	s.traverse(print);
	int x = 2;
	s.heap_insert_new(x);
	cout << "���룺" << x << endl << "�����";
	s.traverse(print);
}