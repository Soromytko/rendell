#include <CallbackTable.h>

namespace rendell {
static CallbackTable<size_t, ResultCallback> s_resultCallbackTable;
} // namespace rendell

namespace rendell {
CallbackTable<size_t, ResultCallback> &getResultCallbackTable() {
    return s_resultCallbackTable;
}
} // namespace rendell