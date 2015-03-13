# Introduction #

Description of stage-format and map-format


# Details #
**Tilemap-bits:**
**24 in Total:**|8 | bit|
|:-|:---|
|1 | ladder|
|4+1 | slippery behavior |
|2 | kill|
|1 | invisibility|
|1 | destroyable|
|1 | water|
|1 | sink|
|4 | script-defined actions|

**Level-description:**
```
<StageName>Metal man</StageName>

<StageDescription>Defeat metal in his furious rage....</StageDescription>

<Level0>
<Size>30,30</Size>
<damageLevels>40,80,100</damageLevels>
<PlayerSpawn>posX,posY</PlayerSpawn>
<Password>asdasdasd</Password>
<Tiles>/gfx/tiles/tile1.png</Tiles>
<Platforms>/gfx/platforms/platform1.png</Platforms>
<Bitmaps>/gfx/bitmaps/bitmap1.png</Bitmaps>
<Tilemap>tilemap1.map</Tilemap>
<StaticPlatforms>posX,posY,platformTile/...</StaticPlatforms>
<DynamicPlatforms>posX,posY,platformTile,behaviour/...</DynamicPlatforms>
<EnemySpawns>posX,posY,type/...</EnemySpawns>
<ItemSpawns>posX,posY,type/...</ItemSpawns>
<ScriptDefine1>#name of script</ScriptDefine1>
<ScriptDefine2></ScriptDefine2>
<ScriptDefine3></ScriptDefine3>
<ScriptDefine4></ScriptDefine4>
</Level0>
```