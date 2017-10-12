template <typename type> struct listnode
{
  listnode<type>* previous; //указатель на предыдущий узел
  type value; //содержимое узла
};

template<typename type> class queue
{
    listnode<type>* p_first; //указатель на последний элемент очереди
    listnode<type>* p_last; //указатель на первый элемент очереди
public:
    queue(){p_first = 0; p_last = 0;}
    void Push(const type& v); //добавляет элемент в конец списка
    type Pop(); //удаляет и возвращает элемент из начала списка
    type Peek(); //возвращает элемент из начала списка
    void Clear(); //удаляет список
};

template<typename type> void queue<type>::Clear(){
    listnode<type>* temp;
    do{
        temp = p_last;
        p_last = p_last->previous;
        delete temp;
    }while(p_last != 0);
    p_first = 0;
    p_last = 0;
}

template <typename type> void queue<type>::Push(const type& v){
    listnode<type>* node = new listnode<type>;
    node->value = v;
    if(p_first == 0){
        p_first = node;
        p_last = node;
        return;
    }
    p_first->previous = node;
    node->previous = 0;
    p_first = node;
}

template <typename type> type queue<type>::Pop(){
    if(p_first == 0)
        return 0;
    type var;
    if(p_first == p_last){
        var = p_first->value;
        delete p_first;
        p_first = 0;
        p_last = 0;
        return var;
    }
    listnode<type>* temp;
    temp = p_last;
    var = temp->value;
    p_last = p_last->previous;
    delete temp;
    return var;
}

template <typename type> type queue<type>::Peek(){
    if(p_last != 0)
        return p_last->value;
    return 0;
}

