#ifndef TNODE_H
#define TNODE_H

#include <QList>

template<typename T>
class TNode
{
private:
    QList<TNode<T> *> Childs;
    TNode<T> * Father;
    T Data;

public:
    TNode(): Father(nullptr)
    {}

    //          get and set methods     //
    void setChilds(QList<TNode<T> *> & chl)
    {
        this->Childs = chl;
    }

    QList<TNode<T> *> getChilds()
    {
        return this->Childs;
    }

    void setFather(TNode<T> * fa)
    {
        this->Father = fa;
    }

    TNode<T> *getFather()
    {
        return this->Father;
    }

    void setData(T & dat)
    {
        this->Data = dat;
    }

    T getData()
    {
        return this->Data;
    }

    //          =================       //

    //          public methods          //

    void AddToChilds(T & a)
    {
        TNode<T> * nn = new TNode<T>();

        nn->setData(a);
        this->Childs.push_back(nn);
    }

    void RemoveFromChilds(T & r)
    {

    }

    bool IsInChilds(T & c);
    bool ChildsIsEmpty();
    bool IsRoot();


};

#endif // TNODE_H
