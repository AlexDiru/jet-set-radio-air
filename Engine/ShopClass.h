class cShop
{
public:
	int ID;
	bool Item[100]; //if item[x] = true then it is sold, if false it isn't sold
	int ItemList;

	bool ClickTimer;//so the user doesn't buy loads of an item with just one click

	//Shop Pos
	float XPos,YPos,ZPos;
	//Shop entrance radius - how close you have to be to enter
	float EntranceRadius;
	bool IsOpen; //if the player is in the shop

	int ImageID;

	void SetPos(float X,float Y, float Z) { XPos = X; YPos = Y; ZPos = Z; }
	bool InRange(int userobj) 
	{
		float del;
		float X,Y,Z;
		float deltaX = XPos - dbObjectPositionX(userobj);
		float deltaY = YPos - dbObjectPositionY(userobj);
		float deltaZ = ZPos - dbObjectPositionZ(userobj);

		X = deltaX*deltaX;
		Y = deltaY*deltaY; 
		Z = deltaZ*deltaZ;
		
		del = X+Y+Z;

		del = dbSqrt(del);

		if (del < EntranceRadius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

bool ManageShop(cShop Shop,Inventory *Inv1,std::list<Inventory*> ilist, actor user)
{
	/* SHOP
			*/
		if (Shop.IsOpen == false)
		{
			if (Shop.InRange(user.id) == true)
			{
				if (dbDownKey() == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		if (Shop.IsOpen == true)
		{
			dbShowMouse();
			//Display the shop
			dbCLS();
			dbPasteImage(Shop.ImageID,0,0);
			//Shop.ItemList = 0;
			for (int i = 0;i<10;i++)
			{
				if (Shop.Item[i] == true)
				{
					//then item i is sold in the shop
					for(std::list<Inventory*>::iterator k = ilist.begin() ; k != ilist.end() ; k++)
					{
						dbText(0,Shop.ItemList*12,(*k)->Item[i].Name);
						if (dbMouseY() > Shop.ItemList*12 && dbMouseY() < Shop.ItemList*12+12)
						{
							if (dbMouseClick() && Shop.ClickTimer == false)
							{
								(*k)->AddItem(i,1);
								Shop.ClickTimer = true;
							}
							else if (dbMouseClick() == 0)
							{
								Shop.ClickTimer = false;
							}
						}
						Shop.ItemList++;
					}
				}
			}
			Shop.ItemList = 0;
			if (dbUpKey())
			{
				return false;
			}
		}
}