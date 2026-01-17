#!/bin/bash
# set -e

# install dependencies
conan install . --profile=profiles/macosx

# build library
conan build .

# export package to local cache
conan export-pkg . \
    --name=datalintlib \
    --version=0.1.0 \
    --user=test \
    --channel=stable \
    --profile:host=profiles/macosx
