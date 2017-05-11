/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.1 at Wed Mar 15 21:32:42 2017. */

#include "simple_matrix.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t SimpleMatrix_fields[8] = {
    PB_FIELD(  1, STRING  , OPTIONAL, CALLBACK, FIRST, SimpleMatrix, id, id, 0),
    PB_FIELD(  2, SINT32  , OPTIONAL, STATIC  , OTHER, SimpleMatrix, num_cols, id, 0),
    PB_FIELD(  3, ENUM    , OPTIONAL, STATIC  , OTHER, SimpleMatrix, data_type, num_cols, 0),
    PB_FIELD(  4, BYTES   , REPEATED, CALLBACK, OTHER, SimpleMatrix, payload, data_type, 0),
    PB_FIELD(  5, STRING  , OPTIONAL, CALLBACK, OTHER, SimpleMatrix, device_id, payload, 0),
    PB_FIELD(  6, INT64   , OPTIONAL, STATIC  , OTHER, SimpleMatrix, timestamp_utc_millis, device_id, 0),
    PB_FIELD(  7, INT32   , OPTIONAL, STATIC  , OTHER, SimpleMatrix, tz_offset_millis, timestamp_utc_millis, 0),
    PB_LAST_FIELD
};


