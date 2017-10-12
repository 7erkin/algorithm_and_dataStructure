#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <QDebug>

template <typename type1, typename type2> struct listnode
{
    listnode<type1, type2>* next;
    listnode<type1 ,type2>* previous;
    type1 key;
    type2 value;
};

template <typename type1, typename type2> class hashtable
{
    int size;
    listnode<type1, type2>** table;
    double LOAD_FACTOR;
    bool is_evolution()
    {
        if(load_factor() >= LOAD_FACTOR)
            return true;
        return false;
    }
    double load_factor()
    {
        int sum = 0;
        for(int i = 0; i < size; i++)
            if(table[i] != 0)
                sum += 1;
        return 1.0f*sum/size;
    }
public:
    hashtable();
    void Add(type1 key, type2 value);
    int hashfunction(type1 key);
    bool Contains(type1 key);
    bool Remove(type1 key);
    void hash_evolution();
    int get_size(){return size;}
};

template<typename type1, typename type2> hashtable<type1, type2>::hashtable()
{
    LOAD_FACTOR = 0.75;
    size = 7;
    table = new listnode<type1, type2>* [size];
    for(int i = 0; i < size; i++)
        table[i] = 0;
}

//добавляем в начало, нужен один указатель
template<typename type1, typename type2> void hashtable<type1, type2>::Add(type1 key, type2 value)
{
    qDebug () << "a"; //RIGHT HERE!
    int index = hashfunction(key);
    listnode<type1, type2>* temp; temp = new listnode<type1, type2>;
    temp->key = key; temp->value = value;
    if(table[index] == 0)
    {
        temp->previous = 0;
        temp->next = 0;
        table[index] = temp;
        qDebug() << load_factor();
        if(is_evolution())
            hash_evolution();
        return;
    }
    table[index]->previous = temp;
    temp->next = table[index];
    table[index] = temp;
    table[index]->previous = 0;
}
template<typename type1, typename type2> int hashtable<type1, type2>::hashfunction(type1 key)
{
    return key % size;
}
template<typename type1, typename type2> bool hashtable<type1, type2>::Contains(type1 key)
{
    int index = hashfunction(key);
    listnode<type1, type2>* temp = new listnode<type1, type2>;
    temp = table[index];
    if(temp == 0)
        return false;
    for(;temp->next != 0; temp = temp->next)
        if(temp->key == key)
            return true;
    if(temp->key == key)
        return true;
    return false;
}
template<typename type1, typename type2> bool hashtable<type1, type2>::Remove(type1 key)
{
   int index = hashfunction(key);
   listnode<type1, type2>* temp = new listnode<type1, type2>;
   temp = table[index];
   if(temp == 0)
       return false;
   if(temp->key == key && temp->previous == 0 && temp->next != 0)
   {
       table[index] = temp->next;
       table[index]->previous = 0;
       return true;
   }
   if(temp->key == key && temp->previous == 0 && temp->next == 0)
   {
       table[index] = 0;
       return true;
   }
   for(;temp->next != 0; temp = temp->next)
   {
       if(temp->key == key)
       {
           temp->previous->next = temp->next;
           temp->next->previous = temp->previous;
           return true;
       }
   }
   if(temp->key == key)
   {
       temp->previous->next = 0;
       return true;
   }
   return false;
}
template<typename type1, typename type2> void hashtable<type1, type2>::hash_evolution()
{
    int simple_number;
    //выберем простое число в качестве значения размера таблицы
    for(int i = 2*size + 1; i != 0; i++)
        if(i%2 != 0 && i%3 != 0 && i%5 != 0 && i%7 != 0)
        {
            simple_number = i;
            break;
        }
    listnode<type1, type2>** temp = new listnode<type1, type2>* [size];
    for(int i = 0; i < size; i++)
        temp[i] = table[i];
    table = new listnode<type1, type2>* [simple_number];
    //теперь все элементы temp перехешируем в table с новым размером
    int nsize = size;
    size = simple_number;
    int a, b;
    for(int i = 0; i < nsize; i++)
    {
        if(temp[i] == 0)
            continue;
        for(;temp[i] != 0; temp[i] = temp[i]->next)
            Add(temp[i]->key, temp[i]->value);
    }
}

#endif // HASHTABLE_H
