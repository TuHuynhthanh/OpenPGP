#include "Tag2Sub23.h"

Tag2Sub23::Tag2Sub23() :
    Tag2Subpacket(23),
    flags()
{}

Tag2Sub23::Tag2Sub23(std::string & data) :
    Tag2Sub23()
{
    read(data);
}

void Tag2Sub23::read(std::string & data){
    flags = data[0];
    size = data.size();
}

std::string Tag2Sub23::show(const uint8_t indents, const uint8_t indent_size) const{
    uint8_t tab = indents * indent_size;
    std::stringstream out;
    for(uint8_t bit = 0; bit < 8; bit++){
        if (flags & (1 << bit)){
            out << std::string(tab, ' ') << "            Flag - " << Key_Server_Preferences.at(1 << bit) << " (key " << static_cast <unsigned int> (1 << bit) << ")\n";
        }
    }
    return out.str();
}

std::string Tag2Sub23::raw() const{
    return std::string(1, flags);
}

char Tag2Sub23::get_flags() const{
    return flags;
}

void Tag2Sub23::set_flags(const char c){
    flags = c;
}

Tag2Subpacket::Ptr Tag2Sub23::clone() const{
    return Ptr(new Tag2Sub23(*this));
}
