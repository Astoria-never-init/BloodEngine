#include <wx/wx.h>
#include "viewport_gl/input/input.h"

class SF_Wx_keyboard_layout
{
    public:
        void load_layout_file(char* patch);
        sf_input::SF_Key get_key_description(int _key_code);
        
    private:

        struct key_description
        {
            int key_code = 0;
            sf_input::SF_Key key = sf_input::SF_Key::null;
        };

        key_description * kd = 0x0;
};



class SF_Wx_input_manager : public sf_input::SF_Input
{
public:
    SF_Wx_input_manager(wxWindow * window);
    SF_Wx_input_manager(){}

private:
    void OnKeyDown(wxKeyEvent& event);
    

    
    //key_remap *key_layout = 0x0;
};