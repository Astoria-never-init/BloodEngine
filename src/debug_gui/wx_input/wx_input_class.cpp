#include "wx_input_class.h"
#include <tinyxml2.h>
#include <vector>




bool SF_Wx_keyboard_layout::load_layout_file(char *patch)
{
    std::vector <key_description> temp;

    tinyxml2::XMLDocument xml_doc;
    tinyxml2::XMLError result = xml_doc.LoadFile(patch);

    if(result != tinyxml2::XML_SUCCESS)
    {
        return false;
    }

    tinyxml2::XMLNode * root = xml_doc.FirstChild();

    if (root == nullptr)
    {
        return false;
    }

    tinyxml2::XMLElement * key_remaper = root->FirstChildElement("Layout");
    while (key_remaper != nullptr)
    {
        int key, bind;
        if((key_remaper->QueryIntAttribute("key", &key) != tinyxml2::XML_SUCCESS) || (key_remaper->QueryIntAttribute("bind", &bind) != tinyxml2::XML_SUCCESS))
        {
            return false;
        }

        key_remaper = key_remaper->NextSiblingElement("Layout");
    }
    
    kd_len = temp.size();
    if(kd_len > 0)
    {
        kd = (key_description*)malloc(sizeof(key_description) * kd_len);
        memcpy(kd, temp.data(), sizeof(key_description) * kd_len);
        return true;
    }
    
    return false;
}

sf_input::SF_Key SF_Wx_keyboard_layout::get_key_description(int _key_code)
{
    return sf_input::SF_Key();
}



SF_Wx_input_manager::SF_Wx_input_manager(wxWindow * window) : SF_Input()
{
    //
}

void SF_Wx_input_manager::init(wxWindow *window)
{
    //key_layout = new key_remap[key_lenght];

    window->Bind(wxEVT_KEY_DOWN, &SF_Wx_input_manager::OnKeyDown, this);
}

void SF_Wx_input_manager::OnKeyDown(wxKeyEvent& event)
{
    int keycode = event.GetKeyCode();

    event.Skip();
}

