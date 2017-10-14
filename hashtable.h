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

//узел списка
template <typename type1, typename type2> struct listnode{
    listnode<type1, type2>* next;
    type1 key;
    type2 value;
};

template <typename type1, typename type2> class hashtable{
    int size; //размер таблицы
    double LOAD_FACTOR; //коэффициент заполнения
    listnode<type1, type2>** table; //указатель на указатели
    bool is_evolution(){ //проверка на превышение коэффициента заполнения
        if(load_factor() >= LOAD_FACTOR)
            return true;
        return false;
    }
    double load_factor(){ //расчёт коэффициента заполнения
        int sum = 0;
        for(int i = 0; i < size; i++)
            if(table[i] != 0)
                sum += 1;
        return 1.0f*sum/size;
    }
    int quantity; //количество пар ключ-значение хранящихся в таблицы
public:
    hashtable(double L_FACTOR = 1, int SIZE = 7); //конструктор
    void Add(type1 key, type2 value); //добавление ключа в таблицу
    int hashfunction(type1 key); //хеш функция
    bool Contains(type1 key); //проверка на наличие ключа в таблице
    bool Remove(type1 key); //удаление пары по ключу
    void hash_evolution(); //перехеширование
    int get_size(){return size;} //возвращает размер таблицы
    int qet_quantity(){return quantity;} //возвращает количество пар ключ-значение в таблице
};

template<typename type1, typename type2> hashtable<type1, type2>::hashtable(double L_FACTOR, int SIZE){
    quantity = 0;
    LOAD_FACTOR = L_FACTOR;
    size = SIZE;
    table = new listnode<type1, type2>* [size];
    for(int i = 0; i < size; i++)
        table[i] = 0;
}

template<typename type1, typename type2> void hashtable<type1, type2>::Add(type1 key, type2 value){ //все элементы добавляем в начало списка
    int index = hashfunction(key);
    listnode<type1, type2>* temp = new listnode<type1, type2>;
    temp->key = key; temp->value = value;
    if(table[index] == 0){
        temp->next = 0;
        table[index] = temp;
        quantity++;
        if(is_evolution())
            hash_evolution();
        return;
    }
    temp->next = table[index];
    table[index] = temp;
    quantity++;
}

template<typename type1, typename type2> int hashtable<type1, type2>::hashfunction(type1 key){
    return key % size;
}

template<typename type1, typename type2> bool hashtable<type1, type2>::Contains(type1 key){
    int index = hashfunction(key);
    listnode<type1, type2>* temp;
    temp = table[index];
    if(temp == 0)
        return false;
    for(;temp != 0; temp = temp->next)
        if(temp->key == key)
            return true;
}
template<typename type1, typename type2> bool hashtable<type1, type2>::Remove(type1 key){
   int index = hashfunction(key);
   listnode<type1, type2>* temp;
   temp = table[index];
   if(temp == 0)  //если список пуст
       return false;
   if(temp->key == key && temp->next != 0){ //если удаляем первый элемент в списке
       table[index] = temp->next;
       delete temp;
       return true;
   }
   if(temp->key == key && temp->next == 0){ //если элемент в спике единственный
       table[index] = 0;
       delete temp;
       return true;
   }
   listnode<type1, type2>* previous = temp;
   for(temp = temp->next; temp->next != 0; temp = temp->next){
       if(temp->key == key){
           previous->next = temp->next;
           delete temp;
           return true;
       }
   }
   if(temp->key == key){
       previous->next = 0;
       delete temp;
       return true;
   }
   return false;
}
template<typename type1, typename type2> void hashtable<type1, type2>::hash_evolution(){
    listnode<type1, type2>* temp;
    type1* var1 = new type1[quantity]; type2* var2 = new type2[quantity]; //два массива для записи пар ключ-значение
    int Q = quantity;
    for(int i = 0, j = 0; i < size; i++){
        temp = table[i];
        for(;temp != 0; temp = temp->next){
            var1[j] = temp->key;
            var2[j] = temp->value;
            j++;
        }
        delete table[i];
    }
    delete [] table;
    int simple_number;
    //выберем простое число в качестве значения размера таблицы
    for(int i = 2*size + 1; i != 0; i++)
        if(i%2 != 0 && i%3 != 0 && i%5 != 0 && i%7 != 0){
            simple_number = i;
            break;
        }
    size = simple_number;
    quantity = 0;
    table = new listnode<type1, type2>* [size];
    for(int i = 0; i < size; i++)
        table[i] = 0;
    for(int i = 0; i < Q; i++)
        Add(var1[i], var2[i]);
}

