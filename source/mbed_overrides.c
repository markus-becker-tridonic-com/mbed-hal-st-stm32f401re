#include <stdint.h>

// from http://www.st.com/web/en/resource/technical/document/reference_manual/CD00171190.pdf chapter 30.2
#define STM_UUID_REGISTER_BASE_ADDRESS 0x1FFFF7E8
#define STM_UUID_REGISTER_OFFSET_MID 0x4
#define STM_UUID_REGISTER_OFFSET_LOW 0x8

// Provide ethernet devices with a semi-unique MAC address from the UUID
void mbed_mac_address(char *mac)
{
    // Fetch word 0
    uint32_t word0 = *(uint32_t *)(STM_UUID_REGISTER_BASE_ADDRESS + STM_UUID_REGISTER_OFFSET_LOW);
    // Fetch word 1
    // we only want bottom 16 bits of word1 (MAC bits 32-47)
    // and bit 9 forced to 1, bit 8 forced to 0
    // Locally administered MAC, reduced conflicts
    // http://en.wikipedia.org/wiki/MAC_address
    uint32_t word1 = *(uint32_t *)(STM_UUID_REGISTER_BASE_ADDRESS + STM_UUID_REGISTER_OFFSET_MID);
    word1 |= 0x00000200;
    word1 &= 0x0000FEFF;
    
    mac[0] = (word1 & 0x000000ff);
    mac[1] = (word1 & 0x0000ff00) >> 8;
    mac[2] = (word0 & 0xff000000) >> 24;
    mac[3] = (word0 & 0x00ff0000) >> 16;
    mac[4] = (word0 & 0x0000ff00) >> 8;
    mac[5] = (word0 & 0x000000ff);
}
