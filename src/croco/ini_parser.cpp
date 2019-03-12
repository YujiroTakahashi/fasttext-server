#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <cstring>
#include <cstdlib>

#include "croco.h"

namespace croco { namespace ini {

/**
 * 格納
 * @var values_t
 */
static values_t values;

std::string _strReplace(std::string search, std::string replace, std::string subject);
void _parse(std::string subject);

/**
 * iniファイル読み込み
 *
 * @access public
 * @param  char* filename
 * @return bool
 */
bool load(const char* filename)
{
    std::ifstream ifs(filename);
    std::string line;

    while (std::getline(ifs, line)) {
        if (line[0] == '[' || line[0] == '#' || line[0] == ';' || line.empty()) {
            continue;
        }

        line = _strReplace("\t", "", line);
        line = _strReplace(" ", "", line);

        _parse(line);
    }

    return true;
}

/**
 * データの取得
 *
 * @access public
 * @param  string filename
 * @return string
 */
const char* get(std::string key)
{
    return values[key].c_str();
}

/**
 * 数値の取得
 *
 * @access public
 * @param  string filename
 * @return int
 */
const int value(std::string key)
{
    return atoi(values[key].c_str());
}

/**
 * データのダンプ
 *
 * @access public
 * @param  string filename
 * @return void
 */
void dump()
{
    ini::values_t::iterator rows;

    for (rows = ini::values.begin(); rows != ini::values.end(); rows++) {
        std::cout << (*rows).first << ":" << (*rows).second << std::endl;
    }
}

/**
 * 置換処理
 *
 * @access private
 * @param  string search
 * @param  string replace
 * @param  string subject
 * @return string
 */
std::string _strReplace(std::string search, std::string replace, std::string subject)
{
    std::string::size_type  pos(subject.find(search));

    while (pos != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos = subject.find(search, pos + replace.length());
    }

    return subject;
}

/**
 * キーと値の格納
 *
 * @access private
 * @param  string subject
 * @return void
 */
void _parse(std::string subject)
{
    std::string::size_type  pos(subject.find("="));

    if (pos != std::string::npos) {
        ini::values[subject.substr(0, pos)] = subject.substr(pos + 1);
    }
}


}} // namespace croco::ini
