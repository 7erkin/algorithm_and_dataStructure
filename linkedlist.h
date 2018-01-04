template <typename T> class LinkedList
{
private:
    //структура описывает структуру узла списка
    struct listnode{
        listnode* nextNode_; //указатель на следующий узел списка
        T valueInNode_; //значение узла списка
    };
    int elementsInList_; //количество элементов в списке
    listnode* pointerToFirstElement_; //указатель на первый узел списка
    listnode* pointerToLastElement_; //указатель на последний узел списка
private:
    void initialize() //начальная инициализация
    {
        pointerToFirstElement_ = nullptr;
        pointerToLastElement_ = nullptr;
        elementsInList_ = nullptr;
    }
public:
    LinkedList(){initialize();}
    ~LinkedList();
    bool pushBack(const T& value); //добавляет элемент в конец списка
    bool pushFront(const T& value); //добавляет элемент в конец списка
    bool isEmpty(); //проверка пустой список или нет
    bool removeFront(); //удаляет элемент из начала списка
    bool removeBack(); //удаляет элемент из конца списка
    bool remove(const int& index); //удаляет элемент по номеру в списке
    int isValueInList(const T& value); //проверяет наличие элемента в списке
    bool clear(); //очищает список
    int getElementsInList(){return elementsInList_;}
    T operator [] (const int& index); //возвращает элемент списка по номеру
};

template<typename type> LinkedList<type>::~LinkedList(){
    clear();
}
template <typename T> T LinkedList<T>::operator [](const int& index)
{
    if(index - getElementsInList() > 0){
        return -1;
    }
    listnode* temp = pointerToFirstElement_;
    for(int i = 0;; temp = temp->nextNode_, i++)
        if(i == index)
            break;
    return temp->valueInNode_;
}

template <typename type> bool LinkedList<type>::pushFront(const type& v)
{
    try{
        listnode* p_new = new listnode; //создаём новый узел
        p_new->valueInNode_ = v; //присваиваем значение узлу
        p_new->nextNode_ = pointerToFirstElement_; //обнуляем указатель на следующий элемент
        if(pointerToFirstElement_ == nullptr)
            pointerToLastElement_ = p_new;
        pointerToFirstElement_ = p_new;
        elementsInList_++; //увеличиваем число элементов
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::pushBack(const type& v)
{
    try{
        listnode* p_new = new listnode; //создаём новый узел
        p_new->valueInNode_ = v; //присваиваем значение узлу
        p_new->nextNode_ = nullptr; //обнуляем указатель на следующий элемент
        if(pointerToFirstElement_ == nullptr) //если список пустой, то указатель на начало и на конец списка ссылаются на один единственный элемент
            pointerToFirstElement_ = p_new;
        else
            pointerToLastElement_->nextNode_ = p_new; //связываем последний элемент списка с добавляемым в список элемент
        pointerToLastElement_ = p_new; //переносим указатель на последний элемент на добавленный в список элемент
        elementsInList_++;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::removeFront()
{
    try{
        if(pointerToFirstElement_ == nullptr)
            return true;
        listnode* temp;
        temp = pointerToFirstElement_;
        if(pointerToFirstElement_ == pointerToLastElement_){
            delete temp;
            initialize();
            return true;
        }
        pointerToFirstElement_ = pointerToFirstElement_->nextNode_;
        delete temp;
        elementsInList_--;
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::removeBack()
{
    try{
        if(pointerToFirstElement_ == nullptr)
            return true;
        listnode* temp;
        temp = pointerToFirstElement_;
        if(pointerToFirstElement_ == pointerToLastElement_){
            delete temp;
            initialize();
            return true;
        }
        for(;temp->nextNode_ != pointerToLastElement_; temp = temp->nextNode_);
        pointerToLastElement_ = temp;
        temp = temp->nextNode_;
        pointerToLastElement_->nextNode_ = nullptr;
        delete temp;
        elementsInList_--;
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::remove(const int& index)
{
    try{
        if(index - elementsInList_ >= 0)
            return false;
        if(index == 0)
            return removeFront();
        if(index == elementsInList_ - 1)
            return removeBack();
        listnode* current = pointerToFirstElement_->nextNode_;
        listnode* previous = pointerToFirstElement_;
        for(int i = 1;; current = current->nextNode_, previous = previous->nextNode_)
            if(i == index){
                previous->nextNode_ = current->nextNode_;
                delete current;
                return true;
            }
    }
    catch(...){
        return false;
    }
}

template <typename type> int LinkedList<type>::isValueInList(const type& v)
{
    try{
        int i = 0;
        listnode* temp = pointerToFirstElement_; //создаём указатель, для прохода по списку
        do{
            if(temp->valueInNode_ == v) //если значение в узле совпало с переданным в функцию значением
                return i; //эдлемент найден
            temp = temp->nextNode_; //иначе перемещаемся на следующий элемент
            i++;
        }while(temp != nullptr);
        return -1;
    }
    catch(...){
        return -1;
    }
}

template <typename type> bool LinkedList<type>::clear()
{
    try{
        if(pointerToFirstElement_ == nullptr)
            return true;
        listnode* temp = pointerToFirstElement_;
        do{
            pointerToFirstElement_ = temp->nextNode_;
            delete temp;
            temp = pointerToFirstElement_;
        }while(pointerToFirstElement_ != nullptr);
        initialize();
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::isEmpty()
{
    if(pointerToFirstElement_ == nullptr)
        return true;
    return false;
}

