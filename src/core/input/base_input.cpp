#include "base_input.h"
#include <cstring>
#include <core/logger/logger.h>



SF_Input::SF_Input()
{
    key_states = new bool[key_lenght];
    memset(key_states, 0, key_lenght * sizeof(bool));

    display = XOpenDisplay(NULL);
    root_window = DefaultRootWindow(display);
}
SF_Input::~SF_Input()
{
    if (key_states) delete[](key_states);

    XCloseDisplay(display);
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
    XSelectInput(display, root_window, KeyReleaseMask);
    XWarpPointer(display, None, root_window, 0, 0, 0, 0, x, y);
    XFlush(display);
}

int SF_Input::key_to_int(SF_Key button = SF_Key::null)
{
    return static_cast<unsigned short>(button);
}