#include <iostream>
#include <sstream>
#include <map>
#include <fasttext/fasttext.h>

#include "croco.h"
#include "action.h"
#include "json.hpp"

using json = nlohmann::json;

namespace croco {

std::string _sentence(http::Request &req);
std::string _word(http::Request &req);

/**
 * アクションリスト
 * @var values_t
 */
actions_t vectorsActions = {
    {"sentence", _sentence},
    {"word", _word}
};

/**
 * 文章ベクトルの取得
 *
 * @package ftext-server
 * @param   http::Request *req
 * @return  std::string
 */
std::string _sentence(http::Request &req)
{
    if (req.requests.find("text") == req.requests.end()) {
        return "Please send the text.";
    }

    fasttext::FastText& ftext = Di<fasttext::FastText>::get();

    std::string text = req.requests.at("text");

    for (int _idx=0; _idx < text.length(); _idx++) {
        if (text[_idx] == '+') {
            text[_idx] = ' ';
        }
    }
    logger::debug(text);

    std::stringstream ioss(text);
    fasttext::Vector vec(ftext.getDimension());

    ftext.getSentenceVector(ioss, vec);

    std::stringstream os;
//    os << std::setprecision(5);
    os << "\"";

    int64_t idx, loop = vec.size() -1;
    for (idx = 0; idx < loop; idx++) {
        os << vec[idx] << " ";
    }
    os << vec[idx] << "\"";

    return os.str();
}

/**
 * 単語ベクトルの取得
 *
 * @package ftext-server
 * @param   http::Request *req
 * @return  std::string
 */
std::string _word(http::Request &req)
{
    if (req.requests.find("text") == req.requests.end()) {
        return "Please send the text.";
    }

    fasttext::FastText& ftext = Di<fasttext::FastText>::get();
    fasttext::Vector vec(ftext.getDimension());
    std::string text = req.requests.at("text");

    ftext.getWordVector(vec, text);

    std::stringstream os;
    os << std::setprecision(5);
    os << "\"";

    int64_t idx, loop = vec.size() -1;
    for (idx = 0; idx < loop; idx++) {
        os << vec[idx] << " ";
    }
    os << vec[idx] << "\"";

    return os.str();
}

} // namespace croco
