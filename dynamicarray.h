#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <QDebug>

template<typename type> class DynamicArray
{
private:
    int size; //размер массива
    int capacity; //ёмкость массива
    type* arr; //указатель на массив
    void Resize(){ //функция перевыделения памяти
        type* temp;
        capacity *= 2; //увеличиваем ёмкость массива в два раза
        temp = arr;
        arr = new type[capacity]; //перевыделяем память
        for(int i = 0; i < (capacity >> 1); i++) //перезаписываем массив
            arr[i] = temp[i];
        delete temp; //удаляем указатель на старую область памяти
    }
    void init(){
        capacity = 2; //создается массив с ёмкостью = 2
        arr = new type [capacity];
        size = 0;
    }
public:
    DynamicArray(){init();}
    ~DynamicArray(){delete arr;}
    //добавляет значение insert_value в ячейку массива по номеру index_to_insert_value
    void insert(const type& insert_value ,short index_to_insert_value);
    //добавляет значение в конец массива
    void add(const type& value);
    //удаляет значение массива по номеру index_remove_value
    void removeAt(short index_remove_value);
    //вовзращает номер элемента value в массиве. Возвращает -1 если элемент не найден
    int indexOf(const type& value);
    //вовзращает элемент массива по его номеру
    type operator [](short index);
    int get_size(){return size;}
    int get_capacity(){return capacity;}
    //резервируем ёмкость массива
    void reserve(int );
    //очищаем массив
    void clear(){delete arr; init();}
};

template<typename type> void DynamicArray<type>::reserve(int res){
    if(res < capacity)
        return;
    type* temp;
    capacity = res; //увеличиваем ёмкость массива в два раза
    temp = arr;
    arr = new type[res]; //перевыделяем память
    for(int i = 0; i < size; i++) //перезаписываем массив
        arr[i] = temp[i];
    delete temp; //удаляем указатель на старую область памяти
}

template<typename type> void DynamicArray<type>::add(const type& a){
    if(size == capacity)
        Resize();
    arr[size] = a;
    size++;
}

template<typename type> type DynamicArray<type>::operator [](short index){
    if(index < size)
        return arr[index];
    return 0;
}

template<typename type> int DynamicArray<type>::indexOf(const type& v){
    for(int i = 0; i < size; i++)
        if(arr[i] == v)
            return i;
    return -1;
}

template<typename type> void DynamicArray<type>::removeAt(short index){
    for(int i = index; i < size; i++)
        arr[i] = arr[i + 1];
    size -= 1;
}


template<typename type> void DynamicArray<type>::insert(const type& v, short index){
    if(index > size)
        return;
    if(size == capacity)
        Resize();
    for(int i = size + 1; i > index; i--)
        arr[i] = arr[i - 1];
    arr[index] = v;
    size ++;
}


#endif // DYNAMICARRAY_H
