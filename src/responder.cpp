#include <csignal>
#include <iostream>

#include "action.h"
#include "croco.h"
#include "json.hpp"

namespace croco {

using json = nlohmann::json;

void _renderJson(http::Request &req, http::Response &res, std::string &data);

/**
 * レスポンダーコールバック
 *
 * @package     exchanger
 * @param   Request req
 * @param   Response res
 * @return void
 */
void responder(http::Request &req, http::Response &res)
{
    route::Route router;
    auto match = router.set(req.url);
    std::map<std::string, int> error = {
        {"result", 0},
        {"error", 1}
    };
    std::string data = json(error).dump();

    if (match.test("/vectors/:action/:params")) {
        std::string action = match.get("action");
        if (vectorsActions.find(action) != vectorsActions.end()) {
            logger::debug(action);
            data = vectorsActions[action](req);
        }
        _renderJson(req, res, data);
    } else if (match.test("/predict/:action/:params")) {
        _renderJson(req, res, data);
    } else {
        std::string action = match.get("action");
        std::cout << action << std::endl;

        res.setStatus(200);
        res.setHeader("Content-Type", "text/html; charset=UTF-8");
        res.setHeader("Connection", "keep-alive");

        std::cout << "url:" << req.url << std::endl;

        for(auto &p : req.requests) {
            res << p.first << ":" << p.second << "<br>\n";
        }

        res << "default page!" << std::endl;
    }
}

void _renderJson(http::Request &req, http::Response &res, std::string &data)
{
    res.setStatus(200);
    res.setHeader("Content-Type", "application/json; charset=UTF-8");
    res.setHeader("Connection", "keep-alive");

    if (req.requests.find("callback") != req.requests.end()) {
        res << req.requests["callback"] << "(" << data << ")" << std::endl;
    } else {
        res << data << std::endl;
    }
}

} // namespace croco
