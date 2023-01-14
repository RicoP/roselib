#pragma once

#include <rose/hash.h>
#include <rose/serializer.h>

namespace rose::reflection {
    struct TypeInfo {
        // a unique id that should be unique for this type (for now simply 'hash(name)')
        rose::hash_value unique_id = 0;
        // a hash based on the members of that type. Changes when the members change.
        rose::hash_value member_hash = 0;
        // sizeof(T)
        std::size_t memory_footprint = 0;
        // memory alignment
        std::size_t memory_alignment = 16;

        void (*fp_default_construct)(void *) = nullptr;
        void (*fp_default_destruct)(void *) = nullptr;

        void (*fp_serialize)(void *, ISerializer &) = nullptr;
        void (*fp_deserialize)(void *, IDeserializer &) = nullptr;

        // Name of the type. Should be unique. (Not a char* because lifetime of string is bound to system.dll)
        char name[64];
    };
}
