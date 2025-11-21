#include "connector/duckdb_secret_manager.h"

#include "s3fs_config.h"

namespace ladybug {
namespace duckdb_extension {

static std::string getDuckDBExtensionOptions(httpfs_extension::S3AuthParams ladybugOptions) {
    std::string options = "";
    options.append(common::stringFormat("KEY_ID '{}',", ladybugOptions.accessKeyID));
    options.append(common::stringFormat("SECRET '{}',", ladybugOptions.secretAccessKey));
    options.append(common::stringFormat("ENDPOINT '{}',", ladybugOptions.endpoint));
    options.append(common::stringFormat("URL_STYLE '{}',", ladybugOptions.urlStyle));
    options.append(common::stringFormat("REGION '{}',", ladybugOptions.region));
    return options;
}

std::string DuckDBSecretManager::getRemoteS3FSSecret(main::ClientContext* context,
    const httpfs_extension::S3FileSystemConfig& config) {
    KU_ASSERT(config.fsName == "S3" || config.fsName == "GCS");
    std::string templateQuery = R"(CREATE SECRET {}_secret (
        {}
        TYPE {}
    );)";
    return common::stringFormat(templateQuery, config.fsName,
        getDuckDBExtensionOptions(config.getAuthParams(context)), config.fsName);
}

} // namespace duckdb_extension
} // namespace ladybug
