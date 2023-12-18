#include "logger.h"

#include <iostream>



void SF_Log::message(std::string _module, std::string _message, SF_Message_type type, unsigned short offset)
{
    print_module(_module, offset);
    cout<<get_color_command((SF_Text_colors)type);
    cout<<' '<<_message;
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::bool_message(std::string _module, std::string _var_description, bool boolean, SF_Message_type type, unsigned short offset)
{
    print_var_start(_module, _var_description, type, offset);
    cout<<(boolean ? "(true)" : "(false)");
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::int_message(std::string _module, std::string _var_description, int integer, SF_Message_type type, unsigned short offset)
{
    print_var_start(_module, _var_description, type, offset);
    cout<<'('<<integer<<')';
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::vec2_message(std::string _module, std::string _var_description, glm::vec2 vector, SF_Message_type type, unsigned short offset)
{
    print_var_start(_module, _var_description, type, offset);
    cout<<'('<<"X = "<<vector.x<<", Y = "<<vector.y<<')';
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::vec3_message(std::string _module, std::string _var_description, glm::vec3 vector, SF_Message_type type, unsigned short offset)
{
    print_var_start(_module, _var_description, type, offset);
    cout<<'('<<"X = "<<vector.x<<", Y = "<<vector.y<<", Z = "<<vector.z<<')';
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::vec4_message(std::string _module, std::string _var_description, glm::vec4 vector, SF_Message_type type, unsigned short offset)
{
    print_var_start(_module, _var_description, type, offset);
    cout<<'('<<"X = "<<vector.x<<", Y = "<<vector.y<<", Z = "<<vector.z<<", W = "<<vector.w<<')';
    cout<<get_color_command(SF_Text_colors::color_return);
}

void SF_Log::print_var_start(std::string _module, std::string _var_description, SF_Message_type type, unsigned short offset)
{
    print_module(_module, offset);
    cout<<get_color_command((SF_Text_colors)type);
    cout<<' '<<_var_description<<" = ";

    cout<<get_color_command(SF_Text_colors::color_white);
}

void SF_Log::print_module(std::string _module, unsigned short offset)
{
    cout<<'\n'<<get_color_command(SF_Text_colors::color_blue)<<"[ "<<_module<<" ]"<< string((int)offset, ' ');
}

const char *SF_Log::get_color_command(SF_Text_colors color)
{

    switch (color)
    {
    case SF_Text_colors::color_black:
        return "\u001b[30m";
        break;
    
    case SF_Text_colors::color_blue:
        return "\u001b[34m";
        break;

    case SF_Text_colors::color_cyan:
        return "\u001b[36m";
        break;

    case SF_Text_colors::color_green:
        return "\u001b[32m";
        break;

    case SF_Text_colors::color_purple:
        return "\u001b[35m";
        break;

    case SF_Text_colors::color_red:
        return "\u001b[31m";
        break;

    case SF_Text_colors::color_white:
        return "\u001b[37m";
        break;

    case SF_Text_colors::color_yellow:
        return "\u001b[33m";
        break;
        
    case SF_Text_colors::color_return:
        return "\u001b[0m";
        break;
    
    default:
        return nullptr;
        break;
    }
}
