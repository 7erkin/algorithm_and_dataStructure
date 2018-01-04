
template<typename T> class dynamicArray{
private:
    int size_; //размер массива
    int capacity_; //ёмкость массива
    T* arr_; //указатель на массив
private:
    void resize(int multi = 2){ //функция перевыделения памяти
        T* temp;
        capacity_ *= multi; //увеличиваем ёмкость массива в два раза
        temp = arr_;
        arr_ = new T[capacity_]; //перевыделяем память
        for(int i = 0; i < (capacity_ >> 1); i++) //перезаписываем массив
            arr_[i] = temp[i];
        delete temp; //удаляем указатель на старую область памяти
    }
    void initialize(){
        capacity_ = 2; //создается массив с ёмкостью = 2
        arr_ = new T [capacity_];
        size_ = 0;
    }

public:
    dynamicArray(){initialize();}
    ~dynamicArray(){delete arr_;}
    //добавляет значение insert_value в ячейку массива по номеру index_to_insert_value
    void insert(const T& insert_value ,short index_to_insert_value);
    //добавляет значение в конец массива
    void pushBack(const T& value);
    //удаляет значение массива по номеру index_remove_value
    void removeAt(short index_remove_value);
    //вовзращает номер элемента value в массиве. Возвращает -1 если элемент не найден
    int getIndexOf(const T& value);
    //вовзращает элемент массива по его номеру
    T& operator [](short index);
    int getSize(){return size_;}
    int getCapacity(){return capacity_;}
    //резервируем ёмкость массива
    void reserve(int size);
    //очищаем массив
    void clear(){delete arr_; initialize();}
};

template<typename T> void dynamicArray<T>::reserve(int res){
    if(res < capacity_)
        return;
    resize(res);
}

template<typename T> void dynamicArray<T>::pushBack(const T& a){
    if(size_ == capacity_)
        resize();
    arr_[size_] = a;
    size_++;
}

template<typename T> T& dynamicArray<T>::operator [](short index){
    if(index < size_)
        return arr_[index];
}

template<typename T> int dynamicArray<T>::getIndexOf(const T& v){
    for(int i = 0; i < size_; i++)
        if(arr_[i] == v)
            return i;
    return -1;
}

template<typename T> void dynamicArray<T>::removeAt(short index){
    for(int i = index; i < size_; i++)
        arr_[i] = arr_[i + 1];
    size_ -= 1;
}
template<typename T> void dynamicArray<T>::insert(const T& v, short index){
    if(index > size_)
        return;
    if(size_ == capacity_)
        resize();
    for(int i = size_ + 1; i > index; i--)
        arr_[i] = arr_[i - 1];
    arr_[index] = v;
    size_ ++;
}

