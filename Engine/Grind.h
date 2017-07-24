
int Grind(int playerid, int GrindObject)
{
	int direction;

	if (dbWrapValue(dbObjectAngleY(playerid)) <= dbWrapValue(dbObjectAngleY(GrindObject)+110) && dbWrapValue(dbObjectAngleY(playerid)) <= dbWrapValue(dbObjectAngleY(GrindObject)+250)) { direction=1; }
	else if (dbWrapValue(dbObjectAngleY(playerid)) >= dbWrapValue(dbObjectAngleY(GrindObject)+70) && dbWrapValue(dbObjectAngleY(playerid)) >= dbWrapValue(dbObjectAngleY(GrindObject)+0)) { direction=2; }
	else if (dbWrapValue(dbObjectAngleY(playerid)) <= dbWrapValue(dbObjectAngleY(GrindObject)+290) && dbWrapValue(dbObjectAngleY(playerid)) <= dbWrapValue(dbObjectAngleY(GrindObject)+360)) { direction=2; }
	else { direction = 0; }
	if (dbObjectCollision(GrindObject,playerid)==0) { direction=0; }
	return direction;
		
}


int Wallride(actor user, int GrindObject)
{
	int direction;

	if (dbWrapValue(dbObjectAngleY(user.id)) <= dbWrapValue(dbObjectAngleY(GrindObject)+110) && dbWrapValue(dbObjectAngleY(user.id)) <= dbWrapValue(dbObjectAngleY(GrindObject)+250)) { direction=1; }
	else if (dbWrapValue(dbObjectAngleY(user.id)) >= dbWrapValue(dbObjectAngleY(GrindObject)+70) && dbWrapValue(dbObjectAngleY(user.id)) >= dbWrapValue(dbObjectAngleY(GrindObject)+0)) { direction=2; }
	else if (dbWrapValue(dbObjectAngleY(user.id)) <= dbWrapValue(dbObjectAngleY(GrindObject)+290) && dbWrapValue(dbObjectAngleY(user.id)) <= dbWrapValue(dbObjectAngleY(GrindObject)+360)) { direction=2; }
	else { direction = 0; }
	if (dbObjectCollision(GrindObject,user.id)==0) { direction=0; }
	return direction;
		
}