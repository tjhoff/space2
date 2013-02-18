#include <stdlib.h>
class GLWindow{
	public:
		static GLWindow * getInstance();
		float m_width_ratio;
		float m_width;
		float m_height;
	private:
		static GLWindow * instance;
};
