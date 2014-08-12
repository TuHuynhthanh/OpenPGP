#include "Tag2Sub24.h"

Tag2Sub24::Tag2Sub24() :
    Tag2Subpacket(24),
    pks()
{}

Tag2Sub24::Tag2Sub24(std::string & data) :
    Tag2Sub24()
{
    read(data);
}

void Tag2Sub24::read(std::string & data){
    pks = data;
    size = data.size();
}

std::string Tag2Sub24::show(const uint8_t indents, const uint8_t indent_size) const{
    return std::string(indents * indent_size, ' ') + "            URI - " + pks;
}

std::string Tag2Sub24::raw() const{
    return pks;
}

std::string Tag2Sub24::get_pks() const{
    return pks;
}

void Tag2Sub24::set_pks(const std::string & p){
    pks = p;
}

Tag2Subpacket::Ptr Tag2Sub24::clone() const{
    return Ptr(new Tag2Sub24(*this));
}
