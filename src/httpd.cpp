#include <iostream>

#include "uv/http.h"
#include "uv/route.h"


/**
 * メイン関数
 *
 * @access public
 * @param int  argc
 * @param char **argv
 * @return int
 */
int main(int argc, char **argv)
{
    http::Server hs([](auto &req, auto &res) {
        route::Route router;
        auto match = router.set(req.url);

        if (match.test("/fasttext/:action")) {

            res.setStatus(200);
            res.setHeader("Content-Type", "text/plain");
            res.setHeader("Connection", "keep-alive");

            //res << "You ordered #" << match.get("id") << res.end();
            res << "You ordered #" << match.get("action") << std::endl;
        }
    });

    hs.listen("0.0.0.0", 9090);

    return 0;
}
