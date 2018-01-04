/*в методе Remove  рассмотрены случаи, когда 1) у удаляемого узла нет детей  2) когда у удаляемого узла есть только левый
ребенок 3) когда у удаляемого узла есть правый ребенок но без левого ребенка 4) когда у удаляемого узла есть правый ребенок, с
левым ребенком. В этом случае мы идем в самый левый узел дерева с корнем "правый ребенок удаляемого узла" и ставим его на место
удаляемого. НО! есть еще случай, когда у самого левого ребенка, может быть правый ребенок, поэтому этот случай тоже учитывается
в коде*/

#include <dynamicarray.h>
#include <memory>

template <typename T>
class binaryTree{
private:
    struct listnode{
        listnode* parent_;                //указатель на родительский узел
        listnode* left_;                  //указатель на левого потомка
        listnode* right_;                 //указатель на правого потомка
        T key_;                              //значения узла
    };
    listnode* pointerNode_;                 //указатель на корень дерева
    int elementsInBinaryTree_;                           //количество элементов в дереве
private:
    void preOrder(const listnode* p, dynamicArray<T>& array);       //префиксный обход
    void isfOrder(const listnode* p, dynamicArray<T>& array);       //исфиксный обход
    void postOrder(const listnode* p, dynamicArray<T>& array);      //постфиксный обход
public:
    enum class roundType {PREODRDER, ISFORDER, POSTORDER};   //для определения правила обхода дерева
public:
    binaryTree(){pointerNode_ = 0; elementsInBinaryTree_ = 0;}        //конструктор
    void addValue(const T value);                          //метод добавления значения в дерево
    bool isValueInBinaryTree(const T& value);                     //метод проверки существования значения в дереве
    bool removeValue(const T& value);                       //метод удаления значения из дерева
    dynamicArray<T> roundTree(const roundType& );                        //функция определения правила обхода дерева
    int getElementsInBinaryTree(){return elementsInBinaryTree_;}      //количество узлов в дереве
};

template <typename T>
void binaryTree<T>::addValue(const T value){
    listnode* node = new listnode;      //выделяем память под новый узел
    node->key_ = value;                             //инициализируем узел
    node->left_ = nullptr;
    node->right_ = nullptr;
    elementsInBinaryTree_++;
    if(pointerNode_ == nullptr){                                //если дерево пустое
        pointerNode_ = node;
        pointerNode_->parent_ = nullptr;
        return;
    }
    listnode* temp = pointerNode_;                  //если дерево не пустое
    while(1){                                       //поиск места для добавления узел
        if(value >= temp->key_){                    //идем вправо
            if(temp->right_ != nullptr){
                temp = temp->right_;
                continue;
            }
            temp->right_ = node;
            node->parent_ = temp;
            return;
        }
        if(value < temp->key_){                     //идем влево
            if(temp->left_ != nullptr){
                temp = temp->left_;
                continue;
            }
            temp->left_ = node;
            node->parent_ = temp;
            return;
        }
    }
}

template <typename T>
bool binaryTree<T>::isValueInBinaryTree(const T& value){
    if(pointerNode_ == nullptr)               //если дерево пустое
        return false;
    listnode* temp = pointerNode_;//указатель для обхода по дереву
    while(1){
        if(value == temp->key_)   //нашли узел со значением, равному переданному в функцию
            return true;
        if(value >= temp->key_){  //не нашли, идем вправо
            if(temp->right_ == nullptr) //если дальше идти некуда
                return false;     //узел не найден
            temp = temp->right_;
            continue;
        }
        if(value < temp->key_){   //не нашли, идем влево
            if(temp->left_ == nullptr)  //если дальше идти некуда
                return false;     //узел не найден
            temp = temp->left_;
            continue;
        }
    }
}
template <typename T>
bool binaryTree<T>::removeValue(const T& value){
    if(pointerNode_ == nullptr)                 //если дерево пусто
        return false;
    listnode* temp = pointerNode_;  //создаем указатель для поиска по дереву
    while(1){                       //в цикле находим указатель на удаляемый узел
        if(value == temp->key_)
            goto delete_it;         //если нашли узел, то поиск прошел успешно, и пора перейти к удалению узла (переходим по метке)
        if(value >= temp->key_){    //идем вправо
            if(temp->right_ == nullptr)
                return false;
            temp = temp->right_;
            continue;
        }
        if(value < temp->key_){     //идем влево
            if(temp->left_ == nullptr)
                return false;
            temp = temp->left_;
            continue;
        }
    }
    delete_it:                                               //сама метка. Начало болезненного процесса удаления узла из дерева
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЕСТЬ САМ КОРЕНЬ ==========
    if(temp->parent_ == nullptr){
        if(temp->left_ == nullptr && temp->right_ == nullptr){             //если дерево состоит из одного узла
            delete pointerNode_;
            pointerNode_ = nullptr;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ == nullptr){                                 //если у корня есть левый ребенок но нет правого
            temp->left_->parent_ = nullptr;
            pointerNode_ = temp->left_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ != 0 && temp->right_->left_ == 0){     //если у корня есть правый узел без левого ребенка
            temp->right_->parent_ = 0;
            temp->right_->left_ = temp->left_;
            temp->left_->parent_ = temp->right_;
            pointerNode_ = temp->right_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_->left_ != nullptr){                           //у правого узла есть левый узел
            listnode* temp1 = temp->right_->left_;
            for( ;temp1->left_ != nullptr; temp1 = temp1->left_);     //смещаемся в самый левый узел
            if(temp1->right_ != nullptr){                             //а если у самого левого узла есть еще и правый узел
                temp1->parent_->left_ = temp1->right_;
                temp1->right_->parent_ = temp1->parent_;
            }
            temp1->parent_->left_ = nullptr;
            temp1->parent_ = nullptr;
            temp1->left_ = temp->left_;
            temp1->right_ = temp->right_;
            temp->left_->parent_ = temp1;
            temp->right_->parent_ = temp1;
            pointerNode_ = temp1;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
    }
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЛЕЖИТ СПРАВА ОТ РОДИТЕЛЯ ==========
    if(temp->key_ >= temp->parent_->key_){
        if(temp->left_ == nullptr && temp->right_ == nullptr){             //у удаляемого узла нет потомков
            temp->parent_->right_ = nullptr;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ == nullptr && temp->left_ != nullptr){             //у удаляемого узла есть только левый потомок
            temp->parent_->right_ = temp->left_;
            temp->left_->parent_ = temp->parent_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ != nullptr && temp->right_->left_ == nullptr){     //у удаляемого узла есть правый потомок, у которого нет левого узла
            temp->parent_->right_ = temp->right_;
            temp->right_->parent_ = temp->parent_;
            temp->right_->left_ = temp->left_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_->left_ != nullptr){                          //у удаляемого узла есть правый потомок, у который есть левый узел
            listnode* temp1 = temp->right_->left_;
            for( ;temp1->left_ != nullptr; temp1 = temp1->left_);    //самый левый узел ставится на место удаляемого узла
            if(temp1->right_ != nullptr){                            //а если у самого левого узла есть еще и правый узел
                temp1->parent_->left_ = temp1->right_;
                temp1->right_->parent_ = temp1->parent_;
            }
            temp1->parent_->left_ = nullptr;
            temp1->parent_ = temp->parent_;
            temp1->left_ = temp->left_;
            temp1->right_ = temp->right_;
            temp->parent_->right_ = temp1;
            if(temp->right_ != nullptr)
                temp->right_->parent_ = temp1;
            if(temp->left_ != nullptr)
                temp->left_->parent_ = temp1;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
    }
    // ========== УДАЛЯЕМЫЙ УЗЕЛ ЛЕЖИТ СЛЕВА ОТ РОДИТЕЛЯ ==========
    if(temp->key_ < temp->parent_->key_){
        if(temp->left_ == nullptr && temp->right_ == nullptr){               //у удаляемого узла нет потомков
            temp->parent_->left_ = nullptr;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ == nullptr){                                   //у удаляемого узла есть только левый потомок
            temp->parent_->left_ = temp->left_;
            temp->left_->parent_ = temp->parent_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_ != nullptr && temp->right_->left_ == nullptr){       //у удаляемого узла есть правый потомок, у которого нет левого узла
            temp->parent_->left_ = temp->right_;
            temp->right_->parent_ = temp->parent_;
            temp->right_->left_ = temp->left_;
            temp->left_->parent_ = temp->right_;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
        if(temp->right_->left_ != nullptr){                            //у удаляемого узла есть правый потомок, у который есть левый узел
            listnode* temp1 = temp->right_->left_;
            for( ; temp1->left_ != nullptr; temp1 = temp1->left_);      //самый левый узел ставится на место удаляемого узла
            if(temp1->right_ != nullptr){                              //а если у самого левого узла есть еще и правый узел
                temp1->parent_->left_ = temp1->right_;
                temp1->right_->parent_ = temp1->parent_;
            }
            temp1->parent_ = temp->parent_;
            temp1->left_ = temp->left_;
            temp->parent_->left_ = temp1;
            temp1->right_ = temp->right_;
            if(temp->left_ != nullptr)
                temp->left_->parent_ = temp1;
            if(temp->right_ != nullptr)
                temp->right_->parent_ = temp1;
            delete temp;
            elementsInBinaryTree_--;
            return true;
        }
    }

}
// ========== ОБХОДЫ ДЕРЕВА ==========
template<typename T>
void binaryTree<T>::preOrder(const listnode* p, dynamicArray<T>& array){
    array.pushBack(p->key_);
    if(p->left_ != nullptr)
        preOrder(p->left_, array);
    if(p->right_ != nullptr)
        preOrder(p->right_, array);
}
template<typename T>
void binaryTree<T>::postOrder(const listnode* p, dynamicArray<T>& array){
    if(p != nullptr){
        postOrder(p->left_, array);
        postOrder(p->right_, array);
        array.pushBack(p->key_);
    }
}
template <typename T>
void binaryTree<T>::isfOrder(const listnode* p, dynamicArray<T>& array){
    if(p != nullptr){
        isfOrder(p->left_, array);
        array.pushBack(p->key_);
        isfOrder(p->right_, array);
    }
}
template <typename T>
dynamicArray<T> binaryTree<T>::roundTree(const roundType& R)
{
    listnode* p = pointerNode_;
    dynamicArray<T> arrayForFill;
    arrayForFill.reserve(elementsInBinaryTree_);
    if(R == roundType::POSTORDER)
        postOrder(p, arrayForFill);
    if(R == roundType::ISFORDER)
        isfOrder(p, arrayForFill);
    if(R == roundType::PREODRDER)
        preOrder(p, arrayForFill);
    return arrayForFill;
}

