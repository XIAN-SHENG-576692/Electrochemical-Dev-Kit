# Electrochemical-Dev-Kit

An efficient and modular toolkit designed for **electrochemical application development**.

This kit provides the core logic and utilities needed to streamline your electrochemical research or product engineering.

## File Structure

- `cicd/`: Some scripts for CI/CD.
- `demo/`: For CI/CD to build demo.
- `dev/`: Some scripts for developer.
- `src/`: The source codes.
- `tests/`: For CI/CD to build tests.

## Getting Started

### Integration

To use this toolkit in your own project, simply include the files located in the `src/` directory.

The `src.zip` are available for download in the latest release:

- 
    [![Download src.zip](https://img.shields.io/github/v/release/XIAN-SHENG-576692/Electrochemical-Dev-Kit?label=Download%20src.zip&style=flat)](https://github.com/XIAN-SHENG-576692/Electrochemical-Dev-Kit/releases/download/latest/src.zip)
- 
    ```bash
    curl -s https://api.github.com/repos/XIAN-SHENG-576692/Electrochemical-Dev-Kit/releases/latest \
    | grep "browser_download_url" \
    | cut -d : -f 2,3 \
    | tr -d \" \
    | grep "src.zip" \
    | wget -qi -

    unzip src.zip -d <UTILS_DIR>
    rm src.zip
    ```

### Trying the Demo

You don't need to build everything from scratch to see it in action. Our **CI/CD pipeline** automatically builds a functional demo for every release:
1. Navigate to the **Releases** section of this repository.
2. Download the latest `demo` artifact.
3. Run the executable to explore the toolkit's capabilities.

[![Download demo](https://img.shields.io/github/v/release/XIAN-SHENG-576692/Electrochemical-Dev-Kit?label=Download%20demo&style=flat)](
https://github.com/XIAN-SHENG-576692/Electrochemical-Dev-Kit/releases/download/latest/demo)

## Development and Testing

If you wish to contribute or modify the kit, you can leverage the automated tools provided:
- **Builds**: Use scripts in `cicd/` to set up your local environment.
- **Developing**: Use scripts in `dev/` for an improved development experience.
- **Testing**: Run scripts in `tests/` to validate any changes you make to the source code.
