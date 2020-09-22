#ifndef DISH_COMMON_HEADER_HEAD_H
#define DISH_COMMON_HEADER_HEAD_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS }
#else
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif

#endif //DISH_COMMON_HEADER_HEAD_H
