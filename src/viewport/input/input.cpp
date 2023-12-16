#include "input.h"
#include <cstring>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

SF_Input::SF_Input()
{
    key_states = new bool[key_lenght];
    memset(key_states, 0, key_lenght * sizeof(bool));
}
SF_Input::~SF_Input()
{
    
    if (key_states) delete[](key_states);
}

void SF_Input::set_key_state(bool * _key_states, SF_Key key, bool state)
{
    _key_states[key_to_int(key)] = state;
}

void SF_Input::set_key_state(SF_Key key, bool state)
{
    key_states[key_to_int(key)] = state;
}

bool SF_Input::get_key_state(SF_Key button = SF_Key::null)
{
    return key_states[static_cast<unsigned short>(button)];
}

void SF_Input::set_mouse_position_global(unsigned int x, unsigned int y)
{
    Display *dpy;
    Window root_window;

    dpy = XOpenDisplay(0);
    root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);

    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);

    XFlush(dpy);
}

int SF_Input::key_to_int(SF_Key button = SF_Key::null)
{
    return static_cast<unsigned short>(button);
}