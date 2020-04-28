g_staticObjectTableSize = 0;
g_animatedObjectTableSize = 1;

WORLD_WIDTH = 5960.
WORLD_HEIGHT = 1000.
gapX = 90;
gapY = -60;

g_staticObjectTable = {};
g_animatedObjectTable = {};
tableSize = 0;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse0";
	x = -2817.;
	y = 85.;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse3";
	x = -2000;
	y = 102.5;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse2";
	x = -1592.5;
	y = 144;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse1";
	x = -1283;
	y = 25;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse4";
	x = 2600;
	y = -86;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse5";
	x = 1300;
	y = 82.5;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse6";
	x = 1420.;
	y = 125;
};
tableSize = tableSize + 1;

g_staticObjectTable[tableSize] = 
{
	objectName = "HenesysHouse";
	textureName = "HenesysHouse7";
	x = 1600;
	y = 127;
};
tableSize = tableSize + 1;

local tileNum = 0;
for i = 0, 66, 1 do
	for j = 0, 3, 1 do

	local str0 = "WoodMarbleTile";;
	local str1 = tostring(tileNum);

	g_staticObjectTable[tableSize] = 
	{
		objectName = str0;
		-- string.format : ���ڿ� ��ġ�� �Լ�
		textureName = string.format("%s%s", str0, str1);

		--textureName = "WoodMarbleTile0";

		x = (-WORLD_WIDTH * 0.5) + (gapX * i);
		y = (WORLD_HEIGHT * 0.5) + (gapY * j);
	};

	tileNum = tileNum + 1;	
	if tileNum >= 6 then
		tileNum = 0;
	end
	tableSize = tableSize + 1;
	end
end

tileNum = 0;
for i = 0, 66, 1 do
	local str0 = "WoodMarbleTop";
	local str1 = tostring(tileNum);

	g_staticObjectTable[tableSize] = 
	{
		objectName = str0;
		textureName = string.format("%s%s", str0, str1);
		x = (-WORLD_WIDTH * 0.5) + (gapX * i);
		y = (WORLD_HEIGHT * 0.5) - 180 - 30 - (33 * 0.5);
	};

	tileNum = tileNum + 1;	
	if tileNum >= 4 then
		tileNum = 0;
	end
	tableSize = tableSize + 1;
end

g_staticObjectTableSize = tableSize;

function GetHenesysStaticObjectInfo(id)
	API_HenesysStaticObjectInfo(g_staticObjectTable[id].objectName, g_staticObjectTable[id].textureName, g_staticObjectTable[id].x, g_staticObjectTable[id].y);
end

g_animatedObjectTable[0] = 
{
	objectName = "HenesysHouse1_Flag";
	animationName = "base";
	textureName = "HenesysHouse1_Flag";
	x = -1295;
	y = -179;
	size = 7;
};

function GetHenesysAnimatedObjectInfo(id)
	API_HenesysAnimatedObjectInfo(g_animatedObjectTable[id].objectName, g_animatedObjectTable[id].animationName, g_animatedObjectTable[id].textureName, g_animatedObjectTable[id].x, g_animatedObjectTable[id].y, g_animatedObjectTable[id].size);
end