#ifndef LINELIST_H
#define LINELIST_H

class LineListException {};

template <class T> class LineList;

template <class T>
class LineListElem {
    T data;
    LineListElem<T>* next;
public:
    LineListElem(const T& adata, LineListElem<T>* anext);
    const T& getData() const;
    LineListElem<T>* getNext();
    template <class U> friend class LineList;
};

template <class T>
class LineList {
    LineListElem<T>* start;
    LineListElem<T>* last;
public:
    LineList();
    ~LineList();
    LineListElem<T>* getStart();
    void deleteFirst();
    void deleteAfter(LineListElem<T>* ptr);
    void insertFirst(const T& data);
    void makeCircular();
};

#endif