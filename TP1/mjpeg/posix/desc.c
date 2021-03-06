
/**
 ** MARKER_BEGIN
 ** Auto-generated file, dont modify directly
 ** your changes will be lost !
 **
 ** Generated by DSX on 2016-12-12 12:49:29.685654
 ** by jchen@ubuntu
 ** MARKER_END
 **/

#include <srl.h>
#include <srl_private_types.h>

#define SRL_INMAIN
# include "idct_proto.h"
# include "vld_proto.h"
# include "iqzz_proto.h"
# include "demux_proto.h"
# include "tg_proto.h"
# include "ramdac_proto.h"
# include "libu_proto.h"
#undef SRL_INMAIN

static srl_barrier_s _start_barrier   = SRL_BARRIER_INITIALIZER(7);
static unsigned char demux_stack[4096] ;
static unsigned char demux_vld_buf[64] ;
static unsigned char huffman_buf[64]  ;
static unsigned char idct_libu_buf[128] ;
static unsigned char idct_stack[1024] ;
static unsigned char iqzz_idct_buf[512] ;
static unsigned char iqzz_stack[1024] ;
static unsigned char libu_ramdac_buf[768] ;
static unsigned char libu_stack[4096] ;
static unsigned char quanti_buf[128]  ;
static unsigned char ramdac_stack[1024] ;
static unsigned char tg_demux_buf[64] ;
static unsigned char tg_stack[4096]   ;
static unsigned char vld_iqzz_buf[256] ;
static unsigned char vld_stack[2048]  ;
static srl_mwmr_status_s demux_vld_status = SRL_MWMR_STATUS_INITIALIZER(  32,    2);
static srl_mwmr_status_s huffman_status = SRL_MWMR_STATUS_INITIALIZER(  32,    2);
static srl_mwmr_status_s idct_libu_status = SRL_MWMR_STATUS_INITIALIZER(  64,    2);
static srl_mwmr_status_s iqzz_idct_status = SRL_MWMR_STATUS_INITIALIZER( 256,    2);
static srl_mwmr_status_s libu_ramdac_status = SRL_MWMR_STATUS_INITIALIZER( 384,    2);
static srl_mwmr_status_s quanti_status = SRL_MWMR_STATUS_INITIALIZER(  64,    2);
static srl_mwmr_status_s tg_demux_status = SRL_MWMR_STATUS_INITIALIZER(  32,    2);
static srl_mwmr_status_s vld_iqzz_status = SRL_MWMR_STATUS_INITIALIZER( 128,    2);
#ifdef SRL_MWMR_USE_SEPARATE_LOCKS // ;
static srl_mwmr_lock_t demux_vld_lock = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t huffman_lock   = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t idct_libu_lock = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t iqzz_idct_lock = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t libu_ramdac_lock = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t quanti_lock    = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t tg_demux_lock  = SRL_MWMR_LOCK_INITIALIZER;
static srl_mwmr_lock_t vld_iqzz_lock  = SRL_MWMR_LOCK_INITIALIZER;
#endif // ;
const srl_mwmr_s demux_vld     = SRL_MWMR_INITIALIZER(  32,    2,        demux_vld_buf, &demux_vld_status, "demux_vld", &demux_vld_lock);
const srl_mwmr_s huffman       = SRL_MWMR_INITIALIZER(  32,    2,          huffman_buf, &huffman_status, "huffman", &huffman_lock);
const srl_mwmr_s idct_libu     = SRL_MWMR_INITIALIZER(  64,    2,        idct_libu_buf, &idct_libu_status, "idct_libu", &idct_libu_lock);
const srl_mwmr_s iqzz_idct     = SRL_MWMR_INITIALIZER( 256,    2,        iqzz_idct_buf, &iqzz_idct_status, "iqzz_idct", &iqzz_idct_lock);
const srl_mwmr_s libu_ramdac   = SRL_MWMR_INITIALIZER( 384,    2,      libu_ramdac_buf, &libu_ramdac_status, "libu_ramdac", &libu_ramdac_lock);
const srl_mwmr_s quanti        = SRL_MWMR_INITIALIZER(  64,    2,           quanti_buf, &quanti_status, "quanti", &quanti_lock);
const srl_mwmr_s tg_demux      = SRL_MWMR_INITIALIZER(  32,    2,         tg_demux_buf, &tg_demux_status, "tg_demux", &tg_demux_lock);
const srl_mwmr_s vld_iqzz      = SRL_MWMR_INITIALIZER( 128,    2,         vld_iqzz_buf, &vld_iqzz_status, "vld_iqzz", &vld_iqzz_lock);
static const struct _demux_args_t demux_args = {
	.input = (const srl_mwmr_t)&tg_demux,
	.quanti = (const srl_mwmr_t)&quanti,
	.huffman = (const srl_mwmr_t)&huffman,
	.output = (const srl_mwmr_t)&demux_vld,
};
static const struct _idct_args_t idct_args = {
	.input = (const srl_mwmr_t)&iqzz_idct,
	.output = (const srl_mwmr_t)&idct_libu,
};
static const struct _iqzz_args_t iqzz_args = {
	.input = (const srl_mwmr_t)&vld_iqzz,
	.quanti = (const srl_mwmr_t)&quanti,
	.output = (const srl_mwmr_t)&iqzz_idct,
};
static const struct _libu_args_t libu_args = {
	.input = (const srl_mwmr_t)&idct_libu,
	.output = (const srl_mwmr_t)&libu_ramdac,
};
static const struct _ramdac_args_t ramdac_args = {
	.input = (const srl_mwmr_t)&libu_ramdac,
};
static const struct _tg_args_t tg_args = {
	.output = (const srl_mwmr_t)&tg_demux,
};
static const struct _vld_args_t vld_args = {
	.input = (const srl_mwmr_t)&demux_vld,
	.huffman = (const srl_mwmr_t)&huffman,
	.output = (const srl_mwmr_t)&vld_iqzz,
};
static srl_task_s demux               = SRL_TASK_INITIALIZER(0, demux_FUNC_NAME(demux), 4096, demux_stack, &demux_args, "demux", 0x0, 0);
static srl_task_s idct                = SRL_TASK_INITIALIZER(0, idct_FUNC_NAME(idct), 1024, idct_stack, &idct_args, "idct", 0x0, 0);
static srl_task_s iqzz                = SRL_TASK_INITIALIZER(0, iqzz_FUNC_NAME(iqzz), 1024, iqzz_stack, &iqzz_args, "iqzz", 0x0, 0);
static srl_task_s libu                = SRL_TASK_INITIALIZER(0, libu_FUNC_NAME(libu), 4096, libu_stack, &libu_args, "libu", 0x0, 0);
static srl_task_s ramdac              = SRL_TASK_INITIALIZER(ramdac_FUNC_NAME(bootstrap), ramdac_FUNC_NAME(ramdac), 1024, ramdac_stack, &ramdac_args, "ramdac", 0x0, 0);
static srl_task_s tg                  = SRL_TASK_INITIALIZER(tg_FUNC_NAME(bootstrap), tg_FUNC_NAME(tg), 4096, tg_stack, &tg_args, "tg", 0x0, 0);
static srl_task_s vld                 = SRL_TASK_INITIALIZER(0, vld_FUNC_NAME(vld), 2048, vld_stack, &vld_args, "vld", 0x0, 0);
static srl_task_s * const cpu_task_list[7] = {&tg, &idct, &demux, &ramdac, &vld, &libu, &iqzz, };
static const srl_cpudesc_s cpu_cpu_desc = SRL_CPUDESC_INITIALIZER(   7, cpu_task_list, 0x0, 0);
static const srl_mwmr_s const * const all_mwmr[9] = {&demux_vld, &huffman, &idct_libu, &iqzz_idct, &libu_ramdac, &quanti, &tg_demux, &vld_iqzz, NULL };
static srl_task_s* const all_task[8]  = {&demux, &idct, &iqzz, &libu, &ramdac, &tg, &vld, NULL };
static const srl_cpudesc_s *cpu_desc_list[] = {&cpu_cpu_desc, NULL};
const srl_appdesc_s app_desc   = SRL_APPDESC_INITIALIZER(   7, cpu_desc_list, all_mwmr, all_task, &_start_barrier, 0x0, 0);

