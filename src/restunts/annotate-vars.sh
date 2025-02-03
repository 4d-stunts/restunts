#! /bin/bash

# Annotate variables via mass search-and-replace
# This puts the .asm files out of sync with the IDA database; however, by
# keeping track of the renames one can update the db in future

replace () {
	for ext in c h asm inc ; do
		d="$( printf '\001' )"

		grep -rl \
				--include "*.$ext" \
				--exclude-dir "build" \
				--exclude-dir ".*" \
				-P "$1" | xargs perl -i -pe "s${d}$1${d}$2${d}g"
	done
}

