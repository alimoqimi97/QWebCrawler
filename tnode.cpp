#include "tnode.h"

//template<typename c>
//TNode<c>::TNode(): Father(nullptr)
//{
//}

//template<typename s>
//void TNode<s>::setChilds(QList<TNode<s> *> &chl)
//{
//    this->Childs = chl;
//}

//template<typename t>
//QList<TNode<t> *> TNode<t>::getChilds()
//{
//    return this->Childs;
//}

//template<typename f>
//void TNode<f>::setFather(TNode<f> *fa)
//{
//    this->Father = fa;
//}

//template<typename g>
//TNode<g> *TNode<g>::getFather()
//{
//    return this->Father;
//}

//template<typename d>
//void TNode<d>::setData(d &dat)
//{
//    this->Data = dat;
//}

//template<typename G>
//G TNode<G>::getData()
//{
//    return this->Data;
//}

template<typename i>
bool TNode<i>::IsInChilds(i &c)
{
    return this->Childs.contains(c);
}

//template<typename e>
//bool TNode<e>::ChildsIsEmpty()
//{
//    return this->Childs.isEmpty();
//}

template<typename r>
bool TNode<r>::IsRoot()
{
    return (this->Father == nullptr);
}
