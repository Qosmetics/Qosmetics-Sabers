#include "Element.hpp"
#include <stack>

class ElementPool
{

private:
    std::stack<std::unique_ptr<Element>> stack = {};

public:
    int get_count() { return stack.size(); }

    ElementPool(){};

    void Reserve(int count)
    {
        if (stack.size() < count)
        {
            while (stack.size() < count)
            {
                stack.emplace(new Element());
            }
        }
    }

    std::unique_ptr<Element> Get()
    {
        std::unique_ptr<Element> element;
        if (stack.size() == 0)
        {
            element.reset(new Element());
        }
        else
        {
            element = std::move(stack.top());
            stack.pop();
        }
        return element;
    }

    void Release(std::unique_ptr<Element>&& element)
    {
        stack.emplace(std::move(element));
    }
};