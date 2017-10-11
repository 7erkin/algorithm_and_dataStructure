#define NULL;

//структура описывает структуру узла списка
template <typename type> struct listnode
{
    listnode* next; //указатель на следующий узел списка
    type value; //значение узла списка
};

template <typename type> class LinkedList
{
    int NUM_NODE; //количество элементов в списке
    listnode <type>* p_next; //указатель на первый узел списка
    listnode <type>* p_tail; //указатель на последний узел списка
    void POINT_TO_ZERO() //начальная инициализация
    {
        p_next = 0;
        p_tail = 0;
        NUM_NODE = 0;
    }
 public:
    LinkedList(){POINT_TO_ZERO();}
    ~LinkedList();
    bool PushBack(const type& ); //добавляет элемент в конец списка
    bool PushFront(const type& ); //добавляет элемент в конец списка
    bool isEmpty(); //проверка пустой список или нет
    bool RemoveFront(); //удаляет элемент из начала списка
    bool RemoveBack(); //удаляет элемент из конца списка
    bool Remove(int index); //удаляет элемент по номеру в списке
    int Contains(const type& ); //проверяет наличие элемента в списке
    bool Clear(); //очищает список
    int ShowNumNode(){return NUM_NODE;}
    type operator [] (int index); //возвращает элемент списка по номеру
};

template<typename type> LinkedList<type>::~LinkedList()
{
    //Clear();
}
template <typename type> type LinkedList<type>::operator [](int index)
{
    if(index - ShowNumNode() > 0){
        return NULL;
    }
    listnode<type>* temp = p_next;
    for(int i = 0;; temp = temp->next, i++)
        if(i == index)
            break;
    return temp->value;
}

template <typename type> bool LinkedList<type>::PushFront(const type& v)
{
    try{
        listnode<type>* p_new = new listnode<type>; //создаём новый узел
        p_new->value = v; //присваиваем значение узлу
        p_new->next = p_next; //обнуляем указатель на следующий элемент
        if(p_next == 0)
            p_tail = p_new;
        p_next = p_new;
        NUM_NODE++; //увеличиваем число элементов
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::PushBack(const type& v)
{
    try{
        listnode<type>* p_new = new listnode<type>; //создаём новый узел
        p_new->value = v; //присваиваем значение узлу
        p_new->next = 0; //обнуляем указатель на следующий элемент
        if(p_next == 0) //если список пустой, то указатель на начало и на конец списка ссылаются на один единственный элемент
            p_next = p_new;
        else
            p_tail->next = p_new; //связываем последний элемент списка с добавляемым в список элемент
        p_tail = p_new; //переносим указатель на последний элемент на добавленный в список элемент
        NUM_NODE++;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::RemoveFront()
{
    try{
        if(p_next == 0)
            return true;
        listnode<type>* temp;
        temp = p_next;
        if(p_next == p_tail){
            delete temp;
            POINT_TO_ZERO();
            return true;
        }
        p_next = p_next->next;
        delete temp;
        NUM_NODE--;
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::RemoveBack()
{
    try{
        if(p_next == 0)
            return true;
        listnode<type>* temp;
        temp = p_next;
        if(p_next == p_tail){
            delete temp;
            POINT_TO_ZERO();
            return true;
        }
        for(;temp->next != p_tail; temp = temp->next);
        p_tail = temp;
        temp = temp->next;
        p_tail->next = 0;
        delete temp;
        NUM_NODE--;
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::Remove(int index)
{
    try{
        if(index - NUM_NODE >= 0)
            return false;
        if(index == 0)
            return RemoveFront();
        if(index == NUM_NODE - 1)
            return RemoveBack();
        listnode<type>* current = p_next->next;
        listnode<type>* previous = p_next;
        for(int i = 1;; current = current->next, previous = previous->next)
            if(i == index){
                previous->next = current->next;
                delete current;
                return true;
            }
    }
    catch(...){
        return false;
    }
}

template <typename type> int LinkedList<type>::Contains(const type& v)
{
    try{
        int i = 0;
        listnode<type>* temp = p_next; //создаём указатель, для прохода по списку
        do{
            if(temp->value == v) //если значение в узле совпало с переданным в функцию значением
                return i; //эдлемент найден
            temp = temp->next; //иначе перемещаемся на следующий элемент
            i++;
        }while(temp != 0);
        return -1;
    }
    catch(...){
        return -1;
    }
}

template <typename type> bool LinkedList<type>::Clear()
{
    try{
        if(p_next == 0)
            return true;
        listnode<type>* temp = p_next;
        do{
            p_next = temp->next;
            delete temp;
            temp = p_next;
        }while(p_next != 0);
        POINT_TO_ZERO();
        return true;
    }
    catch(...){
        return false;
    }
}

template <typename type> bool LinkedList<type>::isEmpty()
{
    if(p_next == 0)
        return true;
    return false;
}

