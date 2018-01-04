template <typename T>
class stack
{
    struct listnode{                                           //структура, описывающая элемент стека
        T valueInNode_;                                        //значение узла
        listnode* pointerToPreviouseNode_;                     //указатель на предыдущий узел
    };
    listnode* pointerToFirstElement;                           //указатель на первый на удаление в стеке узел
public:
    stack(){
        pointerToFirstElement = nullptr;                       //обнуляем при создании стека (стек пуст)
    }
    void push(const T& value);                                 //функция добавления элемента
    T pop();                                                   //функция удаления элемента. При удалении элемент возвращается функцией
    T peek();                                                  //функция, которая возвращает элемент из стека, который стоит первым на удаление
};

template <typename T>
void stack <T>::push(const T& value)
{
    listnode* node = new listnode; //создаётся новый узел
    node->valueInNode_ = value; //присваиваем значение узлу
    if(pointerToFirstElement == nullptr) //если лист пустой
    {
        pointerToFirstElement = node; //указателю присваиваем первый элемент, он же первый элемент в списке
        pointerToFirstElement->pointerToPreviouseNode_ = nullptr; //обнуляем указатель на предыдущий элемент. Список же пустой
        return;
    }
    node->pointerToPreviouseNode_ = pointerToFirstElement; //связываем последний элемент с предпоследним
    pointerToFirstElement = node; //устанавливаем указатель на добаленный элемент. Он же последний и первый на удаление
}

template<typename T>
T stack <T>::pop()
{
    if(pointerToFirstElement != nullptr) //если стек не пуст
    {
        int exitCode = pointerToFirstElement->valueInNode_; //запоминаем значение узла
        listnode* temp = pointerToFirstElement; //создаём новый указатель на узел, который ссылается на удаляемый элемент
        pointerToFirstElement = pointerToFirstElement->pointerToPreviouseNode_; //перемещаем наш указатель на предыдущий перед удаляемым элементом элемент
        delete temp; //удаляем узел
        return exitCode; //возвращаем значение удаленного узла
    }
    return -1;
}

template<typename T>
T stack <T>::peek()
{
    if(pointerToFirstElement != nullptr) //если стек не пуст
        return pointerToFirstElement->valueInNode_; //возвращаем значение первого на удаление элемента
    return -1;
}
