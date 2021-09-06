class CSphere : public CSceneObject
{
public:
	CSphere(void);
	~CSphere(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	float radiusChangePerUpdate;
protected:
	GLuint _displayListId;
	int weight;
	float radius;
};