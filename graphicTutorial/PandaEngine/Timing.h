#ifndef TIMINIG_H
#define TIMINIG_H

namespace PandaEngine {

	class FpsLimiter
	{
	public:

		FpsLimiter();
		
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		// end will return the current FPS
		float end();
	private:

		void calculateFPS();
		
		float _maxFps;
		
		unsigned int _startTicks;

		float _fps, _frameTime;
	};

	
}

#endif // !TIMINIG_H

