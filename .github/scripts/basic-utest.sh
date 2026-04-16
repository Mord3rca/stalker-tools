#!/bin/bash

[ -v V ] && set -x

set -eu -o pipefail

ifile="${1}"
wfile="$(mktemp --tmpdir dltx-reader-out-XXXXXX)"
trap 'rm "${wfile}"' EXIT

valgrind --show-error-list=yes --error-exitcode=1 --leak-check=full out/dltx-reader "tests/data/${ifile}" >"${wfile}"

read -r ihash _ < <(md5sum "tests/expected/${ifile}")
read -r whash _ < <(md5sum "${wfile}")

[ "${ihash}" == "${whash}" ] || {
	echo "Hash did not match, aborting"
	diff "tests/expected/${ifile}" "${wfile}"
	exit 1
} >&2
