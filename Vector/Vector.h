#include "pch.h"
#include <iostream>

typedef int Rank; 
#define DEFULT_CAPACITY 3 //默认的初始容量

template <typename T> class Vector { 
protected:
	Rank _size; int _capacity; T* _elem; // 规模，容量，数据区
	void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间A[lo,hi]
	void expand(); //空间不足时扩容
	void shrink(); //装填因子过小时压缩
	bool bubble(Rank lo, Rank hi); //扫描交换
	void bubbleSort(Rank li, Rank hi); //起泡排序
	Rank max(Rank lo, Rank hi); //
	void selectionSort(Rank lo, Rank hi); //
	void merge(Rank lo, Rank mi, Rank hi); //并归算法
	void mergeSort(Rank lo, Rank hi); //并归排序算法
	void partition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi); //
	void heapSort(Rank lo, Rank hi); //
public:
	//构造函数
	Vector(int c = DEFULT_CAPACITY, int s = 0, T v = 0) //容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v); //s <= c
	}
	Vector(T* const A, Rank lo, Rank hi) {
		copyFrom(A, lo, hi); //数组区间复制
	}
	Vector(T* const A, Rank n) {
		copyFrom(A, 0, n); //数组整体复制
	}
	Vector(Vector<T> const& V, Rank lo, Rank hi) {
		copyFrom(V._elem, lo, hi); //向量区间复制
	}
	Vector(Vector<T> const& V) {
		copyFrom(V._elem, 0, V._size); //向量整体复制
	}

	//析构函数
	~Vector() {
		delete[] _elem;
	}

	//只读访问接口
	Rank size() const {
		return _size; //规模
	}
	bool empty() const {
		return !_size; //判空
	}
	int disrodered() const; //判断是否已经排序
	Rank find(T const& e) const {
		return find(e, 0, Rank()_size; //无序向量整体查找
	}
	Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找
	Rank search(T const& e) const {
		return(0 >= _size) ? -1 : search(e, (Rank)0, (Rank)_size); //有序向量整体查找
	}
	Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
	//可写访问接口
	T& operator[](Rank r) const; //重载下标操作符，实现引用元素
	Vector<T> & operator = (Vector<T> const&); //克隆向量
	T remove(Rank r); //删除秩为r的元素
	int remove(Rank lo, Rank hi); //删除秩在区间[lo,hi)之内的元素
	Rank insert(Rank r, T const& e); //默认作为末元素插入
	Rank insert(T const& e) {
		return insert(_size, e); //插入元素
	}
	void sort(Rank lo, Rank hi); //对[lo,hi)排序 
	void sort() { 
		sort(0, _size); //整体排序
	}
	void unsort(Rank lo, Rank hi); //对[lo,hi）置乱
	void unsort() { 
		unsort(0, _size);//整体置乱
	}
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	//遍历
	void traverse(void(*)(T&)); //遍历（使用函数指针，只读或局部性修改）
	template<typename VST> void traverse(VST&); //遍历（使用函数对象，可全局修改）
};

