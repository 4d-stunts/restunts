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

replace byte_3C09C detail_threshold_by_level
replace off_3C084 lookahead_tiles_tables
replace timertestflag2 detail_level
replace transformed_shape_op_helper2 projectiondata9_times_ratio
replace transformed_shape_op_helper3 is_facing_camera
replace transformed_shape_op_helper insert_newest_poly_in_poly_linked_list_40ED6
replace word_40ED6 poly_linked_list_40ED6
replace word_45D98 poly_linked_list_40ED6_tail
replace timertestflag slow_video_mgmt
replace do_mrl_textres show_graphic_levels_menu
