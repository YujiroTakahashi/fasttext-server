#ifndef __CROCO_H__
#define __CROCO_H__

#include <cassert>
#include <map>
#include <mutex>
#include <string>

namespace croco {

namespace ini {
/**
 * キーバリュー配列
 * @typedef std::pair<std::string, std::string>
 */
typedef std::map<std::string, std::string> values_t;

/**
 * ファイル読み込み
 *
 * @access public
 * @param  string filename
 * @return bool
 */
bool load(const char* filename);

/**
 * データの取得
 *
 * @access public
 * @param  string filename
 * @return string
 */
const char* get(std::string key);

/**
 * データの取得
 *
 * @access public
 * @param  string filename
 * @return int
 */
const int value(std::string key);

/**
 * データのダンプ
 *
 * @access public
 * @param  string filename
 * @return void
 */
void dump();

} // namespace ini

namespace logger {
/**
 * 何もしない
 * @const integer
 */
const int SILENT = 0;

/**
 * ログの保存
 * @const integer
 */
const int LOGGING = 1;

/**
 * ログの出力
 * @const integer
 */
const int DISPLAY = 2;

/**
 * ログの出力と保存
 * @const integer
 */
const int LOGDISP = 3;

/**
 * 初期設定
 *
 * @access public
 * @param std::string logfile
 * @param std::string errfile
 * @param int flag
 * @return void
 */
void init(std::string _logfile, std::string _errfile, int _flag);

/**
 * メッセージ
 *
 * @access public
 * @return void
 */
void msg(std::string msg);

/**
 * インフォメーション
 *
 * @access public
 * @return void
 */
void info(std::string msg);

/**
 * デバッグメッセージ
 *
 * @access public
 * @return void
 */
void debug(std::string msg);

/**
 * エラー出力
 *
 * @access public
 * @return void
 */
void error(std::string msg);

/**
 * ログの保存
 *
 * @access public
 * @return void
 */
void log(std::string msg);
} // namespace logger


class DiFinalizer {
public:
    typedef void(*FinalizerFunc)();

    static void addFinalizer(FinalizerFunc func);
    static void finalize();
}; // class DiFinalizer

template <typename T>
class Di final {
public:
    static T& get()
    {
        std::call_once(initFlag, create);
        assert(instance);
        return *instance;
    }

private:
    static void create() {
        instance = new T;
        DiFinalizer::addFinalizer(&Di<T>::destroy);
    }

    static void destroy() {
        delete instance;
        instance = nullptr;
    }

    static std::once_flag initFlag;
    static T* instance;
}; // class Di final

template <typename T> std::once_flag Di<T>::initFlag;
template <typename T> T* Di<T>::instance = nullptr;

} // namespace croco::logger

#endif // #ifndef __CROCO_H__
