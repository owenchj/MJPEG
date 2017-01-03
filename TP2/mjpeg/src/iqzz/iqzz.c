#include <srl.h>
#include "iqzz_proto.h"

#include "../common/jpeg.h"


static const uint8_t ZZ[64] = {
  0, 1, 8, 16, 9, 2,3,10,
  17, 24, 32, 25, 18, 11,  4, 5,
  12, 19, 26, 33, 40, 48, 41, 34,
  27, 20, 13,  6,  7, 14, 21, 28,
  35, 42, 49, 56, 57, 50, 43, 36,
  29, 22, 15, 23, 30, 37, 44, 51,
  58, 59, 52, 45, 38, 31, 39, 46,
  53, 60, 61, 54, 47, 55, 62, 63
};

FUNC(iqzz)
{
  srl_mwmr_t input_mwmr = GET_ARG(input);
  srl_mwmr_t output_mwmr = GET_ARG(output);
  srl_mwmr_t quanti_mwmr = GET_ARG(quanti);

  int16_t in[BLOCK_SIZE];
  uint8_t quanti_buffer[64];
  int32_t Iqzz[BLOCK_SIZE];

  uint32_t i;
  int16_t block;

  srl_mwmr_read( quanti_mwmr, quanti_buffer, 64);

  for ( block=0; block<NBLOCKS; ++block ) {

    srl_log_printf(TRACE, "IQZZ processing block %d/%d\n",
		   block, NBLOCKS);

    srl_mwmr_read( input_mwmr, in, BLOCK_SIZE * sizeof(*in) );

    for (i = 0; i < BLOCK_SIZE; i++)
      {
	Iqzz[ZZ[i]] = in[i] * quanti_buffer[i];
      }

    srl_mwmr_write(output_mwmr, (uint8_t *)Iqzz, BLOCK_SIZE * sizeof(*Iqzz));
  }

}
