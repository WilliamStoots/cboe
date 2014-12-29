/*
 *  universe.h
 *  BoE
 *
 *  Created by Celtic Minstrel on 24/04/09.
 *
 */

#ifndef BOE_DATA_UNIVERSE_H
#define BOE_DATA_UNIVERSE_H

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "party.h"
#include "creatlist.h"
#include "item.h"
#include "town.h"
#include "talking.h"
#include "simpletypes.h"
#include "scenario.h"

namespace fs = boost::filesystem; // TODO: Centralize this namespace alias?

namespace legacy {
	struct out_info_type;
	struct current_town_type;
	struct town_item_list;
	struct stored_town_maps_type;
	struct stored_outdoor_maps_type;
	struct big_tr_type;
};

class cCurTown {
	short cur_talk_loaded = -1;
	bool free_for_sfx(short x, short y);
	cUniverse& univ;
	cTown* arena;
	cTown*const record() const;
public:
	bool quickfire_present = false, belt_present = false;
	// formerly current_town_type
	short num; // 200 if outdoors (my addition)
	short difficulty;
	//char explored[64][64];
	bool hostile;
	cPopulation monst;
	bool in_boat; // is this really needed?
	location p_loc;
	
	cItemRec items[115]; // formerly town_item_list type
	
	//ter_num_t template_terrain[64][64];
	unsigned long fields[64][64];
	
	void append(legacy::current_town_type& old);
	void append(legacy::town_item_list& old);
	void append(unsigned char(& old_sfx)[64][64], unsigned char(& old_misc_i)[64][64]);
	void append(legacy::big_tr_type& old);
	
	cTown* operator -> ();
	explicit cCurTown(cUniverse& univ);
	short countMonsters();
	cSpeech& cur_talk(); // Get the currently loaded speech
	bool prep_talk(short which); // Prepare for loading specified speech, returning true if already loaded
	void prep_arena(); // Set up for a combat arena
	void place_preset_fields();
	
	bool is_explored(char x, char y) const;
	bool is_force_wall(char x, char y) const;
	bool is_fire_wall(char x, char y) const;
	bool is_antimagic(char x, char y) const;
	bool is_scloud(char x, char y) const; // stinking cloud
	bool is_ice_wall(char x, char y) const;
	bool is_blade_wall(char x, char y) const;
	bool is_sleep_cloud(char x, char y) const;
	bool is_block(char x, char y) const; // currently unused
	bool is_spot(char x, char y) const;
	bool is_special(char x, char y) const;
	bool is_web(char x, char y) const;
	bool is_crate(char x, char y) const;
	bool is_barrel(char x, char y) const;
	bool is_fire_barr(char x, char y) const;
	bool is_force_barr(char x, char y) const;
	bool is_quickfire(char x, char y) const;
	bool is_sm_blood(char x, char y) const;
	bool is_med_blood(char x, char y) const;
	bool is_lg_blood(char x, char y) const;
	bool is_sm_slime(char x, char y) const;
	bool is_lg_slime(char x, char y) const;
	bool is_ash(char x, char y) const;
	bool is_bones(char x, char y) const;
	bool is_rubble(char x, char y) const;
	bool is_force_cage(char x, char y) const;
//	bool is_trim(char x, char y, char t) const;
	bool set_explored(char x, char y, bool b);
	bool set_force_wall(char x, char y, bool b);
	bool set_fire_wall(char x, char y, bool b);
	bool set_antimagic(char x, char y, bool b);
	bool set_scloud(char x, char y, bool b); // stinking cloud
	bool set_ice_wall(char x, char y, bool b);
	bool set_blade_wall(char x, char y, bool b);
	bool set_sleep_cloud(char x, char y, bool b);
	bool set_block(char x, char y, bool b); // currently unused
	bool set_spot(char x, char y, bool b);
	bool set_web(char x, char y, bool b);
	bool set_crate(char x, char y, bool b);
	bool set_barrel(char x, char y, bool b);
	bool set_fire_barr(char x, char y, bool b);
	bool set_force_barr(char x, char y, bool b);
	bool set_quickfire(char x, char y, bool b);
	bool set_sm_blood(char x, char y, bool b);
	bool set_med_blood(char x, char y, bool b);
	bool set_lg_blood(char x, char y, bool b);
	bool set_sm_slime(char x, char y, bool b);
	bool set_lg_slime(char x, char y, bool b);
	bool set_ash(char x, char y, bool b);
	bool set_bones(char x, char y, bool b);
	bool set_rubble(char x, char y, bool b);
	bool set_force_cage(char x, char y, bool b);
//	bool set_trim(char x, char y, char t, bool b);
	bool is_impassable(short x, short y);
	void writeTo(std::ostream& file) const;
	void readFrom(std::istream& file);
	
	~cCurTown();
};

class cCurOut {
	cUniverse& univ;
public:
	char expl[96][96]; // formerly out_info_type
	ter_num_t out[96][96];
	unsigned char out_e[96][96];
	
	void append(legacy::out_info_type& old);
	
	typedef ter_num_t arr_96[96];
	arr_96& operator [] (size_t i);
	ter_num_t& operator [] (location loc);
	void writeTo(std::ostream& file) const;
	void readFrom(std::istream& file);
	cOutdoors* operator->();
	explicit cCurOut(cUniverse& univ);
};

enum eAmbientSound {
	AMBIENT_NONE,
	AMBIENT_DRIP,
	AMBIENT_BIRD,
	AMBIENT_CUSTOM,
};

class cUniverse{
public:
	cScenario scenario;
	cParty party;
	cCurTown town;
	char town_maps[200][8][64]; // formerly stored_town_maps_type
	cCurOut out;
	char out_maps[100][6][48]; // formerly stored_outdoor_maps_type
	snd_num_t out_sound;
	fs::path file;
	
	void append(legacy::stored_town_maps_type& old);
	void append(legacy::stored_outdoor_maps_type& old);
	short difficulty_adjust() const;
	explicit cUniverse(long party_type = 'dflt');
};

#endif
