#include <QCoreApplication>
#include <hashtable.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    hashtable <int, int> mytable;
    mytable.Add(7,1);
    mytable.Add(8,2);
    mytable.Add(9,3);
    mytable.Add(10,1);
    mytable.Add(11,2);
    mytable.Add(12,3);
//    qDebug() << mytable.Remove(21);
//    qDebug() << mytable.Remove(14);
//    qDebug() << mytable.Remove(7);
//    qDebug() << mytable.Remove(8);
//    qDebug() << mytable.Remove(7);
//    qDebug() << mytable.Contains(21);
    return a.exec();
}
