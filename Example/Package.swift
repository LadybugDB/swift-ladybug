// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "swift-ladybug-example",
    platforms: [
        .macOS(.v11),
        .iOS(.v14),
    ],
    dependencies: [
        .package(url: "https://github.com/LadybugDB/swift-ladybug/", branch: "main"),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "swift-ladybug-example",
            dependencies: [
                .product(name: "Ladybug", package: "swift-ladybug"),
            ]
        ),
    ]
)
