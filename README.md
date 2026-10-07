# swift-ladybug

Official Swift language binding for [Ladybug](https://github.com/LadybugDB/ladybug). Ladybug an embeddable property graph database management system built for query speed and scalability. For more information, please visit the [Ladybug GitHub repository](https://github.com/LadybugDB/ladybug) or the [Ladybug website](https://ladybugdb.com).

## Get started

To add swift-ladybug to your Swift project, you can use the Swift Package Manager:

1. Add `.package(url: "https://github.com/LadybugDB/swift-ladybug/", branch: "main"),` to your Package.swift dependencies.
   You can change the branch to a tag to use a specific version, e.g., `.package(url: "https://github.com/LadybugDB/swift-ladybug/", branch: "0.16.1"),` to use version 0.16.1.
2. Add `Ladybug` to your target dependencies.
   ```swift
    dependencies: [
        .product(name: "Ladybug", package: "swift-ladybug"),
    ]
    ```

Alternatively, you can add the package through Xcode:
1. Open your Xcode project.
2. Go to `File` > `Add Packages Dependencies...`.
3. Enter the URL of the swift-ladybug repository: `https://github.com/LadybugDB/swift-ladybug`.
4. Select the version you want to use (e.g., `main` branch or a specific tag).

## Docs

The API documentation for swift-ladybug is [available here](https://docs.ladybugdb.com/client-apis/swift/).

## Examples

A simple CLI example is provided in the [Example](Example) directory.

A demo iOS application is [provided here](https://github.com/LadybugDB/swift-ladybug-demo).

## System requirements

swift-ladybug requires Swift 5.9 or later. It supports the following platforms:
- macOS v14 or later
- iOS v17 or later
- Linux platforms (see the [official documentation](https://www.swift.org/platform-support/) for the supported distros)

Windows platform is not supported and there is no future plan to support it. 

The CI pipeline tests the package on macOS v15, Ubuntu 24.04, and iOS 18.6 Simulator.

## Build

### Prebuilt library build (default)

By default swift-ladybug links against a prebuilt `liblbug` shared library, so
neither fresh clones nor downstream packages need to compile the Ladybug C++
sources. Download the library for your platform, then build normally:

```bash
bash scripts/download-liblbug.sh
swift build
```

By default the script downloads the shared library release matching
`LBUG_VERSION` (default `0.21.2`) from `LadybugDB/ladybug` into `lib/`, which
the package links automatically. You can set `LBUG_VERSION`, `LBUG_LIB_KIND`,
`LBUG_LINUX_VARIANT`, `LBUG_PRECOMPILED_RUN_ID`, `LBUG_GITHUB_REPOSITORY`, or
`LBUG_TARGET_DIR` to select a specific release, static/shared archive, Linux
variant, workflow artifact, repository, or install directory (`LBUG_TARGET_DIR`
overrides the default `<package>/lib` lookup).

If you consume swift-ladybug as a package dependency, run the download script
from inside the resolved checkout (e.g.
`.build/checkouts/swift-ladybug/scripts/download-liblbug.sh`, or under Xcode
the `SourcePackages/checkouts` directory in DerivedData) so the library lands
in that checkout's `lib/` directory, then build your project with no extra
configuration.

### Source build (opt-in)

To compile the Ladybug C++ sources from scratch instead of using the prebuilt
library, initialize the submodules, generate the `cxx-ladybug` SwiftPM target,
and opt out of prebuilt mode:

```bash
git clone https://github.com/LadybugDB/swift-ladybug.git
cd swift-ladybug
git submodule update --init Sources/LadybugCpp dataset
git -C Sources/LadybugCpp submodule update --init dataset
python3 scripts/collect-ladybug-src/collect-ladybug-src.py
LBUG_USE_PREBUILT=0 swift build
```

Set `LBUG_USE_PREBUILT=0` whenever building or testing from source (including
`swift test`). Source builds require the submodules and only work from a full
clone, not from a package checkout. iOS device/simulator builds currently use
this path; a prebuilt XCFramework for iOS is planned (see issue #12).

## Tests

To run the tests, you can use the following command:

```bash
swift test
```

## Contributing
We welcome contributions to swift-ladybug. By contributing to swift-ladybug, you agree that your contributions will be licensed under the [MIT License](LICENSE). Please read the [contributing guide](CONTRIBUTING.md) for more information.
