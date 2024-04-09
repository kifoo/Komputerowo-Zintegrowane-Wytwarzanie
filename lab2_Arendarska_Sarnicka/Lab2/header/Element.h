#pragma once
struct Element
{
	int id;
	int p; //czas potrzebny na wykonanie zadania
	int w; //waga do wyliczenia kary zadania
	int d; // czas okreœlaj¹cy wymagany termin dostarczenia zadania
	int penalty; //kara za spóŸnienie
	int p_done; // czas oddania - czas w którym zadania zosta³o wykonane
};

