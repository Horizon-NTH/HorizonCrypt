find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARY NAMES gmp gmpxx)

if (GMP_INCLUDE_DIR AND GMP_LIBRARY)
    set(GMP_FOUND TRUE)
else ()
    set(GMP_FOUND FALSE)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP DEFAULT_MSG GMP_LIBRARY GMP_INCLUDE_DIR)
