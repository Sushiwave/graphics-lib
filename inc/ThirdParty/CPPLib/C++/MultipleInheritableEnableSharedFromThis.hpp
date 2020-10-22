#pragma once
#include <memory>





//https://stackoverflow.com/questions/16082785/use-of-enable-shared-from-this-with-multiple-inheritance
class MultipleInheritableEnableSharedFromThis
    : public std::enable_shared_from_this<MultipleInheritableEnableSharedFromThis>
{
public:
    virtual ~MultipleInheritableEnableSharedFromThis() = default;
};

