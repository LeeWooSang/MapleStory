g_tableSize = 8;

WORLD_WIDTH = 5960.
WORLD_HEIGHT = 1000.

g_objectTable = {};

g_objectTable[0] = 
{
	name = "HenesysHouse0";
	x = -2817.;
	y = 85.;
};

g_objectTable[1] = 
{
	name = "HenesysHouse3";
	x = -2000;
	y = 102.5;
};

g_objectTable[2] = 
{
	name = "HenesysHouse2";
	x = -1592.5;
	y = 144;
};

g_objectTable[3] = 
{
	name = "HenesysHouse1";
	x = -1283;
	y = 25;
};

g_objectTable[4] = 
{
	name = "HenesysHouse4";
	x = 2600;
	y = -86;
};

g_objectTable[5] = 
{
	name = "HenesysHouse5";
	x = 1300;
	y = 82.5;
};

g_objectTable[6] = 
{
	name = "HenesysHouse6";
	x = 1420.;
	y = 125;
};

g_objectTable[7] = 
{
	name = "HenesysHouse7";
	x = 1600;
	y = 127;
};

function GetHenesysObjectInfo(id)
	API_HenesysObjectInfo(g_objectTable[id].name, g_objectTable[id].x, g_objectTable[id].y);
end
