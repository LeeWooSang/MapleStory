g_characterObjectTableSize = 9;

g_characterObjectTable = {};

g_characterObjectTable[0] = 
{
	objectName = "Body";
	animationName = "Idle";
	textureName = "IdleBody";
	x = 0;
	y = 0;
	size = 3;
};

g_characterObjectTable[1] = 
{
	objectName = "Body";
	animationName = "Walk";
	textureName = "WalkBody";
	x = 0;
	y = 0;
	size = 4;
};

g_characterObjectTable[2] = 
{
	objectName = "Body";
	animationName = "Jump";
	textureName = "JumpBody";
	x = 0;
	y = 0;
	size = 1;
};

g_characterObjectTable[3] = 
{
	objectName = "Arm";
	animationName = "Idle";
	textureName = "IdleArm";
	x = 0;
	y = 0;
	size = 3;
};

g_characterObjectTable[4] = 
{
	objectName = "Arm";
	animationName = "Walk";
	textureName = "WalkArm";
	x = 0;
	y = 0;
	size = 4;
};

g_characterObjectTable[5] = 
{
	objectName = "Arm";
	animationName = "Jump";
	textureName = "JumpArm";
	x = 0;
	y = 0;
	size = 1;
};

g_characterObjectTable[6] = 
{
	objectName = "Head";
	animationName = "Idle";
	textureName = "FrontHead";
	x = 0;
	y = 0;
	size = 1;
};

g_characterObjectTable[7] = 
{
	objectName = "Head";
	animationName = "Walk";
	textureName = "FrontHead";
	x = 0;
	y = 0;
	size = 1;
};

g_characterObjectTable[8] = 
{
	objectName = "Head";
	animationName = "Jump";
	textureName = "FrontHead";
	x = 0;
	y = 0;
	size = 1;
};

function GetCharacterObjectInfo(id)
	API_CharacterObjectInfo(g_characterObjectTable[id].objectName, g_characterObjectTable[id].animationName, g_characterObjectTable[id].textureName, g_characterObjectTable[id].x, g_characterObjectTable[id].y, g_characterObjectTable[id].size);
end