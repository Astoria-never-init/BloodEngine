#include "input.h"
#include <cstring>

using namespace sf_input;

SF_Input::SF_Input()
{
    key_states = new bool[key_lenght];
    memset(key_states, 0, key_lenght * sizeof(bool));
}
SF_Input::~SF_Input()
{
    if(key_states)
    {
        delete[] key_states;
    }
}

void SF_Input::set_key_state(SF_Key key, bool state)
{
    key_states[get_key_code(key)] = state;
}

bool SF_Input::get_key_state(SF_Key button = SF_Key::null)
{
    return key_states[static_cast<unsigned short>(button)];
}

unsigned short SF_Input::get_key_code(SF_Key button = SF_Key::null)
{
    return static_cast<unsigned short>(button);
}