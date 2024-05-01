/* hpack extension for PHP */

#ifndef PHP_HPACK_H
# define PHP_HPACK_H

extern zend_module_entry hpack_module_entry;
# define phpext_hpack_ptr &hpack_module_entry

# define PHP_HPACK_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_HPACK)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_HPACK_H */
