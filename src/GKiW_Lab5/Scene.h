class CScene
{
public:
	CSkydome * Skydome;
	CTerrain * Terrain;
	CLufa * Lufa;
	CPlayer player;
	vector<CSceneObject *> * Objects;
	vector<CSceneObject *> * Spheres;
	vector<CSceneObject *> * Cubes;
	CScene(void);
	~CScene(void);
	int random(int, int);
	void Initialize(void);
	void Update(void);
	void Render(void);
	double T;
	void Menu();
	void Info();
	bool spawn;
	bool wygrana;
	bool przegrana;
	bool start;
	bool info;
	int licznik;
	int N;
	int globallicznik;
	int tlicz;
protected:
	CTexture * _button1Texture;
	CTexture * _button2Texture;
	CTexture * _button3Texture;
	CTexture * _button4Texture;
	CTexture * _info1Texture;
	CTexture * _info2Texture;
};