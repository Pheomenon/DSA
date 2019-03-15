#include "Vector.h"
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //以数组区间[lo,hi]为蓝本复制向量
	_elem = new T[_capacity = 2 * (hi - lo)]; //分配空间，规模清零
	_size = 0;
	while (lo<hi) //A[lo,hi]内的元素逐一复制至_elem[0,hi-lo]
	{
		_elem[_size++] = A[lo++];
	}
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V) { //重载赋值操作符
	if (_elem) delete[] _elem; //释放原有内容
	copyFrom(V._elem, 0, V.size()); //整体复制
	return *this; //返回当前对象的引用，以便链式复制
}
template <typename T> void Vector<T>::expand() { //向量空间不足时扩容
	if (_size < _capacity) return; //尚未满员时，不必扩容
	if (_capacity < DEFULT_CAPACITY)_capacity = DEFULT_CAPACITY; //不低于最小容量
	T* oldelem = _elem; 
	_elem = new T[_capacity <<= 1]; //容量加倍
	for (int i = 0; i < _size; i++) 
		_elem[i] = oldelem[i]; //复制元向量内容(T 为基本类型，或已重载赋值操作符'=')
	delete[] oldelem; //释放原空间
}
template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占用的空间
	if (_capacity < DEFULT_CAPACITY << 1)return; //不至收缩到DEFAULT_CAPACITY以下
	if (_size << 2 > _capacity)return; //以25%为界
	T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
	delete[] oldElem; //释放原空间
}
template <typename T> T& Vector<T>::operator[](Rank r)const { //重载下标运算符
	return _elem[r]; //assert： 0 <= r < _size
}
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //等概率的随机置乱向量区间[lo,hi)
	T* V = _elem + lo; //将子向量_elem[lo,hi)视作另一向量V[0,hi - lo)
	for (Rank i = hi - lo; i > 0; i--) //自后向前
		swap(V[i - 1], V[rand() % i]); //将V[i - 1]与V[0, i)中的某一元素随机交换
}
template <typename T> //将e作为秩为r的元素插入

Rank Vector<T>::insert(Rank r, T const& e) { //assert : 0 <= r <= size
	expand(); //若有必要，扩容
	for (int i = size; i > r; i--) _elem[i] = _elem[i - 1]; //自前向后，后继元素顺次向后移动一个单元
	_elem[r] = e; _size++; //置入新元素并更新容量
	return r; //返回秩
}
template <typename T>int Vector<T>::remove(Rank lo, Rank hi) { //删除区间[lo,hi]
	if (lo == hi) return 0; //出于效率考虑，单独处理退化情况，比如romove(0,0)
	while (hi < _size) _elem[_io++] = _elem[hi++]; //[hi,_size)顺次向前移lo - hi 个单元
	_size = lo; //更新规模。直接丢弃尾部[lo, _size = hi)区间
	shrink(); //若有必要，则缩容
	return hi - lo; //返回被删除元素的数目
}