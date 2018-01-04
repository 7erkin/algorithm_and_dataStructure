template<typename T>
class queue{
    struct listnode{
      listnode previous_; //указатель на предыдущий узел
      T valueInNode_; //содержимое узла
    };
    listnode* pointerToFirstElement_; //указатель на последний элемент очереди
    listnode* pointerToLastElement_; //указатель на первый элемент очереди
public:
    queue(){pointerToFirstElement_ = nullptr; pointerToLastElement_ = nullptr;}
    void push(const T& v); //добавляет элемент в конец списка
    T pop(); //удаляет и возвращает элемент из начала списка
    T peek(); //возвращает элемент из начала списка
    void clear(); //удаляет список
};

template<typename T>
void queue<T>::clear(){
    listnode* temp;
    do{
        temp = pointerToLastElement_;
        pointerToLastElement_ = pointerToLastElement_->previous_;
        delete temp;
    }while(pointerToLastElement_ != nullptr);
    pointerToFirstElement_ = nullptr;
    pointerToLastElement_ = nullptr;
}

template <typename T>
void queue<T>::push(const T& v){
    listnode* node = new listnode;
    node->valueInNode_ = v;
    if(pointerToFirstElement_ == nullptr){
        pointerToFirstElement_ = node;
        pointerToLastElement_ = node;
        return;
    }
    pointerToFirstElement_->previous_ = node;
    node->previous_ = nullptr;
    pointerToFirstElement_ = node;
}

template <typename T>
T queue<T>::pop(){
    if(pointerToFirstElement_ == nullptr)
        return 0;
    T var;
    if(pointerToFirstElement_ == pointerToLastElement_){
        var = pointerToFirstElement_->valueInNode_;
        delete pointerToFirstElement_;
        pointerToFirstElement_ = nullptr;
        pointerToLastElement_ = nullptr;
        return var;
    }
    listnode* temp;
    temp = pointerToLastElement_;
    var = temp->valueInNode_;
    pointerToLastElement_ = pointerToLastElement_->previous_;
    delete temp;
    return var;
}

template <typename T>
T queue<T>::peek(){
    if(pointerToLastElement_ != nullptr)
        return pointerToLastElement_->valueInNode_;
    return 0;
}

