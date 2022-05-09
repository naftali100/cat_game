#include "Log.h"

#ifdef has_concepts
namespace plog {
template <PrintableShape S>
Record& operator<<(Record& record, const S& s) {
    record << s.getPosition().x << ", " << s.getPosition().y << " : " << s.getSize().x << ", " << s.getSize().y
           << " (low r corner " << sf::util::getGlobalBottomRight(s) << ")";
    return record;
}

template <PrintableVec V>
Record& operator<<(Record& record, const V& v) {
    record << v.x << ", " << v.y;
    return record;
}
}
#endif