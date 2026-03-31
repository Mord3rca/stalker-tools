#!/bin/bash

set -eu -o pipefail

test_file="${1}"
test_hash="${2}"

read hash _ < <(valgrind --show-error-list=yes --error-exitcode=1 --leak-check=full out/dltx-reader "tests/data/${test_file}" | md5sum -)

[ "${hash}" == "${test_hash}" ] || {
	echo "Hash did not match, aborting"
	exit 1
} >&2
