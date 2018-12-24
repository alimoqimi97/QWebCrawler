#ifndef TTREE_H
#define TTREE_H

#include "tnode.h"
#include <QTextStream>

template<typename n>
class TTree
{
private:
    TNode<n> *Root;
    int Size;

public:
    TTree(): Root(nullptr),Size(0)
    {}

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
            ++Size;
            return true;
        }
        return false;
    }

    TNode<n> *Find(n &data)
    {
        TNode<n> * cur = this->Root;

        return this->Search(cur,data);

    }

    bool isEmpty()
    {
        return (this->Root == nullptr);
    }

    QList<TNode<n> *> getANodeChilds(n &data);

//    bool Contains(n & data)
//    {
//        //          inorder the tree + searching in ascending list for finding "data".//
//    }

/*
 * if the speed of the search() algorithm became low,
 * it is due to the recursion algorithm...
 * in this case you can change the implementation of the
 * TTree with QMap<...> that you wrote...!!
*/
    TNode<n> *Search(TNode<n> *current,n &data)
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
//            return this->Search(current->getChilds().at(index),data);
            if(this->Search(current->getChilds().at(index),data) != nullptr)
            {
                return current->getChilds().at(index);
            }
        }

        return nullptr;
    }

    void PrintTree(TNode<n> *cur,QTextStream & output)
    {
        output << *(cur->getData()) << endl;

        //      testing             //
//        output<< cur->getData() << endl;
        //      =======             //

        if(cur->ChildsIsEmpty())
        {
            return;
        }

        for(int i = 0 ; i < cur->getChilds().size() ; i++)
        {
            this->PrintTree(cur->getChilds().at(i),output);
        }
    }

    void PrintAllTree()
    {
        QTextStream qprint(stdout);

        this->PrintTree(this->Root,qprint);
    }

};

#endif // TTREE_H
