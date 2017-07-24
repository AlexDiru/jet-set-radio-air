struct Item
{
	int ID; // a numerical value for the array ID of the item
	int Amount; // the amount of the item the inventory holds
	char* Name; // an alphanumeric name for the item
	int DrunkLevel; //how much it adds to your drunk level
	int HealthBonus; // health bonus for the item (can be +ve or -ve)
};

class Inventory
{
  public:
     Inventory() { }

	 Item Item[100];

  int Gold;
  bool IsDisplayed; //if the inv is displayed
  bool ClickTimer; //so the user doesnt use loads of items at once
  int ItemList; //so all items are displayed
	
  //void Display()

  //Gold functions
  void AddGold(int AmountToAdd) { Gold += AmountToAdd; }
  void SubtractGold(int AmountToTake) { Gold -= AmountToTake; }
  bool CanAfford(int Amount) { if (Gold >= Amount) { return true; } else { return false; } }
  void DisplayGold() { std::cout << Gold << std::endl; }

  //Item functions
  void CreateItem(int ID, char* Name, int HealthBonus, int DrunkLevel) { Item[ID].ID = ID; Item[ID].Name = Name; Item[ID].HealthBonus = HealthBonus; Item[ID].DrunkLevel = DrunkLevel; }
  void AddItem(int itemID, int AmountToAdd) { Item[itemID].Amount += AmountToAdd; }
  void SubtractItem(int itemID, int AmountToTake) { Item[itemID].Amount -= AmountToTake; }
  void DisplayItem(int itemID) { std::cout << Item[itemID].Name; }
  void DisplayItemQuantity(int itemID,int Xpos,int Ypos, int FONT_SIZE)
  { 
	  char *ItemChar = Item[itemID].Name;
	  char *MultiplierChar = " X ";
	  dbText(Xpos,Ypos,ItemChar);
	  dbText((dbLen(ItemChar)*FONT_SIZE/1.5)+Xpos,Ypos,MultiplierChar);
	  dbText((dbLen(ItemChar)*FONT_SIZE/1.5)+(dbLen(MultiplierChar)*FONT_SIZE/1.5)+Xpos,Ypos,dbStr(Item[itemID].Amount));
  }
};