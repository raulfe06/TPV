#pragma once
#include "GameCharacter.h"

// CONSTANTES: 
const int ENERGY_TIME = 4000;

/*
Clase Pacman: Inicializa a Pacman y controla su dirección, movimiento, vidas, etc.

- Contiene variables propias de Pacman -> siguiente dirección, vidas, energía, etc.

- Define (y redefine) métodos propios de Pacman -> render propio de su movimiento, update, etc.

*/
class Pacman : public GameCharacter
{
private:
	// Siguiente dirección guardada (hasta hacerse posible su actualización)
	int nextDirX, nextDirY;

	// Vidas restantes
	int lives;

	// Energía de Pacman: estado y tiempo restante de energía
	bool energy = false;
	int energyTime = ENERGY_TIME;


	// MÉTODOS PRIVADOS

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


	// Métodos relacionados con la energía de Pacman 
	bool energyEnabled() const { return energy; };
	void timer();

	bool getEnergy() const { return energy; };
	void setEnergy(bool b) { energy = b; };
	int getEnergyTime() const { return energyTime; };
	void setEnergyTime(int t) { energyTime = t; };
	
	// Métodos relacionados con las vidas
	int getLives() const { return lives; };
	void subLives() { lives--; };
	void setLives(int l) { lives = l; };
	

	~Pacman();
};