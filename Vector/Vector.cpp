#include "Vector.h"
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //以数组区间[lo,hi]为蓝本复制向量
	_elem = new T[_capacity = 2 * (hi - lo)]; //分配空间，规模清零
	_size = 0;
	while (lo<hi) //A[lo,hi]内的元素逐一复制至_elem[0,hi-lo]
	{
		_elem[_size++] = A[lo++] 
	}
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V) { //重载赋值操作符
	if (_elem) delete[] _elem; //释放原有内容
	copyFrom(V._elem, 0, V.size()); //整体复制
	return *this; //返回当前对象的引用，以便链式复制
}