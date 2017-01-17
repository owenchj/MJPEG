#include "srl.h"
#include "srl_endianness.h"

#include "../common/jpeg.h"

#include "../common/block_io.h"

uint16_t get_next_mk(block_io *f)
{
    uint8_t buf;
    buf = block_io_read_int8(f);
    return buf;
}

FUNC(split) {

    uint8_t input_buffer[32];
    block_io input;

    block_io output_0;
    block_io output_1;
    uint8_t output_buffer[2][32];

    uint8_t buf_b, buf_m;

    srl_mwmr_t input_mwmr = GET_ARG(input);
    srl_mwmr_t output_mwmr[2];
    output_mwmr[0] = GET_ARG(output_0);
    output_mwmr[1] = GET_ARG(output_1);

    /*
     * Les block_io sont des optimisation des acces aux canaux mwmr
     * quand ceux-ci servent a faire transiter des donnees de tailles
     * non fixes.
     *
     * Les transferts inities par les block_io se feront par blocs de
     * n _octets_, n etant la taille passee lors de leur intialisation
     * (ici 32 ou 64 octets, soit 8 ou 16 mots 32 bits).
     */
    block_io_init_in(&input, input_buffer, 32, input_mwmr);
    block_io_init_out(&output_0, output_buffer[0], 32, output_mwmr[0]);
    block_io_init_out(&output_1, output_buffer[1], 32, output_mwmr[1]);

    int r = 0;

    while(1) {

        buf_b = block_io_read_int8(f);
        if (buf_b == 0xff)
        {
            buf_m = block_io_read_int8(f);
            if (buf_m == 0xd8)
            {
                if(r == 0) {
                    block_io_set_left(&output_0);
                    block_io_flush(&output_0);
                }
                else {
                    block_io_set_left(&output_1);
                    block_io_flush(&output_1);
                }

                r = 1 - r;
            }
            if(r == 0) {
                block_io_write_int8(&output_0, buf_b);
                block_io_write_int8(&output_0, buf_m);
            }
            else {
                block_io_write_int8(&output_1, buf_b);
                block_io_write_int8(&output_1, buf_m);
            }
            continue;
        }
        else
        {
            if(r == 0)
                block_io_write_int8(output_0, buf_b);
            else
                block_io_write_int8(output_1, buf_b);
        }

    }
}
