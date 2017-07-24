//TODO
//Combo counter
/* THEORY
every game loop, it is checked if the user is on the ground
if they are on the ground then the combo counter is reset to 0 and the combo multiplier is reset to 1

every game loop it is checked that every time the combo variable increases to a multiple of 3 
if it is a multiple of 3 then the combo multiplier is increased by 1 to a maximum of 10

if the user is grinding on a rail then 1 is added to the combo variable
if the user is doing a trick in the air then 1 is added to the combo variable
*/

//L_Control = keystate 29 (trick)
#include <iostream>
#include <list>
#include <new>
#include <DarkGDK.h>
#include <SC_Collision.h>
#include <Free.h>
#include "GameStructs.h"
#include <ImageText.h>
#include "Grind.h"
#include "UsefulFunctions.h"
#include "AI.h"
#include "d3dfunc.h"
#include "CharacterFileReader.h"
#include "LevelFileReader.h"
#include "CreateSprayCans.h"
#include "InventoryClass.h"
//#include "MotionBlur.h"
#include "ShopClass.h"

#define FallingHeight 0
#define FallingHeight 0
#define MIDDLEOFSCREEN dbScreenWidth()/2,dbScreenHeight()/2
#define DRUNKSTATE_none 0
#define DRUNKSTATE_tipsy 2
#define DRUNKSTATE_drunk 4
#define DRUNKSTATE_esperanto 10 //completely shit faced :)

		////////////*****/////////////
		////////////*****/////////////
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///
		///************************///

///********************////***************///*****************
///********************///****************///*****************
///////////****///////////****///////////////****/////////****
///////////****///////////****///////////////****/////////****
///////////****////////////**************////****/////////***/
///////////****/////////////**************///***************//
///////////****///////////////////////****///**************///
///////////****///////////////////////****///****////////****/
//************/////////////**************////****/////////****
//***********/////////////***************////****/////////****


//Always export maps with true left-hand data

//Controls
//W - acc forward
//A - powerbrake
//Mousemove - rotate player


float TIMERUPDATE;

#define MIDDLEOFSCREEN dbScreenWidth()/2,dbScreenHeight()/2

actor user[1];
int NumberOfShopsOpen; 
int numberofshops = 1;
//cShop* Shop;
cShop* Shop = new cShop[numberofshops];


//function for getting the distance between two objects
float GetDist(int Obj1,int Obj2)
{
	float X,Y,Z;
	X = dbObjectPositionX(Obj1) - dbObjectPositionX(Obj2);
	Y = dbObjectPositionY(Obj1) - dbObjectPositionY(Obj2);
	Z = dbObjectPositionZ(Obj1) - dbObjectPositionZ(Obj2);
	return dbSqrt(X*X+Y*Y+Z*Z);
}
///////////////////////////////////////////////////////

//functions for the timer
#pragma region TimerCommands

void tm_init ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_factor = 1;
}

float tm_update ()
{
   user[0].tm_timer = dbTimer();
   user[0].tm_difference = user[0].tm_timer - user[0].tm_last;
   user[0].tm_last = user[0].tm_timer;
   user[0].tm_result = user[0].tm_difference * user[0].tm_factor;
   return user[0].tm_result;
}

void tm_setmultiplicator ( float f_flt )
{
   user[0].tm_factor = f_flt;
}

float tm_getfactor ()
{
   float f_flt = 0;
   f_flt = user[0].tm_result;
   return f_flt;
}
#pragma endregion
void DebugControls(int SphereNum) { if (dbKeyState(16)) { dbMoveObjectUp(SphereNum,10); } if (dbKeyState(18)) { dbMoveObjectDown(SphereNum,10); } }
char* GetChosenCharacterFile(int NumOfCharacters, int FONTSIZE)
{
	//std::string Chara;
	//std::string File;
	/*
	for (int i = 0; i < NumOfCharacters; i++)
	{
		dbText(0,FONTSIZE*i,Char[i].Name);
	}
	*/
	
	//File = "Media//JCHA FILES//";
	//File.append(Chara);
	//File.append(".jcha");
	//char ReturnChar = File.c_str();
	//return (char*)File.c_str();
	//dbCLS();

	//for now pick a random char
	int x = dbRnd(2)+1;
	if (x == 1)
	{
		//user[0].radius = user[0].radius *0.7;
		return "Media//JCHA FILES//PK.jcha";
	}
	if (x == 2)
	{
		//user[0].radius = user[0].radius *0.7;
		return "Media//JCHA FILES//PK.jcha";
	}
	if (x == 3)
	{
		//user[0].radius = user[0].radius *0.7;
		return "Media//JCHA FILES//PK.jcha";
	}
}




void ManageDrunkState()
{
	//If not drunk turn blur cam off
		if (user[0].DrunkState < DRUNKSTATE_tipsy)
		{
			//MotionBlur(0,BlurCam,1000,2000,3000,xang,yang,1,2);
		}
		//when TIPSY you have slow speed and your turn slower
		if (user[0].DrunkState >= DRUNKSTATE_tipsy)
		{
			user[0].topspeed = 0.3*0.7; //a third slower
			user[0].turnspeed = 3*0.7; //a third slower
			//MotionBlur(0,BlurCam,1000,2000,3000,xang,yang,5,1);
		}
		//when DRUNK you have slow speed, turn slower, jump lower, can't boost
		if (user[0].DrunkState >= DRUNKSTATE_drunk)
		{
			//if (user[0].DrunkState < DRUNKSTATE_esperanto)
			//{
			//	MotionBlur(0,BlurCam,1000,2000,3000,xang,yang,25,1);
			//}
			user[0].jumptimer = 0; //can't jump
			user[0].boosttimer = 0; //can't boost
		}
		//esperanto
		if (user[0].DrunkState >= DRUNKSTATE_esperanto)
		{
			//MotionBlur(0,BlurCam,1000,2000,3000,xang,yang,50,1);
		}
}


bool UpdateTheCamera(int SphereNum)
{
	if (dbKeyState(29))
	{
		dbRotateCamera(dbCameraAngleX() + dbMouseMoveY()/3,dbCameraAngleY() + dbMouseMoveX()/3,dbObjectAngleZ(SphereNum));
		dbPositionCamera( dbObjectPositionX(SphereNum),dbObjectPositionY(SphereNum)+3,dbObjectPositionZ(SphereNum));
		dbMoveCamera(-8);
		return true;
	}
	else
	{
		dbXRotateCamera(dbCameraAngleX() + dbMouseMoveY()/3 );
		dbPositionCamera( dbObjectPositionX(SphereNum),dbObjectPositionY(SphereNum)+3,dbObjectPositionZ(SphereNum));
		dbRotateCamera(dbCameraAngleX(),dbObjectAngleY(SphereNum),dbObjectAngleZ(SphereNum));
		dbMoveCamera(-8);
		return false;
	}
}
void Setup(int FPS,int WndX,int WndY,int WndZ,bool FullScr)
	{
		dbSyncOn( );
		dbSyncRate(FPS);
		dbAutoCamOff( );
		dbRandomize( dbTimer() );
		SC_Start( );
		dbHideMouse();
		dbSetCameraRange(1,30000);

		if (FullScr)
		{
			dbSetImageColorKey(0,0,0);
			dbSetWindowOff();
			dbSetWindowLayout(0,0,0);
			dbMaximiseWindow();
			dbSetWindowPosition(0,0);
			dbSetDisplayMode(1280,800,32);
		}
	}
/////////////////////////

void DarkGDK()
{
	
	Shop[0].ID = 1;
	Shop[0].XPos = 0;
	Shop[0].YPos = 20;
	Shop[0].EntranceRadius = 20000;

	//stuff which:
	#pragma region Should be loaded from files

	user[0].rtimer = 0;
	user[0].stimer = 0;
	user[0].vtimer = 0;
	user[0].gravity = -0.04f;
	user[0].slope = 0.1f;
	user[0].ground = 1;
	user[0].jumptimer = 0;
	user[0].vx = 0;
	user[0].vy = 0;
	user[0].vz = 0;
	user[0].angy = 0;
	user[0].oldx = 0;
	user[0].oldy = 0;
	user[0].oldz = 0;
	user[0].x = 0;
	user[0].y = 0;
	user[0].z = 0;
	user[0].radius = 0.6;
	user[0].ny = 0;
	//physics
	user[0].accel = 0.0037;
	user[0].topspeed = 0.3;
	user[0].grindspeed = 0.35;
	user[0].boostspeed = 0.4;
	user[0].decel = 0.007;
	user[0].speed = 0;
	user[0].powerbrake = 0.1;
	//cans
	user[0].spraycans = 0;
	//health barwda
	user[0].currenthealth = 100;
	user[0].maxhealth = 100;
	//experience
	user[0].experiencetolevel = 200;
	user[0].experience = 0;

	user[0].combocounter = 0;
	//user[0].combocountdepletetimer = 20;

#pragma endregion
	//setup the game
	Setup(60,640,480,32,false);
	//spray cans
	#pragma region Spray cans
	
	SprayCan yellowspraycan[10];
	int numberofspraycans = 10;
	//load the spray can in a temp object to copy it later
	int TempCanObj = FObj();
	dbLoadObjectDebug("Media//SprayCan.x",TempCanObj);
	dbScaleObject(TempCanObj,10,10,10);
	for (int i = 0; i<numberofspraycans; i++)
	{
		yellowspraycan[i].id = FObj();
		dbCloneObject(yellowspraycan[i].id,TempCanObj);
		dbPositionObject(yellowspraycan[i].id,0,10,dbRnd(10)*10);
		dbZRotateObject(yellowspraycan[i].id,10);
		yellowspraycan[i].texid = FImg();
		dbLoadImage("Media//SilentLaws Textures//th_spraycan1.png",yellowspraycan[i].texid);
		dbTextureObject(yellowspraycan[i].id,yellowspraycan[i].texid);
	}
	dbDeleteObject(TempCanObj);
#pragma endregion
	//make player
#pragma region Make Player
	user[0].id = FObj();
	char* _jcha = GetChosenCharacterFile(15,12);
	user[0].radius = ManageCharacterFile(_jcha,user[0].id,user[0].radius);
	//user[0].radius = user[0].radius * 0.6;
#pragma endregion
	//Create the level
#pragma region Create Level
	//Create the level struct which contains the object id of the parts of the level
	LEVEL lvl[8];

	//load the map
	lvl[0].id = FObj();
	ManageLevelFile("Media//JLEV FILES//SwallowLane.jlev",lvl[0].id);
	dbSetObjectCull(lvl[0].id,1);
	lvl[0].numberofrails = 2;
	lvl[0].spraycans = 10;
	//Make a sphere the size of radius to be positioned at the plr every loop
	user[0].SphereNum = FObj();
	dbMakeObjectSphere(user[0].SphereNum,user[0].radius*2.5);
	SC_SetupObject(user[0].SphereNum,0,1);
#pragma endregion
	//Create the grinding rails
	#pragma region Create grind rails
	//Grind rail struct
	//Later on load data from files
	//int railnum = lvl[0].numberofrails;
	grindrail GrindRail[3];
	//GrindRail[0] data
	GrindRail[0].posx = 10;
	GrindRail[0].posy = 0;
	GrindRail[0].posz = 20;
	GrindRail[0].rotx = 45;
	GrindRail[0].roty = 45;
	GrindRail[0].rotz = 0;
	GrindRail[0].sizx = 10;
	GrindRail[0].sizy = 1;
	GrindRail[0].sizz = 100;
	//GrindRail[1] data
	GrindRail[1].posx = 10;
	GrindRail[1].posy = 0;
	GrindRail[1].posz = 20;
	GrindRail[1].rotx = 0;
	GrindRail[1].roty = 45;
	GrindRail[1].rotz = 0;
	GrindRail[1].sizx = 10;
	GrindRail[1].sizy = 1;
	GrindRail[1].sizz = 200;
	//GrindRail[2] data
	/*
	GrindRail[2].posx = 20;
	GrindRail[2].posy = 0;
	GrindRail[2].posz = -200;
	GrindRail[2].rotx = 0;
	GrindRail[2].roty = 45;
	GrindRail[2].rotz = 0;
	GrindRail[2].sizx = 2;
	GrindRail[2].sizy = 2;
	GrindRail[2].sizz = 100;
	//GrindRail[3] data
	GrindRail[3].posx = 30;
	GrindRail[3].posy = 0;
	GrindRail[3].posz = -300;
	GrindRail[3].rotx = 0;
	GrindRail[3].roty = 45;
	GrindRail[3].rotz = 0;
	GrindRail[3].sizx = 3;
	GrindRail[3].sizy = 3;
	GrindRail[3].sizz = 100;
	//GrindRail[4] data
	GrindRail[4].posx = 40;
	GrindRail[4].posy = 0;
	GrindRail[4].posz = -400;
	GrindRail[4].rotx = 0;
	GrindRail[4].roty = 45;
	GrindRail[4].rotz = 0;
	GrindRail[4].sizx = 4;
	GrindRail[4].sizy = 4;
	GrindRail[4].sizz = 100;
	*/

	for (int x=0;x<lvl[0].numberofrails;x++)
	{
		GrindRail[x].id = FObj();
		dbMakeObjectBox(GrindRail[x].id,GrindRail[x].sizx,GrindRail[x].sizy,GrindRail[x].sizz);
		dbPositionObject(GrindRail[x].id,GrindRail[x].posx,GrindRail[x].posy,GrindRail[x].posz);
		dbColorObject(GrindRail[x].id,dbRGB(0,255,0));
		dbRotateObject(GrindRail[x].id,GrindRail[x].rotx,GrindRail[x].roty,GrindRail[x].rotz);
		SC_SetupObject(GrindRail[x].id,1,2);
	}
	#pragma endregion

#pragma region Player Voice
	user[0].Voice[0].filedir = "Media//Gum VA//Gum - Alright.mp3";
	user[0].Voice[1].filedir = "Media//Gum VA//Gum - Huh.mp3";
	user[0].Voice[2].filedir = "Media//Gum VA//Gum - Huh Hah.mp3";
	user[0].Voice[3].filedir = "Media//Gum VA//Gum - Yeah.mp3";
	//user[0].Voice[4].filedir = "Media//Gum VA//Gum - .mp3";
	for (int q = 0;q<4;q++)
	{
		user[0].Voice[q].id = FMus();
		dbLoadMusicDebug(user[0].Voice[q].filedir,user[0].Voice[q].id);
	}
#pragma endregion
	
#pragma region SFX
	sfx SFX;
	SFX.Sound[FallingHeight].filedir = "Media//SFX//Falling.mp3";
	SFX.Sound[FallingHeight].id = FSnd();
	dbLoadMusic(SFX.Sound[FallingHeight].filedir,SFX.Sound[FallingHeight].id);
#pragma endregion

#pragma region Pedestrians
	int numberofpedestrians = 10;
	pedestrian Pedestrian[10];
	Pedestrian[0].id = FObj();
	dbMakeObjectBox(Pedestrian[0].id,3,10,3);
	//make 19 more pedestrians
	for (int i = 1;i<numberofpedestrians;i++)
	{
		Pedestrian[i].id = FObj();
		dbInstanceObject(Pedestrian[i].id,Pedestrian[0].id);
		dbPositionObject(Pedestrian[i].id,0,-9999,0);//dbRnd(80),0,dbRnd(130));
	}
#pragma region
	
#pragma region BG Music
	music Music;
	Music.Songs = 7;
	Music.SongSelect = 1;
	Music.Background[0].filedir = "Media//Music//Soul Fear.mp3";
	Music.Background[0].SongName = "Soul Fear";
	Music.Background[0].SongArtist = "Ryzbot";
	Music.Background[1].filedir = "Media//Music//Swash.mp3";
	Music.Background[1].SongName = "Swash";
	Music.Background[1].SongArtist = "Ryzbot";
	Music.Background[2].filedir = "Media//Music//Running Beats.mp3";
	Music.Background[2].SongName = "Running Beats";
	Music.Background[2].SongArtist = "Ryzbot";
	Music.Background[2].SongSecondArtist = "Keiichi Sugiyama";
	Music.Background[3].filedir = "Media//Music//Drumbeats.mp3";
	Music.Background[3].SongName = "Drumbeats";
	Music.Background[3].SongArtist = "Ryzbot";
	Music.Background[4].filedir = "Media//Music//Evil (JSRA Mix).mp3";
	Music.Background[4].SongName = "Evil (JSRA Mix)";
	Music.Background[4].SongArtist = "Ryzbot";
	Music.Background[5].filedir = "Media//Music//Where I Am.mp3";
	Music.Background[5].SongName = "Where I Am";
	Music.Background[5].SongArtist = "Ryzbot";
	Music.Background[5].SongSecondArtist = "Solid Inc";
	Music.Background[6].filedir = "Media//Music//Cut a Break (Bagjac Remix).mp3";
	Music.Background[6].SongName = "Cut a Break";
	Music.Background[6].SongArtist = "Bagjac";
	Music.SongSelect = 1;
	Music.TrackTimerTime = 60;
	Music.TrackTimer = 0;
	//dbPlayMusic(Music.Background[Music.SongSelect-1].id);
	//dbLoopMusic(Music.Background[Music.SongSelect-1].id);
	
	for (int i=0;i<Music.Songs;i++)
	{
		Music.Background[i].id = FMus();
		dbLoadMusicDebug(Music.Background[i].filedir,Music.Background[i].id);
	}
	
#pragma endregion
	

#pragma region Players Graffiti
	//Create the players graffiti
	//small graffiti
	user[0].GraffitiSmall.imgdir = "Media//Beat//beat tex.tga";
	user[0].GraffitiSmall.size = 1;
	for (int a=0;a<3;a++)
	{
		user[0].GraffitiSmall.stage[a] = a;
		int TempBmp = FBmp();
		//Load the bitmap for the image
		dbLoadBitmap(user[0].GraffitiSmall.imgdir,TempBmp);
		//Fade the bitmap in a percentage due to size ( 100/sizestage )
		int BmpFade = 100/(user[0].GraffitiSmall.stage[a]+1);
		dbFadeBitmap(TempBmp,BmpFade);
		//Create an image for the faded texture to go into
		user[0].GraffitiSmall.imgid[a] = FImg();
		dbGetImage(user[0].GraffitiSmall.imgid[a],0,0,dbBitmapWidth(TempBmp),dbBitmapHeight(TempBmp));
		//Delete the bitmap
		dbDeleteBitmap(TempBmp);
	}

	//Medium graffiti
	//user[0].GraffitiMedium.img
		user[0].GraffitiMedium.imgdir[0] = "Media//Graffiti//GGGraffitiMediumSprayStageOneRapid99Background.tga";
	user[0].GraffitiMedium.imgdir[1] = "Media//Graffiti//GGGraffitiMediumSprayStageTwoRapid99Background.tga";
	user[0].GraffitiMedium.imgdir[2] = "Media//Graffiti//GGGraffitiMediumSprayStageThree.tga";
	user[0].GraffitiMedium.size = 3;
	for (int a=0;a<user[0].GraffitiMedium.size;a++)
	{
		user[0].GraffitiMedium.imgid[a] = FImg();
		dbLoadImage(user[0].GraffitiMedium.imgdir[a],user[0].GraffitiMedium.imgid[a]);
	}
	//Large Graffiti
	user[0].GraffitiLarge.imgdir[0] = "Media//Graffiti//GGGraffitiLargeSprayStageOneLoveShockerBackground.tga";
	user[0].GraffitiLarge.imgdir[1] = "Media//Graffiti//GGGraffitiLargeSprayStageTwoLoveShockerBackground.tga";
	user[0].GraffitiLarge.imgdir[2] = "Media//Graffiti//GGGraffitiLargeSprayStageThreeLoveShockerBackground.tga";
	user[0].GraffitiLarge.imgdir[3] = "Media//Graffiti//GGGraffitiLargeSprayStageFourLoveShockerBackground.tga";
	user[0].GraffitiLarge.imgdir[4] = "Media//Graffiti//GGGraffitiLargeSprayStageFive.tga";
	user[0].GraffitiLarge.size = 5;
	for (int a=0;a<user[0].GraffitiLarge.size;a++)
	{
		user[0].GraffitiLarge.imgid[a] = FImg();
		dbLoadImageDebug(user[0].GraffitiLarge.imgdir[a],user[0].GraffitiLarge.imgid[a]);
	}
/*
	//Large graffiti
	user[0].GraffitiLarge.imgdir = "Media//Beat//beat tex.tga";
	user[0].GraffitiLarge.size = 6;
	for (int a=0;a<3;a++)
	{
		user[0].GraffitiLarge.stage[a] = a;
		int TempBmp = FBmp();
		//Load the bitmap for the image
		dbLoadBitmap(user[0].GraffitiLarge.imgdir,TempBmp);
		//Fade the bitmap in a percentage due to size ( 100/sizestage )
		int BmpFade = 100-(100/(user[0].GraffitiLarge.stage[a]+1));
		dbFadeBitmap(TempBmp,BmpFade);
		//Create an image for the faded texture to go into
		user[0].GraffitiLarge.imgid[a] = FImg();
		dbGetImage(user[0].GraffitiLarge.imgid[a],0,0,dbBitmapWidth(TempBmp),dbBitmapHeight(TempBmp));
		//Delete the bitmap
		dbDeleteBitmap(TempBmp);
	}

	//XLarge graffiti
	user[0].GraffitiXLarge.imgdir = "Media//Beat//beat tex.tga";
	user[0].GraffitiXLarge.size = 10;
	for (int a=0;a<3;a++)
	{
		user[0].GraffitiXLarge.stage[a] = a;
		int TempBmp = FBmp();
		//Load the bitmap for the image
		dbLoadBitmap(user[0].GraffitiXLarge.imgdir,TempBmp);
		//Fade the bitmap in a percentage due to size ( 100/sizestage )
		int BmpFade = 100/(user[0].GraffitiXLarge.stage[a]+1);
		dbFadeBitmap(TempBmp,BmpFade);
		//Create an image for the faded texture to go into
		user[0].GraffitiXLarge.imgid[a] = FImg();
		dbGetImage(user[0].GraffitiXLarge.imgid[a],0,0,dbBitmapWidth(TempBmp),dbBitmapHeight(TempBmp));
		//Delete the bitmap
		dbDeleteBitmap(TempBmp);
	}
	*/
#pragma endregion
#pragma region Particles
	/*
	user[0].grindparticlesimage = FImg();
	dbLoadImage("Media//Particles//Grinding.png",user[0].grindparticlesimage);
	user[0].grindparticlesid = FPar();
	dbMakeFireParticles(user[0].grindparticlesid,user[0].grindparticlesimage,100,0,0,0,1.5,0.6,1.5);
	dbSetParticleVelocity(user[0].grindparticlesid,10);
	dbSetParticleChaos(user[0].grindparticlesid,5);
	*/
#pragma endregion

	//Create the graffiti planes
	int numberofgraffitiplanes = 2;
	graffitiplane GraffitiPlane[2];
	GraffitiPlane[0].size = 3;
	GraffitiPlane[0].imgdir = "Media//Graffiti//Rapid99GraffitiMedium.bmp";
	GraffitiPlane[0].posx = 0;
	GraffitiPlane[0].posy = -990;
	GraffitiPlane[0].posz = 0;
	GraffitiPlane[1].size = 5;
	GraffitiPlane[1].imgdir = "Media//Graffiti//GraffitiLargeLoveShocker.tga";
	GraffitiPlane[1].posx = 0;
	GraffitiPlane[1].posy = -990;
	GraffitiPlane[1].posz = 10;

	for (int x=0;x<numberofgraffitiplanes;x++)
	{
		GraffitiPlane[x].objid = FObj();
		dbMakeObjectBox(GraffitiPlane[x].objid,GraffitiPlane[x].size*2,GraffitiPlane[x].size*2,1);
		dbMoveObjectUp(GraffitiPlane[x].objid,5);
		GraffitiPlane[x].spraystage = 0;
		dbPositionObject(GraffitiPlane[x].objid,GraffitiPlane[x].posx,GraffitiPlane[x].posy,GraffitiPlane[x].posz);
		for (int a=0;a<GraffitiPlane[x].size;a++)
		{
			//int TempVar = a;
			GraffitiPlane[x].stage[a] = a;
			int TempBmp = FBmp();
			//Load the bitmap for the image
			dbLoadBitmap(GraffitiPlane[x].imgdir,TempBmp);
			//Fade the bitmap in a percentage due to size ( 100/sizestage )
			int BmpFade = 100/(GraffitiPlane[x].stage[a]+1);
			dbFadeBitmap(TempBmp,BmpFade);
			//Create an image for the faded texture to go into
			GraffitiPlane[x].imgid[a] = FImg();
			dbGetImage(GraffitiPlane[x].imgid[a],0,0,dbBitmapWidth(TempBmp),dbBitmapHeight(TempBmp));
			//Delete the bitmap
			dbDeleteBitmap(TempBmp);
		}
		dbTextureObject(GraffitiPlane[x].objid,GraffitiPlane[x].imgid[GraffitiPlane[x].size-1]);
	}

	//Create the sky
	int sky = FObj();
	dbLoadObject("Media//SkysphereSunnyBeach//sb.x",sky);
	dbSetObjectCull(sky,1);
	dbSetObjectLight (sky,0);

	//Create the bmp text for the experience
	char *ExperienceDisplayString = dbStr(user[0].experience);
	strcat(ExperienceDisplayString,"/"); 
	strcat(ExperienceDisplayString,dbStr(user[0].experiencetolevel));

	char *ComboDisplayString = dbStr(user[0].combocounter);
	strcat(ComboDisplayString," Trick Combo");

	InitText();
	SetFont(1,"NiseJSRF",16,0,0);
	StartText();
	AAText(1,0,448,0,ExperienceDisplayString);
	AAText(1,0,16,0,dbStr(user[0].spraycans));
	AAText(1,0,35,0,ComboDisplayString);
	EndText();
	//imageText CurrentExp(ExperienceDisplayString,"Media//Text//RedNeon.png",16,16,624,0,16);

	tm_init();

	dbRandomize(dbTimer());

	//initialize d3d
	InitD3DFunc();

	//create the inventory
	Inventory *Inv1 = new Inventory();

		// Just declare the list object - using 'new' in the way it was is wrong in C++ (too much Java influence perhaps?)
		std::list<Inventory*> ilist;

		// You push_back on lists, not push
		// The items being pushed are already the pointers we want, so this doesn't need the address-of operator.
		ilist.push_back(Inv1);
		for(std::list<Inventory*>::iterator i = ilist.begin() ; i != ilist.end() ; i++)
		{
			(*i)->CreateItem(1,"Sake",-10,1);
			(*i)->Item[1].Amount = 0;
			(*i)->IsDisplayed = false;
		}
		
	//user[0].grinding[x] = 0;
	while( LoopGDK( ) )
	{	
		/*
		//print debug text
		if (SC_ObjectCollision(user[0].SphereNum,GrindRail[1].id)>0)
		{
			dbPrint("COLLIDE");
		}
		*/

		DebugControls(user[0].SphereNum);
	
		ManageDrunkState();

		NumberOfShopsOpen = 0;
		for (int i = 0; i < numberofshops;i++)
		{
			Shop[i].IsOpen = ManageShop(Shop[i],Inv1,ilist,user[0]);
			if (Shop[i].IsOpen == true)
			{
				NumberOfShopsOpen++;
			}
		}

		/*INVENTORY
		*/
		//if p is pressed
		if (dbKeyState(25) == 1)
		{
			if (Inv1->IsDisplayed == false)
			{
				if (NumberOfShopsOpen == 0)
				{
					//if (Inv1->OpenTimer == false)
					//{
						Inv1->IsDisplayed = true;
						//Inv1->OpenTimer = true;
					//}
				}
			}
		}
		
		

		if (Inv1->IsDisplayed == true)
		{
			dbShowMouse();
			//display the inv
			dbPasteImage(1,0,0);
			//display all items
			Inv1->ItemList = 0;
			for (int i =1;i<2;i++)
			{
				Inv1->DisplayItemQuantity(i,0,Inv1->ItemList*12,12);
				Inv1->ItemList++;
				//the user can select items
				if (dbMouseY() > Inv1->ItemList*1 && dbMouseY() < Inv1->ItemList*1+12)
				{
					if (dbMouseClick())
					{
						if (Inv1->ClickTimer == false)
						{
							Inv1->SubtractItem(i,1);
							Inv1->ClickTimer = true;
							user[0].currenthealth += Inv1->Item[i].HealthBonus;
							user[0].DrunkState += Inv1->Item[i].DrunkLevel;
						}
					}
				}
			}
			if (dbMouseClick()==0)
			{
				Inv1->ClickTimer = false;
			}

			if (dbKeyState(24))
			{
				Inv1->IsDisplayed = false;
			}
		}

		//get the angle y of player at start of the loop for the camera
		user[0].OldAngleY = dbObjectAngleY(user[0].SphereNum);

		dbPositionMouse(300,300);

		//reset the noncollisioncount variable
		user[0].railcollisioncount = 0;
	
		

		//decrease the trick timer and check if the user should get points
		if (user[0].tricktimer > 0)
		{
			user[0].tricktimer--;
			if (user[0].tricktimer == 1)
			{
				user[0].tricktimer--;
				user[0].experience += 10*user[0].pointsmultiplier;
				
					user[0].combocounter++;
				
			}
		}

		//increase the multiplier every 3 combos
		for (int s=1;s<10;s++)
		{
			if (user[0].combocounter == s*3)
			{
				user[0].pointsmultiplier = s+1;
			}
		}

		for (int i = 0;i < 4;i++)
		{
			if (dbMusicPlaying(user[0].Voice[i].id)==0)
			{
				dbStopMusic(user[0].Voice[i].id);
			}
		}
		//if the user is doing a trick and touches the ground then the user is not doing a trick
		if (user[0].doingtrick == true && user[0].ground == 1)
		{
			user[0].anim.trick = false;
			user[0].doingtrick = false;
		}

		//if you have done a grinding jump and touched the ground, yo arent doing a grinding jump anymore
		if (user[0].ground == 1 && user[0].grindingjump == true)
		{
			user[0].grindingjump = false;
		}

		if (user[0].grindingjump == false && user[0].boosttimer == 0)
		{
			user[0].topspeed = 0.3;
		}

		//Check if player is close to a pedestrian
		for (int i=0;i<numberofpedestrians;i++)
		{
			if (Get3DDistance(user[0].SphereNum,Pedestrian[i].id) < 10)
			{
				PedestrianAI(Pedestrian[i].id,user[0].SphereNum);
				//dbYRotateObject(Pedestrian[i].id,dbRnd(360));
				//dbMoveObject(Pedestrian[i].id,3);
			}
		}

		//Check if right mouse button is pressed for boosting
		if (dbMouseClick()==2)
		{
			//if the player isn't already boosting
			if (user[0].boosttimer == 0)
			{
				user[0].boosttimer = 200;
				user[0].topspeed = user[0].boostspeed;
				user[0].speed = user[0].topspeed;
			}
		}

		//Decrease the boost timer
		if (user[0].boosttimer > 0)
		{
			user[0].boosttimer--;
			//if the boosttimer gets to 0 set the user's speed back to normal
			if (user[0].boosttimer == 0)
			{
				user[0].anim.boost == true;
				user[0].topspeed = 0.3;
				user[0].speed = user[0].topspeed;
			}
			else
			{
				//boost anim
				user[0].anim.boost == true;
				//keep the player's speed at the boost speed
				user[0].topspeed = user[0].boostspeed;
				user[0].speed = user[0].boostspeed;
				user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].speed); 
				user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].speed);
			}
		}

			//set the speed to boosting speed
	
		//lock the mouse cursor
		//dbPositionMouse(300,300);

		//if the user is on the ground and not grinding and not boosting set the top speed back to normal 
		if (user[0].ground == 1 && user[0].grinding == 0 && user[0].boosttimer == 0)
		{
			user[0].topspeed = 0.3;
		}

		//if the user is over the top speed then decrease the user's speed
		if (user[0].speed > user[0].topspeed)
		{
			user[0].speed -= user[0].decel;
			//if the user's speed goes lower than the top speed then set it to the top speed
			if (user[0].speed < user[0].topspeed)
			{
				user[0].speed = user[0].topspeed;
			}
		}
	
		

		//decrease the TrackTimer if it is greater than 0
		if (Music.TrackTimer > 0)
		{
			Music.TrackTimer--;
		}

		//Get the song selection
		//Change songs with left and right arrow keys
		if (Music.TrackTimer <= 0)
		{
			if (dbLeftKey())
			{
				int OldSong = Music.SongSelect-1;
				Music.TrackTimer = Music.TrackTimerTime;
				//Decrease track number
				Music.SongSelect--;
				//Keep the song selection within the range of songs
				//If the track number is smaller than 1 then the highest track is selected
				if (Music.SongSelect < 1)
				{
					Music.SongSelect = Music.Songs;
				}
				if (Music.SongSelect > Music.Songs)
				{
					Music.SongSelect = 1;
				}
				//Load the new track and delete the old one
				//dbLoadMusic(Music.Background[Music.SongSelect-1].filedir,Music.Background[Music.SongSelect-1].id);
				dbStopMusic(Music.Background[OldSong].id);
				dbDeleteMusic(Music.Background[OldSong].id);
				Music.Background[Music.SongSelect-1].id = FMus();
				dbLoadMusic(Music.Background[Music.SongSelect-1].filedir,Music.Background[Music.SongSelect-1].id);
				//dbLoopMusic(Music.Background[Music.SongSelect-1].id);
				dbPlayMusic(Music.Background[Music.SongSelect-1].id);
				dbLoopMusic(Music.Background[Music.SongSelect-1].id);
			}
			if (dbRightKey())
			{
				int OldSong = Music.SongSelect-1;
				Music.TrackTimer = Music.TrackTimerTime;
				//Decrease track number
				Music.SongSelect++;
				//Keep the song selection within the range of songs
				//If the track number is greater than the amount of songs then track 0 is selected
				if (Music.SongSelect < 1)
				{
					Music.SongSelect = Music.Songs;
				}
				if (Music.SongSelect > Music.Songs)
				{
					Music.SongSelect = 1;
				}
				//dbLoadMusic(Music.Background[Music.SongSelect-1].filedir,Music.Background[Music.SongSelect-1].id);
				dbStopMusic(Music.Background[OldSong].id);
				dbDeleteMusic(Music.Background[OldSong].id);
				Music.Background[Music.SongSelect-1].id = FMus();
				dbLoadMusic(Music.Background[Music.SongSelect-1].filedir,Music.Background[Music.SongSelect-1].id);
				//dbLoopMusic(Music.Background[Music.SongSelect-1].id);
				dbPlayMusic(Music.Background[Music.SongSelect-1].id);
				dbLoopMusic(Music.Background[Music.SongSelect-1].id);
			}
		}
		//dbPrint(dbStr(Music.SongSelect));
		
		//if the player can do a trick - if they are going fast enough
		if (user[0].speed >= user[0].grindspeed && user[0].topspeed >= user[0].grindspeed)
		{
			user[0].trickavailable = true;
		}
		else
		{
			user[0].trickavailable = false;
		}

		for (int x=0;x<lvl[0].numberofrails;x++)
		{
			dbText(200,0,dbStr(user[0].grinding[x]));
			if (user[0].grinding[x] == 0)
			{
				//reset the rotations
				dbXRotateObject(user[0].SphereNum,0);
				dbZRotateObject(user[0].SphereNum,0);
			}
		}
		for (int x=0;x<lvl[0].numberofrails;x++)
		{
			if (user[0].grinding[x] == 1 || user[0].grinding[x] > 2)
			{
				if (SC_ObjectCollision(user[0].SphereNum,GrindRail[x].id))//(SC_SphereCast(GrindRail[x].id, user[0].oldx,user[0].oldy,user[0].oldz,user[0].oldx,user[0].oldy,
					//user[0].oldz,user[0].radius,53465 )>0)//(SC_ObjectCollision(user[0].id,GrindRail[x].id))
				{
					dbSetObjectToObjectOrientation(user[0].SphereNum,GrindRail[x].id);
					dbMoveObject(user[0].SphereNum,user[0].topspeed);
					//dbYRotateObject(user[0].id,dbWrapValue(dbObjectAngleY(user[0].id)+180));
					user[0].speed = user[0].grindspeed;
					user[0].topspeed = user[0].grindspeed;
					if (user[0].combocounted == false)
					{
						user[0].combocounter++;
						user[0].combocounted = true;
						user[0].wasintheair = 0;
					}
					/*
					if (user[0].wasintheair == 1 && user[0].tricktimer == 0)
					{
							user[0].combocounted == false;
						//{
							user[0].wasintheair = false;
							//user[0].combocounted = true;
							user[0].combocounter ++;
						//}
					}*/
					//if user is grinding then tricktimer = 16
					user[0].tricktimer = 16;
					
				}
			}
			else if (user[0].grinding[x] == 2)
			{
				if (SC_ObjectCollision(user[0].SphereNum,GrindRail[x].id))//(SC_SphereCast(GrindRail[x].id, user[0].oldx,user[0].oldy,user[0].oldz,user[0].oldx,user[0].oldy,
					//user[0].oldz,user[0].radius,0 ))//(SC_ObjectCollision(user[0].id,GrindRail[x].id))
				{
					dbSetObjectToObjectOrientation(user[0].SphereNum,GrindRail[x].id);
					dbMoveObject(user[0].SphereNum,-user[0].topspeed);
					dbYRotateObject(user[0].SphereNum,dbWrapValue(dbObjectAngleY(user[0].SphereNum)+180));
					user[0].speed = user[0].grindspeed;
					user[0].topspeed = user[0].grindspeed;
					if (user[0].combocounted == false)
					{
						user[0].combocounter++;
						user[0].combocounted = true;
						user[0].wasintheair = 0;
					}
					/*
					if (user[0].wasintheair == 1 && user[0].tricktimer == 0)
					{
							user[0].combocounted == false;
						//{
  							user[0].wasintheair = false;
							//user[0].combocounted = true;
							user[0].combocounter ++;
						//}
					}*/
					//if user is grinding then tricktimer = 16
					user[0].tricktimer = 16;
					
				}
			}
			
			else if (user[0].ground == 1)
				{
					if (user[0].combocounter > 0)
					{
						if (user[0].grindingtotal < 1)
						{
							//if (user[0].combocountdepletetimer == 0)
							//{
								//if (user[0].wasintheair == true)
								//{
									for (int o = 0;o<lvl[0].numberofrails;o++)
									{
										if (SC_ObjectCollision(user[0].SphereNum,GrindRail[o].id)==1)
										{
											user[0].railcollisioncount += 1;
										}
									}
									if (user[0].railcollisioncount == 0)
									{
										user[0].combocounter = 0;
										user[0].pointsmultiplier = 1;
										user[0].combocounted = false;
										user[0].wasintheair = false;
									}
								//}
							/*}/*
							else if (user[0].combocountdepletetimer > 0)
							{
								user[0].combocountdepletetimer--;
							}
 							else
							{
								user[0].combocountdepletetimer = 20;
							}*/
						}
					}
					/*
					if (user[0].grindingtotal > 1)
					{
						if (user[0].combocountdepletetimer == 0)
						{
							user[0].combocounter = 0;
							user[0].pointsmultiplier = 1;
							user[0].combocounted = false;
							user[0].wasintheair = false;
						}
						else if (user[0].combocountdepletetimer > 0)
						{
							user[0].combocountdepletetimer--;
						}
 						else
						{
							user[0].combocountdepletetimer = 10;
						}
					}
					*/
				}
			
		}
			
		
		if (user[0].grindingjump == true)
		{
			user[0].speed = user[0].grindspeed;
		}
		//quick check to make sure the player needs a direction
		for (int x=0;x<lvl[0].numberofrails;x++)
		{
			if (user[0].grinding[x] == 0)
			{
				
					if (SC_ObjectCollision(user[0].SphereNum,GrindRail[x].id)==1)
					{
						user[0].grinding[x] = Grind(user[0].SphereNum,GrindRail[x].id);
						user[0].wasintheair = 0;
					}
					else
					{
						user[0].grinding[x] = 0;
					}
				
				
			}
			else if (SC_ObjectCollision(user[0].SphereNum,GrindRail[x].id)==0)
			{
				user[0].grinding[x] = 0;
			}
		}

		//Work out the grinding total - if the player is grinding
		for (int x = 0;x<lvl[0].numberofrails;x++)
		{
			user[0].grindingtotal += user[0].grinding[x];
		}
		
		//if the user is in the air and not pulling a trick
		if (user[0].ground == 0)
		{
			//if they are not boosting
			if (user[0].boosttimer == 0)
			{
				//set the jump anim variable
				user[0].anim.jump = true;
				//set the other anim vars to false
				user[0].anim.runforward = false;
				user[0].anim.boost = false;
			}
			else
			{
				//play boost
				user[0].anim.boost = true;
			}
		}

		//pulling a trick
		//if the user is in the air
		if (user[0].ground == 0)
		{
			//if left ctrl is pressed
			if (user[0].doingtrick == false)
			{
				if (user[0].trickavailable == 1)
				{
					user[0].wasintheair = true;
					user[0].doingtrick = true;
					user[0].anim.trick = true;
					//set the trick timer
					user[0].tricktimer = 16;
					//increase the score and player's experience
					//user[0].score += 50;
					dbPlayMusic(user[0].Voice[dbRnd(3)].id);
				}
			}
		}
		else
		{
			user[0].anim.trick = false;
		}

		//apply rotation to spray cans
		/*
		for (int z=0;z<numberofspraycans;z++)
		{
			//if the spray can is there
			if (dbObjectExist(yellowspraycan[z].id)==1)
			{
				dbYRotateObject(yellowspraycan[z].id,dbObjectAngleY(yellowspraycan[z].id)+1);
			}
		}
		//////////////////////////////
*/
		
		
		//if the inventory is closed and there are no shops open then render the non inventory text and the
		//health bar
		if (Inv1->IsDisplayed == false && NumberOfShopsOpen == 0)
		{
			ExperienceDisplayString = dbStr(user[0].experience);
			strcat(ExperienceDisplayString,"/");
			strcat(ExperienceDisplayString,dbStr(user[0].experiencetolevel));
			ComboDisplayString = dbStr(user[0].combocounter);
			strcat(ComboDisplayString," Trick Combo");
			StartText();
			AAText(1,0,448,0,ExperienceDisplayString);
			AAText(1,0,16,0,dbStr(user[0].spraycans));
			AAText(1,0,35,0,ComboDisplayString);
			AAText(1,0,100,dbStr(dbScreenFPS()));
			AAText(1,0,40,dbStr(dbObjectPositionX(user[0].id)));
			AAText(0,0,60,dbStr(dbObjectPositionY(user[0].id)));
			AAText(0,0,80,dbStr(dbObjectPositionZ(user[0].id)));
			EndText();
			//draw health bar
			for (int a = 0; a<user[0].currenthealth;a++)
			{
				for (int b = 0;b<10;b++)
				{
					d3d_dot(a,b,255,255,0,255);
				}
			}
			//if lost health draw the black bit of the health bar
			if (user[0].currenthealth < user[0].maxhealth)
			{
				for (int a = user[0].currenthealth;a<user[0].maxhealth;a++)
				{
					for (int b = 0;b<10;b++)
					{
						d3d_dot(a,b,1,1,1,255);
					}
				}
			}	
		}

		
		//rotate camera
		
		user[0].oldx = dbObjectPositionX(user[0].SphereNum);
		user[0].oldy = dbObjectPositionY(user[0].SphereNum); 
		user[0].oldz = dbObjectPositionZ(user[0].SphereNum);
		
		//apply gravity, and user changes to movement
		user[0].angy = dbObjectAngleY(user[0].SphereNum);
		user[0].vx = 0;
		user[0].vz = 0;

		//if player is jumping or falling then apply 'normal' gravity
		//if not attempt to keep the player stuck to the floor
		if ( user[0].vy == 0 && user[0].jumptimer == 0 ) user[0].vy = user[0].vy + 10*user[0].gravity; 
		else user[0].vy = user[0].vy + user[0].gravity;

		
			if (user[0].grindingtotal == 0)
			{
				//if freecam is off
				if (user[0].FreeCam == false)
				{
					dbYRotateObject(user[0].SphereNum,dbObjectAngleY(user[0].SphereNum) + dbMouseMoveX()/5.5f );
				}
			if (dbKeyState(32)+dbKeyState(30)+dbKeyState(31)+dbKeyState(17)+dbKeyState(23)+dbKeyState(24) > 0)
			{
					if (user[0].ground == 0)
					{
						if (dbKeyState(23))
						{
							user[0].vx = user[0].vx - (TIMERUPDATE/40)*dbCos(user[0].angy); user[0].vz = user[0].vz + (TIMERUPDATE/40)*dbSin(user[0].angy);
						}
						if (dbKeyState(24))
						{
							user[0].vx = user[0].vx + (TIMERUPDATE/40)*dbCos(user[0].angy); user[0].vz = user[0].vz - (TIMERUPDATE/40)*dbSin(user[0].angy);
						}
					}
					if (dbKeyState(32) == 1 ) 
					{
						dbYRotateObject(user[0].SphereNum, dbObjectAngleY(user[0].SphereNum)+3); 
					}
					if (dbKeyState(30) == 1 ) 
					{ 
						dbYRotateObject(user[0].SphereNum, dbObjectAngleY(user[0].SphereNum)-3);  
					}
					//powerbrake only on ground
					
					if (dbKeyState(31) == 1 ) 
					{
						if (user[0].ground == 1)
						{
							//if speed is higher than zero then break
							if (user[0].speed > 0)
							{
								user[0].speed = 0;
								//rotate the player 180 degree
								//dbYRotateObject(user[0].id,dbObjectAngleY(user[0].id)+180);
								//if the player is boosting stop boosting
								if (user[0].boosttimer > 0)
								{
									user[0].boosttimer = 0;
								}
								if (user[0].speed < 0)
								{
									user[0].speed = 0;
								}
								user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].speed); 
								user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].speed);
									user[0].topspeed = 0.3;
								
							}
						}
					}
					

					if (dbKeyState(17) == 1 && user[0].boosttimer == 0) 
						{	
							//activate running animation if on the ground else don't
							if (user[0].ground == 1)
							{
								user[0].anim.runforward = true;
								//deactivate other animations
								user[0].anim.jump = false;
								user[0].anim.trick = false;
								user[0].anim.boost = false;
							}

							//if speed is lower than max speed than accelerate
							if (user[0].speed < user[0].topspeed)
							{
								user[0].speed = user[0].speed + user[0].accel;
							}
							user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].speed); 
							user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].speed);
						}
					else if (user[0].boosttimer > 0)
					{
						//keep the player's speed at the boost speed
						user[0].topspeed = user[0].boostspeed;
						user[0].speed = user[0].boostspeed;
						user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].boostspeed); 
						user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].boostspeed);
					}
					
				}
			}

			//if boosting ( and not pressing foward) MAKE SURE the player moves forward (BUGFIX)
			if (dbKeyState(17)==0)
			{
				if (user[0].boosttimer > 0)
				{
					//keep the player's speed at the boost speed
					user[0].topspeed = user[0].boostspeed;
					user[0].speed = user[0].boostspeed;
					user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].boostspeed); 
					user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].boostspeed);
				}
			}
	
		
		
			for (int a = 0; a < lvl[0].numberofrails;a++)
			{
				if (dbKeyState(17) == 0 && user[0].boosttimer == 0)
				{
					//decel (only on ground)
					//if (user[0].ground == 0)
					//{
						if (user[0].speed > 0)
						{
							user[0].speed = user[0].speed - user[0].decel;
							user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].speed); 
							user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].speed); 
						}
					//}
						if (user[0].speed <= 0 && user[0].anim.runforward == true)
						{
							user[0].anim.runforward = false;
						}
				}
				else if (SC_ObjectCollision(user[0].SphereNum,GrindRail[a].id)==1)
				{
					if (user[0].speed > 0)
						{
							user[0].speed = user[0].speed - user[0].decel;
							user[0].vx = user[0].vx + (TIMERUPDATE/10)*(dbSin(user[0].angy)*user[0].speed); 
							user[0].vz = user[0].vz + (TIMERUPDATE/10)*(dbCos(user[0].angy)*user[0].speed); 
						}
					//}
						if (user[0].speed <= 0 && user[0].anim.runforward == true)
						{
							user[0].anim.runforward = false;
						}
				}
			}

			//only jump if on ground, and a certain time after last jump
		

		
			if ( user[0].ground == 1 || user[0].grindingtotal > 0 ) 
			{
				if ( dbSpaceKey() == 1 && user[0].jumptimer == 0 ) 
				{
					for (int i=0;i<lvl[0].numberofrails;i++)
					{
						if (SC_ObjectCollision(user[0].SphereNum,GrindRail[i].id))
						{
							user[0].grindingjump = true;
							user[0].combocounted = false;
						}
					}
					if (user[0].boosttimer == 0)
					{
						user[0].vy += 1.3;//1.5;
					}
					else
					{
						user[0].vy += 1.6;
					}
					user[0].jumptimer = 1;
				}
			}

			//if the user is not in the air
			if (user[0].ground == 1)
			{
				//calculate the height the jump was started
				user[0].jumpstartY = dbObjectPositionY(user[0].SphereNum);
			}

			//if the user is in the air
			if (user[0].ground == 0 && user[0].fallheightisdangerous == false)
			{
				user[0].jumplandY = dbObjectPositionY(user[0].SphereNum);
				user[0].jumpfalldistY = user[0].jumpstartY - user[0].jumplandY;
				//if the player has fallen to far
				if (user[0].jumpfalldistY > 30)
				{
					user[0].fallheightisdangerous = true;
				}
			}

			//dbPlayMusic(SFX.Sound[FallingHeight].id);
			//dbLoopMusic(SFX.Sound[FallingHeight].id);

			//if the users fall height is dangerous
			if (user[0].fallheightisdangerous == true)
			{
				//play the falling sound
				dbSetMusicVolume(SFX.Sound[FallingHeight].id,300);
				dbPlayMusic(SFX.Sound[FallingHeight].id);
				dbLoopMusic(SFX.Sound[FallingHeight].id);
				//if the user hits the ground
				if (user[0].ground == 1)
				{
					//the fall height isnt dangerous anymore
					user[0].fallheightisdangerous = false;
					//player gets hurt
					user[0].currenthealth -= 10;
					//falling sound stops
					dbStopMusic(SFX.Sound[FallingHeight].id);
				}
			}
		
			
			//this would be the player's final position without collision
			user[0].x = user[0].oldx + user[0].vx;
			user[0].y = user[0].oldy + user[0].vy;
			user[0].z = user[0].oldz + user[0].vz;
			
			//if (user[0].grinding[x] == 0)
				//{
			user[0].collide = SC_SphereCastGroup( 1, user[0].oldx,user[0].oldy,user[0].oldz,user[0].oldx,user[0].oldy+user[0].vy,user[0].oldz,user[0].radius,0 );
			
			
			if ( user[0].collide > 0 )
			{
				//how flat is this ground
				user[0].ny = SC_GetCollisionNormalY();
				if ( dbAbs(user[0].ny) > user[0].slope )
				{
					//FLAT, stick
					user[0].oldy = SC_GetStaticCollisionY();
				}
				else
				{
					//STEEP, slide
					user[0].x = user[0].x - user[0].oldx; user[0].z = user[0].z - user[0].oldz;
					user[0].oldx = SC_GetCollisionSlideX();
					user[0].oldy = SC_GetCollisionSlideY();
					user[0].oldz = SC_GetCollisionSlideZ();
					user[0].x = user[0].x + user[0].oldx; user[0].z = user[0].z + user[0].oldz;
				}
				
				//ny#<0 means the player has hit a ceiling rather than a floor
				
				if ( user[0].ny > user[0].slope )
				{
					//only on ground if standing on flat ground
					user[0].ground = 1;
					user[0].vy = 0;
				}
				else 
				{
					user[0].ground = 0;
					//if player has hit a flat ceiling then stop vy# movement
					if ( user[0].ny < -user[0].slope ) user[0].vy = user[0].gravity;
				}
			}
			else
			{
				
					//nothing below player, not on ground, add vertical speed to player
					user[0].oldy = user[0].oldy + user[0].vy;
					user[0].ground = 0;
				
			}
			//}
			
			//jumptimer will decrease only when player is back on ground
			//creates a pause between two successive jumps
			if ( user[0].ground == 1 && user[0].jumptimer > 0 ) 
			{
				user[0].jumptimer -= 0.5;
			}
			//handle horizontal movement as sliding
			//player only collides with group 1 (level) objs and moves freely through others
			user[0].collide = SC_SphereSlideGroup( 1, user[0].oldx,user[0].oldy,user[0].oldz,user[0].x,user[0].oldy,user[0].z,user[0].radius,0 );

			if ( user[0].collide > 0 )
			{
				//if hit, reposition player, halt movement vector
				user[0].x = SC_GetCollisionSlideX();
				user[0].oldy = SC_GetCollisionSlideY();
				user[0].z = SC_GetCollisionSlideZ();
				user[0].vx = 0;
				user[0].vz = 0;
			}

			//position the player
			dbPositionObject(user[0].SphereNum,user[0].x,user[0].oldy,user[0].z );
		
			user[0].FreeCam = UpdateTheCamera(user[0].SphereNum);
		//get the change in the players y angle since the start of the loop
			//user[0].ChangeInAngleY = dbWrapValue(dbObjectAngleY(user[0].id) - user[0].OldAngleY);

		//dbSetCameraToFollow(dbObjectPositionX(user[0].id),dbObjectPositionY(user[0].id),dbObjectPositionZ(user[0].id),0,-2,dbObjectPositionY(user[0].id)+3,1,0);

		

		//FINAL CHECK FOR BOOSTING ANIM
		if (user[0].boosttimer > 0 && user[0].anim.trickplaying == false)
		{
			user[0].anim.boost = true;
		}
		else
		{
			user[0].anim.boost = false;
		}

		if (user[0].anim.runforward == true)
		{
			//set the anim speed
			dbSetObjectSpeed(user[0].id,50);
			//loop the anim
			dbLoopObject(user[0].id,32,58);
			//set the anim as playing
			user[0].anim.runforwardplaying = true;
		}

		if (user[0].anim.boost == true)
		{
			//set the anim speed
			dbSetObjectSpeed(user[0].id,50);
			//loop the anim
			dbLoopObject(user[0].id,144,144);
			//dbSetObjectFrame(user[0].id,148);
			//set the anim as playing
			user[0].anim.boostplaying = true;
		}

		if (user[0].anim.jump == true)
		{
			//set the anim speed
			dbSetObjectSpeed(user[0].id,10);
			//loop the anim
			dbPlayObject(user[0].id,60,64);
			//if (dbObjectFrame(user[0].id)==64)
			//{
				//dbSetObjectFrame(user[0].id,64);
			//}
			//set the anim as playing
			user[0].anim.jumpplaying = true;
		}

		if (user[0].anim.trick == true)
		{
			//randomize the trick (3 tricks)
			if (user[0].TrickSelect == 0)
			{
				user[0].TrickSelect = dbRND(1);
				user[0].TrickSelect++;
		    }
			//set the anim speed
			dbSetObjectSpeed(user[0].id,1);
			//loop the anim
			if (user[0].TrickSelect == 1)
			{
				dbLoopObject(user[0].id,66,74);
			}
			else if (user[0].TrickSelect == 2)
			{
				dbPlayObject(user[0].id,90,97);
			}
			//set the anim as playing
			user[0].anim.trickplaying = true;
		}
		else
		{
			user[0].TrickSelect = 0;
		}

		//dbPrint(dbStr(user[0].TrickSelect));

		if (user[0].ground == 1)
		{
			user[0].anim.jump = false;
		}

		if (user[0].anim.runforward == false && user[0].anim.runforwardplaying == true)
		{
			user[0].anim.runforwardplaying = false;
			dbSetObjectSpeed(user[0].id,20);
			//Loop the dance
			dbLoopObject(user[0].id,1,29);
		}

		if (user[0].anim.jump == false && user[0].anim.jumpplaying == true)
		{
			user[0].anim.jumpplaying = false;
			dbSetObjectSpeed(user[0].id,20);
			//Loop the dance
			dbLoopObject(user[0].id,1,29);
		}		

		if (user[0].anim.trick == false && user[0].anim.trickplaying == true)
		{
			user[0].anim.trickplaying = false;
			dbSetObjectSpeed(user[0].id,20);
			//Loop the dance
			dbLoopObject(user[0].id,1,29);
		}	

		if (user[0].anim.boost == false && user[0].anim.boostplaying == true)
		{
			user[0].anim.boostplaying = false;
			dbSetObjectSpeed(user[0].id,20);
			//Loop the dance
			dbLoopObject(user[0].id,1,29);
		}

		//numberofspraycans = lvl[0].spraycans;
		//if player collides with a graffiti can 
		for (int g=0;g<numberofspraycans;g++)
		{
			if (dbObjectExist(yellowspraycan[g].id)==1)
			{
				if(Get3DDistance(user[0].SphereNum,yellowspraycan[g].id)<6)
				//if (SC_ObjectCollision(user[0].id,yellowspraycan[x].id)==1)
				{
					//set he 
					dbDeleteObject(yellowspraycan[g].id);
					//increase players cans by 1 
					user[0].spraycans++;
				}
			}
		}

		for (int n =0;n<numberofgraffitiplanes;n++)
		{
			//Check if close to a graffiti object
			if (Get3DDistance(user[0].SphereNum,GraffitiPlane[n].objid)<5)
			{
				//If the left mouse button is pressed
				if (dbMouseClick()==1)
				{
					if (GraffitiPlane[n].size == 3)
					{
						//if player has enough cans
						if (user[0].spraycans > 0)
						{
							if (GraffitiPlane[n].spraystage < 3)
							{
								//Player loses a spray can
								user[0].spraycans--;
								//SprayStage goes up
								GraffitiPlane[n].spraystage++;
								dbTextureObject(GraffitiPlane[n].objid,user[0].GraffitiMedium.imgid[GraffitiPlane[n].spraystage-1]);
							}
						}
					}
					if (GraffitiPlane[n].size == 5)
					{
						//if player has enough cans
						if (user[0].spraycans > 0)
						{
							if (GraffitiPlane[n].spraystage < 5)
							{
								//Player loses a spray can
								user[0].spraycans--;
								//SprayStage goes up
								GraffitiPlane[n].spraystage++;
								dbTextureObject(GraffitiPlane[n].objid,user[0].GraffitiLarge.imgid[GraffitiPlane[n].spraystage-1]);
							}
						}
					}
				}
			}
		}

		//position the grind particles at the players feet
		//dbPositionParticles(user[0].grindparticlesid,dbObjectPositionX(user[0].id),dbObjectPositionY(user[0].id),dbObjectPositionZ(user[0].id));

		TIMERUPDATE = tm_update();
		//Set the user grinding total variable back to zero so on next loop it can do a fresh count
		user[0].grindingtotal = 0;

		//position the sphere at the plr everyloop
		dbPositionObject(user[0].id,dbObjectPositionX(user[0].SphereNum),dbObjectPositionY(user[0].SphereNum),dbObjectPositionZ(user[0].SphereNum));
		dbRotateObject(user[0].id,dbObjectAngleX(user[0].SphereNum),dbObjectAngleY(user[0].SphereNum),dbObjectAngleZ(user[0].SphereNum));

		SC_UpdateObject(user[0].SphereNum);
		dbSync( );
	}
}