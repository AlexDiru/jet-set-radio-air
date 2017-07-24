//FILE
//ObjectFile
//RotX
//RotY
//RotZ
//ScaX
//ScaY
//ScaZ
float ManageCharacterFile(char* CharacterFileDir,int ObjectID,float radius)
{
	dbOpenToRead(1,CharacterFileDir);
	char* CharacterObjFileDir = dbReadString(1);
	
	float CharacterRotX = atoi(dbReadString(1));
	float CharacterRotY = atoi(dbReadString(1));
	float CharacterRotZ = atoi(dbReadString(1));
	float CharacterScaX = atoi(dbReadString(1));
	float CharacterScaY = atoi(dbReadString(1));
	float CharacterScaZ = atoi(dbReadString(1));
	float ReadRadius = atoi(dbReadString(1));
	dbCloseFile(1);

	//Obj = FObj();
	dbLoadObject(CharacterObjFileDir,ObjectID);
	dbRotateObject(ObjectID,CharacterRotX,CharacterRotY,CharacterRotZ);
	dbScaleObject(ObjectID,CharacterScaX,CharacterScaY,CharacterScaZ);
	dbFixObjectPivot(ObjectID);
	dbPositionObject(ObjectID,4,100,25);
	SC_SetupComplexObject(ObjectID,0,0);
	return ReadRadius * radius;
}