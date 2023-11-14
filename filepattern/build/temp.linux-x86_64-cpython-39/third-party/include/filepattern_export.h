
#ifndef FILEPATTERN_EXPORT_H
#define FILEPATTERN_EXPORT_H

#ifdef FILEPATTERN_STATIC_DEFINE
#  define FILEPATTERN_EXPORT
#  define FILEPATTERN_NO_EXPORT
#else
#  ifndef FILEPATTERN_EXPORT
#    ifdef filepattern_EXPORTS
        /* We are building this library */
#      define FILEPATTERN_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define FILEPATTERN_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef FILEPATTERN_NO_EXPORT
#    define FILEPATTERN_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef FILEPATTERN_DEPRECATED
#  define FILEPATTERN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef FILEPATTERN_DEPRECATED_EXPORT
#  define FILEPATTERN_DEPRECATED_EXPORT FILEPATTERN_EXPORT FILEPATTERN_DEPRECATED
#endif

#ifndef FILEPATTERN_DEPRECATED_NO_EXPORT
#  define FILEPATTERN_DEPRECATED_NO_EXPORT FILEPATTERN_NO_EXPORT FILEPATTERN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FILEPATTERN_NO_DEPRECATED
#    define FILEPATTERN_NO_DEPRECATED
#  endif
#endif

#endif /* FILEPATTERN_EXPORT_H */
