#include "Game.h"
#include<string>
#include<fstream>


using namespace std;


// A) CONSTRUCTORA DEL JUEGO: INICIALIZA SDL, CREA LAS TEXTURAS, OBJETOS, ETC.
Game::Game()
{
	// 1) INICIALIZACI�N DE SDL

	// a) Iniciamos
	SDL_Init(SDL_INIT_EVERYTHING);

	// b) Creamos la ventana y el renderer
	window = SDL_CreateWindow("PACMAN", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		error = true;
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //RGB y alpha

	// 2) CREACI�N DE TEXTURAS

	// a) Creamos cada textura de los objetos no est�ticos y las cargamos en 'textures[]'
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		textures[i] = new Texture();
		const textAtributes& atributes = TEXTURE_ATRIBUTES[i];
		if (!textures[i]->Load(renderer, TEXT_PATHFILE + atributes.filename, atributes.row, atributes.col))
			error = true;
	}
	/*// b) Creamos el mapa y los personajes del mismo
	CreateMap("map1.txt");*/
}


// B) DADO UN FICHERO DE TEXTO, CREA EL MAPA MEDIANTE LA LECTURA DEL MISMO
void Game::CreateMap(string filename)
{
	// a) Enlazamos el archivo mediante el flujo de entrada
	ifstream file;
	if (fexists(filename))
	{
		file.open(filename);

		int cell;

		// b) Seg�n la implementaci�n del archivo, leemos la primera fila para obtener las filas y columnas del mapa
		file >> fils >> cols;

		// c) Creamos el mapa (matriz de celdas) y hacemos que apunte a <Game>
		map = new GameMap(fils, cols, this);

		// d) Recorremos la "matriz" del archivo:
		for (int i = 0; i < fils; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// 1) Leemos cada n�mero... 
				file >> cell;
				// ...y le damos el tipo de celda seg�n el valor del mismo
				map->SetCell(i, j, (mapCell)cell);
				if (cell == 2 || cell == 3)
					numFood++;

				// 2) Al encontrar el valor para Pacman y los fantasmas, los creamos 
				if (cell == 5) {
					map->SetCell(i, j, Empty);
					ghost[0] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 6) {
					map->SetCell(i, j, Empty);
					ghost[1] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 7) {
					map->SetCell(i, j, Empty);
					ghost[2] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 8) {
					map->SetCell(i, j, Empty);
					ghost[3] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 9) {
					map->SetCell(i, j, Empty);
					pacman = Pacman(j, i, textures[charactersText], fils, cols, this);
				}
			}
		}
	}
	
	// e) Cerramos el flujo con el archivo
	file.close();
}


// C) CONTROLA EL JUEGO -> LLAMA A CADA 'Update()' Y 'Render()' DE LOS OBJETOS DEL JUEGO Y CONTROLA LOS EVENTOS
void Game::Run()
{
	while (!exit && !EndLevel(win))
	{
		int startTime = SDL_GetTicks();
		HandleEvents();
		Update();
		Render();
		delta = SDL_GetTicks() - startTime;

		if (delta < FRAME_RATE)
			SDL_Delay(FRAME_RATE - delta);
	}
}


// D) LLAMA A LOS 'Update()' DE CADA OBJETO DEL JUEGO
void Game::Update()
{
	int foodX, foodY;

	if (Energy)
		Timer();

	pacman.Update();
	CheckCapture();

	if (pacman.Eat(foodX, foodY))
	{
		map->SetCell(foodY, foodX, Empty);
		numFood--;
	}

	for (int i = 0; i < NUM_GHOSTS; i++)
		ghost[i]->Update();
	CheckCapture();
	
}


// E) LLAMA A LOS 'Render()' DE CADA OBJETO DEL JUEGO
void Game::Render()
{
	
	// 1) Borra el renderer actual 
	SDL_RenderClear(renderer);
	
	// 2) Llama a los 'Render()' de cada objeto
	map->Render(renderer, textures, fils, cols);
	RenderLives();
	RenderOptions();
	pacman.Render(renderer);
	for (int i = 0; i < NUM_GHOSTS; i++)
		ghost[i]->Render(renderer, 0, i * 2, Energy);
	
	// 3) Actualiza la patalla con todos los 'Render()' que se hayan llamado
	SDL_RenderPresent(renderer);
}


// F) CONTROLA TODOS LOS EVENTOS PRODUCIDOS
void Game::HandleEvents()
{
	SDL_Event event;

	// Mientras NO queden eventos por procesar en la cola...
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)

			exit = true;
		if (event.key.keysym.sym == SDLK_g) {
			SaveGame();
		}
		// ...entramos al bucle y metemos todos los eventos en la cola para procesarlos
		pacman.SetDir(event);
	}
}


// G) AUMENTA, SI ES POSIBLE, LA POSICI�N SEG�N LA DIRECCI�N TOMADA, Y TENIENDO EN CUENTA LOS EXTREMOS DEL MAPA 
bool Game::NextCell(int x, int y, int dx, int dy, int& nx, int& ny) const
{
	// 1) Avanzamos la posici�n seg�n la direcci�n entrante
	 nx = x + dx;
	 ny = y + dy;

	// 2) Observamos si cruzamos de un lado al otro del mapa:

	// a) Direcci�n X
	if (nx < 0)
		nx = cols - 1;
	else if (nx >= cols)
		nx = 0;

	// a) Direcci�n Y
	if (ny < 0)
		ny = fils - 1;
	else if (ny >= fils)
		ny = 0;

	// 3) Miramos si podemos o no avanzar (si hay o no hay muro en la nueva posici�n):
	if (map->GetCell(nx, ny) != Wall)
	{
		// a) Si NO hay, actualizamos la posici�n y devolvemos 'true'
		return true;
	}
	// b) Si lo hubiera, entonces devolvemos 'false'
	else
	{
		
		nx = x;
		ny = y;
		return false;
	}
}


// H) COMPRUEBA SI HAY ALG�N FANTASMA EN LA POSICI�N DADA
bool Game::ExistGhost(int posX, int posY) const
{
	int i = 0;
	bool ghostFound = false;

	// Recorremos todos los fantasmas y comprobamos su posici�n
	while (i < NUM_GHOSTS && !ghostFound)
	{
		if (ghost[i]->GetPosX() == posX && ghost[i]->GetPosY() == posY)
		{
			// Si coincide la posici�n con alguna de los fantasmas, devuelve 'true'
			ghostFound = true;
		}
		i++;
	}
	return ghostFound;
}


// I) COMPRUEBA SI HA HABIDO ALGUNA COLISI�N ENTRE PACMAN Y LOS FANTASMAS, Y LA PROCESA
void Game::CheckCapture()
{
	int i = 0;
	capture = false;
	// Comprobamos por cada fantasma si coincide la posici�n con la de Pacman:
	while (i < NUM_GHOSTS && !capture)
	{
		if (pacman.GetPosX() == ghost[i]->GetPosX() && pacman.GetPosY() == ghost[i]->GetPosY())
		{
			// 1) Si coincide, pero la energ�a estuviera ACTIVA... 
			if (Energy)
				ghost[i]->RestartPos(); // ...reiniciamos la posici�n del fantasma
			else
			{
				// En caso contrario, damos por v�lida la captura y restamos una vida
				capture = true;
				pacman.SubLifes();
				RestartCharacters();
			}
		}
		i++;
	}
}


// J) REINICIA LA POSICI�N DE TODOS LOS PERSONAJES
void Game::RestartCharacters()
{
	pacman.RestartPos();

	for (int i = 0; i < NUM_GHOSTS; i++)
	{
		ghost[i]->RestartPos();
	}
}


// K) ACTIVA/DESACTIVA LA ENERG�A DE PACMAN SEG�N EL PAR�METRO 'power', Y REINICIA SU DURACI�N
void Game::PacmanEnegy(bool power)
{
	EnergyTime = 4000;
	Energy = power;
}


// L) CONTADOR PARA EL TIEMPO DE USO DE LA ENERG�A DE PACMAN
void Game::Timer()
{
	/* 

	Restamos a "EnergyTime" el tiempo de cada tick (Es decir, FRAME_RATE):

	Como el bucle del juego est� controlado por el delta, a mayor FRAME_RATE, MENOS ticks de MAYOR duraci�n se har�n,
	y a menor FRAME_RATE, M�S ticks de MENOR duraci�n se har�n.
	
	Por tanto, la duraci�n acaba siendo siempre equivalente independientemente de una mayor o menor resta,
	puesto que los ticks, a su vez, aumentan o disminuyen proporcionalmente.

	*/
	if (EnergyTime > 0)
	{
		EnergyTime -= FRAME_RATE;
	}
	else
	{
		PacmanEnegy(false);
	}
}


// M) DEVUELVE EL TIPO DE CELDA DE LA POSICI�N DADA
mapCell Game::GetCell(int posX, int posY) const
{
	return map->GetCell(posX, posY);
}


// N) RENDER DEL HUD: VIDAS  
void Game::RenderLives() const {
	SDL_Rect destRect,numDest;
	destRect.w = 144;
	destRect.h = 50;
	destRect.x = 0; destRect.y = WIN_HEIGHT - destRect.h - 25;
	numDest.w = 40;
	numDest.h = 50;
	numDest.x = 150;
	numDest.y = destRect.y;
	textures[numLives]->RenderFrame(renderer, 0, abs(pacman.GetLifes()-3), numDest);
	textures[Lives]->Render(renderer, destRect);
}

// O) RENDER DEL HUD: OPCIONES EN LA PARTIDA (GUARDAR LA PARTIDA)
void Game::RenderOptions() const {
	SDL_Rect destRect;
	destRect.x = 250; destRect.y = WIN_HEIGHT - 65;
	destRect.w = 256; destRect.h = 50;
	textures[saveOption]->Render(renderer, destRect);
}


// P) CONTROL DEL FINAL DE LA PARTIDA
bool Game::EndLevel(bool& win) {
	bool end = false;
	if (pacman.GetLifes() == 0) {
		end = true;
	}
	else if (numFood == 0) {
		win = true;
		end = true;
	}
	return end;
}


// Q) GUARDA EL ESTADO DE LA PARTIDA EN UN ARCHIVO DE TEXTO 
void Game::SaveGame() const
{

	ofstream level("gameData.txt");
	// 1) Escribimos las filas y columnas del nivel
	level << fils << " " << cols << endl;

	// 2) Escribimos el mapa codificado con el estado actual
	for (int i = 0; i < fils; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j == pacman.GetPosX() && i == pacman.GetPosY())
			{
				level << "9 ";
			}
			else if (j == ghost[0]->GetPosX() && i == ghost[0]->GetPosY())
			{
				level << "5 ";

			}
			else if (j == ghost[1]->GetPosX() && i == ghost[1]->GetPosY())
			{
				level << "6 ";
			}
			else if (j == ghost[2]->GetPosX() && i == ghost[2]->GetPosY())
			{
				level << "7 ";
			}
			else if (j == ghost[3]->GetPosX() && i == ghost[3]->GetPosY())
			{
				level << "8 ";
			}
			else
				level << (int)map->GetCell(j, i) << " ";
		}
		level << endl;
	}
	for (int k = 0; k < 4; k++) {
		level << ghost[k]->GetDefX() << " " << ghost[k]->GetDefY() << endl;
	}
	level << pacman.GetLifes() << endl;
	level << pacman.GetDefX() << " " << pacman.GetDefY();
	level.close();
}


// R) RENDER DE LA IMAGEN DEL MEN� PRINCIPAL
void Game::LoadMenu() const
{
	SDL_Rect destRect;
	destRect.x = destRect.y = 0;
	destRect.w = WIN_WIDTH;
	destRect.h = WIN_HEIGHT;
	textures[mainMenu]->Render(renderer, destRect);
	SDL_RenderPresent(renderer);
}


// S) CONTROL DE LAS OPCIONES DEL MEN�
bool Game::ControlMenu() 
{
	SDL_Event event;
	bool menu = true;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_1)
			{
				CreateMap("map1.txt");
				menu = false;
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				loadLevel("gameData.txt");
				menu = false;
			}
			else if (event.key.keysym.sym == SDLK_3)
			{
				exit = true;
				menu = false;
			}
		}
	}
	return menu;
}


bool Game::fexists(const string& filename) const
{
	std::ifstream ifile(filename.c_str());
	return (bool)ifile;
}

// DESTRUCTORA DEL JUEGO
Game::~Game()
{
	delete map;
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i]->Free();
		delete textures[i];
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::loadLevel(string filename) {
	ifstream file;
	if (fexists(filename))
	{
		file.open(filename);
		int cell;
		int aux;
		int auxLifes;
		// b) Seg�n la implementaci�n del archivo, leemos la primera fila para obtener las filas y columnas del mapa
		file >> fils >> cols;

		// c) Creamos el mapa (matriz de celdas) y hacemos que apunte a <Game>
		map = new GameMap(fils, cols, this);

		// d) Recorremos la "matriz" del archivo:
		for (int i = 0; i < fils; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// 1) Leemos cada n�mero... 
				file >> cell;
				// ...y le damos el tipo de celda seg�n el valor del mismo
				map->SetCell(i, j, (mapCell)cell);
				if (cell == 2 || cell == 3)
					numFood++;

				// 2) Al encontrar el valor para Pacman y los fantasmas, los creamos 
				if (cell == 5) {
					map->SetCell(i, j, Empty);
					ghost[0] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 6) {
					map->SetCell(i, j, Empty);
					ghost[1] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 7) {
					map->SetCell(i, j, Empty);
					ghost[2] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 8) {
					map->SetCell(i, j, Empty);
					ghost[3] = new Ghost(j, i, fils, cols, this, textures[charactersText]);
				}
				if (cell == 9) {
					map->SetCell(i, j, Empty);
					pacman = Pacman(j, i, textures[charactersText], fils, cols, this);
				}
			}
		}
		for (int k = 0; k < 4; k++) {
			file >> aux;
			ghost[k]->SetDefX(aux);
			file >> aux;
			ghost[k]->SetDefY(aux);
		}
		file >> auxLifes;
		pacman.setLifes(auxLifes);

		file >> aux;
		pacman.SetDefX(aux);
		file >> aux;
		pacman.SetDefY(aux);
	
	}

	// e) Cerramos el flujo con el archivo
	file.close();

}

