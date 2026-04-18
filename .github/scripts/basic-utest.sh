#!/bin/bash

[ -v V ] && set -x

set -eu -o pipefail

wfile="$(mktemp --tmpdir dltx-reader-out-XXXXXX)"
trap 'rm "${wfile}"' EXIT

test_file() {
	ifile="${1}"

	valgrind --show-error-list=yes --error-exitcode=1 --leak-check=full out/dltx-reader "tests/data/${ifile}" >"${wfile}"

	read -r ihash _ < <(md5sum "tests/expected/${ifile}")
	read -r whash _ < <(md5sum "${wfile}")

	[ "${ihash}" == "${whash}" ] || {
		echo "Hash did not match, aborting"
		diff "tests/expected/${ifile}" "${wfile}"
		exit 1
	} >&2
}

if [ "${#}" -eq 1 ]; then
	test_file "${@}"
else
	for f in tests/expected/*.ltx; do
		echo "--- TESTING ${f} ---"
		test_file "$(basename "${f}")"
	done
fi
