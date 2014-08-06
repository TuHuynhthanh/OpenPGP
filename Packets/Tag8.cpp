#include "Tag8.h"

std::string Tag8::compress(const std::string & data){
    if (comp){ // if the algorithm value is not zero
        // create both files; forced to use FILE * to use compression algorithms
        FILE * src = fopen("srctmp", "a+b");
        FILE * dst = fopen("dsttmp", "a+b");
        bool good = true;
        
        // write data to source file
        fwrite(data.c_str(), sizeof(char), data.size(), src);
        
        switch (comp){
            case 1: // ZIP [RFC1951]
                break;
            case 2: // ZLIB[RFC1950]
                good = (def(src, dst, Z_DEFAULT_COMPRESSION) == Z_OK);
                break;
            case 3: // BZip2 [BZ2]
                good = (bz2_compress(src, dst) == BZ_OK);
                break;
            case 100: case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110:
                throw std::runtime_error("Error: Private/Experimental algorithm.");
            default:
                {
                    std::stringstream tmp; tmp << (int) comp;
                    throw std::runtime_error("Error: Unknown Compression algorithm value: " + tmp.str());
                }
                break;
        }
        
        if (!good){
            throw std::runtime_error("Error: Ccompression failed");
        }
        
        fclose(src);
        fclose(dst);
        remove("srctmp");
        
        std::ifstream compressed("dsttmp", std::ios::binary);
        std::stringstream buf;
        buf << compressed.rdbuf();
        
        compressed.close();
        remove("dsttmp");
        
        return buf.str();
    }
    return data; // 0: Uncompressed
}

std::string Tag8::decompress(const std::string & data){
    if (comp){ // if the algorithm value is not zero
        // create both files; forced to use FILE * to use compression algorithms
        FILE * src = fopen("srctmp", "a+b");
        FILE * dst = fopen("dsttmp", "a+b");
        bool good = true;
        
        // write data to source file
        fwrite(data.c_str(), sizeof(char), data.size(), src);
        
        switch (comp){
            case 1: // ZIP [RFC1951]
                break;
            case 2: // ZLIB[RFC1950]
                good = (inf(src, dst) == Z_OK);
                break;
            case 3: // BZip2 [BZ2]
                good = (bz2_decompress(src, dst) == BZ_OK);
                break;
            default:
                {
                    std::stringstream tmp; tmp << (int) comp;
                    throw std::runtime_error("Error: Unknown Compression algorithm value: " + tmp.str());
                }
                break;
        }
        
        if (!good){
            throw std::runtime_error("Error: Ccompression failed");
        }
        
        fclose(src);
        fclose(dst);
        remove("srctmp");
        
        std::ifstream compressed("dsttmp", std::ios::binary);
        std::stringstream buf;
        buf << compressed.rdbuf();
        
        compressed.close();
        remove("dsttmp");
        
        return buf.str();
    }
    return data; // 0: Uncompressed
}

Tag8::Tag8() :
    Packet(8, 3),
    comp(0),
    compressed_data()
{
}

Tag8::Tag8(std::string & data) :
    Tag8()
{
    read(data);
}

void Tag8::read(std::string & data){
    size = data.size();
    comp = data[0];
    compressed_data = data.substr(1, data.size() - 1);
}

std::string Tag8::show() const{
    std::stringstream out;
    out << "    Compression algorithm: " << Compression_Algorithms.at(comp) << "(compress " << static_cast <unsigned int> (comp) << ")\n"
        << "    Data in hex (" << compressed_data.size() << " octets): " << hexlify(compressed_data) << "\n";
    return out.str();
}

std::string Tag8::raw() const{
    return std::string(1, comp) + compressed_data;
}

uint8_t Tag8::get_comp() const{
    return comp;
}

std::string Tag8::get_compressed_data() const{
    return compressed_data;
}

std::string Tag8::get_data() const{
    return "Data in hex, so it's easier to copy to a " + Compression_Algorithms.at(comp) + " decompressor:\n\n" + hexlify(compressed_data);
//    return decompress(compressed_data);
}

void Tag8::set_comp(const uint8_t c){
    comp = c;
    size = raw().size();
}

void Tag8::set_data(const std::string & data){
    compressed_data = compress(data);
    size = raw().size();
}

void Tag8::set_compressed_data(const std::string & data){
    compressed_data = data;
    size = raw().size();
}

Packet::Ptr Tag8::clone() const{
    return Ptr(new Tag8(*this));
}
