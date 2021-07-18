#pragma once

class NoMoveNoCopy
{
public:
    NoMoveNoCopy() = default;
    NoMoveNoCopy(const NoMoveNoCopy &) = delete;
    NoMoveNoCopy(NoMoveNoCopy &&) = delete;
    NoMoveNoCopy &operator=(const NoMoveNoCopy &) = delete;
    NoMoveNoCopy &operator=(NoMoveNoCopy &&) = delete;
    virtual ~NoMoveNoCopy() = default;
};
