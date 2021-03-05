#pragma once

enum Error_code { success, underflow, overflow, Range_error };
template<class List_entry>
class List
{
public:
	List(int List_size = 0) :count(0), max_size(List_size) { entry = new List_entry[List_size]; }
	~List() { delete[] entry; }

	int size()const;
	bool full()const;
	bool empty()const;
	//void clear();
	void traverse(void(*visit)(List_entry&));

	Error_code retrieve(int position, List_entry& x)const;
	//Error_code replace(int position, const List_entry& x);
	Error_code remove(int position, List_entry& x);
	Error_code insert(int position, const List_entry& x);
protected:
	int count;
	int max_size;
	List_entry* entry;
};