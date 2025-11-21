# swift-ladybug-example

A simple CLI example using swift-ladybug.

## Build

```bash
swift build -c release
```

## Run

1. Copy the built executable to the data directory:
  ```bash
  cp ./.build/arm64-apple-macosx/release/swift-ladybug-example .
  ```

  If you are using an Intel Mac or Linux, replace `arm64-apple-macosx` with your specific architecture accordingly.

2. Run the executable:
  ```bash
  ./swift-ladybug-example
  ```
