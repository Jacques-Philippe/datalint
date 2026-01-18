#!/bin/bash
set -e

conan install . --profile=profiles/macosx --build=missing
conan build .
