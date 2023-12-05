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

void sf_input::SF_Input::set_key_state(bool * _key_states, SF_Key key, bool state)
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

int SF_Input::key_to_int(SF_Key button = SF_Key::null)
{
    return static_cast<unsigned short>(button);
}