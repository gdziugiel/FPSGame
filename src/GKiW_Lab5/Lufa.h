class CLufa : public CSceneObject
{
public:
	CLufa(void);
	~CLufa(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
protected:
	GLuint _displayListId;
};