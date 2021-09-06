class CCube : public CSceneObject
{
public:
	CCube(void);
	~CCube(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
protected:
	GLuint _displayListId;
	float velM;
	float velS;
	float speed;
	float rot;
	float pos;
	bool strona;
	bool x;
	static bool _isLoaded;
	static CTexture * _roboTexture;
};