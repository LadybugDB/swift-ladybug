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

### Source build

When building from a source checkout, initialize only the top-level Ladybug C++
submodule and generate the `cxx-ladybug` SwiftPM target before running
`swift build`:

```bash
git clone https://github.com/LadybugDB/swift-ladybug.git
cd swift-ladybug
git submodule update --init Sources/LadybugCpp dataset
git -C Sources/LadybugCpp submodule update --init dataset
python3 scripts/collect-ladybug-src/collect-ladybug-src.py
swift build
```

If you already cloned the repository without submodules, run this first:

```bash
git submodule update --init Sources/LadybugCpp dataset
git -C Sources/LadybugCpp submodule update --init dataset
```

After the generated target exists, subsequent builds can be run with:

```bash
swift build
```

### Prebuilt library build

To skip compiling the Ladybug C++ sources, download a prebuilt `liblbug` archive
and enable prebuilt mode:

```bash
bash scripts/download-liblbug.sh
LBUG_USE_PREBUILT=1 swift build
```

By default the script downloads the latest shared library release from
`LadybugDB/ladybug` into `lib/`. You can set `LBUG_VERSION`, `LBUG_LIB_KIND`,
`LBUG_PRECOMPILED_RUN_ID`, `LBUG_GITHUB_REPOSITORY`, or `LBUG_TARGET_DIR` to
select a specific release, static/shared archive, workflow artifact, repository,
or install directory.

## Tests

To run the tests, you can use the following command:

```bash
swift test
```

## Contributing
We welcome contributions to swift-ladybug. By contributing to swift-ladybug, you agree that your contributions will be licensed under the [MIT License](LICENSE). Please read the [contributing guide](CONTRIBUTING.md) for more information.
