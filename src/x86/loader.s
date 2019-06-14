/*
 * File: loader.s
 * Author: Sam Miller (noogii7@gmail.com)
 * -----
 * Last Modified: Thursday, 14th March 2019 10:52:27 pm
 * Modified By: Sam Miller (noogii7@gmail.com>)
 * -----
 * Copyright (c) 2019 Sam Miller (noogii7@gmail.com>)
 */

.set MAGIC, 0x1BADB002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .text
  .code32

  multibootHeader:
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

  .extern kMain
  .extern callConstructors
  .global loader
  .global _stop

  loader:
    cli
    mov $kernelStack, %esp
    mov $kernelStack, %ebp
    #call callConstructors
    push %ebx
    call kMain

  _stop:
    cli
    hlt
    jmp _stop

.section .bss
  .space 2 * 1024 * 1024; # 2 MiB Stack
kernelStack:
