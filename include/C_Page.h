#ifndef _H
#define _H

class Page
{

public:
    virtual ~Page() {};
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleButtonPress() = 0;
    virtual void drawStatusBar() {}
};

#endif