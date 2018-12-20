#include "ttree.h"

//template<typename cnc>
//TTree<cnc>::TTree(): Root(nullptr),Size(0)
//{
//}

//template<typename N>
//void TTree<N>::setRoot(TNode<N> *root)
//{
//    this->Root = root;
//}

//template<typename r>
//TNode<r> *TTree<r>::getRoot()
//{
//    return this->Root;
//}

//template<typename S>
//void TTree<S>::setSize(int s)
//{
//    this->Size = s;
//}

//template<typename g>
//int TTree<g>::getSize()
//{
//    return this->Size;
//}

//template<typename i>
//bool TTree<i>::Insert(i data, TNode<i> *parent)
//{
//    if(parent != nullptr)
//    {
//        parent->AddToChilds(data);
//        return true;
//    }
//    return false;
//}

template<typename f>
TNode<f> *TTree<f>::Find(f &data)
{
    TNode<f> * cur = this->Root;

    return this->Search(cur,data);
}

template<typename chil>
QList<TNode<chil> *> TTree<chil>::getANodeChilds(chil &data)
{
    TNode<chil> * f = this->Find(data);

    return f->getChilds();
}

template<typename Se>
TNode<Se> *TTree<Se>::Search(TNode<Se> *current, Se &data)
{
    if(current == nullptr)
    {
        return nullptr;
    }
    if(current->getData() == data)
    {
        return current;
    }

    if(current->ChildsIsEmpty())
    {
        return nullptr;
    }

    for(int index = 0 ; index < current->getChilds().size() ;  index++)
    {
        if(this->Search(current->getChilds().at(index),data))
        {
            return current->getChilds().at(index);
        }
    }

}
