# Fuse Leak Reproduction

When running fuse under valgrind and maybe other tools which slows down execution,
the fuse does not release all resources when `fusermount -u` is executed immediately
after resource usage.

Adding delay before `fusermount -u` resolves the issue, so this is a timing race.

Reproduce using `make check`

libfuse issue https://github.com/libfuse/libfuse/issues/647


```
./fuse-leak-test
------------------------------------------------------------------------------------------------------------------
| Check with no valgrind, usually releases...
------------------------------------------------------------------------------------------------------------------
getattr '/'
readdir '/'
getattr '/file1'
open '/file1'
read '/file1'
release '/file1'
------------------------------------------------------------------------------------------------------------------
| Check with valgrind, usually fail to release, termination race...
------------------------------------------------------------------------------------------------------------------
getattr '/'
readdir '/'
getattr '/file1'
open '/file1'
read '/file1'
FAIL: No release!
------------------------------------------------------------------------------------------------------------------
| Check with valgrind and sleep before umount, usually releases.. this proves there is a race...
------------------------------------------------------------------------------------------------------------------
getattr '/'
readdir '/'
getattr '/file1'
open '/file1'
read '/file1'
release '/file1'
```
