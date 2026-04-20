#include "LineList.h"

template <class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem<T>* anext) {
    data = adata;
    next = anext;
}

template <class T>
const T& LineListElem<T>::getData() const { return data; }

template <class T>
LineListElem<T>* LineListElem<T>::getNext() { return next; }

template <class T>
LineList<T>::LineList() { start = 0; last = 0; }

template <class T>
LineList<T>::~LineList() {
    if (!start) return;
    if (last) last->next = 0; // Разрываем кольцо для удаления
    while (start) {
        LineListElem<T>* temp = start;
        start = start->next;
        delete temp;
    }
}

template <class T>
LineListElem<T>* LineList<T>::getStart() { return start; }

template <class T>
void LineList<T>::deleteFirst() {
    if (start) {
        LineListElem<T>* temp = start;
        start = start->next;
        delete temp;
    }
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr) {
    LineListElem<T>* temp = ptr->next;
    ptr->next = temp->next;
    if (temp == start) start = temp->next;
    if (temp == last) last = ptr;
    delete temp;
}

template <class T>
void LineList<T>::insertFirst(const T& data) {
    LineListElem<T>* newNode = new LineListElem<T>(data, start);
    if (!start) last = newNode;
    start = newNode;
}

template <class T>
void LineList<T>::makeCircular() {
    if (last && start) last->next = start;
}

template class LineListElem<int>;
template class LineList<int>;