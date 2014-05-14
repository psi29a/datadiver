/* include/config.h.  Generated from config.h.cmake by configure.  */

/* Name of package */
#define PACKAGE "datadiver"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://www.mindwerks.net/projects/datadiver/"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://github.com/Mindwerks/datadiver/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Datadiver"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Datadiver @WILDMIDI_VERSION@"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "datadiver"

/* Define to the version of this package. */
#define PACKAGE_VERSION "@DATADIVER_VERSION@"

/* Version number of package */
#define VERSION "@DATADIVER_VERSION@"

/* Define this to the location of the config file */
#define DATADIVER_CFG "@DATADIVER_CFG@"

/* Define if the C compiler supports the `inline' keyword. */
#cmakedefine HAVE_C_INLINE
/* Define if the C compiler supports the `__inline__' keyword. */
#cmakedefine HAVE_C___INLINE__
/* Define if the C compiler supports the `__inline' keyword. */
#cmakedefine HAVE_C___INLINE
#if !defined(HAVE_C_INLINE) && !defined(__cplusplus)
# ifdef HAVE_C___INLINE__
#  define inline __inline__
# elif defined(HAVE_C___INLINE)
#  define inline __inline
# else
#  define inline
# endif
#endif

/* Define if the compiler has the `__builtin_expect' built-in function */
#cmakedefine HAVE___BUILTIN_EXPECT
#ifndef HAVE___BUILTIN_EXPECT
#define __builtin_expect(x,c) x
#endif

/* define this if you are running a bigendian system (motorola, sparc, etc) */
#cmakedefine WORDS_BIGENDIAN 1

/* Define if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H

/* Define if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H

