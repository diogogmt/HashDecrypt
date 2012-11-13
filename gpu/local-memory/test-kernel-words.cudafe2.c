# 1 "test-kernel-words.cudafe1.gpu"
# 18 "test-kernel-words.cu"
struct md5_state_s;
# 214 "/usr/llvm-gcc-4.2/bin/../lib/gcc/i686-apple-darwin11/4.2.1/include/stddef.h" 3
typedef unsigned long size_t;
#include "crt/host_runtime.h"
# 14 "test-kernel-words.cu"
typedef unsigned char md5_byte_t;
# 15 "test-kernel-words.cu"
typedef unsigned md5_word_t;
# 18 "test-kernel-words.cu"
struct md5_state_s {
# 19 "test-kernel-words.cu"
md5_word_t count[2];
# 20 "test-kernel-words.cu"
md5_word_t abcd[4];
# 21 "test-kernel-words.cu"
md5_byte_t buf[64];};
# 22 "test-kernel-words.cu"
typedef struct md5_state_s md5_state_t;
void *memcpy(void*, const void*, size_t); void *memset(void*, int, size_t);

#include "test-kernel-words.cudafe2.stub.c"
