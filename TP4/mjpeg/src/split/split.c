#include "srl.h"
#include "split_proto.h"
#include "srl_endianness.h"

#include "../common/jpeg.h"

#include "../common/block_io.h"

FUNC(split) {

    uint8_t input_buffer[32];
    block_io input;

    block_io output;
    uint8_t output_buffer[32];

    uint8_t buf_b, buf_m;

    srl_mwmr_t input_mwmr = GET_ARG(input);
    srl_mwmr_t output_mwmr[2] = { GET_ARG(output_0), GET_ARG(output_1)};

    block_io_init_in(&input, input_buffer, 32, input_mwmr);
    block_io_init_out(&output, output_buffer, 32, output_mwmr[0]);

    int r = 1;

    while(1) {

        buf_b = block_io_read_int8(&input);
        if (buf_b == 0xff)
        {
            buf_m = block_io_read_int8(&input);
            if (buf_m == 0xd8)
            {
		  block_io_set_left(&output, 0xff);
		  block_io_flush(&output);
		  r = 1 - r;
		  output.io = output_mwmr[r];
            }
	    block_io_write_int8(&output, buf_b);
	    block_io_write_int8(&output, buf_m);
	}
        else
        {
	  block_io_write_int8(&output, buf_b);
        }
    }
}
