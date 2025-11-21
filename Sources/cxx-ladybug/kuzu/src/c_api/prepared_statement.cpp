#include "main/prepared_statement.h"

#include "c_api/helpers.h"
#include "c_api/ladybug.h"
#include "common/types/value/value.h"

using namespace ladybug::common;
using namespace ladybug::main;

void ladybug_prepared_statement_bind_cpp_value(ladybug_prepared_statement* prepared_statement,
    const char* param_name, std::unique_ptr<Value> value) {
    auto* bound_values = static_cast<std::unordered_map<std::string, std::unique_ptr<Value>>*>(
        prepared_statement->_bound_values);
    bound_values->erase(param_name);
    bound_values->insert({param_name, std::move(value)});
}

void ladybug_prepared_statement_destroy(ladybug_prepared_statement* prepared_statement) {
    if (prepared_statement == nullptr) {
        return;
    }
    if (prepared_statement->_prepared_statement != nullptr) {
        delete static_cast<PreparedStatement*>(prepared_statement->_prepared_statement);
    }
    if (prepared_statement->_bound_values != nullptr) {
        delete static_cast<std::unordered_map<std::string, std::unique_ptr<Value>>*>(
            prepared_statement->_bound_values);
    }
}

bool ladybug_prepared_statement_is_success(ladybug_prepared_statement* prepared_statement) {
    return static_cast<PreparedStatement*>(prepared_statement->_prepared_statement)->isSuccess();
}

char* ladybug_prepared_statement_get_error_message(ladybug_prepared_statement* prepared_statement) {
    auto error_message =
        static_cast<PreparedStatement*>(prepared_statement->_prepared_statement)->getErrorMessage();
    if (error_message.empty()) {
        return nullptr;
    }
    return convertToOwnedCString(error_message);
}

ladybug_state ladybug_prepared_statement_bind_bool(ladybug_prepared_statement* prepared_statement,
    const char* param_name, bool value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_int64(ladybug_prepared_statement* prepared_statement,
    const char* param_name, int64_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_int32(ladybug_prepared_statement* prepared_statement,
    const char* param_name, int32_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_int16(ladybug_prepared_statement* prepared_statement,
    const char* param_name, int16_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_int8(ladybug_prepared_statement* prepared_statement,
    const char* param_name, int8_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_uint64(ladybug_prepared_statement* prepared_statement,
    const char* param_name, uint64_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_uint32(ladybug_prepared_statement* prepared_statement,
    const char* param_name, uint32_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_uint16(ladybug_prepared_statement* prepared_statement,
    const char* param_name, uint16_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_uint8(ladybug_prepared_statement* prepared_statement,
    const char* param_name, uint8_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_double(ladybug_prepared_statement* prepared_statement,
    const char* param_name, double value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_float(ladybug_prepared_statement* prepared_statement,
    const char* param_name, float value) {
    try {
        auto value_ptr = std::make_unique<Value>(value);
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_date(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_date_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(date_t(value.days));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_timestamp_ns(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_timestamp_ns_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(timestamp_ns_t(value.value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_timestamp_ms(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_timestamp_ms_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(timestamp_ms_t(value.value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_timestamp_sec(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_timestamp_sec_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(timestamp_sec_t(value.value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_timestamp_tz(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_timestamp_tz_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(timestamp_tz_t(value.value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_timestamp(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_timestamp_t value) {
    try {
        auto value_ptr = std::make_unique<Value>(timestamp_t(value.value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_interval(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_interval_t value) {
    try {
        auto value_ptr =
            std::make_unique<Value>(interval_t(value.months, value.days, value.micros));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_string(ladybug_prepared_statement* prepared_statement,
    const char* param_name, const char* value) {
    try {
        auto value_ptr = std::make_unique<Value>(std::string(value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}

ladybug_state ladybug_prepared_statement_bind_value(ladybug_prepared_statement* prepared_statement,
    const char* param_name, ladybug_value* value) {
    try {
        auto value_ptr = std::make_unique<Value>(*static_cast<Value*>(value->_value));
        ladybug_prepared_statement_bind_cpp_value(prepared_statement, param_name,
            std::move(value_ptr));
        return LadybugSuccess;
    } catch (Exception& e) {
        return LadybugError;
    }
}
