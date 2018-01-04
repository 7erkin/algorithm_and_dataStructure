#ifndef HEAP_H
#define HEAP_H

#include <memory>
#include <dynamicarray.h>

enum class compareCriterions {GREATER, LESS};     //определяет порядок кучи

template <typename T, compareCriterions compareCriterion = compareCriterions::LESS>
class heap{
private:
    int elementsInHeap_;                                            //количество элементов в куче
    dynamicArray <T> array_;
private:
    bool doComparation(const T& var1, const T& var2);
public:
    heap(){elementsInHeap_ = 0;}
    ~heap() = default;
    void addValue(const T& value);                                         //добавить значение в кучу
    T removeFirst();                                             //удаляет корень дерева и возвращает его значение
    T returnFirst(){return array_[0];}                            //возвращает значение корня дерева
    int getSize(){
        return elementsInHeap_;
    }
    bool isEmpty(){
        return elementsInHeap_ == 0 ? true : false;
    }
    std::unique_ptr<dynamicArray<T>> sortHeap();
};

template<typename T, compareCriterions compareCriterion>
std::unique_ptr<dynamicArray<T>> heap<T, compareCriterion>::sortHeap(){
    std::unique_ptr<dynamicArray<T>> exit_code(new dynamicArray<T>);
    exit_code->reserve(elementsInHeap_);
    int tmp = elementsInHeap_;
    for(int i = 0; i < tmp; i++)
        exit_code->pushBack(removeFirst());
    return move(exit_code);
}
template <typename T, compareCriterions compareCriterion>
bool heap<T, compareCriterion>::doComparation(const T& var1, const T& var2){
    if(compareCriterion == compareCriterions::LESS)
        return var1 < var2 ? true : false;
    else
        return !(var1 < var2) ? true : false;
}
template <typename T, compareCriterions compareCriterion>
void heap<T, compareCriterion>::addValue(const T& value){
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
template <typename T, compareCriterions compareCriterion>
T heap<T, compareCriterion>::removeFirst(){
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

#endif // HEAP_H
