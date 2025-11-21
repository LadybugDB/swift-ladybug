#include "main/query_result.h"

#include "c_api/helpers.h"
#include "c_api/ladybug.h"

using namespace ladybug::main;
using namespace ladybug::common;
using namespace ladybug::processor;

void ladybug_query_result_destroy(ladybug_query_result* query_result) {
    if (query_result == nullptr) {
        return;
    }
    if (query_result->_query_result != nullptr) {
        if (!query_result->_is_owned_by_cpp) {
            delete static_cast<QueryResult*>(query_result->_query_result);
        }
    }
}

bool ladybug_query_result_is_success(ladybug_query_result* query_result) {
    return static_cast<QueryResult*>(query_result->_query_result)->isSuccess();
}

char* ladybug_query_result_get_error_message(ladybug_query_result* query_result) {
    auto error_message = static_cast<QueryResult*>(query_result->_query_result)->getErrorMessage();
    if (error_message.empty()) {
        return nullptr;
    }
    return convertToOwnedCString(error_message);
}

uint64_t ladybug_query_result_get_num_columns(ladybug_query_result* query_result) {
    return static_cast<QueryResult*>(query_result->_query_result)->getNumColumns();
}

ladybug_state ladybug_query_result_get_column_name(ladybug_query_result* query_result, uint64_t index,
    char** out_column_name) {
    auto column_names = static_cast<QueryResult*>(query_result->_query_result)->getColumnNames();
    if (index >= column_names.size()) {
        return KuzuError;
    }
    *out_column_name = convertToOwnedCString(column_names[index]);
    return KuzuSuccess;
}

ladybug_state ladybug_query_result_get_column_data_type(ladybug_query_result* query_result, uint64_t index,
    ladybug_logical_type* out_column_data_type) {
    auto column_data_types =
        static_cast<QueryResult*>(query_result->_query_result)->getColumnDataTypes();
    if (index >= column_data_types.size()) {
        return KuzuError;
    }
    const auto& column_data_type = column_data_types[index];
    out_column_data_type->_data_type = new LogicalType(column_data_type.copy());
    return KuzuSuccess;
}

uint64_t ladybug_query_result_get_num_tuples(ladybug_query_result* query_result) {
    return static_cast<QueryResult*>(query_result->_query_result)->getNumTuples();
}

ladybug_state ladybug_query_result_get_query_summary(ladybug_query_result* query_result,
    ladybug_query_summary* out_query_summary) {
    if (out_query_summary == nullptr) {
        return KuzuError;
    }
    auto query_summary = static_cast<QueryResult*>(query_result->_query_result)->getQuerySummary();
    out_query_summary->_query_summary = query_summary;
    return KuzuSuccess;
}

bool ladybug_query_result_has_next(ladybug_query_result* query_result) {
    return static_cast<QueryResult*>(query_result->_query_result)->hasNext();
}

bool ladybug_query_result_has_next_query_result(ladybug_query_result* query_result) {
    return static_cast<QueryResult*>(query_result->_query_result)->hasNextQueryResult();
}

ladybug_state ladybug_query_result_get_next_query_result(ladybug_query_result* query_result,
    ladybug_query_result* out_query_result) {
    if (!ladybug_query_result_has_next_query_result(query_result)) {
        return KuzuError;
    }
    auto next_query_result =
        static_cast<QueryResult*>(query_result->_query_result)->getNextQueryResult();
    if (next_query_result == nullptr) {
        return KuzuError;
    }
    out_query_result->_query_result = next_query_result;
    out_query_result->_is_owned_by_cpp = true;
    return KuzuSuccess;
}

ladybug_state ladybug_query_result_get_next(ladybug_query_result* query_result,
    ladybug_flat_tuple* out_flat_tuple) {
    try {
        auto flat_tuple = static_cast<QueryResult*>(query_result->_query_result)->getNext();
        out_flat_tuple->_flat_tuple = flat_tuple.get();
        out_flat_tuple->_is_owned_by_cpp = true;
        return KuzuSuccess;
    } catch (Exception& e) {
        return KuzuError;
    }
}

char* ladybug_query_result_to_string(ladybug_query_result* query_result) {
    std::string result_string = static_cast<QueryResult*>(query_result->_query_result)->toString();
    return convertToOwnedCString(result_string);
}

void ladybug_query_result_reset_iterator(ladybug_query_result* query_result) {
    static_cast<QueryResult*>(query_result->_query_result)->resetIterator();
}

ladybug_state ladybug_query_result_get_arrow_schema(ladybug_query_result* query_result,
    ArrowSchema* out_schema) {
    try {
        *out_schema = *static_cast<QueryResult*>(query_result->_query_result)->getArrowSchema();
        return KuzuSuccess;
    } catch (Exception& e) {
        return KuzuError;
    }
}

ladybug_state ladybug_query_result_get_next_arrow_chunk(ladybug_query_result* query_result,
    int64_t chunk_size, ArrowArray* out_arrow_array) {
    try {
        *out_arrow_array =
            *static_cast<QueryResult*>(query_result->_query_result)->getNextArrowChunk(chunk_size);
        return KuzuSuccess;
    } catch (Exception& e) {
        return KuzuError;
    }
}
