#include "wx_input_class.h"
#include <tinyxml2.h>
#include <vector>

#include <logger.h>



SF_Wx_keyboard_layout::SF_Wx_keyboard_layout(char* _patch)
{
    if(load_layout_file(_patch))
    {
        SF_Log::message("SF_Wx_keyboard_layout", "ready to work", SF_Message_type::success);
    }
}

SF_Wx_keyboard_layout::~SF_Wx_keyboard_layout()
{
    free(kd);
}

bool SF_Wx_keyboard_layout::load_layout_file(char *patch)
{
    std::vector <key_description> temp;

    tinyxml2::XMLDocument xml_doc;
    tinyxml2::XMLError result = xml_doc.LoadFile(patch);

    if(result != tinyxml2::XML_SUCCESS)
    {
        SF_Log::message("SF_Wx_keyboard_layout", "Load XML file failed", SF_Message_type::error);
        return false;
    }

    tinyxml2::XMLNode * root = xml_doc.FirstChild();

    if (root == nullptr)
    {
        SF_Log::message("SF_Wx_keyboard_layout", "Load XML root failed", SF_Message_type::error);
        return false;
    }

    tinyxml2::XMLElement * key_remaper = root->FirstChildElement("Layout");
    while (key_remaper != nullptr)
    {
        int key, bind;
        
        if((key_remaper->QueryIntAttribute("key", &key) != tinyxml2::XML_SUCCESS) || (key_remaper->QueryIntAttribute("bind", &bind) != tinyxml2::XML_SUCCESS))
        {
            SF_Log::message("SF_Wx_keyboard_layout", "Load XML attribute failed", SF_Message_type::error);
            SF_Log::int_message("SF_Wx_keyboard_layout", "XML line",key_remaper->GetLineNum() , SF_Message_type::error);
            
            return false;
        }
        temp.push_back(key_description(key, bind));
        key_remaper = key_remaper->NextSiblingElement("Layout");
    }
    
    kd_len = temp.size();
    if(kd_len > 0)
    {
        kd = (key_description*)malloc(sizeof(key_description) * kd_len);
        memcpy(kd, temp.data(), sizeof(key_description) * kd_len);

        SF_Log::message("SF_Wx_keyboard_layout", "Load XML file success", SF_Message_type::success);
        return true;
    }
    
    SF_Log::message("SF_Wx_keyboard_layout", "Copy array failed", SF_Message_type::error);
    return false;
}

SF_Key SF_Wx_keyboard_layout::get_key_description(int _key_code)
{
    for (int i = 0; i < kd_len; i++) 
    {
        if (kd[i].key_code == _key_code) 
        {
            return kd[i].key;
        }
    }

    SF_Log::int_message("SF_Wx_keyboard_layout", "undefine key",_key_code, SF_Message_type::warning);
    return SF_Key::null;
}



SF_Wx_input_manager::SF_Wx_input_manager(wxWindow* _window, SF_Wx_keyboard_layout* _key_layout) : SF_Input()
{
    init(_window, _key_layout);
}

SF_Wx_input_manager::~SF_Wx_input_manager()
{
    if (ptr)  free(ptr);
    if (key_layout) free(key_layout);
}

void SF_Wx_input_manager::init(wxWindow *_window, SF_Wx_keyboard_layout *_key_layout)
{
    if(_window == 0x0)
    {
        SF_Log::message("SF_Wx_input_manager", "window is null", SF_Message_type::error);
        return;
    }

    key_layout = _key_layout;
    window = _window;
    memset(mouse_buttons, 0, 3 * sizeof(bool));

    void** pointers = new void* [3];
    pointers[0] = (void*)key_states;
    pointers[1] = (void*)key_layout;
    pointers[2] = (void*)mouse_buttons;
    ptr = pointers;

    window->Bind(wxEVT_KEY_DOWN, [pointers](wxKeyEvent& event)
    {
        SF_Wx_input_manager::key_state_change(pointers, event, true);
    });
    window->Bind(wxEVT_KEY_UP, [pointers](wxKeyEvent& event)
    {
        SF_Wx_input_manager::key_state_change(pointers, event, false);
    });

    window->Bind(wxEVT_RIGHT_DOWN, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_RIGHT, true);
        event.Skip();
    });
    window->Bind(wxEVT_LEFT_DOWN, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_LEFT, true);
        event.Skip();
    });
    window->Bind(wxEVT_MIDDLE_DOWN, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_MIDDLE, true);
        event.Skip();
    });

    window->Bind(wxEVT_RIGHT_UP, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_RIGHT, false);
        event.Skip();
    });
    window->Bind(wxEVT_LEFT_UP, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_LEFT, false);
        event.Skip();
    });
    window->Bind(wxEVT_MIDDLE_UP, [pointers](wxMouseEvent& event)
    {
        mouse_key_state_change(pointers, SF_Mouse_key::MOUSE_MIDDLE, false);
        event.Skip();
    });

    SF_Log::message("SF_Wx_input_manager", "ready to work", SF_Message_type::success);
}

void SF_Wx_input_manager::key_state_change(void** pointers, wxKeyEvent& event, bool state)
{
    int keycode = event.GetKeyCode();

    bool* keystates_ptr = (bool*)pointers[0];
    SF_Wx_keyboard_layout* layout_ptr = (SF_Wx_keyboard_layout*)pointers[1];

    keystates_ptr[(int)layout_ptr->get_key_description(keycode)] = state;
    event.Skip();
}

void SF_Wx_input_manager::mouse_key_state_change(void** pointers, SF_Mouse_key _button, bool state)
{
    bool * ptr = (bool*)pointers[2];
    ptr[(int)_button] = state;
}

bool SF_Wx_input_manager::get_mouse_button(SF_Mouse_key mouse_key)
{
    return mouse_buttons[(int)mouse_key];
}

void SF_Wx_input_manager::get_mouse_position(float &x, float &y)
{
    int point_x, point_y;
    int pos_x, pos_y;
    int result_x, result_y;
    

    window->GetScreenPosition(&pos_x, &pos_y);
    wxSize size = window->GetSize();

    wxGetMousePosition(&point_x, &point_y);

    result_x = min( max(point_x - pos_x, 0), size.GetX() );
    result_y = min( max(point_y - pos_y, 0), size.GetY() );

    x = (float)result_x / (float)size.GetX();
    y = (float)result_y / (float)size.GetY();

}

void SF_Wx_input_manager::set_mouse_position(float x, float y)
{
    x = min(max(x, 0.0f), 1.0f);
    y = min(max(y, 0.0f), 1.0f);

    int point_x, point_y;
    int pos_x, pos_y;
    
    window->GetScreenPosition(&pos_x, &pos_y);
    wxSize size = window->GetSize();

    point_x = (x * size.GetX()) + pos_x;
    point_y = (y * size.GetY()) + pos_y;

    set_mouse_position_global(point_x, point_y);

}

