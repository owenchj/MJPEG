
/**
 ** MARKER_BEGIN
 ** Auto-generated file, dont modify directly
 ** your changes will be lost !
 **
 ** Generated by DSX on 2016-12-05 21:10:45.978445
 ** by jchen@ubuntu
 ** MARKER_END
 **/
#ifndef _CONSUMER_PROTO_H
#define _CONSUMER_PROTO_H

#include <srl.h>

struct _consumer_args_t {
	const srl_mwmr_t input;
};

#define consumer_FUNC_NAME(sym) consumer_func_ ## sym

#define FUNC(x) void consumer_FUNC_NAME(x) (struct _consumer_args_t *_func_args)

FUNC(cons_func);

#ifdef SRL_INMAIN
# undef FUNC
#else
# define GET_ARG(port) ({ \
srl_log_printf( DEBUG, "%s:%d: arg %s = %p\n", __FILE__, __LINE__, #port, _func_args->port ); \
(_func_args->port); \
})
#endif /* SRL_INMAIN */

#endif /* _CONSUMER_PROTO_H */
