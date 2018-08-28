//
// Created by tangzy on 18年7月23日.
//

#include "curl/curl.h"
#include "curl/easy.h"


/**
 *
 * 使用curl需要添加curl的静态库curl，使用方式编译时添加-lcurl
 */

#ifndef MOLTEN_MOLTEN_HTTP_UTIL_H
#define MOLTEN_MOLTEN_HTTP_UTIL_H

CURLcode post_request(char *uri, char *post_data, char *response);
CURLcode get_request(char *uri, char *resposne);

#endif