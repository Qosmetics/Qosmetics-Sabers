#include "Element.hpp"
#include <memory>
#include <stack>

class ElementPool
{

private:
    std::stack<std::unique_ptr<Element>> stack = {};

public:
    [[nodiscard]] int get_count() const { return stack.size(); }

    ElementPool() = default;;

    void Reserve(int count)
    {
        if (stack.size() < count)
        {
            while (stack.size() < count)
            {
                stack.emplace();
            }
        }
    }

    std::unique_ptr<Element> Get()
    {
        std::unique_ptr<Element> element;
        if (stack.empty())
        {
            element = std::make_unique<Element>();
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