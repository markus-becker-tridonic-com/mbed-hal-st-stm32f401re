#include <stdint.h>


// http://www.st.com/web/en/resource/technical/document/reference_manual/DM00031936.pdf STM32F0 Section 33.1
//#define STM_UUID_REGISTER_BASE_ADDRESS ((uint32_t *)0x1FFFF7AC)

// http://www.st.com/web/en/resource/technical/document/reference_manual/DM00031020.pdf STM32F4 Section 39.1
#define STM_UUID_REGISTER_BASE_ADDRESS ((uint32_t *)0x1FFF7A10)


// Provide ethernet devices with a semi-unique MAC address from the UUID
void mbed_mac_address(char *mac)
{
    // Fetch word 0
    uint32_t word0 = STM_UUID_REGISTER_BASE_ADDRESS[0];
    // Fetch word 1
    // we only want bottom 16 bits of word1 (MAC bits 32-47)
    // and bit 9 forced to 1, bit 8 forced to 0
    // Locally administered MAC, reduced conflicts
    // http://en.wikipedia.org/wiki/MAC_address
    uint32_t word1 = STM_UUID_REGISTER_BASE_ADDRESS[1];
    word1 |= 0x00000200;
    word1 &= 0x0000FEFF;
    
    mac[0] = (word1 & 0x000000ff);
    mac[1] = (word1 & 0x0000ff00) >> 8;
    mac[2] = (word0 & 0xff000000) >> 24;
    mac[3] = (word0 & 0x00ff0000) >> 16;
    mac[4] = (word0 & 0x0000ff00) >> 8;
    mac[5] = (word0 & 0x000000ff);
}

// Provide wireless devices with a semi-unique MAC address from the UUID
void mbed_mac_address_eui64(char *mac)
{
    // Fetch word 0
    //uint32_t word0 = *(uint32_t *)(STM_UUID_REGISTER_BASE_ADDRESS + STM_UUID_REGISTER_OFFSET_LOW);
    uint32_t word0 = STM_UUID_REGISTER_BASE_ADDRESS[0];
    // Fetch word 1
    //uint32_t word1 = *(uint32_t *)(STM_UUID_REGISTER_BASE_ADDRESS + STM_UUID_REGISTER_OFFSET_MID);
    uint32_t word1 = STM_UUID_REGISTER_BASE_ADDRESS[1];

#warning "TODO: fix locally administered bits"
    //word1 |= 0x00000200;
    //word1 &= 0x0000FEFF;

    mac[0] = (word1 & 0xff000000) >> 24;
    mac[1] = (word1 & 0x00ff0000) >> 16;
    mac[2] = (word0 & 0x0000ff00) >> 8;
    mac[3] = (word0 & 0x000000ff);
    mac[4] = (word0 & 0xff000000) >> 24;
    mac[5] = (word0 & 0x00ff0000) >> 16;
    mac[6] = (word0 & 0x0000ff00) >> 8;
    mac[7] = (word0 & 0x000000ff);
}
