#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "SDL/include/SDL.h"

enum COLLIDER_TYPE;
// ----------------------------------------------------
struct MapLayer
{
	p2SString	name;
	int			width;
	int			height;
	uint*		data;
	uint		tileset_used; //pick what tileset need

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		//RELEASE(data);
		if (data != nullptr) {
			delete[] data;
		}
	}

	// TODO 6 (old): Short function to get the value of x,y
	inline uint Get(int x, int y) const
	{
		return x + (width * y);
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;

	~TileSet();	
};

struct MapObjects
{
	p2SString			name;
	int					id;
	SDL_Rect			RectCollider;
	iPoint				StartPoint;
	COLLIDER_TYPE		Collider_type;
	

};
struct ImageLayers
{
	p2SString			name;
	SDL_Texture*		texture;
	int					position_x;
	int					position_y;
	int					image_width;
	int					image_height;
	
	~ImageLayers();
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	layers;
	p2List<MapObjects*>	objects;
	p2List<ImageLayers*>	image_layers;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// Coordinate translation methods
	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
	COLLIDER_TYPE DefineType(int type_as_int);
	void SetAllCollidersAndEntities();
private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObjects(pugi::xml_node& node, MapObjects* object);
	bool LoadImageLayers(pugi::xml_node& node, ImageLayers* object);

public:

	MapData data;
	int speedLayer;
	int positionX_Layer2;
	int colliderPlayer_w;
	int colliderPlayer_h;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__