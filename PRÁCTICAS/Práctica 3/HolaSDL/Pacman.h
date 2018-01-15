#pragma once
#include "GameCharacter.h"

// CONSTANTES: 
const int ENERGY_TIME = 4000;

/*
Clase Pacman: Inicializa a Pacman y controla su direcci�n, movimiento, vidas, etc.

- Contiene variables propias de Pacman -> siguiente direcci�n, vidas, energ�a, etc.

- Define (y redefine) m�todos propios de Pacman -> render propio de su movimiento, update, etc.

*/
class Pacman : public GameCharacter
{
private:
	// Siguiente direcci�n guardada (hasta hacerse posible su actualizaci�n)
	int nextDirX, nextDirY;

	// Vidas restantes
	int lives;

	// Energ�a de Pacman: estado y tiempo restante de energ�a
	bool energy = false;
	int energyTime = ENERGY_TIME;


	// M�TODOS PRIVADOS

	void pacmanEnergy(bool power);
	void setAnimation();
public:
	Pacman(PlayState* game, SDL_Renderer* renderer, int textRow, int textCol);
	Pacman();

	// Lectura y escritura
	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file);


    void render(SDL_Renderer* renderer);
	void update();
	bool handleEvent(SDL_Event& e);

	void setDir(SDL_Event event);

	bool eat(int& foodX, int& foodY);


	// M�todos relacionados con la energ�a de Pacman 
	bool energyEnabled() const { return energy; };
	void timer();

	bool getEnergy() const { return energy; };
	void setEnergy(bool b) { energy = b; };
	int getEnergyTime() const { return energyTime; };
	void setEnergyTime(int t) { energyTime = t; };
	
	// M�todos relacionados con las vidas
	int getLives() const { return lives; };
	void subLives() { lives--; };
	void setLives(int l) { lives = l; };
	

	~Pacman();
};