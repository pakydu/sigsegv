How to trace the crashed issue when we want to dump the stack information?

Solution 1: dladdr():
sigsegv.c
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

solution 2: use backtrace():
   backtrace/dump.c
   NAME
       backtrace, backtrace_symbols, backtrace_symbols_fd - support for application self-debugging

SYNOPSIS
       #include <execinfo.h>

       int backtrace(void **buffer, int size);

       char **backtrace_symbols(void *const *buffer, int size);

       void backtrace_symbols_fd(void *const *buffer, int size, int fd);

DESCRIPTION
       backtrace()  returns  a  backtrace  for  the calling program, in the array pointed to by buffer.  A backtrace is the series of currently active function calls for the program.  Each item in the array pointed to by buffer is of type void *, and is the return
       address from the corresponding stack frame.  The size argument specifies the maximum number of addresses that can be stored in buffer.  If the backtrace is larger than size, then the addresses corresponding  to  the  size  most  recent  function  calls  are
       returned; to obtain the complete backtrace, make sure that buffer and size are large enough.

       Given  the set of addresses returned by backtrace() in buffer, backtrace_symbols() translates the addresses into an array of strings that describe the addresses symbolically.  The size argument specifies the number of addresses in buffer.  The symbolic rep‐
       resentation of each address consists of the function name (if this can be determined), a hexadecimal offset into the function, and the actual return address (in hexadecimal).  The address of the array of string pointers is returned as the function result of
       backtrace_symbols().  This array is malloc(3)ed by backtrace_symbols(), and must be freed by the caller.  (The strings pointed to by the array of pointers need not and should not be freed.)

       backtrace_symbols_fd()  takes  the  same buffer and size arguments as backtrace_symbols(), but instead of returning an array of strings to the caller, it writes the strings, one per line, to the file descriptor fd.  backtrace_symbols_fd() does not call mal‐
       loc(3), and so can be employed in situations where the latter function might fail, but see NOTES.

RETURN VALUE
       backtrace() returns the number of addresses returned in buffer, which is not greater than size.  If the return value is less than size, then the full backtrace was stored; if it is equal to size, then it may have been truncated, in which case the  addresses
       of the oldest stack frames are not returned.

       On success, backtrace_symbols() returns a pointer to the array malloc(3)ed by the call; on error, NULL is returned.
