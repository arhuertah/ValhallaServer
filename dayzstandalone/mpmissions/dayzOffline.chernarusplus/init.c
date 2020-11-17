#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\KrasnostavOverhaul.c"

void SpawnObject(string objectName, vector position, vector orientation)
{
	Object obj;
	obj = Object.Cast(GetGame().CreateObject(objectName, "0 0 0"));
	obj.SetPosition(position);
	obj.SetOrientation(orientation);

	// Force update collisions
	if (obj.CanAffectPathgraph())
	{
		obj.SetAffectPathgraph(true, false);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
	}
}

void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false); // false = use weather controller from Weather.c

	weather.GetOvercast().Set(Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set(0, 0, 1);
	weather.GetFog().Set(Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if (ce)
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}

	KrasnostavOverhaul();
}

class CustomMission : MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat(0.25, 0.65);
			itemEnt.SetHealth01("", "", rndHlt);
		}
	}

	void SetHealth(EntityAI itemEnt, int health)
	{
		itemEnt.SetHealth("", "", health);
	}

	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++)
		{
			mag = player.GetInventory().CreateInInventory(mag_type);
			player.SetQuickBarEntityShortcut(mag, i + 1, true);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{

		/*MATRIZES PARA LA SELECCION DE OBJETOS ALEATORIOS EN EL JUGADOR*/
		TStringArray playera = {"Shirt_BlueCheck", "TShirt_White"};
		TStringArray pantalones = {"Jeans_Black", "Jeans_BlueDark", "Jeans_Blue", "Jeans_Brown", "Jeans_Green", "Jeans_Grey"};

		TStringArray zapatos = {"AthleticShoes_Black", "AthleticShoes_Blue", "AthleticShoes_Brown", "AthleticShoes_Green",
								"AthleticShoes_Grey", "HikingBootsLow_Beige", "HikingBootsLow_Black", "HikingBootsLow_Blue", "HikingBootsLow_Grey",
								"HikingBoots_Black", "HikingBoots_Brown", "HikingJacket_Black"};

		TStringArray herramienta = {"StoneKnife"};
		TStringArray suministromedic = {"BandageDressing"};
		TStringArray bebidas = {"SodaCan_Cola", "SodaCan_Kvass", "SodaCan_Pipsi", "SodaCan_Spite"};
		TStringArray comida = {"Marmalade"};
		TStringArray armas = {"FNX45"};
		TStringArray ammon = {"Mag_FNX45_15Rnd"};
		TStringArray backpack = {"HuntingBag"};
		TStringArray battery = {"Battery9V"};
		TStringArray lampara = {"Flashlight"};

		player.RemoveAllItems();

		EntityAI itemEnt;
		EntityAI itemIn;
		ItemBase itemBs;

		EntityAI item = player.GetInventory().CreateInInventory(playera.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetHealth(itemEnt, 20);

		EntityAI item2 = player.GetInventory().CreateInInventory(pantalones.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetHealth(itemEnt, 20);

		EntityAI item3 = player.GetInventory().CreateInInventory(zapatos.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetHealth(itemEnt, 20);

		EntityAI item4 = player.GetInventory().CreateInInventory(armas.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetHealth(itemEnt, 20);

		itemEnt = player.GetInventory().CreateInInventory(herramienta.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(ammon.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(suministromedic.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(bebidas.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(comida.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(backpack.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(battery.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		itemEnt = player.GetInventory().CreateInInventory(lampara.GetRandomElement());
		itemBs = ItemBase.Cast(itemEnt);
		SetRandomHealth(itemEnt);

		addMags(player, "Mag_FNX45_15Rnd", 1);
	}
};


Mission CreateCustomMission(string path)
{
	return new CustomMission();
}