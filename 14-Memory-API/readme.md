1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. 
Compile this into an executable called null. What happens when you run this program?

```
$ clang -Wall -g -O3 null.c -o null
$ ./null
Dereferencing the null pointer...
value: 69140284
```

3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. 
Run this by typing in the following: valgrind --leak-check=yes null. 
What happens when you run this? Can you interpret the output from the tool?

```
$ clang -fsanitize=address null.c -o null.out
$ ./null.out
null.out(29348,0x100a38580) malloc: nano zone abandoned due to inability to preallocate reserved vm space.
Dereferencing the null pointer...
AddressSanitizer:DEADLYSIGNAL
=================================================================
==29348==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0001006efce0 bp 0x00016f7135a0 sp 0x00016f713570 T0)
==29348==The signal is caused by a READ memory access.
==29348==Hint: address points to the zero page.
    #0 0x1006efce0 in main+0x8c (null.out:arm64+0x100003ce0) (BuildId: 273bc30dc419311d84b64683ab79967532000000200000000100000000000c00)
    #1 0x1009c5084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #2 0xc6547ffffffffffc  (<unknown module>)

==29348==Register values:
 x[0] = 0x0000000000000022   x[1] = 0x0000000000000000   x[2] = 0x00000000000120a8   x[3] = 0x0000000000000001
 x[4] = 0x0000621000000180   x[5] = 0x0000000000000000   x[6] = 0x000000016ef18000   x[7] = 0x0000000000000001
 x[8] = 0x0000000000000000   x[9] = 0x0000000000000000  x[10] = 0x0000000000000002  x[11] = 0x00000000fffffffd
x[12] = 0x0000010000000000  x[13] = 0x0000000000000000  x[14] = 0x0000000000000000  x[15] = 0x0000000000000000
x[16] = 0x000000018962d474  x[17] = 0x00000001e34d1928  x[18] = 0x0000000000000000  x[19] = 0x00000001006fc060
x[20] = 0x00000001006efc54  x[21] = 0x0000000100a20070  x[22] = 0x0000000000000000  x[23] = 0x0000000000000000
x[24] = 0x0000000000000000  x[25] = 0x0000000000000000  x[26] = 0x0000000000000000  x[27] = 0x0000000000000000
x[28] = 0x0000000000000000     fp = 0x000000016f7135a0     lr = 0x00000001006efc80     sp = 0x000000016f713570
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (null.out:arm64+0x100003ce0) (BuildId: 273bc30dc419311d84b64683ab79967532000000200000000100000000000c00) in main+0x8c
==29348==ABORTING
fish: Job 1, './null.out' terminated by signal SIGABRT (Abort)
```

4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. 
What happens when this program runs? Can you use gdb to find any problems with it? 
How about valgrind (again with the --leak-check=yes flag)?

```
$ clang -fsanitize=address forget-to-free.c -o forget-to-free.out
$ ASAN_OPTIONS=detect_leaks=1 ./forget-to-free.out
x: 1

=================================================================
==29909==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x102b9d5b0 in wrap_malloc+0x8c (libclang_rt.asan_osx_dynamic.dylib:arm64+0x515b0) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x10250bb88 in main+0x30 (forget-to-free.out:arm64+0x100003b88) (BuildId: b5383bb93d3b37f7a859375271284f1f32000000200000000100000000000c00)
    #2 0x1026b1084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0x790bfffffffffffc  (<unknown module>)

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```

5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. 
What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?

```
$ ./heap-buffer-overflow.out
=================================================================
==30140==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6140000003d0 at pc 0x0001024f7c50 bp 0x00016d90b4f0 sp 0x00016d90b4e8
WRITE of size 4 at 0x6140000003d0 thread T0
    #0 0x1024f7c4c in main+0x104 (heap-buffer-overflow.out:arm64+0x100003c4c) (BuildId: 04239c5494473dbf93462158389ecee732000000200000000100000000000c00)
    #1 0x1027d1084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #2 0x142fffffffffffc  (<unknown module>)

0x6140000003d0 is located 0 bytes after 400-byte region [0x614000000240,0x6140000003d0)
allocated by thread T0 here:
    #0 0x102cbd5b0 in wrap_malloc+0x8c (libclang_rt.asan_osx_dynamic.dylib:arm64+0x515b0) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x1024f7b84 in main+0x3c (heap-buffer-overflow.out:arm64+0x100003b84) (BuildId: 04239c5494473dbf93462158389ecee732000000200000000100000000000c00)
    #2 0x1027d1084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0x142fffffffffffc  (<unknown module>)

SUMMARY: AddressSanitizer: heap-buffer-overflow (heap-buffer-overflow.out:arm64+0x100003c4c) (BuildId: 04239c5494473dbf93462158389ecee732000000200000000100000000000c00) in main+0x104
Shadow bytes around the buggy address:
  0x614000000100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x614000000180: 00 00 00 00 00 00 00 00 03 fa fa fa fa fa fa fa
  0x614000000200: fa fa fa fa fa fa fa fa 00 00 00 00 00 00 00 00
  0x614000000280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x614000000300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x614000000380: 00 00 00 00 00 00 00 00 00 00[fa]fa fa fa fa fa
  0x614000000400: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x614000000480: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x614000000500: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x614000000580: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x614000000600: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==30140==ABORTING
fish: Job 1, './heap-buffer-overflow.out' terminated by signal SIGABRT (Abort)
```

6. Create a program that allocates an array of integers (as above), frees them, 
and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?

```
$ ./heap-use-after-free.out
=================================================================
==30300==ERROR: AddressSanitizer: heap-use-after-free on address 0x614000000240 at pc 0x0001027efcb8 bp 0x00016d613500 sp 0x00016d6134f8
READ of size 4 at 0x614000000240 thread T0
    #0 0x1027efcb4 in main+0x108 (heap-use-after-free.out:arm64+0x100003cb4) (BuildId: 8a55ceec067838dd83d14b476fbc780432000000200000000100000000000c00)
    #1 0x102bc5084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #2 0xb963fffffffffffc  (<unknown module>)

0x614000000240 is located 0 bytes inside of 400-byte region [0x614000000240,0x6140000003d0)
freed by thread T0 here:
    #0 0x1030b16e4 in wrap_free+0x90 (libclang_rt.asan_osx_dynamic.dylib:arm64+0x516e4) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x1027efc5c in main+0xb0 (heap-use-after-free.out:arm64+0x100003c5c) (BuildId: 8a55ceec067838dd83d14b476fbc780432000000200000000100000000000c00)
    #2 0x102bc5084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0xb963fffffffffffc  (<unknown module>)

previously allocated by thread T0 here:
    #0 0x1030b15b0 in wrap_malloc+0x8c (libclang_rt.asan_osx_dynamic.dylib:arm64+0x515b0) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x1027efbe8 in main+0x3c (heap-use-after-free.out:arm64+0x100003be8) (BuildId: 8a55ceec067838dd83d14b476fbc780432000000200000000100000000000c00)
    #2 0x102bc5084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0xb963fffffffffffc  (<unknown module>)

SUMMARY: AddressSanitizer: heap-use-after-free (heap-use-after-free.out:arm64+0x100003cb4) (BuildId: 8a55ceec067838dd83d14b476fbc780432000000200000000100000000000c00) in main+0x108
Shadow bytes around the buggy address:
  0x613fffffff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x614000000000: fa fa fa fa fa fa fa fa 00 00 00 00 00 00 00 00
  0x614000000080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x614000000100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x614000000180: 00 00 00 00 00 00 00 00 03 fa fa fa fa fa fa fa
=>0x614000000200: fa fa fa fa fa fa fa fa[fd]fd fd fd fd fd fd fd
  0x614000000280: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x614000000300: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x614000000380: fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa fa
  0x614000000400: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x614000000480: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==30300==ABORTING
fish: Job 1, './heap-use-after-free.out' terminated by signal SIGABRT (Abort)
```

7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). 
What happens? Do you need tools to find this type of problem?

```
$ ./free-the-middle.out
=================================================================
==30436==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x614000000244 in thread T0
    #0 0x1031356e4 in wrap_free+0x90 (libclang_rt.asan_osx_dynamic.dylib:arm64+0x516e4) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x102ab3d10 in main+0xb4 (free-the-middle.out:arm64+0x100003d10) (BuildId: 65d5f6178bbf3627a0b0e1a9fcfa767632000000200000000100000000000c00)
    #2 0x102c49084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0xe738fffffffffffc  (<unknown module>)

0x614000000244 is located 4 bytes inside of 400-byte region [0x614000000240,0x6140000003d0)
allocated by thread T0 here:
    #0 0x1031355b0 in wrap_malloc+0x8c (libclang_rt.asan_osx_dynamic.dylib:arm64+0x515b0) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00)
    #1 0x102ab3c98 in main+0x3c (free-the-middle.out:arm64+0x100003c98) (BuildId: 65d5f6178bbf3627a0b0e1a9fcfa767632000000200000000100000000000c00)
    #2 0x102c49084 in start+0x200 (dyld:arm64+0x5084) (BuildId: fbb89662e6f23434b542f75185ac5e7432000000200000000100000000030c00)
    #3 0xe738fffffffffffc  (<unknown module>)

SUMMARY: AddressSanitizer: bad-free (libclang_rt.asan_osx_dynamic.dylib:arm64+0x516e4) (BuildId: 8c60ef4ebca637c4b9d46bbd4441c3c932000000200000000100000000000b00) in wrap_free+0x90
==30436==ABORTING
fish: Job 1, './free-the-middle.out' terminated by signal SIGABRT (Abort)
```