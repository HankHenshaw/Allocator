#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <iostream>
#include <stack>

template<typename T, size_t SIZE = 10>
struct MyAlloc {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = MyAlloc<U>;
    };

    T* allocate([[maybe_unused]]std::size_t n)
    {
#ifdef DEBUG
        std::cout << __PRETTY_FUNCTION__ << '\n';
#endif

        if(m_objcounter == SIZE*m_multiplier)
        {// Надо расширяться
#ifdef DEBUG
            std::cout << "\n----------------REALLOC------------\n\n";
#endif
            ++m_multiplier;
            auto p = malloc(SIZE*sizeof(T));
            if(!p) throw std::bad_alloc();
            m_stack.push(reinterpret_cast<T*>(p));
        }

        if(!m_objcounter)
        {//В первый раз выделяем память
            auto p = malloc(SIZE*sizeof (T));
            if(!p) throw std::bad_alloc();
            m_stack.push(reinterpret_cast<T*>(p));
            ++m_objcounter;
            return m_stack.top();
        }
        return m_stack.top() + (m_objcounter++ - SIZE*(m_multiplier - 1));
    }
    void deallocate([[maybe_unused]]T* p, [[maybe_unused]]std::size_t n)
    {
#ifdef DEBUG
        std::cout << __PRETTY_FUNCTION__ << '\n';
#endif
        --m_objcounter;
        if(!m_objcounter)
        {
            while(!m_stack.empty())
            {
                std::free(m_stack.top());
                m_stack.pop();
            }
        }
    }
    void destroy(T *p)
    {
#ifdef DEBUG
        std::cout << __PRETTY_FUNCTION__ << '\n';
#endif
        p->~T();
    }
    template<typename U, typename ...Args>
    void construct(U *p, Args&&... args)
    {
#ifdef DEBUG
        std::cout << __PRETTY_FUNCTION__ << '\n';
#endif
        new(p) U(std::forward<Args>(args)...);
    }

private:
    std::stack<T*> m_stack;
    size_t m_objcounter{0};
    size_t m_multiplier{1};
};

#endif // MYALLOCATOR_H
