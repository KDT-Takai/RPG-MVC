#pragma once
#include <iostream>

//==============================
// ‰æ–ÊŠî’êƒNƒ‰ƒX 
//==============================
class ScreenBase
{
protected:

    std::string screenName;

public:

    ScreenBase() = default;
    virtual ~ScreenBase() = default;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

};