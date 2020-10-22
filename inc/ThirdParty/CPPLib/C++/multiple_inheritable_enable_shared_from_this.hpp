#pragma once
#include "MultipleInheritableEnableSharedFromThis.hpp"





//https://stackoverflow.com/questions/16082785/use-of-enable-shared-from-this-with-multiple-inheritance
template <class T>
class multiple_inheritable_enable_shared_from_this
    : public virtual MultipleInheritableEnableSharedFromThis
{
public:
    std::shared_ptr<T> shared_from_this() 
    {
        return std::dynamic_pointer_cast<T>(MultipleInheritableEnableSharedFromThis::shared_from_this());
    }
    template <class Down>
    std::shared_ptr<Down> downcasted_shared_from_this() 
    {
        return std::dynamic_pointer_cast<Down>(MultipleInheritableEnableSharedFromThis::shared_from_this());
    }
};
