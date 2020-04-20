g_tableSize = 1;

g_objectTable = {};

g_objectTable[0] = 
{
	name = "House0";
	x = 1.503;
	y = -5.012;
};

function GetHenesysObjectInfo(id)
	API_HenesysObjectInfo(g_objectTable[id].name, g_objectTable[id].x, g_objectTable[id].y);
end
