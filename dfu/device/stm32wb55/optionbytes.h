#pragma once

#include <QString>
#include <QByteArray>

namespace STM32 {
namespace WB55 {

class OptionBytes
{

#pragma pack(push,1)
    struct OptionBytesData {
        struct Word1 {
            unsigned RDP:8;
            unsigned ESE:1;
            unsigned BORLEV:3;
            unsigned nRSTSTOP:1;
            unsigned nRSTSTDBY:1;
            unsigned nRSTSHDW:1;
            unsigned UNUSED1:1;
            unsigned IWDGSW:1;
            unsigned IWDGSTOP:1;
            unsigned IWGDSTDBY:1;
            unsigned WWDGSW:1;
            unsigned UNUSED2:3;
            unsigned nBoot1:1;
            unsigned SRAM2PE:1;
            unsigned SRAM2RST:1;
            unsigned nSwBoot0:1;
            unsigned nBoot0:1;
            unsigned UNUSED3:1;
            unsigned AGCTRIM:3;
        };

        struct Word2 {
            unsigned PCROP1ASTRT:9;
            unsigned UNUSED:23;
        };

        struct Word3 {
            unsigned PCROP1AEND:9;
            unsigned UNUSED:22;
            unsigned PCROPRDP:1;
        };

        struct Word4 {
            uint8_t WRP1ASTRT;
            uint8_t UNUSED1;
            uint8_t WRP1AEND;
            uint8_t UNUSED2;
        };

        struct Word5 {
            uint8_t WRP1BSTRT;
            uint8_t UNUSED1;
            uint8_t WRP1BEND;
            uint8_t UNUSED2;
        };

        struct Word6 {
            unsigned PCROP1BSTRT:9;
            unsigned UNUSED:23;
        };

        struct Word7 {
            unsigned PCROP1BEND:9;
            unsigned UNUSED:23;
        };

        struct Word8 {
            unsigned IPCCDBA:14;
            unsigned UNUSED:18;
        };

        struct Word9 {
            unsigned SFSA:8;
            unsigned FSD:1;
            unsigned UNUSED1:3;
            unsigned DDS:1;
            unsigned UNUSED2:19;
        };

        struct Word10 {
            unsigned SBRV:18;
            unsigned SBRSA:5;
            unsigned BRSD:1;
            unsigned UNUSED1:1;
            unsigned SNBRSA:5;
            unsigned NBRSD:1;
            unsigned C2OPT:1;
        };

        Word1 word1[2];
        Word2 word2[2];
        Word3 word3[2];
        Word4 word4[2];
        Word5 word5[2];
        Word6 word6[2];
        Word7 word7[2];

        uint32_t UNUSED[12];

        Word8 word8[2];
        Word9 word9[2];
        Word10 word10[2];
    };

    static_assert (sizeof(OptionBytesData) == 128, "Check your struct packing!");

#pragma pack(pop)

    OptionBytes();

public:
    OptionBytes(const QByteArray &data);

    static OptionBytes invalid();
    static qint64 size();

    bool isValid() const;
    QByteArray data() const;

    uint8_t RDP() const;

    bool ESE() const;

    uint8_t BORLEV() const;

    bool nRSTSTOP() const;
    bool nRSTSTDBY() const;
    bool nRSTSHDW() const;

    bool IWDGSW() const;
    bool IWDGSTOP() const;
    bool IWGDSTDBY() const;
    bool WWDGSW() const;

    bool nBoot0() const;
    bool nBoot1() const;
    bool nSwBoot0() const;

    bool SRAM2PE() const;
    bool SRAM2RST() const;

    uint8_t AGCTRIM() const;

    bool FSD() const;
    bool DDS() const;
    bool BRSD() const;
    bool NBRSD() const;
    bool C2OPT() const;
    bool PCROPRDP() const;

    uint8_t SFSA() const;

    uint8_t SBRSA() const;
    uint8_t SNBRSA() const;

    uint16_t PCROP1ASTRT() const;
    uint16_t PCROP1AEND() const;

    uint16_t PCROP1BSTRT() const;
    uint16_t PCROP1BEND() const;

    uint8_t WRP1ASTRT() const;
    uint8_t WRP1AEND() const;
    uint8_t WRP1BSTRT() const;
    uint8_t WRP1BEND() const;

    uint16_t IPCCDBA() const;
    uint32_t SBRV() const;

    void setNBoot0(bool set);
    void setNBoot1(bool set);
    void setNSwBoot0(bool set);

    void setSRAM2RST(bool set);
    void setSRAM2PE(bool set);

    void setBORLEV(uint8_t val);

    void setnRSTSTOP(bool set);
    void setnRSTSTDBY(bool set);
    void setnRSTSHDW(bool set);
    void setIWDGSW(bool set);
    void setIWDGSTOP(bool set);
    void setIWGDSTDBY(bool set);
    void setWWDGSW(bool set);

private:
    bool m_isValid;
    OptionBytesData m_data;
};

}
}
