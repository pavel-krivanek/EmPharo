#ifndef PHAROVM_CONFIG_H
#define PHAROVM_CONFIG_H

#pragma once

/* Common configurations */
#define VM_NAME "Pharo"
#define DEFAULT_IMAGE_NAME "Pharo.image"

/* Availabilit of Functions */

#define HAVE_DIRENT_H
#define HAVE_FEATURES_H
#define HAVE_UNISTD_H 1
/* #undef HAVE_NDIR_H */
/* #undef HAVE_SYS_NDIR_H */
#define HAVE_SYS_DIR_H
/* #undef HAVE_SYS_FILIO_H */
#define HAVE_SYS_TIME_H

/* #undef AVE_DLFCN_H */
#define HAVE_LIBDL
/* #undef HAVE_DYLD */
#define HAVE_TM_GMTOFF

/* architecture */

#define OS_TYPE "unix"

#define VM_HOST "Linux-4.15.0-72-generic"
#define VM_HOST_CPU "x86_64"
#define VM_HOST_OS "linux-gnu"
#define VM_TARGET "Linux-4.15.0-72-generic"
#define VM_TARGET_CPU "x86_64"
#define VM_TARGET_OS "linux-gnu"

/* widths of primitive types */

#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_VOID_P 8

#define squeakInt64 long

/* #undef HAVE_SYS_UUID_H */
/* #undef HAVE_UUID_UUID_H */
/* #undef HAVE_UUID_H */

/* #undef HAVE_UUIDGEN */
/* #undef HAVE_UUID_GENERATE */

#if defined(_MSC_VER)
#define VM_BUILD_STRING VM_NAME" 8.2.0 built on "__DATE__ " "__TIME__" Compiler: Visual C"
#define COMPILER_VERSION "Visual C"
#else
#define VM_BUILD_STRING VM_NAME" 8.2.0 built on "__DATE__ " "__TIME__" Compiler: "__VERSION__
#define COMPILER_VERSION __VERSION__
#endif

#define VM_BUILD_SOURCE_STRING "v8.1.0-alpha-245-g3ae44dcbd - Commit: 3ae44dcbd - Date: 2019-12-12 08:41:51 +0100"

#endif //PHAROVM_CONFIG_H
