void CreateSprayCan(SprayCan spraycan,char* ObjectFile,char* ImageFile)
{
	//int TEMPHOLDERFORnumberofspraycans = number_of_spray_cans;
	//load the spray can in a temp object to copy it later
	int TempCanObj = FObj();
	dbMakeObjectBox(TempCanObj,1,1,1);//dbLoadObjectDebug(ObjectFile,TempCanObj);
	dbScaleObject(TempCanObj,10,10,10);
	
		spraycan.id = FObj();
		dbCloneObject(spraycan.id,TempCanObj);
		dbPositionObject(spraycan.id,0,10,dbRnd(10)*10);
		dbZRotateObject(spraycan.id,10);
		spraycan.texid = FImg();
		dbLoadImage(ImageFile,spraycan.texid);
		dbTextureObject(spraycan.id,spraycan.texid);
	
	dbDeleteObject(TempCanObj);

	//number_of_spray_cans = TEMPHOLDERFORnumberofspraycans;
}