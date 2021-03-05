#include"sortable_list_contiguous.h"

template <class List_entry>		//最大键位置
int Sortable_list<List_entry>::max_key(int low, int high)
{
	int largest, current;
	largest = low;
	for (current = low + 1; current <= high; current++)
		if (List<List_entry>::entry[largest] < List<List_entry>::entry[current])
			largest = current;
	return largest;
}
template <class List_entry>		//交换
void Sortable_list<List_entry>::Swap(int low, int high)
{
	if (low != high)	//low等于high不用执行
	{
		List_entry temp = List<List_entry>::entry[low];
		List<List_entry>::entry[low] = List<List_entry>::entry[high];
		List<List_entry>::entry[high] = temp;
	}
}
template <class List_entry>		//选择排序
void Sortable_list<List_entry>::selection_sort()
{
	for (int position = List<List_entry>::count - 1; position > 0; position--)
	{
		int Max = max_key(0, position);
		Swap(Max, position);
	}
}

template <class List_entry>		//希尔排序内部插入排序
void Sortable_list<List_entry>::sort_interval(int start, int increment)
{
	int first_unsorted;
	int position;
	List_entry current;
	for (first_unsorted = start + increment; first_unsorted < List<List_entry>::count; first_unsorted += increment)
		if (List<List_entry>::entry[first_unsorted] < List<List_entry>::entry[first_unsorted - increment])
		{
			position = first_unsorted;
			current = List<List_entry>::entry[position];
			do {
				List<List_entry>::entry[position] = List<List_entry>::entry[position - increment];
				position -= increment;
			} while (position > 0 && List<List_entry>::entry[position - increment] > current);
			List<List_entry>::entry[position] = current;
		}
}
template <class List_entry>		//希尔排序
void Sortable_list<List_entry>::shell_sort()
{
	int increment, start;
	increment = List<List_entry>::count;
	do {
		increment = increment / 3 + 1;		//子表内元素在原表内的间距
		for (start = 0; start < increment; start++)
			sort_interval(start, increment);
	} while (increment > 1);
}

template <class List_entry>		//快速排序：中位数pivot
void Sortable_list<List_entry>::quick_sort_1()
{
	recursive_quick_sort_1(0, List<List_entry>::count - 1);
}
template <class List_entry>		//递归快速排序：头尾中间的中位数pivot(支点),扫描方式和课本不一样
void Sortable_list<List_entry>::recursive_quick_sort_1(int low, int high)
{
	int pivot_position;
	if (low < high)
	{
		pivot_position = partition(low, high);
		recursive_quick_sort_1(low, pivot_position - 1);
		recursive_quick_sort_1(pivot_position + 1, high);
	}
}
template <class List_entry>		//找中位数索引
int Sortable_list<List_entry>::median(int a, int b, int c)
{
	if (List<List_entry>::entry[a] >= List<List_entry>::entry[b])
	{   if (List<List_entry>::entry[b] >= List<List_entry>::entry[c]) return b;
		else {  if (List<List_entry>::entry[a] >= List<List_entry>::entry[c]) return c;
				else return a;}}
	else {
		if (List<List_entry>::entry[a] >= List<List_entry>::entry[c]) return a;
		else {  if (List<List_entry>::entry[b] >= List<List_entry>::entry[c]) return c;
				else return b;}}
}
template <class List_entry>		//根据支点分顺序表，扫描方式和课本不一样
int Sortable_list<List_entry>::partition(int low, int high)
{	
	int median_index = median(low, high, (low + high) / 2);
	//双向扫描，尾部先动
	std::swap(List<List_entry>::entry[median_index], List<List_entry>::entry[low]);
	List_entry pivot = List<List_entry>::entry[low];
	int left = low;
	int right = high;
	while (left < right)
	{
		//从尾部找到一个小于支点，应该放到前边的
		while (left < right && List<List_entry>::entry[right] >= pivot) right--;
		if (left < right) List<List_entry>::entry[left++] = List<List_entry>::entry[right];
		//从头部找到一个大于支点，应该放到后边的
		while (left < right && List<List_entry>::entry[left] < pivot) left++;
		if (left < right) List<List_entry>::entry[right--] = List<List_entry>::entry[left];
	}
	//最后头部和尾部停下的位置就是支点应在位置
	List<List_entry>::entry[left] = pivot;
	return left;
}

template <class List_entry>		//堆排序
void Sortable_list<List_entry>::heap_sort()
{
	List_entry current;
	int last_unsorted;
	build_heap();
	for (last_unsorted = List<List_entry>::count - 1; last_unsorted > 0; last_unsorted--)
	{
		current = List<List_entry>::entry[last_unsorted];
		List<List_entry>::entry[last_unsorted] = List<List_entry>::entry[0];
		insert_heap(current, 0, last_unsorted - 1);
	}
}
template <class List_entry>		//表中已有元素向堆中插入
void Sortable_list<List_entry>::insert_heap(const List_entry& current, int low, int high)
{
	int large = low * 2 + 1;
	while (large <= high)
	{
		if (large < high && List<List_entry>::entry[large] < List<List_entry>::entry[large + 1]) large++;
		if (current >= List<List_entry>::entry[large])break;
		else
		{
			List<List_entry>::entry[low] = List<List_entry>::entry[large];
			low = large;
			large = low * 2 + 1;
		}
	}
	List<List_entry>::entry[low] = current;
}
template <class List_entry>		//创建堆
void Sortable_list<List_entry>::build_heap()
{
	int low;
	for (low = List<List_entry>::count / 2 - 1; low >= 0; low--)
	{
		List_entry current = List<List_entry>::entry[low];
		insert_heap(current, low, List<List_entry>::count - 1);
	}
}
template <class List_entry>		//向表（堆）中插入新元素
void Sortable_list<List_entry>::heap_insert_new(const List_entry& new_entry)
{
	build_heap();											//确保现在是堆
	List<List_entry>::insert(0, new_entry);					//插入表头
	insert_heap(new_entry, 0, List<List_entry>::count - 1);	//然后当表中元素插入堆
}