#if ! defined(RAW_BUFFER_LENGTH)
#define RAW_BUFFER_LENGTH  100  ///< Maximum length of raw duration buffer. Must be even. 100 supports up to 48 bit codings inclusive 1 start and 1 stop bit.
#endif
#if RAW_BUFFER_LENGTH % 2 == 1
#error RAW_BUFFER_LENGTH must be even, since the array consists of space / mark pairs.
#endif