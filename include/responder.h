#ifndef __RESPONDER_H__
#define __RESPONDER_H__

#include "uv/http.h"
#include "uv/route.h"

namespace croco {

/**
 * レスポンダー
 *
 * @package     exchanger
 * @param   Request req
 * @param   Response res
 * @return void
 */
void responder(http::Request &req, http::Response &res);

} // namespace croco

#endif // #define __RESPONDER_H__
