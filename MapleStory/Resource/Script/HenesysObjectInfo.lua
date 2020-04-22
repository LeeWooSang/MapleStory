g_staticObjectTableSize = 8;
g_animatedObjectTableSize = 1;

WORLD_WIDTH = 5960.
WORLD_HEIGHT = 1000.

g_staticObjectTable = {};
g_animatedObjectTable = {};

g_staticObjectTable[0] = 
{
	name = "HenesysHouse0";
	x = -2817.;
	y = 85.;
};

g_staticObjectTable[1] = 
{
	name = "HenesysHouse3";
	x = -2000;
	y = 102.5;
};

g_staticObjectTable[2] = 
{
	name = "HenesysHouse2";
	x = -1592.5;
	y = 144;
};

g_staticObjectTable[3] = 
{
	name = "HenesysHouse1";
	x = -1283;
	y = 25;
};

g_staticObjectTable[4] = 
{
	name = "HenesysHouse4";
	x = 2600;
	y = -86;
};

g_staticObjectTable[5] = 
{
	name = "HenesysHouse5";
	x = 1300;
	y = 82.5;
};

g_staticObjectTable[6] = 
{
	name = "HenesysHouse6";
	x = 1420.;
	y = 125;
};

g_staticObjectTable[7] = 
{
	name = "HenesysHouse7";
	x = 1600;
	y = 127;
};

function GetHenesysStaticObjectInfo(id)
	API_HenesysStaticObjectInfo(g_staticObjectTable[id].name, g_staticObjectTable[id].x, g_staticObjectTable[id].y);
end

g_animatedObjectTable[0] = 
{
	name = "HenesysHouse1_Flag";
	animationName = "base";
	x = -1295;
	y = -179;
	size = 7;
};

function GetHenesysAnimatedObjectInfo(id)
	API_HenesysAnimatedObjectInfo(g_animatedObjectTable[id].name, g_animatedObjectTable[id].animationName, g_animatedObjectTable[id].x, g_animatedObjectTable[id].y, g_animatedObjectTable[id].size);
end