#pragma once
struct Element
{
	int id;
	int p; //czas potrzebny na wykonanie zadania
	int w; //waga do wyliczenia kary zadania
	int d; // czas okre�laj�cy wymagany termin dostarczenia zadania
	int penalty; //kara za sp�nienie
	int p_done; // czas oddania - czas w kt�rym zadania zosta�o wykonane
};

