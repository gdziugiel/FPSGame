struct vec3 {
	float x, y, z;
	vec3()
	{
		x = y = z = 0.0f;
	}
	vec3(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}
	vec3 operator+(const vec3 v)
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 operator*(const float f)
	{
		return vec3(x * f, y * f, z * f);
	}
	vec3 operator-()
	{
		return vec3(-x, -y, -z);
	}
};