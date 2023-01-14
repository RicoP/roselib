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

        // Keep in mind that points are bound to the running dll.
        // The Typeinfo object should be desolved before the DLL is unloaded.

        // Name of the type. Should be unique. (In DLL memory!)
        char * name;

        // static function pointers to constructor and destructor. (In DLL memory!)
        void (*fp_default_construct)(void *) = nullptr;
        void (*fp_default_destruct)(void *) = nullptr;

        // static function pointers to serialization methods. (In DLL memory!)
        void (*fp_serialize)(void *, ISerializer &) = nullptr;
        void (*fp_deserialize)(void *, IDeserializer &) = nullptr;
    };
}
