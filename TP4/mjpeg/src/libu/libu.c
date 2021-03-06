#include <srl.h>
#include "libu_proto.h"

#include "../common/jpeg.h"

FUNC(libu)
{
  srl_mwmr_t input_mwmr[2];
  input_mwmr[0] = GET_ARG(input_0);
  input_mwmr[1] = GET_ARG(input_1);
  srl_mwmr_t output_mwmr = GET_ARG(output);

  uint8_t in[BLOCK_SIZE];
  uint8_t Libu[WIDTH * BLOCK_HEIGHT];

  uint32_t i, j, k, n, m;

  for(m = 0; m < 2; m++)
  {
      for (i = 0; i < BLOCKS_H; i++)
      {
          for (j = 0; j < BLOCKS_W; j++)
          {
              srl_mwmr_read( input_mwmr[m], in, BLOCK_SIZE * sizeof(*in) );

              for (k = 0; k < 8; k++)
                  // memcpy(&Libu[k*48 + 8*j ], &in[k*8], 8);
                  for (n = 0; n < 8; n++)
                      Libu[k * WIDTH + n + BLOCK_WIDTH * j ] = in[k * BLOCK_WIDTH + n];
          }
          srl_mwmr_write(output_mwmr, Libu, WIDTH * BLOCK_HEIGHT * sizeof(*Libu));
      }
  }
}
