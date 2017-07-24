void dbLoadObjectDebug(char* ObjectFilename,int ObjectID)
{
	dbLoadObject(ObjectFilename,ObjectID);
	if (dbObjectExist(ObjectID)==0)
	{
		dbPrint(dbStr(ObjectID));
		dbPrint(ObjectFilename);
		dbPrint("DOES NOT EXIST");
	}
}

void dbLoadMusicDebug(char* MusicFilename,int MusicID)
{
	dbLoadMusic(MusicFilename,MusicID);
	if (dbMusicExist(MusicID)==0)
	{
		dbPrint(dbStr(MusicID));
		dbPrint(MusicFilename);
		dbPrint("DOES NOT EXIST");
	}
}


void dbLoadImageDebug(char* ImageFilename,int ImageID)
{
	dbLoadImage(ImageFilename,ImageID);
	if (dbImageExist(ImageID)==0)
	{
		dbPrint(dbStr(ImageID));
		dbPrint(ImageFilename);
		dbPrint("DOES NOT EXIST");
	}
}

float Get3DDistance(int obja,int objb)
{
	float del;
	float X,Y,Z;
	float deltaX = dbObjectPositionX(obja) - dbObjectPositionX(objb);
	float deltaY = dbObjectPositionY(obja) - dbObjectPositionY(objb);
	float deltaZ = dbObjectPositionZ(obja) - dbObjectPositionZ(objb);

	X = deltaX*deltaX;
	Y = deltaY*deltaY; 
	Z = deltaZ*deltaZ;
	
	del = X+Y+Z;

	return dbSQRT(del);
}

//functions for the timer
#pragma region TimerCommands

void tm_init (actor user)
{
   user.tm_timer = dbTimer();
   user.tm_last = user.tm_timer;
   user.tm_factor = 1;
}

float tm_update (actor user)
{
   user.tm_timer = dbTimer();
   user.tm_difference = user.tm_timer - user.tm_last;
   user.tm_last = user.tm_timer;
   user.tm_result = user.tm_difference * user.tm_factor;
   return user.tm_result;
}
void tm_setmultiplicator (actor user, float f_flt )
{
   user.tm_factor = f_flt;
}
float tm_getfactor (actor user)
{
   float f_flt = 0;
   f_flt = user.tm_result;
   return f_flt;
}

#pragma endregion