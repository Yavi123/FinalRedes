#ifndef _ECS_DEFS_H_
#define _ECS_DEFS_H_

#include <cstdint>

using cmpId_type = uint8_t;

enum cmpId : cmpId_type{
    CMP_TRANSFORM,
    CMP_GRAVITY,
    CMP_RENDERCUBE,
    CMP_PLAYERCONTROLLER,

    CMP_COLLIDER,
    LAST_CMP
};

constexpr cmpId_type maxComponentId = cmpId::LAST_CMP;

#define __CMPID_DECL__(cId) constexpr static cmpId id = cId;

#endif
