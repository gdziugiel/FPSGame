class CWall : public CSceneObject
{
public:
	CWall(vec3 a, vec3 b, vec3 c, vec3 d);
	~CWall(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	vec3 v[4];
	vec3 n;

protected:
	GLuint _displayListId;
	static bool _isLoaded;
	static CTexture * _wallTexture;
};