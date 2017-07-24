	struct wallrideboard
	{
		int objid;
		char* imgdir;
		bool ridden;
		int posx,posy,posz;
		int rotx,roty,rotz;
		int scax,scay,scaz;
		int timer;
		int backobjid;
	};

	struct graffitiplane
	{
		int objid;
		char* objdir;
		char* imgdir;
		int imgid[10];
		int size; //the size of the graffiti, maximum 10
		int stage[10]; //the fade stage of the graffiti plane (10 requires 10 spray cans, maybe have a fade image thing?
		int spraystage; //how many times it has been sprayed
		int posx,posy,posz;
	};

	struct graffititexturesmall
	{
		char* imgdir;
		int imgid[1];
		int size; //the size of the graffiti, maximum 10
		int stage[1]; //the fade stage of the graffiti plane (10 requires 10 spray cans, maybe have a fade image thing?
		//char* alphaimagedir[6]; // low number image is very faded, high number isnt
	};

	struct graffititexturemedium
	{
		char* imgdir[3];
		int imgid[3];
		int size; //the size of the graffiti, maximum 10
		int stage[3]; //the fade stage of the graffiti plane (10 requires 10 spray cans, maybe have a fade image thing?
		//char* alphaimagedir[6]; // low number image is very faded, high number isnt
	};

	struct graffititexturelarge
	{
		char* imgdir[5];
		int imgid[5];
		int size; //the size of the graffiti, maximum 10
		int stage[5]; //the fade stage of the graffiti plane (10 requires 10 spray cans, maybe have a fade image thing?
		//char* alphaimagedir[6]; // low number image is very faded, high number isnt
	};

	struct graffititexturexlarge
	{
		char* imgdir;
		int imgid[10];
		int size; //the size of the graffiti, maximum 10
		int stage[10]; //the fade stage of the graffiti plane (10 requires 10 spray cans, maybe have a fade image thing?
		//char* alphaimagedir[10]; // low number image is very faded, high number isnt
	};

	struct LEVEL
	{
		int id;
		int numberofrails;
		int spraycans;
		int numberofwallrides;
	};

//skater animation
	struct ANIM
	{
		bool runforward;
		bool runforwardplaying;
		bool jump;
		bool jumpplaying;
		bool trick;
		bool trickplaying;
		bool boost; 
		bool boostplaying;
	};

	struct background 
	{
		int id;
		char* filedir;
		char* SongName;
		char* SongArtist;
		char* SongSecondArtist;
	};
	struct music
	{
		int SongSelect;
		int Songs;
		int TrackTimer;
		int TrackTimerTime;
		background Background[7];
	};

		//Spray cans
	struct SprayCan
	{
		int id;
		float posx;
		float posy;
		float posz;
		bool usedup;
		int texid;
	};

	struct grindrail
	{
		int id;
		float posx;
		float posy;
		float posz;
		float rotx;
		float roty;
		float rotz;
		float sizx;
		float sizy;
		float sizz;
	};

	struct sound
	{
		int id;
		char* filedir;
	};

	struct sfx
	{
		sound Sound[1];
	};

	struct pedestrian
	{
		int id;
		char* filedir;
	};

	
	//player
	class actor
	{
	public:
		float OldAngleY;
		float ChangeInAngleY;
		bool FreeCam;
		int wallriding[5];
		int wallridingtotal;
		int wallridecollisioncount;
		int grinding[5];
		int grindingtotal;
		float xrotation,yrotation,zrotation;
		unsigned long tm_last;
		int tm_difference;
		float tm_factor;
		float tm_result;
		unsigned long tm_timer;
		float sx;
		float sz;
		int id;
		int tex;
		int gunlimb;
		int gunmesh;
		int rtimer;
		int stimer;
		int vtimer;
		float gravity;
		float slope;
		int ground;
		int jumptimer;
		float vx;
		float vy;
		float vz;
		float x;
		float y;
		float z;
		float angy;
		float radius;
		int collide;
		float ny;
		float oldx;
		float oldy;
		float oldz;

		float speed;
		float topspeed;
		float grindspeed;
		float boostspeed;
		float accel;
		float decel;
		float powerbrake;

		int boosttimer;

		//tricks
		bool trickavailable;
		bool doingtrick;

		int spraycans;

		int grindparticlesid;
		int grindparticlesimage;

		//experience + leveling
		int level;
		int experience;
		int experiencetolevel;
		int score;

		//animation
		ANIM anim;

		//grinding jump
		bool grindingjump;

		//graffiti
		graffititexturesmall GraffitiSmall;
		graffititexturemedium GraffitiMedium;
		graffititexturelarge GraffitiLarge;
		graffititexturexlarge GraffitiXLarge;

		//to calculate falling height
		float jumpstartY;
		float jumplandY;
		float jumpfalldistY;
		bool fallheightisdangerous;

		//health
		int maxhealth;
		int currenthealth;

		//voice fx
		sound Voice[5];

		//score/points
		int combocounter;
		int pointsmultiplier;
		int combocounted;
		int wasintheair;
		int tricktimer;
		int TrickSelect;

		//railcollisioncount
		int railcollisioncount;

		//timer update
		float TimerUpdate;

		int DrunkState;

		float turnspeed;

		int SphereNum;
	};