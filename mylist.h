#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <memory>
#include "myallocator.h"

template <typename T, typename Allocator = std::allocator<T>>
class MyList {
private:
    class Node {
    public:
        Node *m_next;
        T m_val;

        template<typename ...Args>
        Node(Args&&... args) : m_next(nullptr), m_val(std::forward<Args>(args)...) {}
    };

    Node *m_head;

    using allocator = typename Allocator::template rebind<Node>::other;
    allocator m_allocator;
    T* m_ptrData;
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    class Iterator {
    private:
        Node *m_node;
    public:
        T& operator*()
        {
            return m_node->m_val;
        }
        void operator->()
        {
            return m_node->m_next;
        }
        void operator++()
        {
            if(m_node)
            {
                m_node = m_node->m_next;
            }
        }
        bool operator==(const Iterator& rhs)
        {
            if(this == &rhs) return true;
            return m_node == rhs.m_node;
        }
        bool operator!=(const Iterator& rhs)
        {
            return !operator==(rhs);
        }
        Iterator(Node* node) : m_node(node) {}
    };

    template<typename... Args>
    void emplace(Args&&... args)
    {
        Node* new_node = m_allocator.allocate(1);
        m_allocator.construct(new_node, std::forward<Args>(args)...);
#ifdef DEBUG
        std::cout << "Forward Emplace\n";
#endif
        new_node->m_next = m_head;
        m_head = new_node;
    }

    void remove()
    {
        if(m_head)
        {
            Node *tmp = m_head->m_next;
            m_allocator.destroy(m_head);
            m_head = tmp;
        }
    }
    Iterator begin()
    {
        return Iterator(m_head);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    MyList() : m_head(nullptr){}
    ~MyList()
    {
        while(m_head)
        {
            Node *tmp = m_head->m_next;
            m_allocator.destroy(m_head);
            m_allocator.deallocate(m_head, 1);
            m_head = tmp;
        }

    };
};

#endif // MYLIST_H
