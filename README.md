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
   ```
   python -m venv .venv
   . .venv/Scripts/Activate # Windows
   source .venv/bin/activate # MacOSX
   pip install -r requirements.txt
   ```
1. Activate pre-commit hooks
    ```
    python -m pre_commit install
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

## Todo
1. Define a file parser interface
1. Define a concrete CSV file parser
1. Define unit tests for CSV file parser
1. Define an application name and version provider interface
1. Define a concrete application name and version provider, where the application name comes from key "Application name" and version comes from key "Version"
1. Define unit tests for the concrete application name and version provider
1. Define interface for layout patches
1. Define concrete example application layout patch
1. Define interface for rules patches
1. Define concrete example application rules patch
1. Test functionality in `datalinttool`
1. Create project pipelines with Github Actions
1. Migrate example project `datalinttool` to another repo
