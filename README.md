# DataLint

## Purpose

The purpose of this project is to allow for an open-source solution that allows for setting of expectations on given input files. For instance, suppose I have a CSV file with some fields, and I want to set some expectation on those fields "i.e. Field A should be an integer in range 1 to 5 inclusive."

The input of this tool is some file that can be parsed for values (for instance a CSV or a JSON file), and the output is a JSON report containing the list of all errors found in the file.

We define two main concepts.

1. Layout; the fields (keys) we expect to have present in the file, their occurrence, and their order
1. Rules; the acceptable values which should be associated to given keys

The user is responsible for consuming the `datalint` library to

- specify how to parse the input file
- specify how to extract the application name and version from the input file
- create a layout file (patch) that defines their expected layout
- create a rules file (patch) that defines their expected rules

## Developer Get Started
1. Clone the repo
1. Install the requirements for the python virtual environment
   ```bash
   python -m venv .venv
   . .venv/Scripts/Activate # Windows
   source .venv/bin/activate # MacOSX
   pip install -r requirements.txt
   ```
1. Activate pre-commit hooks
    ```bash
    python -m pre_commit install
    ```
1. Install conan
    ```bash
    brew install conan
    ```

## CSV Parser
A note on the CSV parser. Input files are parsed according to the rules of their format. Validation operates on parsed field values, not raw textual representation. So in other words, the following CSV row
```csv
key2 , value2 , Leading and trailing spaces (unquoted)
```
will be converted to
```csv
key2,value2,Leading and trailing spaces (unquoted)
```
when it's converted to RawData

## How to specify a LayoutSpecification
The LayoutSpecification should be made up of a series of patches that define all expected fields to be found. When we say "expected fields," we are speaking about occurrences of keys in our input file. In the case of a CSV file, these might be the keys of each line, or the left-most value of each line.

The patches allow us to define which keys should be present.

We can also specify expectations in terms of order. Because it's possible theoretically for an input file to contain more than a single key for any given field, we necessarily need to assume that when we query for a field from our layout specification, we always get back a list of values. Therefore, for any layout specification rules related to occurrence of a given key, we need to use the wording "for all occurrences of key X, it should be before any occurrence of key Y."

Please find an example usage of this in main.cpp

## Todo
1. ~~Define a file parser interface~~
1. ~~Define a concrete CSV file parser~~
1. ~~Define unit tests for CSV file parser~~
1. ~~Define an application name and version provider interface~~
1. ~~Define a concrete application name and version provider, where the application name comes from key "Application name" and version comes from key "Version"~~
1. ~~Define an example DefaultCsvApplicationDescriptorResolver with unit tests~~
1. Define interface for layout patches
    1. ~~Define version and version range types~~
    1. ~~Define layout patch~~
1. ~~Define concrete example application layout patch~~
1. ~~Move Add/Remove function definitions from LayoutSpecificationBuilder to LayoutSpecification~~
1. ~~Update unit tests so LayoutSpecification add/remove is properly tested~~
1. ~~remove friend qualification to LayoutSpecificationBuilder from LayoutSpecification~~
1. Define interface for rules patches
    1. ~~Define Field parser~~
    1. ~~Define value selector~~
    1. ~~Define value rule~~
    1. ~~Define rule patches~~
    1. ~~Define rule patch operations~~
    1. ~~Define rule specification~~
    1. ~~Define rule specification builder~~
1. Add conan to project, be able to output local conan package as a static library
1. Define concrete example application rules patch
1. Test functionality in `datalinttool`
1. ~~Create project pipelines with Github Actions~~
1. Migrate example project `datalinttool` to another repo
