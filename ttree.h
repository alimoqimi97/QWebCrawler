#ifndef TTREE_H
#define TTREE_H

#include "tnode.h"

template<typename n>
class TTree
{
private:
    TNode<n> *Root;
    int Size;

public:
    TTree(): Root(nullptr),Size(0)
    {

    }

    //          get and set methods     //
    void setRoot(TNode<n> * root)
    {
        this->Root = root;
    }

    TNode<n> *getRoot()
    {
        return this->Root;
    }

    void setSize(int s)
    {
        this->Size = s;
    }

    int getSize()
    {
        return this->Size;
    }

    //          ==================      //

    bool Insert(n data,TNode<n> * parent)
    {
        if(parent != nullptr)
        {
            parent->AddToChilds(data);
            return true;
        }
        return false;
    }

    TNode<n> *Find(n & data);
    QList<TNode<n> *> getANodeChilds(n & data);

    bool Contains(n & data)
    {
        //          inorder the tree + searching in ascending list for finding "data".//
    }

/*
 * if the speed of the search() algorithm became low,
 * it is due to the recursion algorithm...
 * in this case you can change the implementation of the
 * TTree with QMap<...> that you wrote...!!
*/
    TNode<n> *Search(TNode<n> * current,n & data);
};

#endif // TTREE_H
