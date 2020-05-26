# sigsegv
debug segfault
 #define _GNU_SOURCE
       #include <dlfcn.h>

       int dladdr(void *addr, Dl_info *info);

       int dladdr1(void *addr, Dl_info *info, void **extra_info, int flags);

       Link with -ldl.

DESCRIPTION
       The  function  dladdr()  determines whether the address specified in addr is located in one of the shared objects loaded by
       the calling application.  If it is, then dladdr() returns information about the shared  object  and  symbol  that  overlaps
       addr.  This information is returned in a Dl_info structure:

           typedef struct {
               const char *dli_fname;  /* Pathname of shared object that
                                          contains address */
               void       *dli_fbase;  /* Base address at which shared
                                          object is loaded */
               const char *dli_sname;  /* Name of symbol whose definition
                                          overlaps addr */
               void       *dli_saddr;  /* Exact address of symbol named
                                          in dli_sname */
           } Dl_info;

       If no symbol matching addr could be found, then dli_sname and dli_saddr are set to NULL.
