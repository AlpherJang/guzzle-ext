//
// Created by 何延龙 on 2018/8/6.
//
#include "php.h"
#include "common.h"
#include "handler_stack.h"
#include "ext/standard/php_var.h"
#include <zend_interfaces.h>
#include <zend_closures.h>

zend_class_entry *guzzle_handler_stack_ce;

static zend_function_entry guzzle_handler_stack_method[] = {
        PHP_ME(HandlerStack, create, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(HandlerStack, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(HandlerStack, push, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

void guzzle_init_handler_stack() {
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, GUZZLE_NS, "HandlerStack", guzzle_handler_stack_method);

    guzzle_handler_stack_ce = zend_register_internal_class(&ce);

    zend_declare_property_null(guzzle_client_ce, ZEND_STRL("handler"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(guzzle_client_ce, ZEND_STRL("stack"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(guzzle_client_ce, ZEND_STRL("cached"), ZEND_ACC_PRIVATE);
}

//
static PHP_METHOD (HandlerStack, create) {
    zval
    self;
    object_init_ex(&self, guzzle_handler_stack_ce);

    zend_call_method(&self, guzzle_handler_stack_ce, NULL, ZEND_STRL("__construct"), NULL, 0, NULL, NULL);


    zval name;
    ZVAL_STRING(&name, "a");

    zval http_errors;
    zend_call_method(&self, guzzle_middleware_ce, NULL, ZEND_STRL("httperrors"), &http_errors, 0, NULL, NULL);

    zend_call_method(&self, guzzle_handler_stack_ce, NULL, ZEND_STRL("push"), NULL, 2, &http_errors, &name);
//
    // todo

    RETURN_ZVAL(&self, 1, 0);
}
//
PHP_METHOD (HandlerStack, __construct) {
    zval
    te;
    ZVAL_LONG(&te, 12121);
    zend_update_property(guzzle_handler_stack_ce, getThis(), ZEND_STRL("config"), &te);
}

PHP_METHOD (HandlerStack, push) {

    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    zend_string name;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "f|S", &fci, &fcc, &name) == FAILURE) {
        return;
    }

    zval par;
    ZVAL_LONG(&par, 666);
    fci.retval = &retval;
    fci.param_count = 1;
    fci.params = &par;
    zend_call_function(&fci, &fcc);
}