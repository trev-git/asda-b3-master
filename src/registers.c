#include <soem/soem.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

uint8_t read_ec_reg8(ecx_contextt *ctx, uint16_t slave_addr, uint16_t reg)
{
    uint8_t data = 0;
    int wkc;
    if (!(wkc = ecx_FPRD(&ctx->port, 0x1001, reg, sizeof(uint8_t), &data, 10000)))
    {
        fprintf(stderr, "Failed to read register %04hx:%04hx!\n", slave_addr, reg);
        return data;
    }
    return data;
}

bool write_ec_reg8(ecx_contextt *ctx, uint16_t slave_addr, uint16_t reg, uint8_t data)
{
    int wkc;
    if (!(wkc = ecx_FPWR(&ctx->port, slave_addr, reg, sizeof(uint8_t), &data, 10000)))
    {
        fprintf(stderr, "Failed to read register %04hx:%04hx!\n", slave_addr, reg);
        return false;
    }
    return true;
}
