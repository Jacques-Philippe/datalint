# DataLint

## Purpose

The purpose of this project is to allow for an open-source solution that allows for setting of expectations on given input files. For instance, suppose I have a CSV file with some fields, and I want to set some expectation on those fields "i.e. Field A should be an integer in range 1 to 5 inclusive."

The input of this tool is some file that can be parsed for values (for instance a CSV or a JSON file), and the output is a JSON report containing the list of all errors found in the file.

We define three concepts.

1. Layout; the fields (keys) we expect to have present in the file, their occurrence, and their order
1. Rules; the acceptable values which should be associated to given keys

The user is responsible for consuming the `datalint` library to

- specify how to parse the input file
- specify how to extract the application name and version from the input file
- create a layout file (patch) that defines their expected layout
- create a rules file (patch) that defines their expected rules
