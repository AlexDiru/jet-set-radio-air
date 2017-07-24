//FILE
//ObjectFile
//RotX
//RotY
//RotZ
//ScaX
//ScaY
//ScaZ

void ManageLevelFile(char* LevelFileDir,int ObjectID)
{
	dbOpenToRead(1,LevelFileDir);
	char* LevelObjFileDir = dbReadString(1);
	
	float LevelRotX = atoi(dbReadString(1));
	float LevelRotY = atoi(dbReadString(1));
	float LevelRotZ = atoi(dbReadString(1));
	float LevelScaX = atoi(dbReadString(1));
	float LevelScaY = atoi(dbReadString(1));
	float LevelScaZ = atoi(dbReadString(1));
	dbCloseFile(1);

	//Obj = FObj();
	dbLoadObject(LevelObjFileDir,ObjectID);
	dbRotateObject(ObjectID,LevelRotX,LevelRotY,LevelRotZ);
	dbScaleObject(ObjectID,LevelScaX,LevelScaY,LevelScaZ);
	dbFixObjectPivot(ObjectID);
	dbPositionObject(ObjectID,4,100,25);
	SC_SetupObject(ObjectID,1,0);
}