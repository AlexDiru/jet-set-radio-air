void InitBlur(int BlurCam)
{
	//Motion-Blur Cam
	dbMakeCamera(BlurCam);
	//dbSetCa BlurCam ,1,1000
	//set camera fov BlurCam ,90
	//SET CAMERA TO OBJECT ORIENTATION 1
	dbSetCameraToImage(BlurCam,2000,640,480);
	
	//Create Sprites
	dbSprite(1000, 0,0, 2000);
	dbSetSprite(1000, 0, 1);
	dbSetSpriteAlpha(1000, 45);
	dbSizeSprite( 1000, 800, 600);
	dbSprite(2000, 0,0, 2000);
	dbSetSprite(2000, 0, 1);
	dbSetSpriteAlpha( 2000, 90);
	dbSizeSprite( 2000, 800, 600);
	dbSprite( 3000, 0,0,2000);
	dbSetSprite( 3000, 0, 1);
	dbSetSpriteAlpha( 3000, 135);
	dbSizeSprite(3000, 800, 600);
}

void MotionBlur(int normcam, int blurcam, int sprite1id, int sprite2id, int sprite3id,float xang,float yang,int blurlevel, char BlurOn)
{
	if (dbCameraExist(blurcam)==0 && BlurOn == 1)
	{
		dbMakeCamera(blurcam);
	}

	if (dbCameraExist(blurcam)==1 && BlurOn == 0)
	{
		dbDeleteCamera(blurcam);
		return;
	}
	
	//Get Mousemovement
	float Mouse_X_Speed = dbRnd(blurlevel);
	float Mouse_Y_Speed = dbRnd(blurlevel);
	yang += Mouse_X_Speed * 0.1;
	xang += Mouse_Y_Speed * 0.1;

	//set blur cam to normal cam
	dbRotateCamera(blurcam,dbCameraAngleX(normcam),dbCameraAngleY(normcam),dbCameraAngleZ(normcam));
	dbPositionCamera(blurcam,dbCameraPositionX(normcam),dbCameraPositionY(normcam),dbCameraPositionZ(normcam));

	if (BlurOn == 1)
	{
		dbSetCameraToImage(blurcam,2000,1280,960);
		//Set Blur Offset
		float x = 0;
		float y = 0;

		//Redraw Sprites
		dbSprite( 1000, -Mouse_X_Speed*x,  -Mouse_Y_Speed*y,2000);
		dbSprite(2000, -Mouse_X_Speed*(x*2),   -Mouse_Y_Speed*(y*2),2000);
		dbSprite(3000, -Mouse_X_Speed*(x*4),   -Mouse_Y_Speed*(y*4),2000);
	}
}