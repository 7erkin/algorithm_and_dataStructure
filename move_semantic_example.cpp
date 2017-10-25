#include <QCoreApplication>
#include <QDebug>
using namespace std;

class SSS
{
    int x, y;
    int* arr;
public:
   SSS() : x(10), y(10){//обычный конструктор
       arr = new int[10];
       for(int i = 0; i < 10; i++)
           arr[i] = i;
       qDebug() << "Simple construct...";
   }
   SSS(const SSS& obj) : x(obj.x), y(obj.y){//конструктор копии
       arr = new int[10];
       for(int i = 0; i < 10; i++)
           arr[i] = obj.arr[i];
       qDebug() << "Copy construct...";
   }
   SSS(SSS&& obj) : x(obj.x), y(obj.y), arr(obj.arr){//перемещающий конструктор
       obj.arr = nullptr;
       qDebug() << "Move construct...";
   }
   SSS& operator = (SSS&& obj){//перемещающий оператор присваивания
       x = obj.x;
       y = obj.y;
       arr = obj.arr;
       obj.arr = nullptr;
       qDebug() << "Move assignment...";
       return *this;
   }
   SSS& operator = (const SSS& obj){//копирующий оператор присваивания
       x = obj.x;
       y = obj.y;
       for(int i = 0; i < 10; i++)
           arr[i] = obj.arr[i];
       qDebug() << "Copy assignment...";
       return *this;
   }
   ~SSS(){
       if(arr != nullptr){
           delete [] arr;
           qDebug() << "Destructor for not moved object";
           return;
       }
       qDebug() << "Destructor for moved object";
   }
};

void process(SSS& ){ //принимаем lvalue ссылку
    qDebug() << "&" << endl;
}
void process(SSS&& ){//принимаем rvalue ссылку, это не универсальная ссылка
    qDebug() << "&&" << endl;
}
template <typename T> void fun1(T&& obj){//аргумент есть универсальная ссылка (т.к. универсальная ссылка = вывод типа + T&&)
    process(forward<T>(obj));
}
template <typename T> T&& fun2(T&& obj){//аргумент есть универсальная ссылка
    return(forward<T>(obj));
}

int main()
{
    SSS ob1{};
    SSS ob2(ob1);
    SSS ob3(move(ob1));
    SSS ob4 {};
    ob4 = move(ob2);
    qDebug() << "**********";
    SSS ob5{};
    fun1(fun2(ob5));
    fun1(fun2(move(ob5)));
}
