#ifndef SF_LOGGER_CLASS_H
#define SF_LOGGER_CLASS_H

#include <string>
#include <glm/glm.hpp>

using namespace std;

enum SF_Text_colors
{
    color_black,
    color_red,
    color_green,
    color_yellow,
    color_blue,
    color_purple,
    color_cyan,
    color_white,
    color_return
};

enum SF_Message_type
{
    text    = SF_Text_colors::color_white,  //white
    message = SF_Text_colors::color_cyan,   //blue
    success = SF_Text_colors::color_green,  //green
    warning = SF_Text_colors::color_yellow, //yellow
    error   = SF_Text_colors::color_red     //error
};


class SF_Log
{
public:
    static void message(std::string _module, std::string _message, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);
    static void bool_message(std::string _module, std::string _var_description, bool boolean, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);
    static void int_message(std::string _module, std::string _var_description, int integer, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);
    static void vec2_message(std::string _module, std::string _var_description, glm::vec2 vector, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);
    static void vec3_message(std::string _module, std::string _var_description, glm::vec3 vector, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);
    static void vec4_message(std::string _module, std::string _var_description, glm::vec4 vector, SF_Message_type type = SF_Message_type::message, unsigned short offset = 0);


private:
    static void print_var_start(std::string _module, std::string _var_description, SF_Message_type type, unsigned short offset);
    static void print_module(std::string _module, unsigned short offset);
    static const char* get_color_command(SF_Text_colors color);

};

#endif