/**
 * @defgroup config Configuration Options
 *
 * Defines the MPack configuration options. You can configure MPack by
 * pre-defining any of the below options in your build system or project
 * settings.
 *
 * Custom configuration of MPack is not usually necessary. In almost all
 * cases you can ignore this and use the defaults. If you are using the
 * amalgamation package, you do not need to add @c mpack-defaults.h to your
 * project.
 *
 * If you do want to configure MPack, the easiest way is to pre-define some of
 * the below options as part of your build system or project settings. This
 * will override the below defaults.
 *
 * If you'd like to use a file for configuration instead, define
 * @ref MPACK_HAS_CONFIG to 1 in your build system or project settings.
 * This will cause MPack to include a file you create called @c mpack-config.h.
 * You can copy @c mpack-defaults.h to @c mpack-config.h and make your
 * changes, or create a blank @c mpack-config.h and set only the options you
 * want. The below settings are the defaults if they are not set by your
 * configuration file.
 *
 * @warning The value of all configuration options must be the same in
 * all translation units of your project, as well as in the mpack source
 * itself. These configuration options affect the layout of structs, among
 * other things, which cannot be different in source files that are linked
 * together.
 *
 * @{
 */

// There is intentionally no include guard on this file. If you copy this to
// your own config file, this still needs to be included afterwards. This
// provides forward compatibility: new versions of MPack can introduce new
// options without forcing you to upgrade your config file.


/**
 * @name Features
 * @{
 */

/**
 * @def MPACK_READER
 *
 * Enables compilation of the base Tag Reader.
 */
#ifndef MPACK_READER
#define MPACK_READER 1
#endif

/**
 * @def MPACK_EXPECT
 *
 * Enables compilation of the static Expect API.
 */
#ifndef MPACK_EXPECT
#define MPACK_EXPECT 1
#endif

/**
 * @def MPACK_NODE
 *
 * Enables compilation of the dynamic Node API.
 */
#ifndef MPACK_NODE
#define MPACK_NODE 1
#endif

/**
 * @def MPACK_WRITER
 *
 * Enables compilation of the Writer.
 */
#ifndef MPACK_WRITER
#define MPACK_WRITER 1
#endif

/**
 * @def MPACK_COMPATIBILITY
 *
 * Enables compatibility features for reading and writing older
 * versions of MessagePack.
 *
 * This is disabled by default. When disabled, the behaviour is equivalent to
 * using the default version, @ref mpack_version_current.
 *
 * Enable this if you need to interoperate with applications or data that do
 * not support the new (v5) MessagePack spec. See the section on v4
 * compatibility in @ref docs/protocol.md for more information.
 */
#ifndef MPACK_COMPATIBILITY
#define MPACK_COMPATIBILITY 0
#endif

/**
 * @def MPACK_EXTENSIONS
 *
 * Enables the use of extension types.
 *
 * This is disabled by default. Define it to 1 to enable it. If disabled,
 * functions to read and write extensions will not exist, and any occurrence of
 * extension types in parsed messages will flag @ref mpack_error_invalid.
 *
 * MPack discourages the use of extension types. See the section on extension
 * types in @ref docs/protocol.md for more information.
 */
#ifndef MPACK_EXTENSIONS
#define MPACK_EXTENSIONS 0
#endif


/**
 * @}
 */


/**
 * @name Dependencies
 * @{
 */

/**
 * @def MPACK_HAS_CONFIG
 *
 * Enables the use of an @c mpack-config.h configuration file for MPack.
 * This file must be in the same folder as @c mpack.h, or it must be
 * available from your project's include paths.
 */
// This goes in your project settings.

/**
 * @def MPACK_STDLIB
 *
 * Enables the use of C stdlib. This allows the library to use malloc
 * for debugging and in allocation helpers.
 */
#ifndef MPACK_STDLIB
#define MPACK_STDLIB 1
#endif

/**
 * @def MPACK_STDIO
 *
 * Enables the use of C stdio. This adds helpers for easily
 * reading/writing C files and makes debugging easier.
 */
#ifndef MPACK_STDIO
#define MPACK_STDIO 1
#endif

/**
 * @}
 */


/**
 * @name System Functions
 * @{
 */

/**
 * @def MPACK_MALLOC
 *
 * Defines the memory allocation function used by MPack. This is used by
 * helpers for automatically allocating data the correct size, and for
 * debugging functions. If this macro is undefined, the allocation helpers
 * will not be compiled.
 *
 * The default is @c malloc() if @ref MPACK_STDLIB is enabled.
 */
/**
 * @def MPACK_FREE
 *
 * Defines the memory free function used by MPack. This is used by helpers
 * for automatically allocating data the correct size. If this macro is
 * undefined, the allocation helpers will not be compiled.
 *
 * The default is @c free() if @ref MPACK_MALLOC has not been customized and
 * @ref MPACK_STDLIB is enabled.
 */
/**
 * @def MPACK_REALLOC
 *
 * Defines the realloc function used by MPack. It is used by growable
 * buffers to resize more efficiently.
 *
 * The default is @c realloc() if @ref MPACK_MALLOC has not been customized and
 * @ref MPACK_STDLIB is enabled.
 *
 * This is optional, even when @ref MPACK_MALLOC is used. If @ref MPACK_MALLOC is
 * set and @ref MPACK_REALLOC is not, @ref MPACK_MALLOC is used with a simple copy
 * to grow buffers.
 */
#if defined(MPACK_STDLIB) && MPACK_STDLIB && !defined(MPACK_MALLOC)
#define MPACK_MALLOC malloc
#define MPACK_REALLOC realloc
#define MPACK_FREE free
#endif

/**
 * @}
 */


/**
 * @name Debugging Options
 */

/**
 * @def MPACK_DEBUG
 *
 * Enables debug features. You may want to wrap this around your
 * own debug preprocs. By default, this is enabled if @c DEBUG or @c _DEBUG
 * are defined. (@c NDEBUG is not used since it is allowed to have
 * different values in different translation units.)
 */
#if !defined(MPACK_DEBUG) && (defined(DEBUG) || defined(_DEBUG))
#define MPACK_DEBUG 1
#endif

/**
 * @def MPACK_STRINGS
 *
 * Enables descriptive error and type strings.
 *
 * This can be turned off (by defining it to 0) to maximize space savings
 * on embedded devices. If this is disabled, string functions such as
 * mpack_error_to_string() and mpack_type_to_string() return an empty string.
 */
#ifndef MPACK_STRINGS
#define MPACK_STRINGS 1
#endif

/**
 * Set this to 1 to implement a custom @ref mpack_assert_fail() function.
 * See the documentation on @ref mpack_assert_fail() for details.
 *
 * Asserts are only used when @ref MPACK_DEBUG is enabled, and can be
 * triggered by bugs in MPack or bugs due to incorrect usage of MPack.
 */
#ifndef MPACK_CUSTOM_ASSERT
#define MPACK_CUSTOM_ASSERT 0
#endif

/**
 * @def MPACK_READ_TRACKING
 *
 * Enables compound type size tracking for readers. This ensures that the
 * correct number of elements or bytes are read from a compound type.
 *
 * This is enabled by default in debug builds (provided a @c malloc() is
 * available.)
 */
#if !defined(MPACK_READ_TRACKING) && \
        defined(MPACK_DEBUG) && MPACK_DEBUG && \
        defined(MPACK_READER) && MPACK_READER && \
        defined(MPACK_MALLOC)
#define MPACK_READ_TRACKING 1
#endif

/**
 * @def MPACK_WRITE_TRACKING
 *
 * Enables compound type size tracking for writers. This ensures that the
 * correct number of elements or bytes are written in a compound type.
 *
 * Note that without write tracking enabled, it is possible for buggy code
 * to emit invalid MessagePack without flagging an error by writing the wrong
 * number of elements or bytes in a compound type. With tracking enabled,
 * MPack will catch such errors and break on the offending line of code.
 *
 * This is enabled by default in debug builds (provided a @c malloc() is
 * available.)
 */
#if !defined(MPACK_WRITE_TRACKING) && \
        defined(MPACK_DEBUG) && MPACK_DEBUG && \
        defined(MPACK_WRITER) && MPACK_WRITER && \
        defined(MPACK_MALLOC)
#define MPACK_WRITE_TRACKING 1
#endif

/**
 * @}
 */


/**
 * @name Miscellaneous Options
 * @{
 */

/**
 * @def MPACK_BUILDER
 *
 * Enables compilation of the Builder API (`mpack_build_map()` and
 * `mpack_build_array()`.)
 *
 * This is enabled by default if MPACK_WRITER is enabled and MPACK_MALLOC is
 * defined.
 */
#ifndef MPACK_BUILDER
#if defined(MPACK_MALLOC) && MPACK_WRITER
#define MPACK_BUILDER 1
#else
#define MPACK_BUILDER 0
#endif
#endif

/**
 * @def MPACK_BUILDER_INTERNAL_STORAGE
 *
 * Enables a small amount of internal storage within the writer to avoid some
 * allocations when using builders.
 *
 * This is disabled by default. Enable it to potentially improve performance at
 * the expense of a larger writer.
 *
 * @see MPACK_BUILDER_INTERNAL_STORAGE_SIZE to configure its size.
 */
#ifndef MPACK_BUILDER_INTERNAL_STORAGE
#define MPACK_BUILDER_INTERNAL_STORAGE 0
#endif

/**
 * Whether to optimize for size or speed.
 *
 * Optimizing for size simplifies some parsing and encoding algorithms
 * at the expense of speed, and saves a few kilobytes of space in the
 * resulting executable.
 *
 * This automatically detects -Os with GCC/Clang. Unfortunately there
 * doesn't seem to be a macro defined for /Os under MSVC.
 */
#ifndef MPACK_OPTIMIZE_FOR_SIZE
#ifdef __OPTIMIZE_SIZE__
#define MPACK_OPTIMIZE_FOR_SIZE 1
#else
#define MPACK_OPTIMIZE_FOR_SIZE 0
#endif
#endif

/**
 * Stack space in bytes to use when initializing a reader or writer
 * with a stack-allocated buffer.
 */
#ifndef MPACK_STACK_SIZE
#define MPACK_STACK_SIZE 4096
#endif

/**
 * Buffer size to use for allocated buffers (such as for a file writer.)
 *
 * Starting with a single page and growing as needed seems to
 * provide the best performance with minimal memory waste.
 * Increasing this does not improve performance even when writing
 * huge messages.
 */
#ifndef MPACK_BUFFER_SIZE
#define MPACK_BUFFER_SIZE 4096
#endif

/**
 * Minimum size for paged allocations in bytes.
 *
 * This is the value used by default for MPACK_NODE_PAGE_SIZE and
 * MPACK_BUILDER_PAGE_SIZE.
 */
#ifndef MPACK_PAGE_SIZE
#define MPACK_PAGE_SIZE 4096
#endif

/**
 * Minimum size of an allocated node page in bytes.
 *
 * The children for a given compound element must be contiguous, so
 * larger pages than this may be allocated as needed. (Safety checks
 * exist to prevent malicious data from causing too large allocations.)
 *
 * See @ref mpack_node_data_t for the size of nodes.
 *
 * Using as many nodes fit in one memory page seems to provide the
 * best performance, and has very little waste when parsing small
 * messages.
 */
#ifndef MPACK_NODE_PAGE_SIZE
#define MPACK_NODE_PAGE_SIZE MPACK_PAGE_SIZE
#endif

/**
 * Minimum size of an allocated builder page in bytes.
 *
 * Builder writes are deferred to the allocated builder buffer which is
 * composed of a list of buffer pages. This defines the size of those pages.
 */
#ifndef MPACK_BUILDER_PAGE_SIZE
//#define MPACK_BUILDER_PAGE_SIZE MPACK_PAGE_SIZE
#define MPACK_BUILDER_PAGE_SIZE 99
#endif

/**
 * Amount of space reserved inside mpack_writer_t for the Builders. This can
 * allow small messages to be built with the Builder API without incurring an
 * allocation.
 *
 * An mpack_builder_page_t and several mpack_builder_t are placed within this
 * space in addition to the literal MessagePack data. It needs to be big enough
 * to be useful, but not too big so as to be wasteful; if more space is needed,
 * pages are allocated.
 *
 * This is only used if MPACK_BUILDER_INTERNAL_STORAGE is enabled.
 *
 * @see MPACK_BUILDER_PAGE_SIZE
 * @see MPACK_BUILDER_INTERNAL_STORAGE
 */
#ifndef MPACK_BUILDER_INTERNAL_STORAGE_SIZE
#define MPACK_BUILDER_INTERNAL_STORAGE_SIZE 256
#endif

/**
 * The initial depth for the node parser. When MPACK_MALLOC is available,
 * the node parser has no practical depth limit, and it is not recursive
 * so there is no risk of overflowing the call stack.
 */
#ifndef MPACK_NODE_INITIAL_DEPTH
#define MPACK_NODE_INITIAL_DEPTH 8
#endif

/**
 * The maximum depth for the node parser if @ref MPACK_MALLOC is not available.
 */
#ifndef MPACK_NODE_MAX_DEPTH_WITHOUT_MALLOC
#define MPACK_NODE_MAX_DEPTH_WITHOUT_MALLOC 32
#endif

/**
 * Whether the 'float' type and floating point operations are supported.
 *
 * If MPACK_FLOAT is disabled, floats are read and written as uint32_t instead.
 * This way messages with floats do not result in errors and you can still
 * perform manual float parsing yourself.
 */
#ifndef MPACK_FLOAT
    #ifdef __KERNEL__
        // No floating point support in the Linux kernel.
        #define MPACK_FLOAT 0
    #else
        #define MPACK_FLOAT 1
    #endif
#endif

/**
 * Whether the 'double' type is supported. This requires support for 'float'.
 *
 * If MPACK_DOUBLE is disabled, doubles are read and written as uint32_t
 * instead. This way messages with doubles do not result in errors and you can
 * still perform manual doubles parsing yourself.
 *
 * If MPACK_FLOAT is enabled but MPACK_DOUBLE is not, doubles can be read as
 * floats using the shortening conversion functions, e.g. mpack_expect_float()
 * or mpack_node_float().
 */
#ifndef MPACK_DOUBLE
    #if !MPACK_FLOAT || defined(__AVR__)
        // AVR supports only float, not double.
        #define MPACK_DOUBLE 0
    #else
        #define MPACK_DOUBLE 1
    #endif
#endif

/**
 * @}
 */


/**
 * @}
 */

