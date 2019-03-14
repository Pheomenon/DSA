#include "Vector.h"
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������[lo,hi]Ϊ������������
	_elem = new T[_capacity = 2 * (hi - lo)]; //����ռ䣬��ģ����
	_size = 0;
	while (lo<hi) //A[lo,hi]�ڵ�Ԫ����һ������_elem[0,hi-lo]
	{
		_elem[_size++] = A[lo++] 
	}
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V) { //���ظ�ֵ������
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ����
}