#include <iostream>
#include <memory>

using namespace std;

template <typename type> class dynamicArray;
enum class compareCriterions {GREATER, LESS};     //определяет порядок кучи

template <typename T, compareCriterions compareCriterion = compareCriterions::LESS>
class heap{
private:
    int elementsInHeap_;                                            //количество элементов в куче
    dynamicArray <T> array_;
private:
    bool doComparation(T var1, T var2);
public:
    heap(){elementsInHeap_ = 0;}
    ~heap() = default;
    void addValue(T value);                                         //добавить значение в кучу
    T removeFirst();                                             //удаляет корень дерева и возвращает его значение
    T returnFirst(){return array_[0];}                            //возвращает значение корня дерева
    void showHeap(){
        for(int i = 0; i < elementsInHeap_; i++)
            cout << array_[i] << " ";
        cout << endl;
    }
    int getSize(){
        return elementsInHeap_;
    }
    bool isEmpty(){
        return elementsInHeap_ == 0 ? true : false;
    }
    unique_ptr<dynamicArray<T>> sortHeap();
};

template<typename T, compareCriterions compareCriterion>
unique_ptr<dynamicArray<T>> heap<T, compareCriterion>::sortHeap(){
    unique_ptr<dynamicArray<T>> exit_code(new dynamicArray<T>);
    exit_code->reserve(elementsInHeap_);
    int tmp = elementsInHeap_;
    for(int i = 0; i < tmp; i++)
        exit_code->pushBack(removeFirst());
    return move(exit_code);
}
template <typename T, compareCriterions compareCriterion> bool heap<T, compareCriterion>::doComparation(T var1, T var2){
    if(compareCriterion == compareCriterions::LESS)
        return var1 < var2 ? true : false;
    else
        return !(var1 < var2) ? true : false;
}
template <typename T, compareCriterions compareCriterion> void heap<T, compareCriterion>::addValue(T value){
    array_.pushBack(value);                                                       //добавляем элемент в вектор
    T temp;
    int index = elementsInHeap_;
    elementsInHeap_++;
    while(true){                                                            //производим упорядочивание массива согласно правилам кучи
        if(index == 0)
            break;
        if(index % 2 == 0){
            if(doComparation(array_[int(index - 1)/2],array_[index]))
                break;
            else{
                temp = array_[int((index - 1)/2)];
                array_[int(index - 1)/2] = array_[index];
                array_[index] = temp;
                index = int((index - 1)/2);
                continue;
            }
        }
        if(index % 2 != 0){
            if(doComparation(array_[int(index/2)],array_[index]))
                break;
            else{
                temp = array_[int(index/2)];
                array_[int(index/2)] = array_[index];
                array_[index] = temp;
                index = int(index/2);
                continue;
            }
        }
    }
}
template <typename T, compareCriterions compareCriterion> T heap<T, compareCriterion>::removeFirst(){
    T temp = array_[0];
    int i = 0;
    array_[0] = array_[elementsInHeap_ - 1];
    array_[elementsInHeap_ - 1] = temp;
    elementsInHeap_--;
    while(true){
        if(2*i + 2 > elementsInHeap_ - 1){
            if(2*i + 1 > elementsInHeap_ - 1)
                break;
            else{
                if(!doComparation(array_[i], array_[2*i + 1])){
                    T tmp = array_[i];
                    array_[i] = array_[2*i + 1];
                    array_[2*i + 1] = tmp;
                    break;
                }
                break;
            }
        }
        if(doComparation(array_[2*i + 1], array_[2*i + 2])){
            if(doComparation(array_[i], array_[2*i + 1])) // nothing to do
                break;
            else{
                T tmp = array_[i];
                array_[i] = array_[2*i + 1];
                array_[2*i + 1] = tmp;
                i = 2*i + 1;
            }
        }
        else{
            if(doComparation(array_[i], array_[2*i + 2])) // nothing to do
                break;
            else{
                T tmp = array_[i];
                array_[i] = array_[2*i + 2];
                array_[2*i + 2] = tmp;
                i = 2*i + 2;
            }
        }
    }
    return temp;
}

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

struct usersType{
    usersType(double initValue = 10, char symbol = 'a') : value(initValue), ch(symbol){}
    double value;
    char ch;
    bool operator < (const usersType& obj){
        return (value < obj.value) && (ch < obj.ch) ? true : false;
    }
};

int main(){
    heap<int, compareCriterions::GREATER> h;
    h.addValue(10);
    h.addValue(40);
    h.addValue(30);
    h.addValue(20);
    h.addValue(5);
    h.addValue(7);
    h.addValue(25);
    h.addValue(101);

    unique_ptr<dynamicArray<int>> sortResult = h.sortHeap();
    for(int i = 0; i < sortResult->getSize(); i++)
        cout << sortResult->operator[](i) << " ";
}
