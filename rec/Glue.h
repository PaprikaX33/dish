#ifndef DISH_C_CXX_GLUE_HEAD_HPP
#define DISH_C_CXX_GLUE_HEAD_HPP

#define EXTERN_BRIDGE_BGN #ifdef __cplusplus    \
  namespace DI { extern "C" {                   \
  #endif

#define EXTERN_BRIDGE_END #ifdef __cplusplus    \
  }}                                            \
    #endif

#endif //DISH_C_CXX_GLUE_HEAD_HPP
