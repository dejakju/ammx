@echo off
rem $VER:       build.bat 1.27
rem $DATE:      2023-12-01 (2025-11-17)
rem $AUTHOR:    Goran (dejakju@gmail.com)

pushd libs\

nasm -fwin64 ammx_build.asm
nasm -fwin64 ammx_decrement.asm
nasm -fwin64 ammx_fact.asm
nasm -fwin64 ammx_fib.asm
nasm -fwin64 ammx_getch.asm
nasm -fwin64 ammx_getchar.asm
nasm -fwin64 ammx_increment.asm
nasm -fwin64 ammx_maxofthree.asm
nasm -fwin64 ammx_ncr.asm
nasm -fwin64 ammx_puts.asm

gcc -m64 -c stack.c
gcc -m64 -c toolbox.c
ar rcs ammx.lib *.o *.obj

popd

gcc -m64 ammx.c -Llibs -lammx -o ammx

del libs\*.o
del libs\*.obj

rem ############################################################################
rem # ar: The GNU archiver tool (used for creating static libraries)
rem #   r: Insert/replace files in the archive
rem #   c: Create the archive if it doesn't exist
rem #   s: Write an object-file index (necessary for linking efficiency)

rem ############################################################################
rem # nasm: The Netwide Assembler
rem    -f format      select output file format
rem       bin                  Flat raw binary (MS-DOS, embedded, ...) [default]
rem       ith                  Intel Hex encoded flat binary
rem       srec                 Motorola S-records encoded flat binary
rem       aout                 Linux a.out
rem       aoutb                NetBSD/FreeBSD a.out
rem       coff                 COFF (i386) (DJGPP, some Unix variants)
rem       elf32                ELF32 (i386) (Linux, most Unix variants)
rem       elf64                ELF64 (x86-64) (Linux, most Unix variants)
rem       elfx32               ELFx32 (ELF32 for x86-64) (Linux)
rem       as86                 as86 (bin86/dev86 toolchain)
rem       obj                  Intel/Microsoft OMF (MS-DOS, OS/2, Win16)
rem       obj2                 Intel/Microsoft OMF (i386) (OS/2)
rem       win32                Microsoft extended COFF for Win32 (i386)
rem       win64                Microsoft extended COFF for Win64 (x86-64)
rem       ieee                 IEEE-695 (LADsoft variant) object file format
rem       macho32              Mach-O i386 (Mach, including MacOS X and variants)
rem       macho64              Mach-O x86-64 (Mach, including MacOS X and variants)
rem       dbg                  Trace of all info passed to output stage
rem       elf                  Legacy alias for "elf32"
rem       macho                Legacy alias for "macho32"
rem       win                  Legacy alias for "win32"

@echo on
