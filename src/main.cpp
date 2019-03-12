#include <csignal>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>

#include <fasttext/fasttext.h>

#include "uv/http.h"
#include "uv/route.h"
#include "croco.h"
#include "responder.h"

using namespace croco;

/**
 * ヘルプメッセージ
 *
 * @package     exchanger
 * @param  int  argc
 * @param  char **argv
 * @return int
 */
static void syntax(void)
{
    std::cout
        << "Usage: exchanger [options]\n"
        << "    -c, --config PATH   Config file path\n"
        << "    -d, --daemon Daemonize the process\n"
        << "    -h, --help          This Help.\n"
        << std::endl;
    exit(1);
}

/**
 * デーモンプロセス
 *
 * @access public
 */
int daemonize() {
    /* 実行プロセスの開放. */
    switch (fork()) {
    case -1:
        /* Error */
        return -1;
    case 0:
        /* Continue if child */
        break;
    default:
        /* Exit if parent */
        exit(0);
    }

    /* 新規Session生成 PIDの取得. */
    pid_t newgrp = setsid();

    std::ofstream ofs(ini::get("pid"), std::ios::out | std::ios::trunc);
    ofs << newgrp;
    ofs.close();

    /* Session生成チェック */
    if (-1 == newgrp) {
        return -1;
    }
    return 1;
}

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
    try {
        std::locale::global(std::locale(""));
    } catch (...) {
        return 0;
    }

    /* 引数チェック */
    if (argc < 2) {
        syntax();
    }

    bool isdaemon = false;
    bool loaded = false;

    /* 設定ファイル名取得 */
    for (int pos=1; pos < argc; pos++) {
        if (!strcmp(argv[pos], "-c") || !strcmp(argv[pos], "--config")) {
            ini::load(argv[++pos]);
            loaded = true;
        } else if (!strcmp(argv[pos], "-d") || !strcmp(argv[pos], "--daemon")) {
            isdaemon = true;
        } else {
            syntax();
        }
    }

    /* 設定ファイルの読込チェック */
    if (!loaded) {
        syntax();
    }

    /* プロセスIDの保存 */
    if (isdaemon) {
        daemonize();
    }

    /* ログの設定 */
    logger::init(ini::get("log"), ini::get("error.log"), ini::value("log.type"));

    logger::debug("start http server.");

    fasttext::FastText& ftext = Di<fasttext::FastText>::get();
    ftext.loadModel(ini::get("ftext.wiki"));
    logger::debug("loaded dictionary.");

    try {
        http::Server hs(responder);
        int port = atoi(ini::get("port"));
        hs.listen(ini::get("listen"), port);
    } catch (const char* errmsg) {
        logger::error(errmsg);
    }

    DiFinalizer::finalize();
    std::remove(ini::get("pid"));

    return 0;
}
