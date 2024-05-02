/* hpack extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_hpack.h"
#include "hpack_arginfo.h"
#include <nghttp2/nghttp2.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

#define MAKE_NV(K, V)                                                          \
  {                                                                            \
    (uint8_t *) Z_STRVAL_P(K), (uint8_t *) Z_STRVAL_P(V), Z_STRLEN_P(K), Z_STRLEN_P(V), \
        NGHTTP2_NV_FLAG_NONE                                                   \
  }

/* {{{ string hpack_encode( array $input ) */
PHP_FUNCTION(hpack_encode)
{
    zval *input;
    size_t i;
    size_t sum;
    size_t nvlen;
    uint8_t *buf;
    size_t buflen;
    size_t outlen;
    int rv;
    zval *entry;
    HashTable *myht;
    nghttp2_hd_deflater *deflater;
    zend_string *retval;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(input)
    ZEND_PARSE_PARAMETERS_END();

    myht = Z_ARRVAL_P(input);
    uint32_t num = zend_hash_num_elements(myht);
    nghttp2_nv nva[num];
    i = 0;

    ZEND_HASH_FOREACH_VAL(myht, entry) {
        ZVAL_DEREF(entry);

        zval *value = zend_hash_index_find(Z_ARRVAL_P(entry), 0);
        zval *value2 = zend_hash_index_find(Z_ARRVAL_P(entry), 1);
        nva[i] = (nghttp2_nv) MAKE_NV(value, value2);
        ++i;
    } ZEND_HASH_FOREACH_END();

    nvlen = sizeof(nva) / sizeof(nva[0]);

    rv = nghttp2_hd_deflate_new(&deflater, 4096);

    buflen = nghttp2_hd_deflate_bound(deflater, nva, nvlen);
    buf = malloc(buflen);
    rv = nghttp2_hd_deflate_hd(deflater, buf, buflen, nva, nvlen);
    outlen = (size_t)rv;

    retval = strpprintf(outlen, "%s", buf);

    RETURN_STR(retval);
    free(buf);
    nghttp2_hd_deflate_del(deflater);
}
/* }}} */


/* {{{ array hpack_decode( string $input ) */
PHP_FUNCTION(hpack_decode)
{
    char *var;
    size_t var_len;
    zend_string *retval;
    ssize_t rv;
    nghttp2_hd_inflater *inflater;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(var, var_len)
    ZEND_PARSE_PARAMETERS_END();

    rv = nghttp2_hd_inflate_new(&inflater);
    nghttp2_hd_inflate_del(inflater);
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(hpack)
{
#if defined(ZTS) && defined(COMPILE_DL_HPACK)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(hpack)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "hpack support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ hpack_module_entry */
zend_module_entry hpack_module_entry = {
	STANDARD_MODULE_HEADER,
	"hpack",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(hpack),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(hpack),			/* PHP_MINFO - Module info */
	PHP_HPACK_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HPACK
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(hpack)
#endif
