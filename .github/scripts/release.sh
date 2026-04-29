#!/bin/bash

set -eu

output_name=artifacts/stalker-tools-linux-x86_64.tar.gz
platform=linux

run_linux() {
	mkdir package/
	cmake --install out DESTDIR=package/

	cd package || exit 1
	tar czf "../${output_name}" *
}

run_msys() {
	mkdir package/
	cd package || exit 1

	cp /usr/bin/msys-2.0.dll .
	cp ../out/src/dltx-reader .

	zip ../${output_name} *
}

if [ "${RUNNER_OS}" == "Windows" ]; then
	output_name=artifacts/stalker-tools-msys-win64.zip
	platform=msys
fi

mkdir -p "$(dirname "${output_name}")"

"run_${platform}"
