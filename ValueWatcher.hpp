#pragma once

#include <Arduino.h>

#include "NoMoveNoCopy.hpp"

template <typename T>
class Value : NoMoveNoCopy
{

public:
    Value(T initial_value, bool initially_valid = true)
        : value{initial_value}, valid{initially_valid}
    {
    }

    void update(T value, bool valid = true)
    {
        if (this->valid == false && valid == false)
        {
            return;
        }

        this->value = value;
        this->valid = valid;
        this->iteration_number++;
    }

    uint64_t get_iteration_number() const
    {
        return iteration_number;
    }

    const T &get() const
    {
        return value;
    }

    bool is_valid() const
    {
        return valid;
    }

private:
    T value;
    bool valid;
    uint64_t iteration_number = 0;
};

template <typename T>
class ValueWatcher
{
public:
    ValueWatcher(Value<T> const *parent)
        : iteration_number{parent->get_iteration_number()},
          parent{parent}
    {
    }

    bool new_value_available()
    {
        bool result = iteration_number != parent->get_iteration_number();
        clear();
        return result;
    }

    const T &get()
    {
        return parent->get();
    }

    bool is_valid()
    {
        return parent->is_valid();
    }

    void clear()
    {
        iteration_number = parent->get_iteration_number();
    }

private:
    uint64_t iteration_number;
    Value<T> const *parent;
};
