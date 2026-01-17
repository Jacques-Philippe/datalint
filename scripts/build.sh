#!/bin/bash

conan install . --profile=profiles/macosx --build=missing
conan build .
