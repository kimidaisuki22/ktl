
#ifdef NDEBUG
#define CHECKS_BOOL 0
#else
#define CHECKS_BOOL 1
#endif

#define CHECKS if constexpr (CHECKS_BOOL)
