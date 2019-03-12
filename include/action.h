#ifndef __ACTION_H__
#define __ACTION_H__

#include <functional>
#include <unordered_map>

#include "uv/http.h"
#include "uv/route.h"

namespace croco {

typedef std::function<std::string(http::Request &req)> action_t;
typedef std::unordered_map<std::string, action_t> actions_t;

extern actions_t vectorsActions;
// extern actions_t predictActions;

} // namespace croco

#endif // #define __ACTION_H__
