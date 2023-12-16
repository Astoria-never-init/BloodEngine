#include <wx/wx.h>
#include "viewport/input/input.h"
#include <iostream>

using namespace std;
class SF_Wx_keyboard_layout
{
    public:
        SF_Wx_keyboard_layout(){}
        SF_Wx_keyboard_layout(char* _patch);
        ~SF_Wx_keyboard_layout();

        bool load_layout_file(char* patch);
        SF_Key get_key_description(int _key_code);
        
    private:

        struct key_description
        {
            key_description(int _sf_key, int _key_code) : key((SF_Key)_sf_key), key_code(_key_code) {}

            int key_code = 0;
            SF_Key key = SF_Key::null;
        };

        size_t kd_len = 0;
        key_description * kd = 0x0;
};



class SF_Wx_input_manager : public SF_Input
{
public:
    SF_Wx_input_manager(wxWindow * _window, SF_Wx_keyboard_layout* _key_layout);
    SF_Wx_input_manager(){}
    ~SF_Wx_input_manager();

    void init(wxWindow* _window, SF_Wx_keyboard_layout* _key_layout);


    bool get_mouse_button(SF_Mouse_key mouse_key) override;
    void get_mouse_position(float &x, float &y) override;
    void set_mouse_position(float x, float y) override;
    

private:
    static void key_state_change(void** pointers, wxKeyEvent& event, bool state);
    static void mouse_key_state_change(void** pointers, SF_Mouse_key, bool state);

    bool mouse_buttons[3];

    wxWindow* window = 0x0;

    void** ptr = 0x0;
    SF_Wx_keyboard_layout* key_layout = 0x0;
};