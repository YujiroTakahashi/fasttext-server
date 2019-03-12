#include "croco.h"

namespace croco {

const  int kMaxFinalizersSize = 256;
static int gNumFinalizersSize = 0;
static DiFinalizer::FinalizerFunc gFinalizers[kMaxFinalizersSize];

/**
 * インスタンス（開放用）の追加
 *
 * @access public
 * @return void
 */
void DiFinalizer::addFinalizer(FinalizerFunc func)
{
    assert(gNumFinalizersSize < kMaxFinalizersSize);
    gFinalizers[gNumFinalizersSize++] = func;
}

/**
 * 格納インスタンスの開放
 *
 * @access public
 * @return void
 */
void DiFinalizer::finalize()
{
    for (int i = gNumFinalizersSize - 1; i >= 0; --i) {
        (*gFinalizers[i])();
    }
    gNumFinalizersSize = 0;
}

} // namespace croco
