#pragma once
#include <SDL.h>
#include"Pacman.h"
#include "Ghost.h"
#include"GameMap.h"
#include "checkML.h"


using namespace std;

// *CONSTANTES GENERALES*

//const int FRAME_RATE = 50;
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int FRAME_RATE = 160; // milliseconds per frame -> 6 frames/s
const int NUM_TEXTURES = 8;
const int NUM_GHOSTS = 4;
const string TEXT_PATHFILE = "..\\images\\";

// *A�adimos las clases para evitar errores de compilaci�n*
class GameMap;
class Pacman;
class Ghost;

/*
Clase Game: controla el juego a alto nivel

1) Inicializa SDL y crea la ventana y el renderer.
2) Crea todas las texturas que se van a utilizar en el juego.
3) Crea el mapa y los personajes.
4) Controla el juego -> Updates, Render, eventos, etc., de cada objeto del juego.

*/
class Game
{
private:
	// Struct con los atributos necesarios por cada textura:
	typedef struct {
		// 1) Nombre del archivo de la imagen
		string filename; 
		// 2) Fila y columna de la textura (por si estuviera dividida como un sprite sheet)
		int row = 0;
		int col = 0;
	} textAtributes;

	// Enum con los nombres ordenados de las texturas del juego
	enum textureName { wallText, FoodText, VitaminText, charactersText, Lives, numLives, mainMenu, saveOption };
	
	// Array de los atributos de cada textura del juego
	const textAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES] = { {"wall.png", 1, 1}, { "food.png", 1, 1 }, {"vitamin.png", 1, 1},
	{ "characters1.png", 4, 14 } ,{ "LIVES.png",1,1 }, {"numLives.png",1,4},{"menu.jpg",1,1},{"saveOption.png",1,1} };

	// Ventana y renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Posici�n de la ventana
	int winX = SDL_WINDOWPOS_CENTERED;
	int winY = winX;

	// Delta time del juego
	int delta;

	// Array de punteros a cada textura de los objetos del juego
	Texture* textures[NUM_TEXTURES];

	// Puntero al mapa del juego (matriz de celdas) y las filas y columnas de la misma
	GameMap* map = nullptr;
	int fils, cols;

	// Objeto Pacman
	Pacman pacman;

	// Array de fantasmas
	Ghost* ghost[NUM_GHOSTS];

	// Comida total restante
	int numFood;

	// Energ�a de Pacman y su duraci�n en milisegundos
	bool Energy = false;
	int EnergyTime = 4000;


	// Variables de control
	bool error = false;
	bool exit = false;

	bool menu = true;
	bool win = false;
	bool capture = false;

	// M�TODOS PRIVADOS:  

	// Control del juego -> Updates, Render, eventos, etc., de cada objeto del juego
	void Update();
	void Render();
	void HandleEvents();

	// Creaci�n del mapa
	void CreateMap(string filename);

public:
	// Constructora y destructora del juego por defecto
	Game();
	~Game();

	// Bucle principal del juego
	void Run();


	// Indica si la siguiente posici�n, dada una direcci�n determinada, es accesible
	bool NextCell(int x, int y, int dx, int dy, int& nx, int& ny) const;

	// Indica si hay alg�n fantasma en la posici�n dada
	bool ExistGhost(int posX, int posY) const;

	// Comprueba si ha habido alguna colisi�n entre Pacman y los fantasmas, y la procesa como sea debido
	void CheckCapture();

	// Reinicia las posiciones de todos los personajes  
	void RestartCharacters();
	
	// Activa/desactiva la energ�a de Pacman, y reinicia su duraci�n
	void PacmanEnegy(bool energy);

	// Contador para la duraci�n de la energ�a de Pacman cuando �ste toma una vitamina
	void Timer();

	// M�todos de control
	bool GetError() const { return error; };
	void GiveError() { error = true; }

	// Obtiene el tipo de celda de una posici�n dada
	mapCell GetCell(int posX, int posY) const;

	// Render del HUD
	void RenderLives() const;
	void RenderOptions() const;

	// Control del fin del juego
	bool EndLevel(bool& win);

	// M�todo para guardar el estado de la partida en un fichero de texto
	void SaveGame() const;

	// Carga el men� principal y procesa la selecci�n del jugador 
	void LoadMenu() const;
	bool ControlMenu();

	bool fexists(const string& filename) const;
		
	void loadLevel(string filename);
	
};