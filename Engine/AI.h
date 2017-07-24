void PedestrianAI(int Object,int PlayerObject)
{
	//dbSetObjectToObjectOrientation(Object,PlayerObject);
	dbPointObject(Object,dbObjectPositionX(PlayerObject),dbObjectPositionY(Object),dbObjectPositionZ(PlayerObject));
	//dbYRotateObject(Object,dbRnd(360));
	dbMoveObject(Object,-1);
}