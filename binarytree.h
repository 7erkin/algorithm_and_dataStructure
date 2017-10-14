/*в методе Remove  рассмотрены случаи, когда 1) у удаляемого узла нет детей  2) когда у удаляемого узла есть только левый
ребенок 3) когда у удаляемого узла есть правый ребенок но без левого ребенка 4) когда у удаляемого узла есть правый ребенок, с
левым ребенком. В этом случае мы идем в самый левый узел дерева с корнем "правый ребенок удаляемого узла" и ставим его на место
удаляемого. НО! есть еще случай, когда у самого левого ребенка, может быть правый ребенок, поэтому этот случай тоже учитывается
в коде*/

#include <QDebug>


template <typename type> struct listnode{
    listnode<type>* _parent;                //указатель на родительский узел
    listnode<type>* _left;                  //указатель на левого потомка
    listnode<type>* _right;                 //указатель на правого потомка
    type _key;                              //значения узла
};

template <typename type> class BinaryTree{
    listnode<type>* p_node;                 //указатель на корень дерева
    void Preorder(listnode<type>* p);       //префиксный обход
    void Isforder(listnode<type>* p);       //исфиксный обход
    void Postorder(listnode<type>* p);      //постфиксный обход
    int quantity;                           //количество элементов в дереве
public:
    enum round {PREODRDER, ISFORDER, POSTORDER};   //для определения правила обхода дерева
    BinaryTree(){p_node = 0; quantity = 0;}        //конструктор
    void Add(type value);                          //метод добавления значения в дерево
    bool Contains(type value);                     //метод проверки существования значения в дереве
    bool Remove(type value);                       //метод удаления значения из дерева
    void TreeRound(round );                        //функция определения правила обхода дерева
    int QuantityOfElement(){return quantity;}      //количество узлов в дереве
};

template <typename type> void BinaryTree<type>::Add(type value){
    listnode<type>* node = new listnode<type>;      //выделяем память под новый узел
    node->_key = value;                             //инициализируем узел
    node->_left = 0;
    node->_right = 0;
    quantity++;
    if(p_node == 0){                                //если дерево пустое
        p_node = node;
        p_node->_parent = 0;
        return;
    }
    listnode<type>* temp = p_node;                  //если дерево не пустое
    while(1){                                       //поиск места для добавления узел
        if(value >= temp->_key){                    //идем вправо
            if(temp->_right != 0){
                temp = temp->_right;
                continue;
            }
            temp->_right = node;
            node->_parent = temp;
            return;
        }
        if(value < temp->_key){                     //идем влево
            if(temp->_left != 0){
                temp = temp->_left;
                continue;
            }
            temp->_left = node;
            node->_parent = temp;
            return;
        }
    }
}

template <typename type> bool BinaryTree<type>::Contains(type value){
    if(p_node == 0)               //если дерево пустое
        return false;
    listnode<type>* temp = p_node;//указатель для обхода по дереву
    while(1){
        if(value == temp->_key)   //нашли узел со значением, равному переданному в функцию
            return true;
        if(value >= temp->_key){  //не нашли, идем вправо
            if(temp->_right == 0) //если дальше идти некуда
                return false;     //узел не найден
            temp = temp->_right;
            continue;
        }
        if(value < temp->_key){   //не нашли, идем влево
            if(temp->_left == 0)  //если дальше идти некуда
                return false;     //узел не найден
            temp = temp->_left;
            continue;
        }
    }
}
template <typename type> bool BinaryTree<type>::Remove(type value){
    if(p_node == 0)                 //если дерево пусто
        return false;
    listnode<type>* temp = p_node;  //создаем указатель для поиска по дереву
    while(1){                       //в цикле находим указатель на удаляемый узел
        if(value == temp->_key)
            goto delete_it;         //если нашли узел, то поиск прошел успешно, и пора перейти к удалению узла (переходим по метке)
        if(value >= temp->_key){    //идем вправо
            if(temp->_right == 0)
                return false;
            temp = temp->_right;
            continue;
        }
        if(value < temp->_key){     //идем влево
            if(temp->_left == 0)
                return false;
            temp = temp->_left;
            continue;
        }
    }
    delete_it:                                               //сама метка. Начало болезненного процесса удаления узла из дерева
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЕСТЬ САМ КОРЕНЬ ==========
    if(temp->_parent == 0){
        if(temp->_left == 0 && temp->_right == 0){             //если дерево состоит из одного узла
            delete p_node;
            p_node = 0;
            quantity--;
            return true;
        }
        if(temp->_right == 0){                                 //если у корня есть левый ребенок но нет правого
            temp->_left->_parent = 0;
            p_node = temp->_left;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right != 0 && temp->_right->_left == 0){     //если у корня есть правый узел без левого ребенка
            temp->_right->_parent = 0;
            temp->_right->_left = temp->_left;
            temp->_left->_parent = temp->_right;
            p_node = temp->_right;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right->_left != 0){                           //у правого узла есть левый узел
            listnode<type>* temp1 = temp->_right->_left;
            for( ;temp1->_left != 0; temp1 = temp1->_left);     //смещаемся в самый левый узел
            if(temp1->_right != 0){                             //а если у самого левого узла есть еще и правый узел
                temp1->_parent->_left = temp1->_right;
                temp1->_right->_parent = temp1->_parent;
            }
            temp1->_parent->_left = 0;
            temp1->_parent = 0;
            temp1->_left = temp->_left;
            temp1->_right = temp->_right;
            temp->_left->_parent = temp1;
            temp->_right->_parent = temp1;
            p_node = temp1;
            delete temp;
            quantity--;
            return true;
        }
    }
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЛЕЖИТ СПРАВА ОТ РОДИТЕЛЯ ==========
    if(temp->_key >= temp->_parent->_key){
        if(temp->_left == 0 && temp->_right == 0){             //у удаляемого узла нет потомков
            temp->_parent->_right = 0;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right == 0 && temp->_left != 0){             //у удаляемого узла есть только левый потомок
            temp->_parent->_right = temp->_left;
            temp->_left->_parent = temp->_parent;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right != 0 && temp->_right->_left == 0){     //у удаляемого узла есть правый потомок, у которого нет левого узла
            temp->_parent->_right = temp->_right;
            temp->_right->_parent = temp->_parent;
            temp->_right->_left = temp->_left;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right->_left != 0){                          //у удаляемого узла есть правый потомок, у который есть левый узел
            listnode<type>* temp1 = temp->_right->_left;
            for( ;temp1->_left != 0; temp1 = temp1->_left);    //самый левый узел ставится на место удаляемого узла
            if(temp1->_right != 0){                            //а если у самого левого узла есть еще и правый узел
                temp1->_parent->_left = temp1->_right;
                temp1->_right->_parent = temp1->_parent;
            }
            temp1->_parent->_left = 0;
            temp1->_parent = temp->_parent;
            temp1->_left = temp->_left;
            temp1->_right = temp->_right;
            temp->_parent->_right = temp1;
            if(temp->_right != 0)
                temp->_right->_parent = temp1;
            if(temp->_left != 0)
                temp->_left->_parent = temp1;
            delete temp;
            quantity--;
            return true;
        }
    }
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЛЕЖИТ СЛЕВА ОТ РОДИТЕЛЯ ==========
    if(temp->_key < temp->_parent->_key){
        if(temp->_left == 0 && temp->_right == 0){               //у удаляемого узла нет потомков
            temp->_parent->_left = 0;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right == 0){                                   //у удаляемого узла есть только левый потомок
            temp->_parent->_left = temp->_left;
            temp->_left->_parent = temp->_parent;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right != 0 && temp->_right->_left == 0){       //у удаляемого узла есть правый потомок, у которого нет левого узла
            temp->_parent->_left = temp->_right;
            temp->_right->_parent = temp->_parent;
            temp->_right->_left = temp->_left;
            temp->_left->_parent = temp->_right;
            delete temp;
            quantity--;
            return true;
        }
        if(temp->_right->_left != 0){                            //у удаляемого узла есть правый потомок, у который есть левый узел
            listnode<type>* temp1 = temp->_right->_left;
            for( ; temp1->_left !=0; temp1 = temp1->_left);      //самый левый узел ставится на место удаляемого узла
            if(temp1->_right != 0){                              //а если у самого левого узла есть еще и правый узел
                temp1->_parent->_left = temp1->_right;
                temp1->_right->_parent = temp1->_parent;
            }
            temp1->_parent = temp->_parent;
            temp1->_left = temp->_left;
            temp->_parent->_left = temp1;
            temp1->_right = temp->_right;
            if(temp->_left != 0)
                temp->_left->_parent = temp1;
            if(temp->_right != 0)
                temp->_right->_parent = temp1;
            delete temp;
            quantity--;
            return true;
        }
    }

}
// ========== ОБХОДЫ ДЕРЕВА ==========
template<typename type> void BinaryTree<type>::Preorder(listnode<type>* p){
    qDebug() << p->_key;
    if(p->_left != 0)
        Preorder(p->_left);
    if(p->_right != 0)
        Preorder(p->_right);
}
template<typename type> void BinaryTree<type>::Postorder(listnode<type>* p){
    if(p != 0){
        Postorder(p->_left);
        Postorder(p->_right);
        qDebug() << p->_key;
    }
}
template <typename type> void BinaryTree<type>::Isforder(listnode<type>* p){
    if(p != 0){
        Isforder(p->_left);
        qDebug() << p->_key;
        Isforder(p->_right);
    }
}
template <typename type> void BinaryTree<type>::TreeRound(round R)
{
    listnode<type>* p = p_node;
    if(R == POSTORDER)
        Postorder(p);
    if(R == ISFORDER)
        Isforder(p);
    if(R == PREODRDER)
        Preorder(p);
}

