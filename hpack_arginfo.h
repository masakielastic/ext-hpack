ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_hpack_encode, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_hpack_decode, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(hpack_encode);
ZEND_FUNCTION(hpack_decode);

static const zend_function_entry ext_functions[] = {
        ZEND_FE(hpack_encode, arginfo_hpack_encode)
        ZEND_FE(hpack_decode, arginfo_hpack_decode)
        ZEND_FE_END
};
