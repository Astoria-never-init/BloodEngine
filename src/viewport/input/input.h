#ifndef SF_INPUT_H
#define SF_INPUT_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

enum class SF_Key
{
    null = 0,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    RETURN,

    end
};

enum class SF_Mouse_key
{
    MOUSE_RIGHT,
    MOUSE_LEFT,
    MOUSE_MIDDLE
};



class SF_Input
{
public:
    SF_Input();
    ~SF_Input();

    virtual bool get_key_state(SF_Key button);
    virtual bool get_mouse_button(SF_Mouse_key key) = 0;
    virtual void get_mouse_position(float &x, float &y) = 0;
    virtual void set_mouse_position(float x, float y) = 0;
    virtual void set_mouse_position_global(unsigned int x = 0, unsigned int  y = 0);

protected:
    void        set_key_state(SF_Key key, bool state);
    static void set_key_state(bool * _key_states, SF_Key key, bool state);
    static int  key_to_int(SF_Key button);
    

    Display* display;
    Window root_window;

    unsigned short key_lenght = static_cast<unsigned short>(SF_Key::end);
    bool *key_states = 0x0;

};


#endif