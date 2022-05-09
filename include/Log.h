#pragma once
#ifndef LOG_H
#define LOG_H

// convenience file

// #define PLOG_OMIT_LOG_DEFINES
#include <plog/Log.h>
#include "SfmlUtil.h"

// HACK ... probably not thread safe (maybe replace with std::once)
#define PLOG_ONCE(severity) \
    static int once = 2;    \
    if (once > 0) once--;   \
    PLOG_IF(severity, once > 0)

#define LOGV_ONCE PLOG_ONCE(plog::verbose)
#define LOGD_ONCE PLOG_ONCE(plog::debug)
#define LOGI_ONCE PLOG_ONCE(plog::info)
#define LOGW_ONCE PLOG_ONCE(plog::warning)
#define LOGE_ONCE PLOG_ONCE(plog::error)
#define LOGF_ONCE PLOG_ONCE(plog::fatal)
#define LOGN_ONCE PLOG_ONCE(plog::none)

#ifdef has_concepts
template <typename T>
concept PrintableVec = requires(T t) {
    t.x;
    t.y;
};

template <typename T>
concept PrintableShape = requires(T t) {
    t.getPosition();
    t.getSize();
    sf::util::getGlobalTopLeft(t);
};

namespace plog {
    template <PrintableVec V>
    Record& operator<<(Record& record, const V& v);

    template <PrintableShape S>
    Record& operator<<(Record& record, const S& v);
}  // namespace plog
#else
    
#endif

#endif