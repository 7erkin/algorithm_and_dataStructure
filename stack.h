
//структура, описывающая элемент стека
template <typename type> struct listnode
{
    type value; //значение узла
    listnode <type>* previous; //указатель на предыдущий узел
};

template <typename type> class stack
{
    listnode<type>* p_first; //указатель на первый на удаление в стеке узел
public:
    stack()
    {
        p_first = 0; //обнуляем при создании стека (стек пуст)
    }
    void Push(type value); //функция добавления элемента
    type Pop(); //функция удаления элемента. При добавлении элемент возвращается функцией
    type Peek(); //функция, которая возвращает элемент из стека, который стоит первым на удаление
};

template <typename type> void stack <type>::Push(type value)
{
    listnode<type>* node = new listnode<type>; //создаётся новый узел
    node->value = value; //присваиваем значение узлу
    if(p_first == 0) //если лист пустой
    {
        p_first = node; //указателю присваиваем первый элемент, он же первый элемент в списке
        p_first->previous = 0; //обнуляем указатель на предыдущий элемент. Список же пустой
        return;
    }
    node->previous = p_first; //связываем последний элемент с предпоследним
    p_first = node; //устанавливаем указатель на добаленный элемент. Он же последний и первый на удаление
}

template<typename type> type stack <type>::Pop()
{
    if(p_first != 0) //если стек не пуст
    {
        int ret_val = p_first->value; //запоминаем значение узла
        listnode <type>* temp = p_first; //создаём новый указатель на узел, который ссылается на удаляемый элемент
        p_first = p_first->previous; //перемещаем наш указатель на предыдущий перед удаляемым элементом элемент
        delete temp; //удаляем узел
        return ret_val; //возвращаем значение удаленного узла
    }
    return 0;
}

template<typename type> type stack <type>::Peek()
{
    if(p_first != 0) //если стек не пуст
        return p_first->value; //возвращаем значение первого на удаление элемента
    return 0;
}
