class CSceneObject
{
public:
	vec3 Position;
	vec3 Rotation;
	vec3 force;
	float weight;
	float radius;
	bool isAlive;
	CSceneObject(void);
	~CSceneObject(void);
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
};