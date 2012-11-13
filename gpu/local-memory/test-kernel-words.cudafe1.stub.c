#define __NV_CUBIN_HANDLE_STORAGE__ static
#include "crt/host_runtime.h"
#include "test-kernel-words.fatbin.c"
extern void __device_stub__Z10testKernelPhPc(md5_byte_t *, char *);
static void __sti____cudaRegisterAll_25_test_kernel_words_cpp1_ii_9f375eeb(void) __attribute__((__constructor__));
void __device_stub__Z10testKernelPhPc(md5_byte_t *__par0, char *__par1){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 4UL);__cudaLaunch(((char *)((void ( *)(md5_byte_t *, char *))testKernel)));}
# 428 "test-kernel-words.cu"
void testKernel( md5_byte_t *__cuda_0,char *__cuda_1)
# 428 "test-kernel-words.cu"
{__device_stub__Z10testKernelPhPc( __cuda_0,__cuda_1);
# 527 "test-kernel-words.cu"
}
# 1 "test-kernel-words.cudafe1.stub.c"
static void __sti____cudaRegisterAll_25_test_kernel_words_cpp1_ii_9f375eeb(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(md5_byte_t *, char *))testKernel), _Z10testKernelPhPc, (-1));  }
