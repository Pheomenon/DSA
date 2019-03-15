#include "Vector.h"
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������[lo,hi]Ϊ������������
	_elem = new T[_capacity = 2 * (hi - lo)]; //����ռ䣬��ģ����
	_size = 0;
	while (lo<hi) //A[lo,hi]�ڵ�Ԫ����һ������_elem[0,hi-lo]
	{
		_elem[_size++] = A[lo++];
	}
}
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V) { //���ظ�ֵ������
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ����
}
template <typename T> void Vector<T>::expand() { //�����ռ䲻��ʱ����
	if (_size < _capacity) return; //��δ��Աʱ����������
	if (_capacity < DEFULT_CAPACITY)_capacity = DEFULT_CAPACITY; //��������С����
	T* oldelem = _elem; 
	_elem = new T[_capacity <<= 1]; //�����ӱ�
	for (int i = 0; i < _size; i++) 
		_elem[i] = oldelem[i]; //����Ԫ��������(T Ϊ�������ͣ��������ظ�ֵ������'=')
	delete[] oldelem; //�ͷ�ԭ�ռ�
}
template <typename T> void Vector<T>::shrink() { //װ�����ӹ�Сʱѹ��������ռ�õĿռ�
	if (_capacity < DEFULT_CAPACITY << 1)return; //����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity)return; //��25%Ϊ��
	T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //��������
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}
template <typename T> T& Vector<T>::operator[](Rank r)const { //�����±������
	return _elem[r]; //assert�� 0 <= r < _size
}
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�ȸ��ʵ����������������[lo,hi)
	T* V = _elem + lo; //��������_elem[lo,hi)������һ����V[0,hi - lo)
	for (Rank i = hi - lo; i > 0; i--) //�Ժ���ǰ
		swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)�е�ĳһԪ���������
}
template <typename T> //��e��Ϊ��Ϊr��Ԫ�ز���

Rank Vector<T>::insert(Rank r, T const& e) { //assert : 0 <= r <= size
	expand(); //���б�Ҫ������
	for (int i = size; i > r; i--) _elem[i] = _elem[i - 1]; //��ǰ��󣬺��Ԫ��˳������ƶ�һ����Ԫ
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������
}
template <typename T>int Vector<T>::remove(Rank lo, Rank hi) { //ɾ������[lo,hi]
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������romove(0,0)
	while (hi < _size) _elem[_io++] = _elem[hi++]; //[hi,_size)˳����ǰ��lo - hi ����Ԫ
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
	shrink(); //���б�Ҫ��������
	return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}