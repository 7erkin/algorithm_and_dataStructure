/*Хеш таблица, с методом решения коллизий в виде списков. Реализована в виде указателя на указатели на списки.
Хеш функция представлена в виде простой функции нахождения остатка от деления ключа на размер таблицы. Размер таблицы есть простое число.
При превышении коэффициента заполненности, происходит автоматическое перехеширование в таблицу, размер которой удовлеторяет двум условиям
1. размер не меньше удвоенного размера предыдущей таблицы
2. простое число
Указать пороговый коэффициент переполнения можно, передав его значение в конструктор, при создании объекта. По умолчанию коэффициент = 1.
Коэффициент не может быть больше 1.
Метод решения коллизий в виде связных список предполагает, что элементы с одинаковым хеш ключом попадают в один связный список.
Размер таблицы по умолчанию = 7. Его можно задать заранее (чтобы не тратить время на перехеширование), передав соответствующее значение
в конструктор. Для уменьшения коллизий и создания относительной равномерности заполнения хеш таблицы, рекомендуется задавать размер
таблицы в виде простого числа.
*/

template <typename T1, typename T2>
class hashtable{
private:
    struct listnode{
        listnode* pointerToNextNode_;
        T1 key_;
        T2 value_;
    };
    int sizeTable_; //размер таблицы
    double loadFactor_; //коэффициент заполнения
    listnode** pointerToHashTable_; //указатель на указатели
    int elementsInHashtable_; //количество пар ключ-значение хранящихся в таблицы
private:
    bool isEvolution(){ //проверка на превышение коэффициента заполнения
        if(getLoadFactor() >= loadFactor_)
            return true;
        return false;
    }
    double getLoadFactor(){ //расчёт коэффициента заполнения
        int sum = 0;
        for(int i = 0; i < sizeTable_; i++)
            if(pointerToHashTable_[i] != nullptr)
                sum += 1;
        return 1.0f * sum/sizeTable_;
    }
public:
    hashtable(double loadFactor = 1, int sizeTable = 7); //конструктор
    void addValue(T1 key, T2 value); //добавление ключа в таблицу
    int hashfunction(T1 key); //хеш функция
    bool isKeyInHashtable(T1 key); //проверка на наличие ключа в таблице
    bool remove(T1 key); //удаление пары по ключу
    void doHashEvolution(); //перехеширование
    int getSizeTable(){return sizeTable_;} //возвращает размер таблицы
    int getElementsInHashtable(){return elementsInHashtable_;} //возвращает количество пар ключ-значение в таблице
};

template<typename T1, typename T2>
hashtable<T1, T2>::hashtable(double loadFactor, int sizeTable){
    elementsInHashtable_ = 0;
    loadFactor_ = loadFactor;
    sizeTable_ = sizeTable;
    pointerToHashTable_ = new listnode* [sizeTable_];
    for(int i = 0; i < sizeTable_; i++)
        pointerToHashTable_[i] = nullptr;
}

template<typename T1, typename T2>
void hashtable<T1, T2>::addValue(T1 key, T2 value){ //все элементы добавляем в начало списка
    int index = hashfunction(key);
    listnode* temp = new listnode;
    temp->key_ = key; temp->value_ = value;
    if(pointerToHashTable_[index] == nullptr){
        temp->pointerToNextNode_ = nullptr;
        pointerToHashTable_[index] = temp;
        elementsInHashtable_++;
        if(isEvolution())
            doHashEvolution();
        return;
    }
    temp->pointerToNextNode_ = pointerToHashTable_[index];
    pointerToHashTable_[index] = temp;
    elementsInHashtable_++;
}

template<typename T1, typename T2>
int hashtable<T1, T2>::hashfunction(T1 key){
    return key % sizeTable_;
}

template<typename T1, typename T2>
bool hashtable<T1, T2>::isKeyInHashtable(T1 key){
    int index = hashfunction(key);
    listnode* temp;
    temp = pointerToHashTable_[index];
    if(temp == nullptr)
        return false;
    for(;temp != nullptr; temp = temp->pointerToNextNode_)
        if(temp->key_ == key)
            return true;
}
template<typename T1, typename T2>
bool hashtable<T1, T2>::remove(T1 key){
   int index = hashfunction(key);
   listnode* temp;
   temp = pointerToHashTable_[index];
   if(temp == nullptr)  //если список пуст
       return false;
   if(temp->key_ == key && temp->pointerToNextNode_ != nullptr){ //если удаляем первый элемент в списке
       pointerToHashTable_[index] = temp->pointerToNextNode_;
       delete temp;
       return true;
   }
   if(temp->key_ == key && temp->pointerToNextNode_ == nullptr){ //если элемент в спике единственный
       pointerToHashTable_[index] = nullptr;
       delete temp;
       return true;
   }
   listnode* previous = temp;
   for(temp = temp->pointerToNextNode_; temp->pointerToNextNode_ != nullptr; temp = temp->pointerToNextNode_){
       if(temp->key_ == key){
           previous->pointerToNextNode_ = temp->pointerToNextNode_;
           delete temp;
           return true;
       }
   }
   if(temp->key_ == key){
       previous->pointerToNextNode_ = nullptr;
       delete temp;
       return true;
   }
   return false;
}
template<typename T1, typename T2>
void hashtable<T1, T2>::doHashEvolution(){
    listnode* temp;
    T1* var1 = new T1[elementsInHashtable_]; T2* var2 = new T2[elementsInHashtable_]; //два массива для записи пар ключ-значение
    int quantity = elementsInHashtable_;
    for(int i = 0, j = 0; i < sizeTable_; i++){
        temp = pointerToHashTable_[i];
        for(;temp != nullptr; temp = temp->pointerToNextNode_){
            var1[j] = temp->key_;
            var2[j] = temp->value_;
            j++;
        }
        delete pointerToHashTable_[i];
    }
    delete [] pointerToHashTable_;
    int simple_number;
    //выберем простое число в качестве значения размера таблицы
    for(int i = 2*sizeTable_ + 1; i != 0; i++)
        if(i%2 != 0 && i%3 != 0 && i%5 != 0 && i%7 != 0){
            simple_number = i;
            break;
        }
    sizeTable_ = simple_number;
    elementsInHashtable_ = 0;
    pointerToHashTable_ = new listnode* [sizeTable_];
    for(int i = 0; i < sizeTable_; i++)
        pointerToHashTable_[i] = nullptr;
    for(int i = 0; i < quantity; i++)
        addValue(var1[i], var2[i]);
}

