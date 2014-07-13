// Public-Key Encrypted Session Key Packet
#ifndef __TAG1__
#define __TAG1__

#include "packet.h"
class Tag1 : public Packet{
    private:
        std::string keyid;                // 8 octets
        uint8_t pka;
        std::vector <PGPMPI> mpi;      // algorithm specific fields

    public:
        typedef std::shared_ptr<Tag1> Ptr;

        Tag1();
        Tag1(std::string & data);
        void read(std::string & data);
        std::string show() const;
        std::string raw() const;

        std::string get_keyid() const;
        uint8_t get_pka() const;
        std::vector <PGPMPI> get_mpi() const;

        void set_keyid(const std::string & k);
        void set_pka(const uint8_t p);
        void set_mpi(const std::vector <PGPMPI> & m);

        Packet::Ptr clone() const;
};
#endif
