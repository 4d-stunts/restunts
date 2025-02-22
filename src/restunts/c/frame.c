#include "externs.h"
#include "math.h"
#include "shape3d.h"

extern struct RECTANGLE* rectptr_unk2;
extern struct RECTANGLE rect_array_unk[];
extern struct RECTANGLE rect_array_unk2[];
extern struct RECTANGLE rect_unk[];
extern struct RECTANGLE rect_unk2;
extern struct RECTANGLE rect_unk6;
extern struct RECTANGLE rect_unk9;
extern struct RECTANGLE rect_unk11;
extern struct RECTANGLE rect_unk12;
extern struct RECTANGLE rect_unk15;
extern struct RECTANGLE cliprect_unk;
extern struct VECTOR vec_unk2;
extern struct VECTOR vec_planerotopresult;
extern struct MATRIX mat_temp;
extern int word_3B8EC;
extern int word_3B8F0;
extern int word_3B8EE;
extern int word_44D20;
extern char detail_threshold_by_level[];
extern char byte_3C0C6[];
extern char word_46468;
extern int word_3BE34[];
extern char* lookahead_tiles_tables[];
extern struct SHAPE3D* off_3BE44[];
extern int terrainHeight;
extern int planindex;
extern int planindex_copy;
extern char byte_4392C;
extern struct TRANSFORMEDSHAPE3D currenttransshape[29];
//extern struct TRANSFORMEDSHAPE3D transshapeunk;
extern struct TRANSFORMEDSHAPE3D* curtransshape_ptr;
extern struct TRACKOBJECT trkObjectList[215]; // 215 entries
extern unsigned char fence_TrkObjCodes[];
extern int pState_minusRotate_z_2, pState_minusRotate_x_2, pState_minusRotate_y_2, pState_f36Mminf40sar2;

extern char unk_3C0EE[];
extern char unk_3C0F0[];
extern char unk_3C0F8[];
extern char unk_3C0F4[];
extern int word_3C0D6[];
extern int unk_3C0A2[];
extern int unk_3C0A6[];
extern int unk_3C0AE[];
extern int unk_3C0B6[];
extern struct TRACKOBJECT sceneshapes2[];
extern struct TRACKOBJECT sceneshapes3[];
extern struct SHAPE3D game3dshapes[130];
extern struct VECTOR carshapevec;
extern struct VECTOR carshapevecs[6];
extern short word_443E8[];
extern struct VECTOR oppcarshapevec;
extern struct VECTOR oppcarshapevecs[6];
extern short word_4448A[];
extern char backlights_paint_override;
extern int word_449FC[];
extern int word_463D6;
extern int transformedshape_zarray[];
extern int transformedshape_indices[];
extern char transformedshape_arg2array[];
extern int sdgame2_widths[];
extern void far* sdgame2shapes[];
extern void far* fontledresptr;
extern int dialog_fnt_colour;
extern char transformedshape_counter;

void build_track_object(struct VECTOR* a, struct VECTOR* b);
void transformed_shape_add_for_sort(int a, int b);
unsigned char subst_hillroad_track(unsigned char a, unsigned char b);
int skybox_op(int a, struct RECTANGLE* rectptr, int c, struct MATRIX* matptr, int e, int f, int g);
struct RECTANGLE* draw_ingame_text(void);
struct RECTANGLE* init_crak(int frame, int top, int height);
struct RECTANGLE* do_sinking(int frame, int top, int height);
struct RECTANGLE* intro_draw_text(char* str, int a, int b, int c, int d);
void font_set_fontdef2(void far* data);
void format_frame_as_string(char* s, int time, int c);
void shape_op_explosion(int a, void far* shp, int x, int y);
void heapsort_by_order(int n, int* heap, int* data);

void update_frame(char arg_0, struct RECTANGLE* arg_cliprectptr) {
	int si;
	char var_122;
	char var_E4;
	char var_DC[2];
	struct RECTANGLE* var_rectptr;
	struct MATRIX var_mat, var_mat2;
	struct MATRIX* car_rot_matrix;
	struct VECTOR cam_pos, car_pos, offset_vector, var_vec7, var_vec8;
	int car_rot_y, car_rot_x, car_rot_z;
	int car_rot_y_2, car_rot_x_2, car_rot_z_2;
	int var_38, car_rot_z_3;
	int var_transformresult;
	int heading;
	char* lookahead_tiles;
	int skybox_parameter;
	int var_counter, var_counter2;
	char cam_tile_south, cam_tile_east;
	char tile_south, tile_east;
	char tile_to_draw_south_offset, tile_to_draw_east_offset;
	char car_tile_east, car_tile_south;
	unsigned char tiles_to_draw_terr_type_vec[24];
	char should_skip_tile[24];
	char tile_detail_level[24];
	char tiles_to_draw_south[24];
	char tiles_to_draw_east[24];
	unsigned char tiles_to_draw_elem_type_vec[24];
	char detail_threshold;
	char var_3C;
	char var_60;
	char var_6E;
	char var_4A;
	char var_4E;
	int var_6C;
	int var_A4;
	int var_hillheight;
	int idx;
	struct TRACKOBJECT* var_trkobjectptr;
	struct TRACKOBJECT* var_trkobject_ptr; // NOTE: beware of similar names!!
	char tile_det_level;
	char* var_10E;
	int di;
	int var_132;
	int var_5E;
	int var_3A;
	int* var_DA;
	int var_12A;
	unsigned char var_4C;
	struct RECTANGLE var_rect, var_rect2;
	struct VECTOR far* var_108;
	struct CARSTATE* var_stateptr;
	unsigned char elem_map_value;
	unsigned char terr_map_value;

	var_DC[0] = 0;
	var_DC[1] = 0;
	if (video_flag5_is0 == 0 || arg_0 == 0) {
		rectptr_unk = rect_array_unk;
		rectptr_unk2 = rect_array_unk2;
	} else {
		rectptr_unk2 = rect_array_unk;
		rectptr_unk = rect_array_unk2;
	}

	if (slow_video_mgmt_copy != 0) {
		var_122 = 8;
		var_rectptr = rect_unk;
		for (si = 0; si < 15; si++) {
			*var_rectptr = cliprect_unk;
			var_rectptr++;
		}
	} else {
		var_122 = 0;
	}

	// Set car position (own or opponent's)
	if (followOpponentFlag == 0) {		
		car_pos.x = state.playerstate.car_posWorld1.lx >> 6;
		car_pos.y = state.playerstate.car_posWorld1.ly >> 6;
		car_pos.z = state.playerstate.car_posWorld1.lz >> 6;
		car_rot_y = state.playerstate.car_rotate.y;
		car_rot_z = state.playerstate.car_rotate.z;
		car_rot_x = state.playerstate.car_rotate.x;
	} else {
		car_pos.x = state.opponentstate.car_posWorld1.lx >> 6;
		car_pos.y = state.opponentstate.car_posWorld1.ly >> 6;
		car_pos.z = state.opponentstate.car_posWorld1.lz >> 6;
		car_rot_y = state.opponentstate.car_rotate.y;
		car_rot_z = state.opponentstate.car_rotate.z;
		car_rot_x = state.opponentstate.car_rotate.x;
	}

	car_rot_x_2 = -1;
	car_rot_z_2 = 0;
	
	// Set camera position, based on the car position and the camera mode
	if (cameramode == 0) {
		car_rot_x_2 = car_rot_x & 0x3ff;
		car_rot_y_2 = car_rot_y & 0x3ff;
		car_rot_z_2   = car_rot_z & 0x3ff;
		car_rot_matrix = mat_rot_zxy(-car_rot_z, -car_rot_y, -car_rot_x, 0);
		offset_vector.x = 0;
		offset_vector.z = 0;
		offset_vector.y = simd_player.car_height - 6;

		mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec7);
		cam_pos.x = car_pos.x + var_vec7.x;
		cam_pos.y = car_pos.y + var_vec7.y;
		cam_pos.z = car_pos.z + var_vec7.z;
	} else if (cameramode == 1) {
		cam_pos.x = state.game_vec1[followOpponentFlag].x;
		cam_pos.z = state.game_vec1[followOpponentFlag].z;
		cam_pos.y = state.game_vec1[followOpponentFlag].y;
	} else if (cameramode == 2) {
		offset_vector.x = 0;
		offset_vector.y = 0;
		offset_vector.z = 0x4000;
		car_rot_matrix = mat_rot_zxy(-car_rot_z, -car_rot_y, -car_rot_x, 0);
		mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec7);

		offset_vector.x = 0;
		offset_vector.y = 0;
		offset_vector.z = word_3B8EC;
		car_rot_matrix = mat_rot_zxy(0, -word_3B8F0, polarAngle(var_vec7.x, var_vec7.z) - word_3B8EE, 0);

		mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec7);
		cam_pos.x = car_pos.x + var_vec7.x;
		cam_pos.y = car_pos.y + var_vec7.y;
		cam_pos.z = car_pos.z + var_vec7.z;
	} else if (cameramode == 3) {
		cam_pos.x = trackdata9[state.field_3F7[followOpponentFlag] * 3 + 0];
		cam_pos.y = trackdata9[state.field_3F7[followOpponentFlag] * 3 + 1] + word_44D20 + 0x5A;
		cam_pos.z = trackdata9[state.field_3F7[followOpponentFlag] * 3 + 2];
	}

	// Unknown part; seems to be performing some initialization
	if (car_rot_x_2 == -1) {
		build_track_object(&cam_pos, &cam_pos);
		if (cam_pos.y < terrainHeight) {
			cam_pos.y = terrainHeight;
		}

		if (byte_4392C != 0) {		
			si = plane_origin_op(planindex, cam_pos.x, cam_pos.y, cam_pos.z);
			if (si < 0xC) {			
				vec_unk2.x = 0;
				vec_unk2.y = 0xC - si;
				vec_unk2.z = 0;
				planindex_copy = planindex;
				pState_f36Mminf40sar2 = 0;
				pState_minusRotate_x_2 = 0;
				pState_minusRotate_z_2 = 0;
				pState_minusRotate_y_2 = 0;
				plane_rotate_op();
				cam_pos.x += vec_planerotopresult.x;
				cam_pos.y += vec_planerotopresult.y;
				cam_pos.z += vec_planerotopresult.z;
			}
		}

		car_rot_x_2 = (-polarAngle(car_pos.x - cam_pos.x, car_pos.z - cam_pos.z)) & 0x3FF;
		var_38 = polarRadius2D(car_pos.x - cam_pos.x, car_pos.z - cam_pos.z);
		car_rot_y_2 = polarAngle(car_pos.y - cam_pos.y + 0x32, var_38) & 0x3FF;
	}

	if (car_rot_z_2 > 1 && car_rot_z_2 < 0x3FF) {
		car_rot_z_3 = car_rot_z_2;
	} else {
		car_rot_z_3 = 0;
	}

	if (state.game_frame == 0) {
		var_E4 = byte_3C0C6[word_46468&0xF];
	} else {
		var_E4 = byte_3C0C6[state.game_frame&0xF];
	}

	// Select the vector specifying the 23 tiles to draw. The vector contains
	// 24 elements, each 3 bytes long, in format (east_offset, south_offset,
	// detail threshold). A tile is drawn only if its detail threshold is lower
	// enough (0 = draw always, 1 = only if graphic detail is MEDIUM or FULL,
	// 2 = only if graphic detail is FULL).
	// There are 8 possible vectors, but they are all rotations/reflecions of a
	// basic schema. Which is chosen depends on the heading of the car. For a
	// car heading north ($), the schema is the following:
	//
	// OOOOO
	// OOOOO
	// OOOOO
	// OOOOO
	//  O$O
	//
	// Also, note that the tiles appear in the vector in drawing order
	// (farthest tiles first). If a car is heading north but slightly west, the
	// algo will draw the NW tile before the NE, and vice-versa

	heading = select_cliprect_rotate(car_rot_z_3, car_rot_y_2, car_rot_x_2, arg_cliprectptr, 0);
	lookahead_tiles = lookahead_tiles_tables[(heading & 0x3FF) >> 7];

	var_mat = *mat_rot_zxy(car_rot_z_3, car_rot_y_2, 0, 1);
	offset_vector.x = 0;
	offset_vector.y = 0;
	offset_vector.z = 0x3E8;
	mat_mul_vector(&offset_vector, &var_mat, &var_vec8);
	if (var_vec8.z > 0) {
		skybox_parameter = 1;
	} else {
		skybox_parameter = -1;
	}

	// Draw 8 shapes (still TBD what they are), but only if the detail
	// level is the max one
	if (detail_level == 0) {
		currenttransshape->rectptr = &rect_unk9;
		currenttransshape->ts_flags = var_122 | 7;
		currenttransshape->rotvec.x = 0;
		currenttransshape->rotvec.y = 0;
		currenttransshape->unk = 0x400;
		currenttransshape->material = 0;

		for (var_counter = 0; var_counter < 8; var_counter++) {
			si = (word_3BE34[var_counter] + car_rot_x_2 + run_game_random) & 0x3ff;
			if (si < 0x87 || si > 0x379) {
				mat_rot_y(&var_mat2, si);
				offset_vector.x = 0;
				offset_vector.y = 0xAE6 - cam_pos.y;
				offset_vector.z = 0x3A98; //15000
				mat_mul_vector(&offset_vector, &var_mat2, &var_vec7);
				var_vec7.z = 0x3A98; //15000
				mat_mul_vector(&var_vec7, &var_mat, &currenttransshape->pos);
				if (currenttransshape->pos.z > 0xC8) {
					currenttransshape->shapeptr = off_3BE44[var_counter];
					currenttransshape->rotvec.z = -car_rot_x_2;
					var_transformresult = transformed_shape_op(&currenttransshape[0]);
					(void) var_transformresult; // we cannot be out of memory as we are just starting to process
				}
			}
		}
	}

/*
; -----------------------------------------------------------------------------------------------
*/

	cam_tile_east = cam_pos.x >> 0xA;
	cam_tile_south = -((cam_pos.z >> 0xA) - 0x1D);
	if (detail_level != 0) {
		car_tile_east = state.playerstate.car_posWorld1.lx >> 16;
		car_tile_south = 0x1D - (state.playerstate.car_posWorld1.lz >> 16);
	}

	for (si = 0; si < 0x17; si++) {
		should_skip_tile[si] = 0;
	}

	// Select the detail level (FULL if 1st or 2nd option in the graphics menu
	// were chosen, MEDIUM if the 3rd, FASTEST if 4th or 5th)
	detail_threshold = detail_threshold_by_level[detail_level];
	
	// Cycle on the 23 tiles to draw, determine if they really need to be drawn
	for (si = 0x16; si >= 0; si--) {

		// Skip if a previous iteration determined this tile is not needed
		// (happens for multi-tile elements)
		if (should_skip_tile[si] != 0)
			continue;

		// Skip if detail threshold not met (e.g. far tiles in FASTEST detail)
		if (lookahead_tiles[si * 3 + 2] <= detail_threshold) {
			tile_east = lookahead_tiles[si * 3] + cam_tile_east;
			tile_south = lookahead_tiles[si * 3 + 1] + cam_tile_south;

			// Skip if tile is out of bounds
			if (tile_east >= 0 && tile_east <= 0x1D && tile_south >= 0 && tile_south <= 0x1D) {
				elem_map_value = td14_elem_map_main[tile_east + trackrows[tile_south]];
				terr_map_value = td15_terr_map_main[tile_east + terrainrows[tile_south]];
				
				if (elem_map_value != 0) {

					if (terr_map_value >= 7 && terr_map_value < 0xB) {
						elem_map_value = subst_hillroad_track(terr_map_value, elem_map_value);
						terr_map_value = 0;
					}

					// Found a filler tile (non-main tile of a multitile component)
					// Process the main tile of the component instead (the NW one)
					if (elem_map_value == 0xFD) {
						tile_east--;
						tile_south--;
						elem_map_value = td14_elem_map_main[tile_east + trackrows[tile_south]];
						terr_map_value = td15_terr_map_main[tile_east + terrainrows[tile_south]];
					} else if (elem_map_value == 0xFE) {
						tile_south--;
						elem_map_value = td14_elem_map_main[tile_east + trackrows[tile_south]];
						terr_map_value = td15_terr_map_main[tile_east + terrainrows[tile_south]];
					} else if (elem_map_value == 0xFF) {
						tile_east--;
						elem_map_value = td14_elem_map_main[tile_east + trackrows[tile_south]];
						terr_map_value = td15_terr_map_main[tile_east + terrainrows[tile_south]];
					}
				}

				tiles_to_draw_terr_type_vec[si] = terr_map_value;
				tile_detail_level[si] = lookahead_tiles[si * 3 + 2];

				if (elem_map_value != 0 && detail_level != 0 &&
					trkObjectList[elem_map_value].ss_physicalModel >= 0x40 &&
					(tile_east != car_tile_east || tile_south != car_tile_south))
				{
					elem_map_value = 0;
				}

				tiles_to_draw_east[si] = tile_east;
				tiles_to_draw_south[si] = tile_south;
				tiles_to_draw_elem_type_vec[si] = elem_map_value;

				if (elem_map_value != 0) {
					idx = trkObjectList[elem_map_value].ss_multiTileFlag;
					if (idx != 0) {
						// Look the future tiles to process (i.e. with lower index, since si
						// counts backwards) and remove those which belong to the same
						// multi-tile component as this tile

						// Recalculate the offset (needed in case we hit a filler tile)
						tile_to_draw_east_offset = tile_east - cam_tile_east;
						tile_to_draw_south_offset = tile_south - cam_tile_south;
						if (idx == 1) {
							for (di = 0; di < si; di++) {
								if (lookahead_tiles[di * 3] == tile_to_draw_east_offset && (lookahead_tiles[di * 3 + 1] == tile_to_draw_south_offset || lookahead_tiles[di * 3 + 1] == tile_to_draw_south_offset + 1)) {
									should_skip_tile[di] = 1;
								}
							}
						} else if (idx == 2) {
							for (di = 0; di < si; di++) {
								if (lookahead_tiles[si * 3 + 1] == tile_to_draw_south_offset && (lookahead_tiles[si * 3] == tile_to_draw_east_offset || lookahead_tiles[si * 3] != tile_to_draw_east_offset + 1)) {
									should_skip_tile[di] = 1;
								}
							}
						} else if (idx == 3) {
							for (di = 0; di < si; di++) {
								if ((lookahead_tiles[di * 3] == tile_to_draw_east_offset || lookahead_tiles[di * 3] == tile_to_draw_east_offset + 1) &&
									(lookahead_tiles[di * 3 + 1] == tile_to_draw_south_offset || lookahead_tiles[di * 3 + 1] == tile_to_draw_south_offset + 1))
								{
									should_skip_tile[di] = 1;
								}
							}
						}
					}
				}
				
			} else {
				should_skip_tile[si] = 2;
			}
		} else {
			should_skip_tile[si] = 2;
		}
	}
	
//; -----------------------------------------------------------------------------
	
	// Draw own wheels
	var_3C = -1;
	var_6C = 0;
	if (cameramode != 0 || followOpponentFlag != 0) {

		if (state.playerstate.car_crashBmpFlag != 2) {

			car_rot_matrix = mat_rot_zxy(-state.playerstate.car_rotate.z, -state.playerstate.car_rotate.y, -state.playerstate.car_rotate.x, 0);
			idx = -1;
			di = -1;
			for (var_counter2 = 0; var_counter2 < 4; var_counter2++) {
				offset_vector = simd_player.wheel_coords[var_counter2];
				mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec8); //; rotating car wheels, maybe?
				// Tile where the wheel is standing
				tile_east = (var_vec8.x + state.playerstate.car_posWorld1.lx) >> 16; // bits 16-24
				tile_south = -(((var_vec8.z + state.playerstate.car_posWorld1.lz) >> 16) - 0x1D);

				for (si = 0x16; si > idx; si--) {
					if (should_skip_tile[si] != 2 && lookahead_tiles[si * 3] + cam_tile_east == tile_east && lookahead_tiles[si * 3 + 1] + cam_tile_south == tile_south) {
						var_3C = tile_east;
						var_60 = tile_south;
						idx = si;
						di = var_counter2;
					}
				}
			}

			if (di != -1) {
				if (state.playerstate.car_surfaceWhl[0] != 4 || state.playerstate.car_surfaceWhl[1] != 4 || state.playerstate.car_surfaceWhl[2] != 4 || state.playerstate.car_surfaceWhl[3] != 4) {
					offset_vector.x = 0;
					offset_vector.z = 0;
					offset_vector.y = 0x7530;
					mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec8);
					mat_mul_vector(&var_vec8, &mat_temp, &offset_vector);
					if (offset_vector.z <= 0) {
						var_6C = -0x800 ;
					} else {
						var_6C = 0x800;
					}
				}
			}
		}
	}

	// Draw opponent's wheels
	var_4A = -1;
	var_A4 = 0;
	if (gameconfig.game_opponenttype != 0) {

		if (cameramode != 0 || followOpponentFlag == 0) {
			if (state.opponentstate.car_crashBmpFlag != 2) {
				car_rot_matrix = mat_rot_zxy(-state.opponentstate.car_rotate.z, -state.opponentstate.car_rotate.y, -state.opponentstate.car_rotate.x, 0);
				idx = -1;
				di = -1;

				for (var_counter2 = 0; var_counter2 < 4; var_counter2++) {
					offset_vector = simd_opponent.wheel_coords[var_counter2];
					mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec8); //; rotating car wheels, maybe?
					tile_east = (var_vec8.x + state.opponentstate.car_posWorld1.lx) >> 16; // bits 16-24
					tile_south = -(((var_vec8.z + state.opponentstate.car_posWorld1.lz) >> 16) - 0x1D);

					for (si = 0x16; si > idx; si--) {
						if (should_skip_tile[si] != 2 && lookahead_tiles[si * 3] + cam_tile_east == tile_east && lookahead_tiles[si * 3 + 1] + cam_tile_south == tile_south) {
							var_4A = tile_east;
							var_6E = tile_south;
							idx = si;
							di = var_counter2;
						}
					}
				}

				if (di != -1) {
						
					if (state.opponentstate.car_surfaceWhl[0] != 4 || state.opponentstate.car_surfaceWhl[1] != 4 || state.opponentstate.car_surfaceWhl[2] != 4 || state.opponentstate.car_surfaceWhl[3] != 4) {
						offset_vector.x = 0;
						offset_vector.y = 0;
						offset_vector.z = 0x7530;
						mat_mul_vector(&offset_vector, car_rot_matrix, &var_vec8);
						mat_mul_vector(&var_vec8, &mat_temp, &offset_vector);
						if (offset_vector.z <= 0) {
							var_A4 = -0x800; //0xF800; // signed number!
						} else {
							var_A4 = 0x800;
						}
					}
				}
			}
		}
	}
//; -----------------------------------------------------------------------------


	var_4E = 0;
	si = 0;
	
	// With the information collected by the previus tile-scan algorithm,
	// procees to draw the shapes in each tile. Start from the farthest
	// (painter's algorithm)
	for (si = 0; si < 0x17; si++) {
		if (should_skip_tile[si] != 0) {
			continue;
		}
		tile_east = tiles_to_draw_east[si];
		tile_south = tiles_to_draw_south[si];
		elem_map_value = tiles_to_draw_elem_type_vec[si];
		terr_map_value = tiles_to_draw_terr_type_vec[si];
		tile_det_level = tile_detail_level[si];
		var_12A = 0;
		if (elem_map_value == 0) {
			var_counter = 1;
			var_10E = unk_3C0F4;
		} else {
			var_trkobject_ptr = &trkObjectList[elem_map_value];
			if (var_trkobject_ptr->ss_multiTileFlag == 0) {
				var_counter = 1;
				var_10E = unk_3C0EE;
			} else if (var_trkobject_ptr->ss_multiTileFlag == 1) {
				var_counter = 2;
				var_10E = unk_3C0F0;
			} else if (var_trkobject_ptr->ss_multiTileFlag == 2) {
				var_counter = 3;
				var_10E = unk_3C0F4;
			} else if (var_trkobject_ptr->ss_multiTileFlag == 3) {
				var_counter = 4;
				var_10E = unk_3C0F8;
			}
		}

		// Draw the fence
		for (idx = 0; idx < var_counter; idx++) {
			tile_to_draw_east_offset = var_10E[idx * 2] + tile_east;
			tile_to_draw_south_offset = var_10E[idx * 2 + 1] + tile_south;
			
			if (detail_level == 0 || (tile_to_draw_east_offset == car_tile_east && tile_to_draw_south_offset == car_tile_south)) {
				if (tile_to_draw_east_offset == 0) {
					if (tile_to_draw_south_offset == 0) {
						di = 7;
					} else if (tile_to_draw_south_offset == 0x1D) {
						di = 5;
					} else {
						di = 6;
					}
				} else if (tile_to_draw_east_offset == 0x1D) {
					if (tile_to_draw_south_offset == 0) {
						di = 1;
					} else
					if (tile_to_draw_south_offset == 0x1D) {
						di = 1;
					} else {
						di = 2;
					}
				} else {
					if (tile_to_draw_south_offset == 0) {
						di = 0;
					} else if (tile_to_draw_south_offset == 0x1D) {
						di = 4;
					} else {
						di = -1;
					}
				}

				if (di != -1) {
					var_trkobjectptr = &trkObjectList[fence_TrkObjCodes[di]];
					if (tile_det_level == 0) {
						currenttransshape->shapeptr = var_trkobjectptr->ss_shapePtr;
					} else {
						currenttransshape->shapeptr = var_trkobjectptr->ss_loShapePtr;
					}

					currenttransshape->pos.x = trackcenterpos2[tile_to_draw_east_offset] - cam_pos.x;
					currenttransshape->pos.y = -cam_pos.y;
					currenttransshape->pos.z = trackcenterpos[tile_to_draw_south_offset] - cam_pos.z;
					currenttransshape->rectptr = &rect_unk2;
					currenttransshape->ts_flags = var_122 | 5;
					currenttransshape->rotvec.x = 0;
					currenttransshape->rotvec.y = 0;
					currenttransshape->rotvec.z = word_3C0D6[di];
					currenttransshape->unk = 0x400;
					currenttransshape->material = 0;
					var_transformresult = transformed_shape_op(&currenttransshape[0]);
					if (var_transformresult > 0) {
						// if the return value is > 0, we are out of memory
						// for the polygons, so the rendering is interrupted.
						// Note that (since we start from afar) this means that
						// if the scene is too complex only the far objects
						// will be drawn, while our car and its immediate
						// surroundings will be invisible. Luckily, it does not
						// happen often
						break;
					}
				}
			}
		}

		// terrain type 0x06: a flat piece of land at an elevated level  
		if (terr_map_value != 6) {
			var_hillheight = 0;

			// Special treatment of elevated corners
			if (elem_map_value >= 0x69 && elem_map_value <= 0x6C) {
				for (idx = 0; idx < 4; idx++) {
					if (idx == 0) {
						tile_to_draw_east_offset = tile_east;
						tile_to_draw_south_offset = tile_south;
					} else if (idx == 1) {
						tile_to_draw_east_offset = tile_east + 1;
						tile_to_draw_south_offset = tile_south;
					} else if (idx == 2) {
						tile_to_draw_east_offset = tile_east;
						tile_to_draw_south_offset = tile_south + 1;
					} else if (idx == 3) {
						tile_to_draw_east_offset = tile_east + 1;
						tile_to_draw_south_offset = tile_south + 1;
					}
					terr_map_value = td15_terr_map_main[tile_to_draw_east_offset + terrainrows[tile_to_draw_south_offset]];
					if (terr_map_value != 0) {
						var_trkobject_ptr = &sceneshapes2[terr_map_value];
						currenttransshape->shapeptr = var_trkobject_ptr->ss_shapePtr;
						currenttransshape->pos.x = trackcenterpos2[tile_to_draw_east_offset] - cam_pos.x;
						currenttransshape->pos.y = -cam_pos.y;
						currenttransshape->pos.z = trackcenterpos[tile_to_draw_south_offset] - cam_pos.z;
						currenttransshape->rectptr = &rect_unk2;
						currenttransshape->ts_flags = var_122 | 5;
						currenttransshape->rotvec.x = 0;
						currenttransshape->rotvec.y = 0;
						currenttransshape->rotvec.z = var_trkobject_ptr->ss_rotY;
						currenttransshape->unk = 0x400;
						currenttransshape->material = 0;
						var_transformresult = transformed_shape_op(&currenttransshape[0]);
						if (var_transformresult > 0)
							break;
					}
				}
				
				terr_map_value = 0;
			}
		} else {
			var_hillheight = hillHeightConsts[1];
			if (elem_map_value != 0) {
				terr_map_value = 0;
			}
		}

		// The rest of the rendering loop still needs to be analyzed in detail.
		// Anyway, the gist is that every tile is associated with various shape,
		// each of which is rendered via a call to `transformed_shape_op`. The
		// result of such fn is checked each time, since a return value of 1
		// means we ran out of memory

		if (terr_map_value != 0) {
			var_trkobject_ptr = &sceneshapes2[terr_map_value];
			currenttransshape->shapeptr = var_trkobject_ptr->ss_shapePtr;
			currenttransshape->pos.x = trackcenterpos2[tile_east] - cam_pos.x;
			currenttransshape->pos.y = var_hillheight - cam_pos.y;
			currenttransshape->pos.z = trackcenterpos[tile_south] - cam_pos.z;
			if (var_hillheight == 0) {
				currenttransshape->rectptr = &rect_unk2;
			} else {
				currenttransshape->rectptr = &rect_unk6;
			}

			currenttransshape->ts_flags = var_122 | 5;
			currenttransshape->rotvec.x = 0;
			currenttransshape->rotvec.y = 0;
			currenttransshape->rotvec.z = var_trkobject_ptr->ss_rotY;
			currenttransshape->unk = 0x400;
			currenttransshape->material = 0;
			var_transformresult = transformed_shape_op(&currenttransshape[0]);
			if (var_transformresult > 0)
				break;
		}

		transformedshape_counter = 0;
		curtransshape_ptr = currenttransshape;
		if (elem_map_value == 0) {
			tile_to_draw_east_offset = tile_east;
			tile_to_draw_south_offset = tile_south;
		} else {
			var_trkobject_ptr = &trkObjectList[elem_map_value];
			if ((var_trkobject_ptr->ss_multiTileFlag & 1) != 0) {
				var_5E = trackpos[tile_south];
				tile_to_draw_south_offset = tile_south + 1;
			} else {
				var_5E = trackcenterpos[tile_south];
				tile_to_draw_south_offset = tile_south;
			}

			if ((var_trkobject_ptr->ss_multiTileFlag & 2) != 0) {
				var_3A = trackpos2[1 + tile_east];
				tile_to_draw_east_offset = tile_east + 1;
			} else {
				var_3A = trackcenterpos2[tile_east];
				tile_to_draw_east_offset = tile_east;
			}

			var_vec8.x = var_3A - cam_pos.x;
			var_vec8.y = var_hillheight - cam_pos.y;
			var_vec8.z = var_5E - cam_pos.z;
			if (var_hillheight != 0) {
				if (var_trkobject_ptr->ss_multiTileFlag == 0) {
					di = 1;
					var_DA = unk_3C0A2;
				} else if (var_trkobject_ptr->ss_multiTileFlag == 1) {
					di = 2;
					var_DA = unk_3C0A6;
				} else if (var_trkobject_ptr->ss_multiTileFlag == 2) {
					di = 2;
					var_DA = unk_3C0AE;
				} else if (var_trkobject_ptr->ss_multiTileFlag == 3) {
					di = 4;
					var_DA = unk_3C0B6;
				}

				for (idx = 0; idx < di; idx++) {
					currenttransshape->pos.x = *var_DA + var_vec8.x;
					var_DA++;
					currenttransshape->pos.y = var_vec8.y;
					currenttransshape->pos.z = *var_DA + var_vec8.z;
					var_DA++;
					currenttransshape->shapeptr = &game3dshapes[0x3B2 / sizeof(struct SHAPE3D)];
					currenttransshape->rectptr = &rect_unk6;
					currenttransshape->ts_flags = var_122 | 5;
					currenttransshape->rotvec.x = 0;
					currenttransshape->rotvec.y = 0;
					currenttransshape->rotvec.z = 0;
					currenttransshape->unk = 0x800;
					currenttransshape->material = 0;
					var_transformresult = transformed_shape_op(&currenttransshape[0]);
					if (var_transformresult > 0)
						break;
				}
			}

			if (var_trkobject_ptr->ss_ssOvelay != 0) {
				var_trkobjectptr = &trkObjectList[var_trkobject_ptr->ss_ssOvelay];
				if (tile_det_level != 0) {
					currenttransshape[1].shapeptr = var_trkobjectptr->ss_loShapePtr;
				} else {
					currenttransshape[1].shapeptr = var_trkobjectptr->ss_shapePtr;
				}

				if (currenttransshape[1].shapeptr != 0) {
					currenttransshape[1].pos = var_vec8;
					currenttransshape[1].rotvec.x = 0;
					currenttransshape[1].rotvec.y = 0;
					currenttransshape[1].rotvec.z = var_trkobjectptr->ss_rotY;
					if (var_trkobjectptr->ss_multiTileFlag != 0) {
						currenttransshape[1].unk = 0x400;
					} else {
						currenttransshape[1].unk = 0x800;
					}

					if (var_trkobjectptr->ss_surfaceType >= 0) {
						currenttransshape[1].material = var_trkobjectptr->ss_surfaceType;
					} else {
						currenttransshape[1].material = var_E4;
					}

					currenttransshape[1].ts_flags = var_trkobjectptr->ss_ignoreZBias | var_122 | 4;
					if ((currenttransshape[1].ts_flags & 1) != 0) {
						currenttransshape[1].rectptr = &rect_unk2;
						var_transformresult = transformed_shape_op(&currenttransshape[1]);
						if (var_transformresult > 0)
							break;
					} else {
						currenttransshape[1].rectptr = &rect_unk6;
						var_4E = 1;
					}
				}
			}

			if (tile_det_level != 0) {
				currenttransshape->shapeptr = var_trkobject_ptr->ss_loShapePtr;
			} else {
				currenttransshape->shapeptr = var_trkobject_ptr->ss_shapePtr;
			}

			currenttransshape->pos = var_vec8; // whatever
			currenttransshape->rotvec.x = 0;
			currenttransshape->rotvec.y = 0;
			currenttransshape->rotvec.z = var_trkobject_ptr->ss_rotY;
			if (var_trkobject_ptr->ss_multiTileFlag != 0) {
				currenttransshape->unk = 0x400;
			} else {
				currenttransshape->unk = 0x800;
			}

			currenttransshape->ts_flags = var_trkobject_ptr->ss_ignoreZBias | var_122 | 4;
			if (var_trkobject_ptr->ss_surfaceType >= 0) {
				currenttransshape->material = var_trkobject_ptr->ss_surfaceType;
			} else {
				currenttransshape->material = var_E4;
			}

			if ((var_trkobject_ptr->ss_ignoreZBias & 1) != 0) {
				currenttransshape->rectptr = &rect_unk2;
				var_transformresult = transformed_shape_op(&currenttransshape[0]);
				if (var_transformresult > 0)
					break;
			} else {
				currenttransshape->rectptr = &rect_unk6;
				transformed_shape_add_for_sort(0, 0);
				if (var_4E != 0) {
					var_4E = 0;
					transformed_shape_add_for_sort(-0x800 /*0xF800*/, 0);
					if (var_6C != 0) {
						var_6C = -0x400;//0xFC00;
					}

					if (var_A4 != 0) {
						var_A4 -= 0x400;
					}
				}

				if (tile_east == startcol2 && tile_south == startrow2) {
					var_12A = 0;
				} else {
					var_12A = -1;
				}
			}

			var_4C = trackdata19[tile_east + trackrows[tile_south]];
			if (var_4C != 0xFF) {
				if (state.field_3FA[var_4C] == 0) {
					var_trkobject_ptr = &trkObjectList[212 + trackdata23[var_4C]];
					curtransshape_ptr->pos.x = td10_track_check_rel[var_4C * 3 + 0] - cam_pos.x;
					curtransshape_ptr->pos.y = td10_track_check_rel[var_4C * 3 + 1] - cam_pos.y;
					curtransshape_ptr->pos.z = td10_track_check_rel[var_4C * 3 + 2] - cam_pos.z;
					curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
					curtransshape_ptr->rectptr = &rect_unk6;
					curtransshape_ptr->ts_flags = var_122 | 4;
					curtransshape_ptr->rotvec.x = 0;
					curtransshape_ptr->rotvec.y = 0;
					curtransshape_ptr->rotvec.z = td08_direction_related[var_4C];
					curtransshape_ptr->unk = 0x64;
					curtransshape_ptr->material = 0;
					transformed_shape_add_for_sort(0, 0);
				} else if (state.field_42A != 0) {
					for (di = 0; di < 0x18; di++) {
						if (state.field_38E[di] != 0 && var_4C + 2 == state.field_443[di]) {
							var_trkobject_ptr = &sceneshapes3[state.field_42B[di]];
							curtransshape_ptr->pos.x = (state.game_longs1[di] >> 6) + td10_track_check_rel[var_4C * 3 + 0] - cam_pos.x;
							curtransshape_ptr->pos.y = (state.game_longs2[di] >> 6) + td10_track_check_rel[var_4C * 3 + 1] - cam_pos.y;
							curtransshape_ptr->pos.z = (state.game_longs3[di] >> 6) + td10_track_check_rel[var_4C * 3 + 2] - cam_pos.z;
							curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
							curtransshape_ptr->rectptr = &rect_unk6;
							curtransshape_ptr->ts_flags = var_122 | 5;
							curtransshape_ptr->rotvec.x = -state.field_2FE[di];
							curtransshape_ptr->rotvec.y = -state.field_32E[di];
							curtransshape_ptr->rotvec.z = -state.field_35E[di];
							curtransshape_ptr->unk = 0x400;
							curtransshape_ptr->material = 0;
							transformed_shape_add_for_sort(0, 0);
						}
					}
				}
			}
		}

		if ((var_3C == tile_east || var_3C == tile_to_draw_east_offset) && (var_60 == tile_south || var_60 == tile_to_draw_south_offset)) {
			if (state.field_42A != 0) {
				for (di = 0; di < 0x18; di++) {
					if (state.field_38E[di] != 0 && state.field_443[di] == 0) {
						var_trkobject_ptr = &sceneshapes3[state.field_42B[di]];
						curtransshape_ptr->pos.x = (state.game_longs1[di] + state.playerstate.car_posWorld1.lx >> 6) - cam_pos.x;
						curtransshape_ptr->pos.y = (state.game_longs2[di] + state.playerstate.car_posWorld1.ly >> 6) - cam_pos.y;
						curtransshape_ptr->pos.z = (state.game_longs3[di] + state.playerstate.car_posWorld1.lz >> 6) - cam_pos.z;
						curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
						curtransshape_ptr->rectptr = &rect_unk6;
						curtransshape_ptr->ts_flags = var_122 | 5;
						curtransshape_ptr->rotvec.x = -state.field_2FE[di];
						curtransshape_ptr->rotvec.y = -state.field_32E[di];
						curtransshape_ptr->rotvec.z = -state.field_35E[di];
						curtransshape_ptr->unk = 0x400;
						curtransshape_ptr->material = gameconfig.game_playermaterial;
						transformed_shape_add_for_sort(var_6C & var_12A, 0);
					}
				}
			}

			var_trkobject_ptr = &trkObjectList[2];//0x1C / sizeof(struct TRACKOBJECT)];
			curtransshape_ptr->pos.x = (state.playerstate.car_posWorld1.lx >> 6) - cam_pos.x;
			curtransshape_ptr->pos.y = (state.playerstate.car_posWorld1.ly >> 6) - cam_pos.y;
			curtransshape_ptr->pos.z = (state.playerstate.car_posWorld1.lz >> 6) - cam_pos.z;
			
			if (tile_det_level != 0 || detail_level > 2) {
				curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_loShapePtr;
			} else {
				curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
				sub_204AE(&game3dshapes[0x0AD4 / sizeof(struct SHAPE3D)].shape3d_verts[8], state.playerstate.car_steeringAngle, &state.playerstate.car_rc2, word_443E8, carshapevecs, &carshapevec);
			}

			if (slow_video_mgmt_copy != 0) {
				curtransshape_ptr->rectptr = &rect_unk12;
				curtransshape_ptr->ts_flags = 0xC;
			} else if (state.playerstate.car_crashBmpFlag != 1) {
				curtransshape_ptr->ts_flags = 4;
			} else {
				var_rect = cliprect_unk;
				curtransshape_ptr->rectptr = &var_rect;
				curtransshape_ptr->ts_flags = 0xC;
			}

			curtransshape_ptr->rotvec.x = -state.playerstate.car_rotate.z;
			curtransshape_ptr->rotvec.y = -state.playerstate.car_rotate.y;
			curtransshape_ptr->rotvec.z = -state.playerstate.car_rotate.x;
			curtransshape_ptr->unk = 0x12C;
			curtransshape_ptr->material = gameconfig.game_playermaterial;
			transformed_shape_add_for_sort(var_6C & var_12A, 2);
		}
		
		if ((var_4A == tile_east) || (var_4A == tile_to_draw_east_offset)) {
			if ((var_6E == tile_south) || (var_6E == tile_to_draw_south_offset)) {
				if (state.field_42A != 0) {
					for (di = 0; di < 0x18; di++) {
						if (state.field_38E[di] != 0) {
							if (state.field_443[di] == 1) {
								var_trkobject_ptr = &sceneshapes3[state.field_42B[di]];
								curtransshape_ptr->pos.x = (state.game_longs1[di] + state.opponentstate.car_posWorld1.lx >> 6) - cam_pos.x;
								curtransshape_ptr->pos.y = (state.game_longs2[di] + state.opponentstate.car_posWorld1.ly >> 6) - cam_pos.y;
								curtransshape_ptr->pos.z = (state.game_longs3[di] + state.opponentstate.car_posWorld1.lz >> 6) - cam_pos.z;
								curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
								curtransshape_ptr->rectptr = &rect_unk6;
								curtransshape_ptr->ts_flags = var_122 | 5;
								curtransshape_ptr->rotvec.x = -state.field_2FE[di];
								curtransshape_ptr->rotvec.y = -state.field_32E[di];
								curtransshape_ptr->rotvec.z = -state.field_35E[di];
								curtransshape_ptr->unk = 0x400;
								curtransshape_ptr->material = gameconfig.game_opponentmaterial;
								transformed_shape_add_for_sort(var_A4 & var_12A, 0);
							}
						}
					}
				}
				var_trkobject_ptr = &trkObjectList[3];//0x2A / sizeof(struct TRACKOBJECT)];
				curtransshape_ptr->pos.x = (state.opponentstate.car_posWorld1.lx >> 6) - cam_pos.x;
				curtransshape_ptr->pos.y = (state.opponentstate.car_posWorld1.ly >> 6) - cam_pos.y;
				curtransshape_ptr->pos.z = (state.opponentstate.car_posWorld1.lz >> 6) - cam_pos.z;

				if (tile_det_level != 0 || detail_level > 2) {
					curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_loShapePtr;
				} else {
					curtransshape_ptr->shapeptr = var_trkobject_ptr->ss_shapePtr;
					sub_204AE(&game3dshapes[0x0AEA / sizeof(struct SHAPE3D)].shape3d_verts[8], state.opponentstate.car_steeringAngle, &state.opponentstate.car_rc2, word_4448A, oppcarshapevecs, &oppcarshapevec);
				}

				if (slow_video_mgmt_copy != 0) {
					curtransshape_ptr->rectptr = &rect_unk15;
					curtransshape_ptr->ts_flags = 0xC;
				} else {
					if (state.opponentstate.car_crashBmpFlag != 1) {
						curtransshape_ptr->ts_flags = 4;
					} else {
						var_rect2 = cliprect_unk;
						curtransshape_ptr->rectptr = &var_rect2;
						curtransshape_ptr->ts_flags = 0xC;
					}
				}

				curtransshape_ptr->rotvec.x = -state.opponentstate.car_rotate.z;
				curtransshape_ptr->rotvec.y = -state.opponentstate.car_rotate.y;
				curtransshape_ptr->rotvec.z = -state.opponentstate.car_rotate.x;
				curtransshape_ptr->unk = 0x12C;
				curtransshape_ptr->material = gameconfig.game_opponentmaterial;
				transformed_shape_add_for_sort(var_4A & var_12A, 3);
			}
		}

		if (state.game_inputmode == 0) {
			if ((tile_east == startcol2 || tile_to_draw_east_offset == startcol2) && (tile_south == startrow2 || tile_to_draw_south_offset == startrow2)) {

				idx = multiply_and_scale(cos_fast(word_44DCA), 0x24);
				var_counter = multiply_and_scale(sin_fast(word_44DCA), 0x24) + 0x38;

				var_108 = &game3dshapes[0x98A / sizeof(struct SHAPE3D)].shape3d_verts[8];
				var_108[0].x = idx - 0x24;
				var_108[1].x = idx - 0x24;
				var_108[2].x = 0x24 - idx;
				var_108[3].x = 0x24 - idx;

				var_108[0].z = var_counter;
				var_108[1].z = var_counter;
				var_108[2].z = var_counter;
				var_108[3].z = var_counter;
				 
				curtransshape_ptr->pos.x =
					multiply_and_scale(sin_fast(track_angle + 0x100), 0x24) +
					multiply_and_scale(sin_fast(track_angle + 0x200), 0x1B6) + 
					trackcenterpos2[startcol2] - cam_pos.x;
				curtransshape_ptr->pos.y = hillHeightConsts[hillFlag] - cam_pos.y;
				curtransshape_ptr->pos.z =
					multiply_and_scale(cos_fast(track_angle + 0x100), 0x24) +
					multiply_and_scale(cos_fast(track_angle + 0x200), 0x1B6) + 
					trackcenterpos[startrow2] - cam_pos.z;

				curtransshape_ptr->shapeptr = &game3dshapes[0x98A / sizeof(struct SHAPE3D)];
				curtransshape_ptr->rectptr = &rect_unk6;
				curtransshape_ptr->ts_flags = var_122 | 4;
				curtransshape_ptr->rotvec.x = 0;
				curtransshape_ptr->rotvec.y = 0;
				curtransshape_ptr->rotvec.z = track_angle;
				curtransshape_ptr->unk = 0x400;
				idx = word_44DCA >> 6;
				if (idx > 3) {
					idx = 3;
				}

				curtransshape_ptr->material = idx;
				transformed_shape_add_for_sort(var_12A & -0x800 /*0xF800*/, 0);
			}
		}

		if (transformedshape_counter != 0) {
			if (transformedshape_counter > 1) {
				heapsort_by_order(transformedshape_counter, transformedshape_zarray, transformedshape_indices);
			}

			// Draw red overlights on the brake lights on own and opponent's car
			for (idx = 0; idx < transformedshape_counter; idx++) {
				// di is used for index into currenttransshape elsewhere
				di = transformedshape_indices[idx];
				if (transformedshape_arg2array[di] == 2) {
					if (state.playerstate.car_is_braking != 0) {
						backlights_paint_override = 0x2F;
					} else {
						backlights_paint_override = 0x2E;
					}
				} else if (transformedshape_arg2array[di] == 3) {
					if (state.opponentstate.car_is_braking == 0) {
						backlights_paint_override = 0x2E;
					} else {
						backlights_paint_override = 0x2F;
					}
				}

				var_transformresult = transformed_shape_op(&currenttransshape[di]); // DI??
				if (var_transformresult > 0)
					break;

				if (var_transformresult == 0) {
					if (transformedshape_arg2array[di] == 2) {
						if (state.playerstate.car_crashBmpFlag == 1) {
							var_DC[0] = 1;
						}
					} else if (transformedshape_arg2array[di] == 3) {
						if (state.opponentstate.car_crashBmpFlag == 1) {
							var_DC[1] = 1;
						}
					}
				}
			}
		}
	}

	// Draw the skybox
	var_132 = skybox_op(arg_0, arg_cliprectptr, skybox_parameter, &var_mat, car_rot_z_3, car_rot_x_2, cam_pos.y);
	sprite_set_1_size(0, 0x140, arg_cliprectptr->top, arg_cliprectptr->bottom);
	get_a_poly_info();

	// This supposedly draws the explosion. The fact that it cycles three
	// different patterns, each 4 frames long, seems to corroborate the
	// hypothesis
	for (si = 0; si < 2; si++) {
		if (var_DC[si] == 0) {
			continue;
		}
		if (slow_video_mgmt_copy == 0) {
			if (si == 0) {
				var_rectptr = &var_rect;
			} else {
				var_rectptr = &var_rect2;
			}
		} else {
			if (si == 0) {
				var_rectptr = &rect_unk12;
			} else {
				var_rectptr = &rect_unk15;
			}
		}

		if (rect_intersect(var_rectptr, arg_cliprectptr) == 0) {
			sprite_set_1_size(var_rectptr->left, var_rectptr->right, var_rectptr->top, var_rectptr->bottom);
			offset_vector.x = (var_rectptr->right + var_rectptr->left) >> 1;
			offset_vector.y = (var_rectptr->top + var_rectptr->bottom) >> 1;
			idx = var_rectptr->right - var_rectptr->left;
			var_counter = var_rectptr->bottom - var_rectptr->top;
			if (var_counter > idx) {
				idx = var_counter;
			}

			di = (state.game_frame >> 2) % 3 ;
			var_counter = ((long)idx << 8) / (long)sdgame2_widths[di];
			shape_op_explosion(var_counter, sdgame2shapes[di], offset_vector.x, offset_vector.y);
		}
	}

/*
; --------------------------------------------------------
*/

	// Depict windscreen cracking after a crash
	sprite_set_1_size(0, 0x140, arg_cliprectptr->top, arg_cliprectptr->bottom);
	if (cameramode == 0) {

		if (followOpponentFlag != 0) {
			var_stateptr = &state.opponentstate;
			si = state.game_oEndFrame;
		} else {
			var_stateptr = &state.playerstate;
			si = state.game_pEndFrame;
		}

		if (var_stateptr->car_crashBmpFlag == 1) {
			if (slow_video_mgmt_copy != 0) {
				rect_union(init_crak(state.game_frame - si, arg_cliprectptr->top, arg_cliprectptr->bottom - arg_cliprectptr->top), rect_unk, rect_unk);
			} else {
				init_crak(state.game_frame - si, arg_cliprectptr->top, arg_cliprectptr->bottom - arg_cliprectptr->top);
			}
		} else if (var_stateptr->car_crashBmpFlag == 2) {
			if (slow_video_mgmt_copy != 0) {
				rect_union(do_sinking(state.game_frame - si, arg_cliprectptr->top, arg_cliprectptr->bottom - arg_cliprectptr->top), rect_unk, rect_unk);
			} else {
				do_sinking(state.game_frame - si, arg_cliprectptr->top, arg_cliprectptr->bottom - arg_cliprectptr->top);
			}
		}
	}

	// Show elapsed time
	if (game_replay_mode == 0) {
		if (state.game_inputmode != 0) {
			format_frame_as_string(&resID_byte1, elapsed_time1 + elapsed_time2, 0);
			font_set_fontdef2(fontledresptr);
			if (slow_video_mgmt_copy != 0) {
				rect_union(intro_draw_text(&resID_byte1, 0x8C, roofbmpheight + 2, dialog_fnt_colour, 0), &rect_unk11, &rect_unk11);
			} else {
				intro_draw_text(&resID_byte1, 0x8C, roofbmpheight + 2, dialog_fnt_colour, 0);
			}

			font_set_fontdef();
		}
	}

	if (slow_video_mgmt_copy != 0) {
		rect_union(draw_ingame_text(), rect_unk, rect_unk);
		if (var_132 != 0) {
			rect_unk[0] = *arg_cliprectptr;
			for (si = 1; si < 15; si++) {
				rect_unk[si] = cliprect_unk;
			}
		}

		for (si = 0; si < 15; si++) {
			rectptr_unk[si] = rect_unk[si];
		}
		word_449FC[arg_0] = car_rot_x_2;
		word_463D6 = car_rot_x_2;

	} else {
		draw_ingame_text();
	}

}
