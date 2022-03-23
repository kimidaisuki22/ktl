

namespace unicode
{
    unsigned char u8Prefix[]{0, 0, 0b110'00000, 0b1110'0000, 0b11110'000, 0b111110'00, 0b1111110'0};
    unsigned char hibyte(unsigned char byte, int count) noexcept
    {
        byte >>= (8 - count);
        byte <<= (8 - count);
        return byte;
    }
    unsigned char lowbyte(unsigned char byte, int count) noexcept
    {
        auto mask = 0;
        while (count--)
        {
            mask <<= 1;
            mask++;
        }

        return byte & mask;
    }

    

    // get lenth by first byte of utf-8
    int getLentgh(unsigned char byte)
    {

        if (hibyte(byte, 1) == 0)
        {
            return 1;
        }
        else if (hibyte(byte, 3) == 0b110'00000)
        {
            return 2;
        }
        else if (hibyte(byte, 4) == 0b1110'0000)
        {
            return 3;
        }
        else if (hibyte(byte, 5) == 0b11110'000)
        {
            return 4;
        }
        else if (hibyte(byte, 6) == 0b111110'00)
        {
            return 5;
        }
        else if (hibyte(byte, 7) == 0b1111110'0)
        {
            return 6;
        }
        else
        {
            return false;
        }
    }

    // get utf-8 length from a utf-32 char
    int getUnicodeUtf8Len(char32_t character)
    {
        if (character < 0x80)
        {
            return 1;
        }
        else if (character < 0x800)
        {
            return 2;
        }
        else if (character < 0x10'000)
        {
            return 3;
        }
        else if (character < 0x200'000)
        {
            return 4;
        }
        else if (character < 0x4'000'000)
        {
            return 5;
        }
        else if (character < 0x80'000'000)
        {
            return 6;
        }
        else
        {
            throw "out of range";
        }
    }

    // get a u32 char from stream buf, nocheck , return u32 , diff is the move of stream
    char32_t toU32(const char *stream, int *diff)
    {
        if (stream == nullptr)
            return -1;

        int supposeLen = getLentgh(*stream);
        if(diff){
            *diff = supposeLen;
        }


        char32_t val{};
        for (int i = 0;i<supposeLen;i++){
            val |= stream[i];
            val<<=6;
        }
        return val;
    }

    class utf8Char
    {
        char len_;
        char data_[6];

        bool check()
        {
            auto realLenth = getLentgh(data_[0]);

            for (int i = 1; i < realLenth; i++)
            {
                auto hi2byte = (unsigned char)data_[i] >> 6;
                if (hi2byte != 0b10)
                {
                    return false;
                }
            }
            return true;
        }

    public:
        utf8Char(char32_t ch) : len_(getUnicodeUtf8Len(ch)), data_{}
        {
            unsigned char suffix = 0b10'00'0000;
            for (int i = len_ - 1; i >= 1; i--)
            {
                data_[i] = lowbyte(ch, 6) | suffix;
                ch >>= 6;
            }
            {

                int bitCount{};
                if (len_ == 1)
                {
                    bitCount = 7;
                }
                else if (len_ == 2)
                {
                    bitCount = 5;
                }
                else if (len_ == 3)
                {
                    bitCount = 4;
                }
                else if (len_ == 4)
                {
                    bitCount = 3;
                }
                else if (len_ == 5)
                {
                    bitCount = 2;
                }
                else if (len_ == 6)
                {
                    bitCount = 1;
                }
                data_[0] = lowbyte(ch, bitCount) | u8Prefix[len_];
                ch >>= bitCount;
            }
        }
        std::string str()
        {
            return std::string(data_, len_);
        }
        char32_t U32(){
            return toU32(data_,nullptr);
        }
    };

    class u32
    {
        char32_t data_;
        static_assert(sizeof data_ == 4);

    public:
        u32(const utf8Char &ch)
        {
        }
    };
}